#include <TempSetter.h>
#include <Main.h>

TempSetter::TempSetter(TempSettings* settings, uint8_t pin, uint8_t index, String alias) {
    _settings = settings;
    _pin = pin;
    _index = index;
    _alias = alias;
}

void TempSetter::begin() {
    _servo = new Servo();
    _targetTemp = _currentTemp = 0;
}

void TempSetter::loop() {
    bool change = false;
    if (_targetTemp != _currentTemp) {
        change = true;
        _currentTemp = _targetTemp;
        _servo->attach(_pin, 350, 2600, tempToMs(_targetTemp));

        // Keep the servo ON (attached) until the correct position is reached. 
        // 20 * 100ms (main loop delay) = 2 seconds until servo gets detached.
        _countdown = 20;
    }

    if (_countdown > 0) {
        _countdown--;
    } else {
        _servo->detach();
    }
}

uint16_t TempSetter::tempToMs(uint8_t temp) {
    return map(
        temp,
        _settings->lowTemp,
        _settings->highTemp,
        600,
        2200);
}

void TempSetter::setDuty(uint16_t duty) {
    if (duty < _settings->lowTempMs || _settings->highTempMs < duty) {
        logger.log("Cycle of %d ms outside configured range", duty);
        return;
    }

    _servo->writeMicroseconds(duty);
}

uint8_t TempSetter::getTemp() {
    return _currentTemp;
}

void TempSetter::setTemp(uint8_t temp) {
    if (temp < _settings->lowTemp || _settings->highTemp < temp) {
        logger.log("Temperature %d outside configured range", temp);
        return;
    }

    _targetTemp = temp;
}

void TempSetter::get_config_page(char* buffer) {
    sprintf_P(
        buffer,
        TEMP_CONFIG_PAGE,
        _alias.c_str(),
        _index,
        _settings->lowTemp,
        _index,
        _settings->lowTempMs,
        _index,
        _settings->highTemp,
        _index,
        _settings->highTempMs);
}

void TempSetter::parse_config_params(WebServerBase* webServer) {
    if (_index == 1) {
        webServer->process_setting("f1_low_temp", _settings->lowTemp);    
        webServer->process_setting("f1_low_temp_ms", _settings->lowTempMs);    
        webServer->process_setting("f1_high_temp", _settings->highTemp);    
        webServer->process_setting("f1_high_temp_ms", _settings->highTempMs);
    } else if (_index == 2) {
        webServer->process_setting("f2_low_temp", _settings->lowTemp);    
        webServer->process_setting("f2_low_temp_ms", _settings->lowTempMs);    
        webServer->process_setting("f2_high_temp", _settings->highTemp);    
        webServer->process_setting("f2_high_temp_ms", _settings->highTempMs);
    }
}
