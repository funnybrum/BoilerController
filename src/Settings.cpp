#include "Settings.h"
#include "Main.h"

Settings::Settings()
    :SettingsBase(&logger) {
}

void Settings::initializeSettings() {
    strcpy(settingsData.network.hostname, HOSTNAME);
    settingsData.temp1Settings.lowTemp = 25;
    settingsData.temp1Settings.lowTempMs = 350;
    settingsData.temp1Settings.highTemp = 45;
    settingsData.temp1Settings.highTempMs = 2600;
}

SettingsData* Settings::getSettings() {
    return &settingsData;
}

Empty* Settings::getRTCSettings() {
    return NULL;
}
