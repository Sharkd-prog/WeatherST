#pragma once

#include <Arduino.h>            // Базові функції Arduino

#define CITY_COUNT 2            // Кількість міст, для яких буде зберігатися JSON-відповідь, Використовується для визначення розміру масиву

// Структура для зберігання JSON-відповідей від API
struct JSON_value {

    // Масив рядків типу String
    String JSON_Value[CITY_COUNT];
};

extern JSON_value Response_JSON;
extern String City[CITY_COUNT];

// Прототип функції Get_JSON()
void Get_JSON();