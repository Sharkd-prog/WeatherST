# WeatherST
ESP32 Weather Station - this is a project based on ESP32 with 16 MB flash memory that receives weather data for a selected city and displays it on a 16x2 LCD display. 

# Runtime Logic
### - Display start with notification "Connecting to WiFI..."
![](https://github.com/Sharkd-prog/WeatherST/blob/9c56049f9f8930071090df163760007801bef6e7/image/photo_1_2026-02-19_12-55-51.jpg)
### - Connect ESP32 to WiFi
### - Get JSON request to [OpenWeather](https://openweathermap.org/)
### The request perform once an hour 
# Example of the response received
```bash
{
  "coord": {
    "lon": 10.99,
    "lat": 44.34
  },
  "weather": [
    {
      "id": 501,
      "main": "Rain",
      "description": "moderate rain",
      "icon": "10d"
    }
  ],
  "base": "stations",
  "main": {
    "temp": 298.48,
    "feels_like": 298.74,
    "temp_min": 297.56,
    "temp_max": 300.05,
    "pressure": 1015,
    "humidity": 64,
    "sea_level": 1015,
    "grnd_level": 933
  },
  "visibility": 10000,
  "wind": {
    "speed": 0.62,
    "deg": 349,
    "gust": 1.18
  },
  "rain": {
    "1h": 3.16
  },
  "clouds": {
    "all": 100
  },
  "dt": 1661870592,
  "sys": {
    "type": 2,
    "id": 2075663,
    "country": "IT",
    "sunrise": 1661834187,

    "sunset": 1661882248
  },
  "timezone": 7200,
  "id": 3163858,
  "name": "Zocca",
  "cod": 200
}
```
### - Display on LCD "Select  city Press SELECT"
![](https://github.com/Sharkd-prog/WeatherST/blob/9c56049f9f8930071090df163760007801bef6e7/image/photo_2_2026-02-19_12-55-51.jpg)

### The advantage of the code is that it is easy to add a new city. Add it by changing CITY_COUNT, which  responsible for the number of all cities, and filling in the City and Country_code arrays.

## Menu Select City:
![ ](https://github.com/Sharkd-prog/WeatherST/blob/9c56049f9f8930071090df163760007801bef6e7/image/photo_3_2026-02-19_12-55-51.jpg)
### - Аfter selecting a city the LCD show the temperature and humidity(selection is made using the SELECT, LEFT, DOWN, and RIGHT buttons)
![ ](https://github.com/Sharkd-prog/WeatherST/blob/9c56049f9f8930071090df163760007801bef6e7/image/photo_4_2026-02-19_12-55-51.jpg)

# Technologies used
### The project write on Platformio from VS Code, and have a file with the .ini extension. Libraries use [Arduino](https://github.com/arduino/ArduinoCore-avr),[HTTPClient](https://github.com/amcewen/HttpClient),[WiFi](https://github.com/arduino-libraries/WiFi) and libraries that you should instal [Arduino_JSON](https://github.com/arduino-libraries/Arduino_JSON) and [LiquidCrystal](https://github.com/arduino-libraries/LiquidCrystal). Also the work is also performed by files from the [lib](https://github.com/Sharkd-prog/WeatherST/tree/9c56049f9f8930071090df163760007801bef6e7/lib) folder.
### Used ESP32-S3-N16R8[ESP32-S3-N16R8](https://documentation.espressif.com/esp32-s3_datasheet_en.pdf#cd-pins-io-mux-gpio) and [LCD Keybord Shield](https://arduino.ua/ru/prod235-lcd-keypad-shield?srsltid=AfmBOooayeR4v4l66ZFyZmS4Sh2W3Af4jrzPu0Ckfmve_1bfBB7Gn-ii). 

# Schematic of project: 
![](https://github.com/Sharkd-prog/WeatherST/blob/43a25cd7d71195876688f87e9538d4964f1d89ec/image/Schematic_Weather-Stantion_2026-02-19%20(1).png)

# Description of folders in [lib](https://github.com/Sharkd-prog/WeatherST/tree/9c56049f9f8930071090df163760007801bef6e7/lib) folder.
## CLD_Interface
### The CLD_Interface module is responsible for user interaction via the LCD display and control buttons.

## Get_response
### The Get_response module is responsible for receiving data from the server via HTTP requests.

## WiFi_Connect
### The WiFi_Connect module is responsible for connecting the device to Wi-Fi networks. 

# Work of project
https://github.com/Sharkd-prog/WeatherST/blob/ec82f7f9b7db1257577175193a6ec17c031ba4fd/image/video_2026-02-19_12-16-12.mp4
