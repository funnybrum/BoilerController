# Gas Boiler Controller

Controller designed for an Immergas Victric Maior 28 tt gas heater. Provides mechanism for setting and monitoring the heating fluid temperature, and for enabling/disabling the heating.

The hardware is an ESP8266 with attached:
1) A servo that rotates the knob for setting the temperature
2) A relay that simulates the X40 thermostat (connection points 40 & 41)
3) DS18B20 sensor that monitors the heating fluid temperature


OTA updates is supported through POST requests to the /update API.

## Building the project

The project uses a common set of tools that are availabe in another repo - https://github.com/funnybrum/esp8266-base. Clone the esp8266-base repo in the lib folder:

```
cd lib
git clone git@github.com:funnybrum/esp8266-base.git
```
