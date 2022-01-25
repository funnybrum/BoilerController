#pragma once

#include "stdint.h"
#include <DallasTemperature.h>

class DS18B20 {
    public:
        DS18B20(uint8_t pin, uint32_t samplingIntervalMs=500);
        void begin();
        void loop();
        float getTemp();
        float getTempMin();
        float getTempMax();
        void reset();
    private:
        float _tempMin;
        float _tempMax;
        uint32_t _lastReadMs;
        uint32_t _samplingIntervalMs;
        DallasTemperature* _sensors;
};
