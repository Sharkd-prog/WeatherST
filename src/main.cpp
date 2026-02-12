#include <Arduino.h>            // Базові функції Arduino
#include <WiFi.h>               // Бібліотека для роботи з WiFi на ESP32
#include <HTTPClient.h>         // HTTP клієнт для виконання GET запитів
#include <Arduino_JSON.h>       // Бібліотека для роботи з JSON
#include "Get_response.h"       // Заголовочний файл з функцією Get_JSON()

const char* ssid_name = "TP-Link_FD24";  //Назва WiFi мережі (SSID)
const char* password = "01187441";       // Пароль WiFi мережі

void setup() {
  Serial.begin(115200);     // Ініціалізація Serial-порту для виводу діагностичних повідомлень
  
  delay(5000);              //Затримка 5 секунд, щоб Serial Monitor отримав перше повідомлення

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

void loop() {
  // Виклик функції, яка:
  // - перевіряє таймер
  // - виконує HTTP-запит до OpenWeather
  // - повертає структуру JSON_value з відповіддю сервера
   JSON_value JSON = Get_JSON();

    // Вивід JSON для Києва
   Serial.println("Data weather of Kyiv:");
   Serial.println(JSON.JSON_Value[0]);

   // Вивід JSON для Львова
   Serial.println("Data weather of Lviv:");
   Serial.println(JSON.JSON_Value[1]);
   delay(5000);
}
//Приклад виведених даних: (38-43 рядки)
/*Data weather of Kyiv:
{"coord":{"lon":30.5167,"lat":50.4333},"weather":[{"id":804,"main":"Clouds","description":"overcast clouds","icon":"04n"}],"base":"stations","main":{"temp":276.33,"feels_like":276.33,"temp_min":276.33,"temp_max":276.33,"pressure":994,"humidity":96,"sea_level":994,"grnd_level":978},"visibility":61,"wind":{"speed":0.45,"deg":155,"gust":1.34},"clouds":{"all":100},"dt":1770937505,"sys":{"type":2,"id":2003742,"country":"UA","sunrise":1770959625,"sunset":1770995445},"timezone":7200,"id":703448,"name":"Kyiv","cod":200}
Data weather of Lviv:
{"coord":{"lon":24.0232,"lat":49.8383},"weather":[{"id":804,"main":"Clouds","description":"overcast clouds","icon":"04n"}],"base":"stations","main":{"temp":276.8,"feels_like":273.71,"temp_min":276.8,"temp_max":276.8,"pressure":989,"humidity":98,"sea_level":989,"grnd_level":953},"visibility":610,"wind":{"speed":3.44,"deg":172,"gust":8.73},"clouds":{"all":100},"dt":1770937618,"sys":{"country":"UA","sunrise":1770961100,"sunset":1770997087},"timezone":7200,"id":702550,"name":"Lviv","cod":200}*/