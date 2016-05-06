# GQRX controller

## What's it?
GQRX controller allows you to control GQRX with a physical interface. Actually you can control the frequency you are listening at and the type of demodulation.

## Video
Watch the [video](https://processing.org).

## Technical informations
Actually, the Arduino uses the serial port to communicate with the computer. This data is collected by a [processing](https://processing.org) programme which pipe the data in TCP/IP to GQRX.

## Improvements
Here some improvement to do :

* Replace potentiometer with a encoder to control the frequency.
*  Add a potentiometer to control the squelch threshold
*  Add a network interface to avoid the using of [processing](https://processing.org)
