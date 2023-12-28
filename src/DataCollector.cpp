#include "Main.h"
#include "DataCollector.h"

DataCollector::DataCollector():
    InfluxDBCollector(&logger,
                      NULL,
                      &settings.getSettings()->influxDB,
                      &settings.getSettings()->network) {
}

bool DataCollector::shouldCollect() {
    return 0 < bufferTempSensors.getBufferSupplyTemp();
}

void DataCollector::collectData() {
    append("buffer_supply", bufferTempSensors.getBufferSupplyTemp(),1);
    append("buffer_return", bufferTempSensors.getBufferReturnTemp(),1);
    append("ufh_supply", bufferTempSensors.getUFHSupplyTemp(),1);
    append("ufh_return", bufferTempSensors.getUFHReturnTemp(),1);
    append("heating", ufhRelay.isOn(), 0);
}

bool DataCollector::shouldPush() {
    return false;
}   

void DataCollector::beforePush() {
    append("rssi", WiFi.RSSI(), 0);
}

void DataCollector::afterPush() {
}