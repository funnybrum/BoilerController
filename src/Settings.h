#pragma once

#include "SettingsBase.h"
#include "WiFi.h"
#include "TempSetter.h"
#include "InfluxDBCollector.h"


struct SettingsData {
    NetworkSettings network;
    TempSettings temp1Settings;
    InfluxDBCollectorSettings influxDB;
};

struct Empty {};

class Settings: public SettingsBase<SettingsData, Empty> {
    public:
        Settings();
        SettingsData* getSettings();

    protected:
        void initializeSettings();
        Empty* getRTCSettings();

    private:
        SettingsData settingsData;
};
