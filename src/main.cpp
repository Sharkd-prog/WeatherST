#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

const char* ssid_name = "TP-Link_FD24";
const char* password = "01187441";

void setup() {
  Serial.begin(115200);

  delay(3000);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid_name, password);

  Serial.print("Connecting to WiFi ");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
}

void loop() {

  // put your main code here, to run repeatedly:
}
