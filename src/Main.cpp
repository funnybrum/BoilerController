#include "Main.h"

Logger logger = Logger();
Settings settings = Settings();

WiFiManager wifi = WiFiManager(&logger, &settings.getSettings()->network);
WebServer webServer = WebServer(&logger, &settings.getSettings()->network);
TempSetter ufhTemp = TempSetter(&settings.getSettings()->temp1Settings, D1, 1, "UFH temperature");
Relay ufhRelay = Relay(D3, 30);


void setup()
{ 
    Serial.begin(74880);
    settings.begin();
    ufhTemp.begin();
    ufhRelay.begin();
    wifi.begin();
    webServer.begin();

    wifi.connect();
}

void loop() {
    wifi.loop();
    webServer.loop();
    settings.loop();
    ufhTemp.loop();
    ufhRelay.loop();

    if (wifi.isInAPMode() && millis() > 300000L) {
        ESP.reset();
    }

    delay(100);
}
