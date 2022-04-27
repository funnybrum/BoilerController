#include "Relay.h"
#include "Arduino.h"

Relay::Relay(uint8_t pin, uint16_t onDelay) {
    this->_pin = pin;
    this->_onDelay = onDelay;
}

void Relay::begin() {
    pinMode(_pin, OUTPUT);
    off();
}

void Relay::loop() {
    if (_onMillis != 0) {
        if (millis() - _onMillis > _onDelay * 1000) {
            digitalWrite(_pin, LOW);
            _on = true;
            _onMillis = 0;
        }
    }
}

bool Relay::isOn() {
    return _on;
}

void Relay::on() {
    _onMillis = millis();
    if (_onMillis == 0) {
        _onMillis++;
    }
}

void Relay::off() {
    _onMillis = 0;
    _on = false;
    digitalWrite(_pin, HIGH);
}