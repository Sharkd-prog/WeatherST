// Налаштування параметрів LCD
#define LCD_COLUMNS 16      //Ширина дисплей
#define LCD_ROWS 2          //Висота дисплея

// Коди кнопок
#define RIGHT_BUTTON 0
#define LEFT_BUTTON 1
#define SELECT_BUTTON 2
#define DOWN_BUTTON 3
#define NO_BUTTON 4

// Стан екрану
enum State_Screen{
    Start_Screen,           //Початковий екран 
    Select_Screen,          //Екран вибору міста із заспропонованих
    Data_Screen             //Екран даних про погоду в вибраному місті
};

// Прапорці для оновлення дисплея
enum Update{
    No_Redraw,              //Не оновлювати дисплей
    Redraw                  //Оновлювати дані дислея
};
// Прототипи функцій 
void LCD_Settings();        //Налаштування LCD
void Button();              //Визначення яка кнопка натиснута
void Display_Picture();     //Відображення інформації 