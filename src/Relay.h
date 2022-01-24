#pragma once

#include "stdint.h"

class Relay {
    public:
        Relay(uint8_t pin, uint16_t onDelay);
        void begin();
        void loop();
        void on();
        void off();
        bool isOn();
    private:
        uint8_t _pin;
        uint16_t _onDelay;
        bool _on;
        uint32_t _onMillis;
};
