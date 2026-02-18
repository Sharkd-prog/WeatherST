#include <Arduino.h>            // Базові функції Arduino
#include "Get_response.h"       // Заголовочний файл з функцією Get_JSON()
#include "WiFi_Connect.h"       // Заголовочний файл з функцією ConnectToWiFi()

void setup() {
  Serial.begin(115200);     // Ініціалізація Serial-порту для виводу діагностичних повідомлень
  
  delay(5000);              //Затримка 5 секунд, щоб Serial Monitor отримав перше повідомлення
  ConnectToWiFi();          //Підключення до мережі WiFi
}

void loop() {
  // Виклик функції, яка:
  // - перевіряє таймер
  // - виконує HTTP-запит до OpenWeather
  Get_JSON();
  delay(2000);
}
