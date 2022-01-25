#include "Main.h"

DS18B20::DS18B20(uint8_t pin, uint32_t samplingIntervalMs) {
    _sensors = new DallasTemperature(new OneWire(pin));
}

void DS18B20::begin() {
    _sensors->begin();
    _lastReadMs = millis() - _samplingIntervalMs;
}

void DS18B20::loop() {
    if (millis() - _lastReadMs > _samplingIntervalMs) {
        float temp = getTemp();
        if (_tempMin > temp) {
            _tempMin = temp;
        }

        if (temp > _tempMax) {
            _tempMax = temp;
        }
    }
}

void DS18B20::reset() {
    _tempMax = -100;
    _tempMin = 100;
}

float DS18B20::getTemp() {
    _sensors->requestTemperaturesByIndex(0);
    return _sensors->getTempCByIndex(0);
}

float DS18B20::getTempMin() {
    return _tempMin;
}

float DS18B20::getTempMax() {
    return _tempMax;
}
