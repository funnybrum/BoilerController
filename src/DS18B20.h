#pragma once

#include "stdint.h"
#include <DallasTemperature.h>

class DS18B20 {
    public:
        DS18B20(uint8_t pin, uint32_t samplingIntervalMs=2000);
        void begin();
        void loop();
        float getBufferSupplyTemp();
        float getBufferReturnTemp();
        float getUFHSupplyTemp();
        float getUFHReturnTemp();

    private:
        uint32_t _lastReadMs;
        uint32_t _samplingIntervalMs;
        DallasTemperature* _sensors;
        float _buffer_supply;
        float _buffer_return;
        float _ufh_supply;
        float _ufh_return;
};
