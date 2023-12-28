#include "Main.h"

Logger logger = Logger();
Settings settings = Settings();

WiFiManager wifi = WiFiManager(&logger, &settings.getSettings()->network);
DataCollector dataCollector = DataCollector();
WebServer webServer = WebServer(&logger, &settings.getSettings()->network);
TempSetter ufhTemp = TempSetter(&settings.getSettings()->temp1Settings, D1, 1, "UFH temperature");
Relay ufhRelay = Relay(D3, 0);
DS18B20 bufferTempSensors = DS18B20(D7);


void setup()
{ 
    Serial.begin(74880);
    settings.begin();
    ufhTemp.begin();
    ufhRelay.begin();
    bufferTempSensors.begin();
    wifi.begin();
    webServer.begin();
    dataCollector.begin();

    wifi.connect();
}

void loop() {
    wifi.loop();
    webServer.loop();
    settings.loop();
    ufhTemp.loop();
    ufhRelay.loop();
    bufferTempSensors.loop();
    dataCollector.loop();

    delay(100);
}
