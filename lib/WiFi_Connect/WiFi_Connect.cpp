#include <Arduino.h>            // Базові функції Arduino
#include <WiFi.h>               // Робота з WiFi на ESP32

const char* ssid_name = "TP-Link_FD24";  //Назва WiFi мережі (SSID)
const char* password = "01187441";       // Пароль WiFi мережі

void ConnectToWiFi(){                    //Підключення до мережі WiFi
    
    // Переводимо ESP32 у режим клієнта (Station mode)
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid_name, password);
    
    // Повідомлення про спробу підключення
    Serial.print("Connecting to WiFi ");
    
    // Очікування підключення до WiFi
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print("..");
        delay(1000);
    }
    // Повідомлення про успішне підключення
    Serial.print("\n WiFi connected successfully \n");
}