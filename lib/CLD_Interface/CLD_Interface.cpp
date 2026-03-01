#include <Arduino.h>          // Базові функції Arduino
#include <LiquidCrystal.h>    // Бібліотека для програмування LCD 16x2
#include "CLD_Interface.h"    // Заголовочний файл з функціями керування кнопками та LCD дисплеєм 
#include "Get_response.h"     // Оголошення структури JSON_value та прототипу Get_JSON()
#include <Arduino_JSON.h>     // Бібліотека для роботи з JSON (парсинг і створення JSON-даних)

//Символ стрілки вліво
byte Arrow_Left[8]={
    0b00100,
    0b01000,
    0b11111,
    0b01000,
    0b00100,
    0b00000,
    0b00000,
    0b00000,
};

//Символ стрілки вправо
byte Arrow_Right[8]={
    0b00100,
    0b00010,
    0b11111,
    0b00010,
    0b00100,
    0b00000,
    0b00000,
    0b00000,
};

//Пустий символ
byte Empty[8]={
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
};

// Ініціалізація LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal Display_LCD(4, 5, 18, 17, 7, 6); 

// Поточний стан екрану на LCD
State_Screen Current_Screen;

// Прапорець для оновлення дисплея
Update Draw = Redraw;

// Індекс міста
int City_Index = 0;

//Натиснута кнопка
int Pressed_Button = NO_BUTTON;

// Змінні для обробки кнопок дребезку кнопок
int Current_Button = NO_BUTTON;             // поточне читання кнопки
int Last_Button = NO_BUTTON;                // попереднє читання (для дребезгу)
int Stable_Button = NO_BUTTON;              // кнопка на стадії стабільності 
unsigned long Last_Debounce_Time = 0;       // час останньої зміни кнопки
const unsigned long Debounce_Delay = 50;    // затримка для усунення дребезгу 50 мс

// Налаштування дисплея
void LCD_Settings(){
    Display_LCD.begin(LCD_COLUMNS, LCD_ROWS);
    Display_LCD.setCursor(2,0);
    Display_LCD.print("Connecting");
    Display_LCD.setCursor(2,1);
    Display_LCD.print("to WiFI...");
    Current_Screen = Start_Screen;
    Display_LCD.createChar(1, Arrow_Left);   //Заповнюємо в першу локацію Arrow_Left
    Display_LCD.createChar(2, Arrow_Right);  //Заповнюємо в другу локацію Arrow_Right
    Display_LCD.createChar(0, Empty);        //Заповнюємо в нульову локацію Empty
}

// Зчитування кнопок RIGHT, LEFT, SELECT, DOWN та по замовчуванню NO_BUTTON(жодна кнопка не натиснута)
void Button(){
    int Value_Button;
    Value_Button = analogRead(10);

    // Зчитування аналового значення АЦП з виводу A0 на Keypad
    if(Value_Button < 200){
        Current_Button = RIGHT_BUTTON;
    }
    else if(1000 < Value_Button && Value_Button < 1500){
        Current_Button = DOWN_BUTTON;
    }
    else if(Value_Button < 2050){
        Current_Button = LEFT_BUTTON;
    }
    else if(Value_Button < 3000){
        Current_Button = SELECT_BUTTON;
    }
    else{
        Current_Button = NO_BUTTON;   // жодної кнопки не натиснуто
    }
    
    //Логіка усунення дребезгу
    if (Current_Button != Last_Button) {
        Last_Debounce_Time = millis();
    }
    if ((millis() - Last_Debounce_Time) > Debounce_Delay) {
        if (Current_Button != Stable_Button) {
            Stable_Button = Current_Button;
            if (Stable_Button != NO_BUTTON) {
                Pressed_Button = Stable_Button;
            }
        }
    }
    Last_Button = Current_Button;
}

// Відображення інформації на LCD
void Display_Picture(){

    switch (Current_Screen)
    {
        // Стартовий екран
        case Start_Screen:{
            if(Draw){
                Display_LCD.clear();
                Display_LCD.setCursor(2,0);
                Display_LCD.print("Select  city");
                Display_LCD.setCursor(2,1);
                Display_LCD.print("Press SELECT");
                Draw = No_Redraw;
            }

            // якщо натиснули SELECT — переходимо на екран вибору міста
            if(Pressed_Button == SELECT_BUTTON){
                Current_Screen = Select_Screen;
                Pressed_Button = NO_BUTTON;
                Draw = Redraw;
            }
        }
        break;

        // Екран вибору міста
        case Select_Screen:{
            if(Draw){
                Display_LCD.clear();
                
                //Відображення лівої стрілки
                Display_LCD.setCursor(0,1);
                if( City_Index == 0){
                    Display_LCD.write(byte(0));   //Очищення стрілки ЛІВО якщо дійшли до лівого краю вибору
                }
                else{
                    Display_LCD.write(byte(1));
                }
                
                //Відображення правої стрілки
                Display_LCD.setCursor(15,1);
                if(City_Index == CITY_COUNT-1){
                    Display_LCD.write(byte(0));   //Очищення стрілки ПРАВО якщо дійшли до правого краю вибору
                }
                else{
                    Display_LCD.write(byte(2));
                }

                Display_LCD.setCursor(0,0);
                Display_LCD.print("City: ");
                Display_LCD.setCursor(6,0);
                Display_LCD.print(City[City_Index]);
                Display_LCD.setCursor(4,1);
                Display_LCD.print("Count: ");
                Display_LCD.setCursor(11,1);
                Display_LCD.print(City_Index+1);   // показуємо порядковий номер міста 
                Draw = No_Redraw;
            }

            // SELECT — переходимо на екран даних
            if(Pressed_Button == SELECT_BUTTON){
                Current_Screen = Data_Screen;
                Pressed_Button = NO_BUTTON;
                Draw = Redraw;
            }
            
            // RIGHT — наступне місто
            if(Pressed_Button == RIGHT_BUTTON){
                City_Index++;
                if(City_Index >= CITY_COUNT ){
                    City_Index = CITY_COUNT-1;
                }
                Pressed_Button = NO_BUTTON;
                Draw = Redraw;
            }
            
            // LEFT — попереднє місто
            if(Pressed_Button == LEFT_BUTTON){
                City_Index--;
                if(City_Index <= 0){
                    City_Index = 0;
                }
                Pressed_Button = NO_BUTTON;
                Draw = Redraw;
            }

            // DOWN — повертаємось на стартовий екран
            if(Pressed_Button == DOWN_BUTTON){
                Current_Screen = Start_Screen;
                Pressed_Button = NO_BUTTON;
                Draw = Redraw;
            }
        }
        break;

        // Екран даних (погода чи інша інформація)
        case Data_Screen:{
            if(Draw){
                Display_LCD.clear();
                JSONVar Weather_Value = JSON.parse(Response_JSON.JSON_Value[City_Index]);
                Display_LCD.setCursor(0,0);
                Display_LCD.print("Temp: ");
                Display_LCD.setCursor(10,0);
                Display_LCD.print(Weather_Value["main"]["temp"]);
                Display_LCD.setCursor(0,1);
                Display_LCD.print("Humidity: ");
                Display_LCD.setCursor(10,1);
                Display_LCD.print(Weather_Value["main"]["humidity"]);
                Draw = No_Redraw;
            }

            // DOWN — повертаємось на екран вибору міста
            if(Pressed_Button == DOWN_BUTTON){
                Current_Screen = Select_Screen;
                Pressed_Button = NO_BUTTON;
                Draw = Redraw;
            }
        }
        break;
    }
}