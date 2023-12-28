#include "Main.h"

struct TempSensor {
    uint8_t address[8];
    float correction;
};

TempSensor buffer_supply_sensor = {{0x28, 0xF5, 0x60, 0x96, 0xF0, 0x01, 0x3C, 0x2A}, -0.3f};
TempSensor buffer_return_sensor = {{0x28, 0xFF, 0x64, 0x1E, 0x93, 0x87, 0x1D, 0x86}, +0.0f};
TempSensor ufh_supply_sensor    = {{0x28, 0xFF, 0x64, 0x1E, 0x93, 0x93, 0xDA, 0x18}, +0.1f};
TempSensor ufh_return_sensor    = {{0x28, 0xFF, 0x64, 0x1E, 0x93, 0x8B, 0x65, 0xF1}, +0.3f};


DS18B20::DS18B20(uint8_t pin, uint32_t samplingIntervalMs) {
    _sensors = new DallasTemperature(new OneWire(pin));
    _samplingIntervalMs = samplingIntervalMs;
}

void DS18B20::begin() {
    _sensors->begin();
    _lastReadMs = millis() - _samplingIntervalMs;

    uint8_t deviceCount = _sensors->getDeviceCount();
    DeviceAddress addr;
    char addr_str[64];
    _sensors->requestTemperatures();

    for (int i = 0; i < deviceCount; i++) {
        _sensors->getAddress(addr, i);
        sprintf(addr_str, "{0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X, 0x%02X}", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5], addr[6], addr[7]);
        logger.log("Sensor %d, address %s, temp %.1f", i, addr_str, _sensors->getTempCByIndex(i));
    }

    loop();
}

void DS18B20::loop() {
    if (millis() - _lastReadMs >= _samplingIntervalMs) {
        _sensors->requestTemperatures();
        _buffer_supply =_sensors->getTempC(buffer_supply_sensor.address) + buffer_supply_sensor.correction;
        _buffer_return = _sensors->getTempC(buffer_return_sensor.address) + buffer_return_sensor.correction;
        _ufh_supply = _sensors->getTempC(ufh_supply_sensor.address) + ufh_supply_sensor.correction;
        _ufh_return = _sensors->getTempC(ufh_return_sensor.address) + ufh_return_sensor.correction;
        _lastReadMs += _samplingIntervalMs;
    }
}

float DS18B20::getBufferSupplyTemp() {
    return _buffer_supply;
}

float DS18B20::getBufferReturnTemp() {
    return _buffer_return;
}

float DS18B20::getUFHSupplyTemp() {
    return _ufh_supply;
}

float DS18B20::getUFHReturnTemp() {
    return _ufh_return;
}
