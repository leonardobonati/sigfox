# sigfox
Send data to the Sigfox cloud through Radiocrafts modem.

Data are handled by the Texas Instruments CC2650 LaunchPad microcontroller.
They are then sent by the microcontroller to the Radiocrafts RC-1692-HP-SIG Sigfox modem through a UART connection.
Finally, data are transmitted by the modem to the Sigfox cloud through the Sigfox network using a Hop-by-Hop Reliability (HHR) protocol.
