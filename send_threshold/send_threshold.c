/*
 * Copyright (c) 2015-2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== empty.c ========
 */
/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Task.h>

#include <math.h>

/* TI-RTOS Header files */
#include <ti/drivers/I2C.h>
#include <ti/drivers/PIN.h>
#include <ti/drivers/SPI.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/Watchdog.h>
#define CMD_CONFIG 0x00
#define CMD_ID 0x39
#define CMD_IDLE 0x58

/* Board Header files */
#include "Board.h"
#define TASKSTACKSIZE   1024
#define Board_initI2C() I2C_init()

/* Pin driver handles */
static PIN_Handle buttonPinHandle;
static PIN_Handle ledPinHandle;

/* Global memory storage for a PIN_Config table */
static PIN_State buttonPinState;
static PIN_State ledPinState;

static UART_Handle uart;
static UART_Params uartParams;

uint16_t temp_f;

PIN_Config ledPinTable[] = {
                            Board_LED0 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW | PIN_PUSHPULL | PIN_DRVSTR_MAX,
                            Board_LED1 | PIN_GPIO_OUTPUT_EN | PIN_GPIO_LOW  | PIN_PUSHPULL | PIN_DRVSTR_MAX,
                            PIN_TERMINATE
};

/*
 * Application button pin configuration table:
 *   - Buttons interrupts are configured to trigger on falling edge.
 */
PIN_Config buttonPinTable[] = {
                               Board_BUTTON0  | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_NEGEDGE,
                               Board_BUTTON1  | PIN_INPUT_EN | PIN_PULLUP | PIN_IRQ_NEGEDGE,
                               PIN_TERMINATE
};

Task_Struct task0Struct;
Char task0Stack[TASKSTACKSIZE];

Task_Params taskParams;


// measure and send temperature
Void temperature_fxn(UArg arg0, UArg arg1)
{
    CPUdelay(800*50);

    uint8_t txBuffer_i2c[1];
    uint8_t rxBuffer_i2c[2];

    uint16_t temp_c;

    I2C_Handle i2c;
    I2C_Params i2cParams;
    I2C_Transaction i2cTransaction;

    /* Create I2C for usage */
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_400kHz;
    i2c = I2C_open(Board_I2C, &i2cParams);
    if (i2c == NULL) {
        System_abort("Error Initializing I2C\n");
    }
    else {
        System_printf("I2C Initialized!\n");
    }

    txBuffer_i2c[0] = 0xE3;

    i2cTransaction.slaveAddress = 0x40;
    i2cTransaction.writeBuf = txBuffer_i2c;
    i2cTransaction.writeCount = 1;
    i2cTransaction.readBuf = rxBuffer_i2c;
    i2cTransaction.readCount = 2;

    // create UART parameters
    char input;
    unsigned int i=0;
    const char echoPrompt[] = "0x00";

    uint8_t tx_Buffer_uart[1];
    uint8_t rx_Buffer_uart[2];

    uint8_t tx_buffer_config_uart[1];
    uint8_t rx_buffer_config_uart[1];
    uint16_t tx_buffer_data_uart[2];
    uint8_t rx_buffer_id_uart[13];

    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_NEWLINE;
    uartParams.readEcho = UART_ECHO_OFF;
    uartParams.baudRate = 19200;// baud rate of the interface
    uartParams.dataLength = UART_LEN_8;
    uartParams.stopBits = UART_STOP_ONE;
    uartParams.readMode = UART_MODE_CALLBACK;
    uartParams.writeMode = UART_MODE_BLOCKING;

    uart = UART_open(Board_UART0, &uartParams);

    if (uart == NULL) {
        System_abort("Error opening the UART");
    }
    tx_buffer_config_uart[0]=CMD_CONFIG;

    UART_write(uart, &tx_buffer_config_uart, 1);
    UART_read(uart, &rx_buffer_config_uart, 1);

    System_printf("sending the request for config mode\n");
    System_printf("received ACK %d\n",rx_buffer_config_uart[0]);
    System_flush();

    tx_buffer_config_uart[0]=CMD_IDLE;
    UART_write(uart, &tx_buffer_config_uart, 1);

    System_printf("sending the IDLE mode Req\n");
    System_flush();
    /* after this sequence the system is ready to send data */
    /*set the data to be sent in the following format and send the buffer*/

    // Get temperature data
    if (I2C_transfer(i2c, &i2cTransaction)) {

        // perform 20 measurements
        for (i=0; i<20; i++) {

            // Get temperature in Celsius degrees
            temp_c = (uint16_t) (((uint16_t)rxBuffer_i2c[0] << 8) | (rxBuffer_i2c[1]));
            temp_c = 175.72 * temp_c / 65536 - 46.85;

            // Convert temperature to Fahrenheit degrees
            temp_f = (uint16_t) (9.0 / 5.0 * temp_c + 32.0);

            System_printf("Temperature: %d (C) or %d (F)\n", temp_c, temp_f);
            System_flush();

            // Send temperature data if above threshold
            if (temp_f > 90) {

                tx_buffer_data_uart[0]=0x02;
                tx_buffer_data_uart[1]=temp_f;

                UART_write(uart, &tx_buffer_data_uart, 3);
                System_printf("sending Data \n");
                System_flush();

                uint32_t currVal = 0;
                currVal = PIN_getOutputValue(Board_LED1);
                PIN_setOutputValue(ledPinHandle, Board_LED1, !currVal);
            }

            // sleep
            Task_sleep(900000);
        }
    }
    else {
        System_printf("I2C Bus fault\n");

    }

    /* Close UART */
    UART_close(uart);

    /* Deinitialized I2C */
    I2C_close(i2c);
    System_printf("I2C closed!\n");
    System_flush();
}

/*
 *  ======== main ========
 */
int main(void)
{
    //    Task_Params taskParams;

    /* Call board init functions */
    Board_initGeneral();

    Board_initUART();
    Board_initWatchdog();

    /* Construct heartBeat Task  thread */
    Task_Params_init(&taskParams);
    taskParams.arg0 = 1000000 / Clock_tickPeriod;
    taskParams.stackSize = TASKSTACKSIZE;
    taskParams.stack = &task0Stack;

    // launch temperature task
    Task_construct(&task0Struct, (Task_FuncPtr)temperature_fxn, &taskParams, NULL);

    /* Open LED pins */
    ledPinHandle = PIN_open(&ledPinState, ledPinTable);
    if(!ledPinHandle) {
        System_abort("Error initializing board LED pins\n");
    }
    PIN_setOutputValue(ledPinHandle, Board_LED1, 1);

    buttonPinHandle = PIN_open(&buttonPinState, buttonPinTable);
    if(!buttonPinHandle) {
        System_abort("Error initializing button pins\n");
    }


    System_printf("Starting the example\nSystem provider is set to SysMin. "
            "Halt the target to view any SysMin contents in ROV.\n");
    /* SysMin will only print to the console when you call flush or exit */
    System_flush();

    /* Start BIOS */
    BIOS_start();

    return (0);
}
