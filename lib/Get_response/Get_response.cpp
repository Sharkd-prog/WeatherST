#include <Arduino.h>            // Базові функції Arduino
#include <WiFi.h>               // Робота з WiFi на ESP32
#include <HTTPClient.h>         // HTTP клієнт для виконання GET-запитів
#include "Get_response.h"       // Оголошення структури JSON_value та прототипу Get_JSON()


// Змінна для збереження часу останнього HTTP-запиту
unsigned long lastTime = 0;

// Інтервал між запитами (1 година)
unsigned long timerDelay = 3600000;

// Масив назв міст
String City[CITY_COUNT]={"Kyiv", "Lviv"};

// Масив кодів країн
String Contry_code[CITY_COUNT]= {"UA", "UA"};

// API ключ сервісу OpenWeather
String Api_key = "3da792c19c51572a5d6ed31d066561f9";

// Глобальна структура для збереження JSON-відповідей
JSON_value Response_JSON;

// Функція виконує:
// 1) перевірку таймера
// 2) HTTP-запити до OpenWeather
// 3) збереження отриманого JSON

JSON_value Get_JSON(){
    // Надсилає запит через годину від іншого запита(перший запит відбувається одразу)
    if(lastTime == 0 || millis() - lastTime > timerDelay){

        if(WiFi.status() != WL_CONNECTED){
            Serial.println("WiFi not connected");
            return Response_JSON;
        }
        // Цикл по всіх містах
        for(char i=0;i<CITY_COUNT;i++){
            String Server = "https://api.openweathermap.org/data/2.5/weather?q=" + City[i] + "," + Contry_code[i] + "&appid=" + Api_key;

            WiFiClientSecure client;
            HTTPClient http;
            client.setInsecure();
            http.begin(client, Server);

            // Виконання GET-запиту
            int ResponseCode = http.GET();
            if (ResponseCode>0){

                // Вивід HTTP-коду відповіді
                Serial.print("Response code for " + City[i] + ":");
                Serial.println(ResponseCode);
                // Збереження сирого JSON у структуру
                Response_JSON.JSON_Value[i] = http.getString();
            } else {

                 // Вивід коду помилки -1 або інші
                Serial.print("Error code for " + City[i] + ":");
                Serial.println(ResponseCode);
            }
            http.end(); 
        }
        lastTime = millis();

    }
    // Повертаємо структуру з даними
    return Response_JSON;
}