#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

String apiKey = "тайна"; // Enter your Write API key from ThingSpeak

const char* ssid = "тайна"; // Replace with your wifi ssid and WPA2 key
const char* pass = "голяма тайна";
const char* server = "api.thingspeak.com";

#define ONE_WIRE_BUS 4 // Data wire is connected to GPIO 4 i.e. D2 pin of nodemcu

OneWire oneWire(ONE_WIRE_BUS); // Setup a oneWire instance to communicate with any OneWire devices

DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature sensor

WiFiClient client;

uint8_t sensor_HPlow[8]   = { 0x28, 0xEE, 0xD5, 0x64, 0x1A, 0x16, 0x02, 0xEC };
uint8_t sensor_HPhigh[8]  = { 0x28, 0xEE, 0xD5, 0x64, 0x1A, 0x16, 0x02, 0xEC };
uint8_t sensor_hol[8]     = { 0x28, 0xEE, 0xD5, 0x64, 0x1A, 0x16, 0x02, 0xEC };
uint8_t sensor_outside[8] = { 0x28, 0xEE, 0xD5, 0x64, 0x1A, 0x16, 0x02, 0xEC };

void setup()
{
    Serial.begin(9600);
    delay(10);

    Serial.println("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected");

    // Start up the library
    sensors.begin();

    // locate devices on the bus
    Serial.printf("Found %d devices.\n\n", sensors.getDeviceCount());

    DeviceAddress addr;
    for (int i = 0; i < sensors.getDeviceCount(); i++) {
        Serial.printf("Sensor %d address is { ", i);
        sensors.getAddress(addr, i);
        for (uint8_t i = 0; i < 8; i++) {
            Serial.print(addr[i], HEX);
            if (i < 7) {
                Serial.print(", ");
            }
        }
        Serial.println(" }");
    }
}

float getSensor(const uint8_t* addr, const char* name) {
    for (int i = 1; i < 6; i++) {
        float temp = sensors.getTempC(addr);
        if (temp > -125) {
            return temp;
        }
        delay(200 * i);
        sensors.requestTemperatures();
    }

    Serial.printf("Failed to read sensor %s.\n", name);
    return -127.00;
}

void loop() {
    unsigned long start = millis();

    if (WiFi.status() != WL_CONNECTED) {
        Serial.printf("WiFi connection failed, current status is %d.\n", WiFi.status());
        delay(100);
        ESP.restart();
    }

    sensors.requestTemperatures();

    float tempC_HPlow = getSensor(sensor_HPlow, "HPlow");
    float tempC_hol = getSensor(sensor_hol, "hol");
    float tempC_HPhigh = getSensor(sensor_HPhigh, "HPhigh");
    float tempC_outside = getSensor(sensor_outside, "outside");

    int timeout = 5000;
    if (client.connect(server, 80)) { //184.106.153.149 or api.thingspeak.com
        String postStr = apiKey;
        postStr += "&field1=";
        postStr += String(tempC_HPlow);
        // postStr += "&field2=";
        // postStr += String(tempF);
        postStr += "&field2=";
        postStr += String(tempC_hol);
        postStr += "&field3=";
        postStr += String(tempC_HPhigh);
        postStr += "&field4=";
        postStr += String(tempC_outside);
        postStr += "\r\n\r\n";

        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(postStr.length());
        client.print("\n\n");
        client.print(postStr);
        Serial.println("Sent data to Thingspeak");

        // Изчаква до 5 секунди за отговор от сървъра и извежда изважда отговора в терминала.
        while (timeout > 0 && !client.available()) {
            timeout -= 100;
            delay(100);
        }

        if (!client.available()) {
            Serial.println("Server did not respond");
        } else {
            delay(1000);
            Serial.println("Server responded:");
            Serial.println(client.readString());
        }
    } else {
        Serial.println("Connection to thingspeak failed.");
    }
    client.stop();
    Serial.println("Delay of 30 Sec");
    // thingspeak needs minimum 30 sec delay between updates
    delay(30000 - millis() - start);
}


