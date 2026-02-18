#include <Arduino.h>             // Базові функції Arduino
#include "CLD_Interface.h"       // Заголовочний файл з функціями керування кнопками та LCD дисплеєм 

void setup() {
  LCD_Settings();
}

void loop() {
  Button();
  Display_Picture();
}
