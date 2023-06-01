
//--------------------------EEPROM---------------------------------
#define NUMBER_RELE 8
#define MAX_NUMBER_SENSOR 12
#define MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR  40
#define TOTAL_LENGTH_SECTION 0

//****************************************************************
//байт в EEPROM де позначається режим client=0 або accees point>0
#define LENGTH_ADRESS_CLIENT_OR_ACCESS_POINT 1
const int EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT =  (TOTAL_LENGTH_SECTION);//байт в EEPROM де позначається режим client=0 або accees point>0
//****************************************************************

#define TOTAL_LENGTH_SECTION_50 (TOTAL_LENGTH_SECTION + LENGTH_ADRESS_CLIENT_OR_ACCESS_POINT)

//****************************************************************
//Строка де зберігаємо імя пристрою
#define LENGTH_NUMBER_RELE 1
#define LENGTH_NUMBER_SENSOR 1
#define LENGTH_MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR 1
#define LENGTH_REZERVA 17
#define LENGTH_DATA_SETING 20
const int EEPROM_NUMBER_RELE =  (TOTAL_LENGTH_SECTION_50);//байт в EEPROM де позначається кількість реле
const int EEPROM_NUMBER_SENSOR =  (TOTAL_LENGTH_SECTION_50 + 1);//байт в EEPROM де позначається кількість sensoriv
const int EEPROM_LENNGTH_TEXT_NAME_RELE_AND_SENSOR =  (TOTAL_LENGTH_SECTION_50 + 2);//байт в EEPROM де позначається довжина тексту імені реле і датчиків
//****************************************************************

#define TOTAL_LENGTH_SECTION_100 (TOTAL_LENGTH_SECTION_50 + LENGTH_DATA_SETING)

//Строка де зберігаємо імя пристрою
#define LENGTH_STRING_NAME_DEVICE 40
const int EEPROM_ADRESS_STRING_NAME_DEVICE =  (TOTAL_LENGTH_SECTION_100);//байт в EEPROM де позначається режим client=0 або accees point>0
//****************************************************************

#define TOTAL_LENGTH_SECTION_120 (TOTAL_LENGTH_SECTION_100 + LENGTH_STRING_NAME_DEVICE)

//****************************************************************
//Номера реле і піни до яких підключено реле  8 реле і в кожний байт записується номер піна для підключеня реле, якщо пін для реле не призначений записуємо 255
#define LENGTH_BYTE_CONNECT_PIN_RELE 8
const int EEPROM_BYTE_CONNECT_PIN_RELE =  (TOTAL_LENGTH_SECTION_120);//байт в EEPROM де позначається режим client=0 або accees point>0
//****************************************************************

#define TOTAL_LENGTH_SECTION_125 (TOTAL_LENGTH_SECTION_120 + LENGTH_BYTE_CONNECT_PIN_RELE)

//****************************************************************
//Номера кнопок і піни до яких підключені кнопки мах 20 кнопок і в кожний байт записується номер піна для підключеня кнопки, якщо пін для кнопки не призначений записуємо 255
#define LENGTH_BYTE_CONNECT_PIN_BUTTUN 20
const int EEPROM_BYTE_CONNECT_PIN_BUTTUN =  (TOTAL_LENGTH_SECTION_125);//байт в EEPROM де позначається режим client=0 або accees point>0
//****************************************************************

#define TOTAL_LENGTH_SECTION_130 (TOTAL_LENGTH_SECTION_125 + LENGTH_BYTE_CONNECT_PIN_RELE)

//****************************************************************
//Номера DS18B20 і піни до яких підключені DS18B20пки мах 5 DS18B20 і в кожний байт записується номер піна для підключеня DS18B20, якщо пін для DS18B20 не призначений записуємо 255
#define LENGTH_BYTE_CONNECT_PIN_DS18B20 5
const int EEPROM_BYTE_CONNECT_PIN_DS18B20 =  (TOTAL_LENGTH_SECTION_130);//байт в EEPROM де позначається режим client=0 або accees point>0
//****************************************************************

#define TOTAL_LENGTH_SECTION_150 (TOTAL_LENGTH_SECTION_130 + LENGTH_BYTE_CONNECT_PIN_DS18B20)

//****************************************************************
//логіни і паролі
#define NUMBER_CLIENT_CONNECT 4
#define LENGTH_SSID (10*2)
#define LENGTH_PASSWORD (10*2)
#define LENGTH_SECTION_SSID_ADN_PASSWORD  (LENGTH_SSID * NUMBER_CLIENT_CONNECT + LENGTH_PASSWORD * NUMBER_CLIENT_CONNECT)
const int START_SECTION_EEPROM_SSID_AND_PASSWORD = (TOTAL_LENGTH_SECTION_150);
String arraySsidInput[NUMBER_CLIENT_CONNECT];     //для логінів
String arrayPasswordInput[NUMBER_CLIENT_CONNECT]; //для паролів
String arraySsid[NUMBER_CLIENT_CONNECT];     //для логінів
String arrayPassword[NUMBER_CLIENT_CONNECT]; //для паролів
//****************************************************************

#define TOTAL_LENGTH_SECTION_200 (TOTAL_LENGTH_SECTION_150 + LENGTH_SECTION_SSID_ADN_PASSWORD)

//****************************************************************
//температура включеня Від -50 до 100 зміщаємо діапазон (-50градусів=0), (0градусів=50), (100градусів=150);
#define LENGTH_TEMP_ON_OFF (NUMBER_RELE * 2)
const int START_SECTION_EEPROM_TEMP_ON_OFF = (TOTAL_LENGTH_SECTION_200);//температура включеня Від -50 до 100 зміщаємо діапазон (-50градусів=0), (0градусів=50), (100градусів=150);
//****************************************************************

//****************************************************************

#define TOTAL_LENGTH_SECTION_250 (TOTAL_LENGTH_SECTION_200 + LENGTH_TEMP_ON_OFF)

//****************************************************************
// біт 0-7 номер датчика який управляє даним реле якщо код 255 то реле термодатчиком не керується, якщо інший код то він вказує на номер термодатчика, що керує реле
#define LENGTH_RELE_EEPROM_SENSOR_UPR  NUMBER_RELE
const int START_RELE_EEPROM_SENSOR_UPR = (TOTAL_LENGTH_SECTION_250);

#define TOTAL_LENGTH_SECTION_300 (TOTAL_LENGTH_SECTION_250 + LENGTH_RELE_EEPROM_SENSOR_UPR)


////****************************************************************
//// біт 0 один або два діапазона контроля температрур
//// біт 1 вкл або викл реле при зміні температур або таймера
//// біт 2 стан реле при помилці термодатчмка
//#define LENGTH_RELE_EEPROM_SENSOR_CHEKED  NUMBER_RELE
//const int START_RELE_EEPROM_SENSOR_CHEKED = (TOTAL_LENGTH_SECTION_300);

//#define LENGTH_RELE_EEPROM_SENSOR  NUMBER_RELE
//const int START_SECTION_RELE_EEPROM_SENSOR = (TOTAL_LENGTH_SECTION_300);
//****************************************************************

//#define TOTAL_LENGTH_SECTION_400 (TOTAL_LENGTH_SECTION_300 + LENGTH_RELE_EEPROM_SENSOR_CHEKED)

//****************************************************************
#define LENGTH_RELE_EEPROM_FLAGS  NUMBER_RELE
const int START_SECTION_RELE_EEPROM_FLAGS = (TOTAL_LENGTH_SECTION_300);
//const int rele_0_eprom_upr ;
// біт 0 1-ручне або 0-від таймера чи термодатчика  manualAuto
// біт 1 1-Включене реле або 0-Відключене реле onOffManual
// біт 4 один або два діапазона контроля температрур
// біт 5 вкл або викл реле при зміні температур або таймера
// біт 6 стан реле при помилці термодатчмка
// біт 7 rezerva

//****************************************************************

#define TOTAL_LENGTH_SECTION_500 (TOTAL_LENGTH_SECTION_300 + LENGTH_RELE_EEPROM_FLAGS)

//****************************************************************
#define LENGTH_SECTION_EEPROM_SENSOR_ADDRESS  MAX_NUMBER_SENSOR * 8
const int START_SECTION_EEPROM_SENSOR_ADDRESS = (TOTAL_LENGTH_SECTION_500);
//boolean flagRele = true;
//зберігає адреса для 20 датчиків кожен датчик займає 8 байт від 281 до 441
//****************************************************************

#define TOTAL_LENGTH_SECTION_600 (TOTAL_LENGTH_SECTION_500 + LENGTH_SECTION_EEPROM_SENSOR_ADDRESS)

//****************************************************************
#define LENGTH_SECTION_EEPROM_SENSOR_NAME  MAX_NUMBER_SENSOR * MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR
const int START_SECTION_EEPROM_SENSOR_NAME = (TOTAL_LENGTH_SECTION_600);
//const int sensorNameEEprom = 442; //442 + 8*40 = 762
//8 imen по 40 байт
//****************************************************************

#define TOTAL_LENGTH_SECTION_700 (TOTAL_LENGTH_SECTION_600 + LENGTH_SECTION_EEPROM_SENSOR_NAME)

//****************************************************************
#define LENGTH_SECTION_EEPROM_RELE_NAME  NUMBER_RELE * MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR
const int START_SECTION_EEPROM_RELE_NAME = (TOTAL_LENGTH_SECTION_700);
//const int releNameEEprom = 763; //763 + 8*40 = 1083
//8 imen по 40 байт

//****************************************************************

#define TOTAL_LENGTH_SECTION_800 (TOTAL_LENGTH_SECTION_700 + LENGTH_SECTION_EEPROM_RELE_NAME)

//****************************************************************
#define LENGTH_SECTION_EEPROM_TIMERDATE  NUMBER_RELE * 252
const int START_SECTION_EEPROM_TIMERDATE = (TOTAL_LENGTH_SECTION_800);
//const int timerDateEeprom = 1084;// (1084 + 252*8=3100)    byte  2byte-rik(2022-2099), 1byte-month(0-12), 1byte-day(1-31), 1byte-hour(0-23), 1byte-minute(0-59), 1byte-день тижня
//TimeEeprom =  byte 1byte - hodyna, 1byte - minute
//dayEeprom =  40 byte
//delayStartReleEeprom = 4 byte (0-100000 sekund)
//****************************************************************

#define TOTAL_LENGTH_SECTION_900 (TOTAL_LENGTH_SECTION_800 + LENGTH_SECTION_EEPROM_TIMERDATE)
const int TOTAL_LENGTH_SECTION_END = TOTAL_LENGTH_SECTION_900;

////****************************************************************
//#define LENGTH_SECTION_EEPROM_CONNECT_RELE  16
//const int START_SECTION_EEPROM_CONNECT_RELE = (TOTAL_LENGTH_SECTION_900);
////const int timerDateEeprom = 1084;// (1084 + 252*8=3100)    byte  2byte-rik(2022-2099), 1byte-month(0-12), 1byte-day(1-31), 1byte-hour(0-23), 1byte-minute(0-59), 1byte-день тижня
////TimeEeprom =  byte 1byte - hodyna, 1byte - minute
////dayEeprom =  40 byte
////delayStartReleEeprom = 4 byte (0-100000 sekund)
////****************************************************************
//
//#define TOTAL_LENGTH_SECTION_900 (TOTAL_LENGTH_SECTION_800 + LENGTH_SECTION_EEPROM_TIMERDATE)
//
////****************************************************************
//#define LENGTH_SECTION_EEPROM_CONNECT_RELE  16
//const int START_SECTION_EEPROM_CONNECT_RELE = (TOTAL_LENGTH_SECTION_900);
////const int timerDateEeprom = 1084;// (1084 + 252*8=3100)    byte  2byte-rik(2022-2099), 1byte-month(0-12), 1byte-day(1-31), 1byte-hour(0-23), 1byte-minute(0-59), 1byte-день тижня
////TimeEeprom =  byte 1byte - hodyna, 1byte - minute
////dayEeprom =  40 byte
////delayStartReleEeprom = 4 byte (0-100000 sekund)
////****************************************************************
//
//#define TOTAL_LENGTH_SECTION_900 (TOTAL_LENGTH_SECTION_800 + LENGTH_SECTION_EEPROM_TIMERDATE)
