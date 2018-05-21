# Send when above threshold
Send measured temperature data to the Sigfox cloud when the temperature is above the specified threshold.

Temperature data are measured by the Texas Instruments CC2650 LaunchPad microcontroller connected through the I2C interface to the Si7021-A20 humidity and temperature sensor.
Data are then sent by the microcontroller to the Radiocrafts RC-1692-HP-SIG Sigfox modem through a UART connection.
Measured data are, then, sent by the modem to the Sigfox cloud through the Sigfox network using a Hop-by-Hop Reliability (HHR) protocol.
