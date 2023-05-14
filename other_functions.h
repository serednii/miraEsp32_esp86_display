


class OtherFunction{
  public:

//*************************************************************************************************************************************************
  static void defineDevice(String message1, String message2 ) {//Приводимо в початковий стан всі змінні
  for (int i = START_SECTION_EEPROM_SSID_AND_PASSWORD; i < START_SECTION_EEPROM_SSID_AND_PASSWORD + LENGTH_SECTION_SSID_ADN_PASSWORD; i++) EEPROM.write(i, 0);
  for (int i = START_SECTION_RELE_EEPROM_SENSOR; i < START_SECTION_RELE_EEPROM_SENSOR + LENGTH_RELE_EEPROM_SENSOR; i++) EEPROM.write(i, 255);
  for (int i = START_SECTION_EEPROM_TEMP_ON_OFF; i < START_SECTION_EEPROM_TEMP_ON_OFF + LENGTH_TEMP_ON_OFF; i += 2) EEPROM.write(i, 75);
  for (int i = START_SECTION_EEPROM_TEMP_ON_OFF + 1; i < START_SECTION_EEPROM_TEMP_ON_OFF + LENGTH_TEMP_ON_OFF; i += 2) EEPROM.write(i, 80);
  for (int i = START_SECTION_EEPROM_SENSOR_ADDRESS; i < START_SECTION_EEPROM_SENSOR_ADDRESS + LENGTH_SECTION_EEPROM_SENSOR_ADDRESS + 20 * NUMBER_RELE; i++) EEPROM.write(i, 0);
  for (int i = START_SECTION_EEPROM_SENSOR_NAME; i < START_SECTION_EEPROM_SENSOR_NAME + LENGTH_SECTION_EEPROM_SENSOR_NAME; i++) EEPROM.write(i, 0);
  for (int i = START_SECTION_EEPROM_RELE_NAME; i < START_SECTION_EEPROM_RELE_NAME + LENGTH_SECTION_EEPROM_RELE_NAME; i++) EEPROM.write(i, 0);
  Serial.print("void defineDevice()");
  for (int i = 0; i < 8; i++) {
    String message = message1 + String(i) + message2;
    delay(50);
    client.publish(nameUser + "_set-rele-data-time", message);
  }
  Serial.print("void defineDevice()");
  Eeprom::comitEprom();
  //resetFunc();
}
//*************************************************************************************************************************************************

//*************************************************************************************************************************************************
static  void ledBlink(byte n, int t) {
  for (byte i = 0; i < n; i++) {
    pinMode(PIN_LED_KONTROL, INPUT);
    delay(t);
    pinMode(PIN_LED_KONTROL, OUTPUT);
    delay(t);
  }
}
//*************************************************************************************************************************************************
};



//*************************************************************************************************************************************************
int loopRefresh = 0;//counter refresh eeprom to date

void refreshData() {
  //Якщо в памяті є записаний реальний мас адрес датчика то присвоюємо йому температуру датчика
  Sensor::readSensorsAddressTemp(ds18b20); //читаємо в обєкт DS18B20 адреса і температуру датчиків що є підключенні до контроллера
  Sensor::readEepromDataSensor(ds18b20EEprom); //читаємо імя, address і температуру з памяті ЕЕПРОМ  в обєкт ds18b20EEprom що є вибрані в програмі
  Sensor::searchCodeSennsorInEEPROM(ds18b20EEprom, ds18b20);//Записуємо температуру в EEPROM sensory з реальних датчиків
  //  readEepromNameSensor(); //читаємо імя з памяті ЕЕПРОМ в обєкт ds18b20EEprom

  Rele::readEepromNameRele(releControl);//читаємо address з памяті ЕЕПРОМ в обєкт releControl

  if (loopRefresh == 0) {
    //    TimerDate::sendDateTime(dataAndTime);
    loopRefresh = 2;
  }

  loopRefresh--;

  //читаємо температури включення і відключення
  for (int i = START_SECTION_EEPROM_TEMP_ON_OFF, n = 0; i < START_SECTION_EEPROM_TEMP_ON_OFF + 16; i += 2, n++)
  {
    ds18b20[n].tempVkl = EEPROM.read(i) - 50;
    ds18b20[n].tempOtkl = EEPROM.read(i + 1) - 50;
  }

  for (int i = 0; i < 8; i++)
  {
    //    byte temp = EEPROM.read(START_SECTION_RELE_EEPROM_SENSOR + i);
    //START_SECTION_RELE_EEPROM_SENSOR
    releControl[i].numberSensorControl = releControl[i].getNumberSensorControlEEPROM(i);
    prin("numberSensorControl++++++++++++++++++   ", releControl[i].numberSensorControl);

    releControl[i].bit4OneOrTwoRange = releControl[i].getOneOrTwoRangeEEPROM(i);
    releControl[i].bit5OnOffChange = releControl[i].getOnOffChangeEEPROM(i);
    releControl[i].bit6ReleError = releControl[i].getReleErrorEEPROM(i);

    //    releControl[i].numberSensorControl = temp & ~0b11110000;
    //    releControl[i].bit4OneOrTwoRange = (temp & ~0b11101111) >> 4;
    //    releControl[i].bit5OnOffChange = (temp & ~0b11011111) >> 5;
    //    releControl[i].bit6ReleError = (temp & ~0b10111111) >> 6;
    //    temp = EEPROM.read(START_SECTION_RELE_EEPROM_UPR + i);
    //START_SECTION_RELE_EEPROM_UPR
    releControl[i].manualAuto = releControl[i].getManualAutoEEPROM(i);
    releControl[i].onOffManual = releControl[i].getOnOffManualEEPROM(i);
    //    releControl[i].termoControl = releControl[i].getTermoControlEEPROM(i);//Не використовується
    //    releControl[i].timerControl =  releControl[i].getTimerControlEEPROM(i);//Не використовується для EEPROM

    //    releControl[i].manualAuto = temp & ~0b11111110;
    //    releControl[i].onOffManual = ((temp & ~0b11111101) >> 1);
    //    releControl[i].termoControl = ((temp & ~0b11111011) >> 2);//Не використовується
    //    releControl[i].timerControl = ((temp & ~0b00000111) >> 3);
    ds18b20EEprom[i].tempVkl =  EEPROM.read(START_SECTION_EEPROM_TEMP_ON_OFF + i * 2) - 50;
    ds18b20EEprom[i].tempOtkl =  EEPROM.read(START_SECTION_EEPROM_TEMP_ON_OFF + i * 2 + 1) - 50;
  }
}

//*************************************************************************************************************************************************


//*************************************************************************************************************************************************

String message1 = "RELE";
String message2 = "-65535-\
4294967295-65535-99-99-99-99-99-\
4294967295-65535-99-99-99-99-99-\
4294967295-65535-99-99-99-99-99-\
4294967295-65535-99-99-99-99-99-\
4294967295-65535-99-99-99-99-99-\
4294967295-65535-99-99-99-99-99-\
4294967295-65535-99-99-99-99-99-\
4294967295-65535-99-99-99-99-99-\
4294967295-65535-99-99-99-99-99-\
4294967295-65535-99-99-99-99-99-\
99-99-99-99-99-99-99-99-99-99-\
99-99-99-99-99-99-99-99-99-99-\
99-99-99-99-99-99-99-99-99-99-\
99-99-99-99-99-99-99-99-99-99-\
99-99-99-99-99-99-99-99-99-99-\
99-99-99-99-99-99-99-99-99-99-\
99-99-99-99-99-99-99-99-99-99-\
99-99-99-99-99-99-99-99-99-99-\
99-99-99-99-99-99-99-99-99-99-\
99-99-99-99-99-99-99-99-99-99-\
1-1-1-1-1-1-1-\
1-1-1-1-1-1-1-\
1-1-1-1-1-1-1-\
1-1-1-1-1-1-1-\
1-1-1-1-1-1-1-";





//*************************************************************************************************************************************************
void analoReadA0() {
#ifdef ESP8266
  if (analogRead(inputAnalogPortADC1_0) > 1000) {
#else
  //             Serial.print(analogRead(A0));
  //            Serial.print("  --  ");
  if (analogRead(inputAnalogPortADC1_0) > 800) {
#endif

    if (counterAnalogInput > 120) {

      if (EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT) > 0) { //if access point goto client
        EEPROM.write(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT, 0); //переходимо в точку доступа
        checkClientAccessPointRom = 0;
        Eeprom::comitEprom();
        OtherFunction::ledBlink(5, 300);
        //        Serial.println("connect to acess point");
        lcd.clear();                                         // Очищаем LCD дисплей
        lcd.setCursor(0, 0);
        lcd.print("Chenge device to");
        lcd.setCursor(0, 1);
        lcd.print("acess point");
        delay(1000);
        //resetFunc(); //вызываем reset
      } else {//if client goto access point
        EEPROM.write(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT, 255); //переходимо в client
        checkClientAccessPointRom = 255;
        Eeprom::comitEprom();
        Serial.println("connect to client");
        OtherFunction::ledBlink(5, 300);
        lcd.clear();                                         // Очищаем LCD дисплей
        lcd.setCursor(0, 0);
        lcd.print("Chenge device to");
        lcd.setCursor(0, 1);
        lcd.print("wifi router");
        delay(1000);
        //resetFunc(); //вызываем reset
      }

      EEPROM.write(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT, 0); //переходимо в точку доступа
      checkClientAccessPointRom = 0;
      Eeprom::comitEprom();
      Serial.println("connect to acess point");
      resetFunc(); //вызываем reset
    }

    //            Serial.print(analogRead(A0));
    //            Serial.print("  --  ");
    //        Serial.println(counterAnalogInput++);
    counterAnalogInput++;
    //*************************lcd***************************
    lcd.clear();                                         // Очищаем LCD дисплей

    lcd.setCursor(0, 0);
    lcd.print("counterAnalogInput");
    lcd.setCursor(0, 1);
    lcd.print(counterAnalogInput);
    //*************************lcd***************************
  } else {
    //        Serial.print(analogRead(A0));
    //        Serial.print("  --  ");
    //        Serial.println(counterAnalogInput++);
    counterAnalogInput = 0;
  }
}
//*************************************************************************************************************************************************

//*************************************************************************************************************************************************
