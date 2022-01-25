#include "Main.h"
#include "DataCollector.h"

DataCollector::DataCollector():
    InfluxDBCollector(&logger,
                      NULL,
                      &settings.getSettings()->influxDB,
                      &settings.getSettings()->network) {
}

bool DataCollector::shouldCollect() {
    return 0 < ufhTempSensor.getTemp() && ufhTempSensor.getTemp() < 80;
}

void DataCollector::collectData() {
    append("set_temp", ufhTemp.getTemp());
    append("actual_temp", ufhTempSensor.getTemp(),1);
    append("min_temp", ufhTempSensor.getTempMin(),1);
    append("max_temp", ufhTempSensor.getTempMax(),1);
    append("heating", ufhRelay.isOn(), 0);
    ufhTempSensor.reset();
}

bool DataCollector::shouldPush() {
    return false;
}   

void DataCollector::onPush() {
}