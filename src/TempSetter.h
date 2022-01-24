#pragma once

#include <Servo.h>
#include "WiFi.h"

const char TEMP_CONFIG_PAGE[] PROGMEM = R"=====(
<fieldset style='display: inline-block; width: 300px'>
<legend>%s</legend>
Low temperature:<br>
<input type="text" name="t%d_low_temp" value="%d"><br>
Low temperature pulse (ms, i.e. 350):<br>
<input type="text" name="t%d_low_temp_ms" value="%d"><br>
High temperature:<br>
<input type="text" name="t%d_low_temp" value="%d"><br>
High temperature pulse (ms, i.e. 2600):<br>
<input type="text" name="t%d_low_temp_ms" value="%d"><br>
</fieldset>
)=====";


struct TempSettings {
    uint8_t lowTemp;
    uint16_t lowTempMs;
    uint8_t highTemp;
    uint16_t highTempMs;
};

class TempSetter {
    public:
        TempSetter(TempSettings* settings, uint8_t pin, uint8_t index, String alias);
        void begin();
        void loop();
        void get_config_page(char* buffer);
        void parse_config_params(WebServerBase* webServer);

        void setDuty(uint16_t);
        void setTemp(uint8_t);
        uint8_t getTemp();
    private:
        uint16_t tempToMs(uint8_t temp);

        uint8_t _index;
        String _alias;

        uint8_t _pin;
        TempSettings* _settings;
        Servo* _servo;

        uint8_t _currentTemp;
        uint8_t _targetTemp;
        uint16_t _countdown = 0;
};
