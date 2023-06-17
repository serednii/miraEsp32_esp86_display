//#define ESP8266
#define ESP32

#ifdef ESP8266
//ESP8266
const byte PIN_DS18B20 = 14;
const byte PIN_RELE_OUT_0 = 5;
const byte PIN_RELE_OUT_1 = 4;
const byte PIN_RELE_OUT_2 = 0;
const byte PIN_RELE_OUT_3 = 2;
const byte PIN_RELE_OUT_4 = 12;
const byte PIN_RELE_OUT_5 = 13;
const byte PIN_RELE_OUT_6 = 0;//3
const byte PIN_RELE_OUT_7 = 0;//1
//const byte PIN_LED_KONTROL = 16;
//const byte PIN_RELE_IN_0 = 33;//
//const byte PIN_RELE_IN_1 = 34;//
//const byte PIN_RELE_IN_2 = 35;
//const byte PIN_RELE_IN_3 = 39;//svn
//const byte PIN_RELE_IN_4 = 26;//
//const byte PIN_RELE_IN_5 = 27;//
//const byte PIN_RELE_IN_6 = 32;//
//const byte PIN_RELE_IN_7 = 33;//
//const byte PIN_RELE_IN_8 = 5;//
//const byte PIN_RELE_IN_9 = 2;//
//const byte PIN_RELE_IN_10 = 3;
//const byte PIN_RELE_IN_11 = 4;//
//const byte PIN_RELE_IN_12 = 5;//
//const byte PIN_RELE_IN_13 = 12;//
//const byte PIN_RELE_IN_14 = 14;//
//const byte PIN_RELE_IN_15 = 15;//
#else

//ESP32         
//Підключаємо ds18b20
const byte PIN_DS18B20 = 15;
//Display
const byte PIN_sda = 21;//sda i2c display 2004 or 1602
const byte PIN_scl = 22;//scl i2c display 2004 or 1602
//Піжключаємо виходи реле
const byte PIN_RELE_OUT_0 = 23;  
const byte PIN_RELE_OUT_1 = 19;//12
const byte PIN_RELE_OUT_2 = 18;
const byte PIN_RELE_OUT_3 = 5;//19
const byte PIN_RELE_OUT_4 = 17;//18
const byte PIN_RELE_OUT_5 = 16;
const byte PIN_RELE_OUT_6 = 4;//17
const byte PIN_RELE_OUT_7 = 0;

//const byte PIN_RELE_8 = 1;//При відключеному UART
//const byte PIN_RELE_8 = 2;
//const byte PIN_RELE_8 = 3;//При відключеному UART
//const byte PIN_RELE_8 = 18;
//const byte PIN_RELE_8 = 12;
//const byte PIN_RELE_8 = 14;
//const byte PIN_RELE_8 = 26;
//const byte PIN_RELE_8 = 27;
//const byte PIN_RELE_8 = 32;
//const byte PIN_RELE_8 = 33;

//const byte PIN_LED_KONTROL = 2;

const byte PIN_RELE_IN_0 = 39;//
const byte PIN_RELE_IN_1 = 34;//
const byte PIN_RELE_IN_2 = 35;//ok
const byte PIN_RELE_IN_3 = 32;//
const byte PIN_RELE_IN_4 = 33;//
const byte PIN_RELE_IN_5 = 25;//
const byte PIN_RELE_IN_6 = 26;//
const byte PIN_RELE_IN_7 = 27;//
const byte PIN_RELE_IN_8 = 36;//
//const byte PIN_RELE_IN_9 = 2;//
//const byte PIN_RELE_IN_10 = 3;;//При відключеному UART
//const byte PIN_RELE_IN_11 = 4;//
//const byte PIN_RELE_IN_12 = 5;//
//const byte PIN_RELE_IN_13 = 12;//
//const byte PIN_RELE_IN_14 = 14;//
//const byte PIN_RELE_IN_15 = 15;//
#endif
