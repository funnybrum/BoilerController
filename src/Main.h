#pragma once

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>

#include <Servo.h>

#include "user_interface.h"

#include "Relay.h"
#include "TempSetter.h"
#include "DS18B20.h"
#include "DataCollector.h"

#include "esp8266-base.h"


#define HTTP_PORT 80
#define HOSTNAME "boiler"

extern Logger logger;
extern Settings settings;
extern WiFiManager wifi;
extern TempSetter ufhTemp;
extern Relay ufhRelay;
extern DS18B20 ufhTempSensor;
extern DataCollector dataCollector;