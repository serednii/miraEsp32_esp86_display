int counterLcdPage  = 0;
boolean flagShowCounter = false;
const byte numLcdShowDisplay = 5;
void clearLcdChar() {
  for (byte i = 0; i < 4; i++) {
    lcd.setCursor(0, i);
    lcd.print("--------------------");
  }
}

const byte NUMBER_CHARS_NAME = 8; //Кількість символів імені що виводиться на дисплей
class OtherFunction {
  public:
    //*************************************************************************************************************************************************
    static void defineDevice() { //Приводимо в початковий стан всі змінні
      for (int i = START_SECTION_EEPROM_SSID_AND_PASSWORD; i < START_SECTION_EEPROM_SSID_AND_PASSWORD + LENGTH_SECTION_SSID_ADN_PASSWORD; i++) EEPROM.write(i, 0);
      for (int i = START_RELE_EEPROM_SENSOR_UPR; i < START_RELE_EEPROM_SENSOR_UPR + LENGTH_RELE_EEPROM_SENSOR_UPR; i++) EEPROM.write(i, 255);
      for (int i = START_SECTION_RELE_EEPROM_FLAGS; i < START_SECTION_RELE_EEPROM_FLAGS + LENGTH_RELE_EEPROM_FLAGS; i++) EEPROM.write(i, 0b10101101);
      for (int i = START_SECTION_EEPROM_TEMP_ON_OFF; i < START_SECTION_EEPROM_TEMP_ON_OFF + LENGTH_TEMP_ON_OFF; i += 2) EEPROM.write(i, 75);
      for (int i = START_SECTION_EEPROM_TEMP_ON_OFF + 1; i < START_SECTION_EEPROM_TEMP_ON_OFF + LENGTH_TEMP_ON_OFF; i += 2) EEPROM.write(i, 80);
      for (int i = START_SECTION_EEPROM_SENSOR_ADDRESS; i < START_SECTION_EEPROM_SENSOR_ADDRESS + LENGTH_SECTION_EEPROM_SENSOR_ADDRESS + 20 * NUMBER_RELE; i++) EEPROM.write(i, 0);
      for (int i = START_SECTION_EEPROM_SENSOR_NAME; i < START_SECTION_EEPROM_SENSOR_NAME + LENGTH_SECTION_EEPROM_SENSOR_NAME; i++) EEPROM.write(i, 0);
      for (int i = START_SECTION_EEPROM_RELE_NAME; i < START_SECTION_EEPROM_RELE_NAME + LENGTH_SECTION_EEPROM_RELE_NAME; i++) EEPROM.write(i, 0);
      Eeprom::comitEprom();
      //      Serial.print("void defineDevice()");
      TimerDate::readTimerEEPROMToObjeckt(dataAndTime);
      //      printObjectTime();
      for (int i = 0; i < NUMBER_RELE; i++) {
        //{"rele":0,"default":"default"}
        String str = "{\"rele\":" + String(i) + ",\"default\":\"default\"}";
        TimerDate::writeEepromObjectDataTimeSendBrouser(dataAndTime, str);
      }
      //      printObjectTime();
//      kontr_temp();
      Serial.print("void defineDevice()");
      resetFunc();
//      deviceCountSensor
    }
    //*************************************************************************************************************************************************

    //*************************************************************************************************************************************************
    //    static  void ledBlink(byte n, int t) {
    //      for (byte i = 0; i < n; i++) {
    ////        pinMode(PIN_LED_KONTROL, INPUT);
    //        delay(t);
    //        pinMode(PIN_LED_KONTROL, OUTPUT);
    //        delay(t);
    //      }
    //    }
    //*************************************************************************************************************************************************

    //*************************************************************************************************************************************************
    static void showInformation() {
      const byte NUMBER_CHARS_NAME = 8; //Кількість символів імені що виводиться на дисплей
      Sensor tempDs18b20EEprom[MAX_NUMBER_SENSOR];
      byte temtCounter = 0;
      //Створюємо новий обєкт тільки із діючих сенсорів, список включає в себе сенсори які ідуть один за одним в масиві обєкта
      for (int i = 0; i < 12; i++) {
        if (ds18b20EEprom[i].strAddress != "0000000000000000") {
          tempDs18b20EEprom[temtCounter].tempNumberSensor = i;
          tempDs18b20EEprom[temtCounter].strAddress = ds18b20EEprom[i].strAddress;
          tempDs18b20EEprom[temtCounter].nameSensor = ds18b20EEprom[i].nameSensor;
          tempDs18b20EEprom[temtCounter].temp = ds18b20EEprom[i].temp;
          temtCounter++;
        }
      }
    //Дописуємо заглушку для масиву в кінець незаповнених обєктів 
      for (int i = temtCounter; i < 12; i++) {
        tempDs18b20EEprom[i].tempNumberSensor = 100;
        tempDs18b20EEprom[i].strAddress = "0000000000000000";
        tempDs18b20EEprom[i].nameSensor = "----";
        tempDs18b20EEprom[i].temp = 1000;
      }

//      for (int i = 0, l = 0; i < 12; i++, l++) {
//        prin("ds18b20EEprom", ds18b20EEprom[i].strAddress);
//        prin("tempDs18b20EEprom", tempDs18b20EEprom[i].strAddress);
//      }
//
//      for (int i = 0, l = 0; i < 12; i++, l++) {
//        prin("ds18b20EEprom", ds18b20EEprom[i].nameSensor);
//        prin("tempDs18b20EEprom", tempDs18b20EEprom[i].nameSensor);
//      }
//
//      for (int i = 0, l = 0; i < 12; i++, l++) {
//        prin("ds18b20EEprom", ds18b20EEprom[i].temp);
//        prin("tempDs18b20EEprom", tempDs18b20EEprom[i].temp);
//      }
//
//      for (int i = 0, l = 0; i < 12; i++, l++) {
//        prin("ds18b20EEprom", ds18b20EEprom[i].tempNumberSensor);
//        prin("tempDs18b20EEprom", tempDs18b20EEprom[i].tempNumberSensor);
//      }


start:
      Serial.println("showInformation>>>>>>>>>>>>>>>>>");
      Serial.println( counterLcdPage  );
      Serial.println(flagShowCounter);
      if ( counterLcdPage < -1) counterLcdPage = 0;
      if ( counterLcdPage == 0) {
        //*************************lcd***************************
        lcd.clear();
        if (EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT) > 0) {
          // Очищаем LCD дисплей
          lcd.setCursor(0, 0);
          String temp = "SSID=" + WiFi.SSID();
          lcd.print(temp);
          lcd.setCursor(0, 1);
          temp = "IP=" + WiFi.localIP().toString();
          lcd.print(temp);
          lcd.setCursor(0, 2);
          lcd.print("Name Deice");
          lcd.setCursor(0, 3);
          lcd.print(nameUser);
        } else {
          lcd.setCursor(0, 0);  //Set cursor to character 2 on line 0
          lcd.print("ACCESS_POINT");
          lcd.setCursor(0, 1);  //Set cursor to character 2 on line 0
          lcd.print("IP " + myIP.toString());
          lcd.setCursor(0, 2);  //Set cursor to character 2 on line 0
          lcd.print("ssid ");
          lcd.setCursor(0, 3);  //Set cursor to character 2 on line 0
          lcd.print("pass ");
          lcd.setCursor(5, 2);  //Set cursor to character 2 on line 0
          lcd.print(APSSID);
          lcd.setCursor(5, 3);  //Set cursor to character 2 on line 0
          lcd.print(APPSK);
        }
        //*************************lcd***************************
      } else if ( counterLcdPage == 1) {
        //*************************lcd***************************
        lcd.clear();                                         // Очищаем LCD дисплей
        for (int i = 0; i < 4; i++) {
          lcd.setCursor(0, i);
          releControl[i].nameRele.trim();
          String temp = String(i + 1) + "-" + releControl[i].nameRele;
          lcd.print(temp.substring(0, NUMBER_CHARS_NAME));
          lcd.setCursor(13, i);
          releControl[i].numberSensorControl < 255 && lcd.print(int(ds18b20EEprom[releControl[i].numberSensorControl].temp));
          lcd.setCursor(16, i);
          lcd.print(releControl[i].manualAuto ? "M" : "A");
          lcd.setCursor(18, i);
          lcd.print(digitalRead(releControl[i].numberPin) ? "OF" : "ON");
        }
      } else if ( counterLcdPage == 2) {
        //*************************lcd***************************
        lcd.clear();                                         // Очищаем LCD дисплей
        for (int i = 4, l = 0; i < 8; i++, l++) {
          lcd.setCursor(0, l);
          releControl[i].nameRele.trim();
          String temp = String(i + 1) + "-" + releControl[i].nameRele;
          lcd.print(temp.substring(0, NUMBER_CHARS_NAME));
          lcd.setCursor(13, i);
          releControl[i].numberSensorControl < 255 && lcd.print(int(ds18b20EEprom[releControl[i].numberSensorControl].temp));
          lcd.setCursor(16, l);
          lcd.print(releControl[i].manualAuto ? "M" : "A");
          lcd.setCursor(18, l);
          lcd.print(digitalRead(releControl[i].numberPin) ? "OF" : "ON");
        }
      } else if ( counterLcdPage == 3) {
          //Якщо на сторінці немає підключених сенсорів то її пропускаємо
        if (tempDs18b20EEprom[0].strAddress == "0000000000000000" && tempDs18b20EEprom[1].strAddress == "0000000000000000" && tempDs18b20EEprom[2].strAddress == "0000000000000000" && tempDs18b20EEprom[3].strAddress == "0000000000000000") {
          counterLcdPage < numLcdShowDisplay ?  counterLcdPage++ : counterLcdPage = 0;
          goto start;
        }
        lcd.clear();
        for (int i = 0; i < 4; i++) {
          if (tempDs18b20EEprom[i].tempNumberSensor != 100) {
            lcd.setCursor(0, i);
            tempDs18b20EEprom[i].nameSensor.trim();
            String temp = String(tempDs18b20EEprom[i].tempNumberSensor) + "-" + tempDs18b20EEprom[i].nameSensor;
            lcd.print(temp.substring(0, NUMBER_CHARS_NAME));
            lcd.setCursor(14, i);
            searchAddressSensor(tempDs18b20EEprom[i].strAddress) ? lcd.print(tempDs18b20EEprom[i].temp) : lcd.print("ERROR") ;
          }
        }
      } else if ( counterLcdPage == 4) {
        //Якщо на сторінці немає підключених сенсорів то її пропускаємо
        if (tempDs18b20EEprom[4].strAddress == "0000000000000000" && tempDs18b20EEprom[5].strAddress == "0000000000000000" && tempDs18b20EEprom[6].strAddress == "0000000000000000" && tempDs18b20EEprom[7].strAddress == "0000000000000000") {
          counterLcdPage < numLcdShowDisplay ?  counterLcdPage++ : counterLcdPage = 0;
          goto start;
        }
        lcd.clear();
        for (int i = 4, l = 0; i < 8; i++, l++) {
          if (tempDs18b20EEprom[i].tempNumberSensor != 100) {
            lcd.setCursor(0, l);
            tempDs18b20EEprom[i].nameSensor.trim();
            String temp = String(tempDs18b20EEprom[i].tempNumberSensor) + "-" + tempDs18b20EEprom[i].nameSensor;
            lcd.print(temp.substring(0, NUMBER_CHARS_NAME));
            lcd.setCursor(14, l);
            searchAddressSensor(tempDs18b20EEprom[i].strAddress) ? lcd.print(tempDs18b20EEprom[i].temp) : lcd.print("ERROR") ;
          }
        }
      } else if ( counterLcdPage == 5) {
          //Якщо на сторінці немає підключених сенсорів то її пропускаємо
        if (tempDs18b20EEprom[8].strAddress == "0000000000000000" && tempDs18b20EEprom[9].strAddress == "0000000000000000" && tempDs18b20EEprom[10].strAddress == "0000000000000000" && tempDs18b20EEprom[11].strAddress == "0000000000000000") {
          counterLcdPage < numLcdShowDisplay ?  counterLcdPage++ : counterLcdPage = 0;
          goto start;
        }
        lcd.clear();
        for (int i = 8, l = 0; i < 12; i++, l++) {
          if (tempDs18b20EEprom[i].tempNumberSensor != 100) {
            lcd.setCursor(0, l);
            tempDs18b20EEprom[i].nameSensor.trim();
            String temp = String(tempDs18b20EEprom[i].tempNumberSensor) + "-" + tempDs18b20EEprom[i].nameSensor;
            lcd.print(temp.substring(0, NUMBER_CHARS_NAME));
            lcd.setCursor(14, l);
            //Якщо в списку ненаходимо дійсно підключених датчиків то виводимо ERROR
            //
            searchAddressSensor(tempDs18b20EEprom[i].strAddress) ? lcd.print(tempDs18b20EEprom[i].temp) : lcd.print("ERROR") ;
//             searchAddressSensor(tempDs18b20EEprom[i].strAddress) ? lcd.print(tempDs18b20EEprom[i].temp) : tempDs18b20EEprom[i].strAddress == "0000000000000000" ? lcd.print("NONE") : lcd.print("ERROR") ;
          }
        }
      }
      flagShowCounter ? counterLcdPage  : (counterLcdPage < numLcdShowDisplay ?  counterLcdPage++ : counterLcdPage = 0);
    }
    //*************************************************************************************************************************************************

    //*************************************************************************************************************************************************
    static boolean searchAddressSensor(String addressSearch) {
      for (int m = 0; m < MAX_NUMBER_SENSOR; m++ ) {
        if (ds18b20[m].strAddress == addressSearch)return true;
      }
      return false;
    }
    //*************************************************************************************************************************************************

    //*************************************************************************************************************************************************
    static void connectMqttTopic() {
      if (!client.connected()) {
        if (client.connect(MQTT::Connect("Chexh_test")
                           .set_auth(mqtt_user, mqtt_pass)))
        {
          String ssid = WiFi.SSID();
          String localip = WiFi.localIP().toString();
          Serial.println("Connected to MQTT server secssesful");
          Serial.println(nameUser);
          Serial.println(mqtt_server);
          Serial.println(mqtt_port);
          Serial.println("Connected to MQTT server secssesful");

          lcd.setCursor(0, 2);
          lcd.print("Connected to MQTT");
          lcd.setCursor(0, 3);
          lcd.print("server secssesful");

          client.set_callback(callback);
          client.subscribe(nameUser + "_rele-temp");
          client.subscribe(nameUser + "_rele-all");
          client.subscribe(nameUser + "_start-data-sensor-eepromAndDevice");
          client.subscribe(nameUser + "_deviceSensorData");
          client.subscribe(nameUser + "_eepromSensorData");
          client.subscribe(nameUser + "_brouser_to_esp__hex_address_sensor_eeprom");
          client.subscribe(nameUser + "_flagRele");
          client.subscribe(nameUser + "_brouser_to_esp_rele_eprom_upr_set_number_sensor");
          client.subscribe(nameUser + "_brouser_to_esp_rele_erorr_vkl_vukl");
          client.subscribe(nameUser + "_brouser_to_esp_rele_set_one_or_two_range_temp");
          client.subscribe(nameUser + "_brouser_to_esp_rele__set_change_on_or_off");
          client.subscribe(nameUser + "_save-rele-name");
          client.subscribe(nameUser + "_brouser_to_esp_rele_get_eprom_upr_manual");
          client.subscribe(nameUser + "_brouser_to_esp_set_rele_vkl_otkl");
          client.subscribe(nameUser + "_brouser_to_esp_set-rele-data-time");
          client.subscribe(nameUser + "_brouser_to_esp_save_data_sensor_temp");
          client.subscribe(nameUser + "_define_device");
          client.subscribe(nameUser + "_resetFunction");
          client.subscribe(nameUser + "_get_name_device");
          client.subscribe(nameUser + "_cleareEPROM");

          client.publish(nameUser + "_ssid", ssid); // отправляем в топик для термодатчика значение температуры
          client.publish(nameUser + "_ip", localip); // отправляем в топик для термодатчика значение температуры
          client.publish("name_user_esp_wifi", nameUser); // отправляем в топик для термодатчика значение температуры
          client.publish(nameUser + "_ssid", ssid); // отправляем в топик для термодатчика значение температуры
          client.publish(nameUser + "_ip", localip); // отправляем в топик для термодатчика значение температуры
        }
        else
        {
          Serial.println("Could not connect to MQTT server");
          Serial.println(nameUser);
          Serial.println(mqtt_server);
          Serial.println(mqtt_port);
          Serial.println("Could not connect to MQTT server");

          lcd.setCursor(0, 2);
          lcd.print("Could not connect");
          lcd.setCursor(0, 3);
          lcd.print("to MQTT server");
        }
      }
    }
    //*************************************************************************************************************************************************


};


OtherFunction otherFanction;

//*************************************************************************************************************************************************
void controlPins() {
#ifdef ESP32
  counterPin_0 = controlPin( 0,  counterPin_0,  PIN_RELE_IN_0);
  counterPin_1 = controlPin( 1,  counterPin_1,  PIN_RELE_IN_1);
  counterPin_2 = controlPin( 2,  counterPin_2,  PIN_RELE_IN_2);
  counterPin_3 = controlPin( 3,  counterPin_3,  PIN_RELE_IN_3);
  counterPin_4 = controlPin( 4,  counterPin_4,  PIN_RELE_IN_4);
  counterPin_5 = controlPin( 5,  counterPin_5,  PIN_RELE_IN_5);
  counterPin_6 = controlPin( 6,  counterPin_6,  PIN_RELE_IN_6);
  counterPin_7 = controlPin( 7,  counterPin_7,  PIN_RELE_IN_7);
  counterPin_8 = controlPinRestart(counterPin_8,  PIN_RELE_IN_8 );
  if (counterPin_0 > 0 || counterPin_1 > 0 || counterPin_2 > 0 || counterPin_3 > 0 || counterPin_4 > 0 || counterPin_5 > 0 || counterPin_6 > 0 || counterPin_7 > 0 || counterPin_8 > 0) {
    disableScanerSensors = true;
  } else {
    disableScanerSensors = false;
  }
#endif
}
//*************************************************************************************************************************************************


//*************************************************************************************************************************************************
int controlPinRestart(int counterPin, byte pinConected) {

  if (analogRead(pinConected) > 1000) {

    //    if (counterPin > (connectedInternet ? 120 : 5)) {
    if (counterPin > 120) {
      if (EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT) > 0) { //if access point goto client
        EEPROM.write(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT, 0); //переходимо в точку доступа
        checkClientAccessPointRom = 0;
        Eeprom::comitEprom();
        //        OtherFunction::ledBlink(5, 300);
        //        Serial.println("connect to acess point");
        lcd.clear();                                         // Очищаем LCD дисплей
        lcd.setCursor(0, 0);
        lcd.print("Chenge device to");
        lcd.setCursor(0, 1);
        lcd.print("acess point");
        delay(1000);
        resetFunc(); //вызываем reset
      } else {//if client goto access point
        EEPROM.write(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT, 255); //переходимо в client
        checkClientAccessPointRom = 255;
        Eeprom::comitEprom();
        Serial.println("connect to client");
        //        OtherFunction::ledBlink(5, 300);
        lcd.clear();                                         // Очищаем LCD дисплей
        lcd.setCursor(0, 0);
        lcd.print("Chenge device to");
        lcd.setCursor(0, 1);
        lcd.print("wifi router");
        delay(1000);
        resetFunc(); //вызываем reset
      }

      EEPROM.write(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT, 0); //переходимо в точку доступа
      checkClientAccessPointRom = 0;
      Eeprom::comitEprom();
      Serial.println("connect to acess point");
      resetFunc(); //вызываем reset
    }

    Serial.print(analogRead(pinConected));
    Serial.print("  ++++++  ");
    Serial.println(counterPin);
    counterPin++;
    //*************************lcd***************************
    lcd.clear();                                         // Очищаем LCD дисплей
    lcd.setCursor(0, 0);
    lcd.print("counterPin");
    lcd.setCursor(0, 1);
    lcd.print(counterPin);
    //*************************lcd***************************
  } else {
    //    Serial.print(analogRead(pinConected));
    //    Serial.print("  -------  ");
    //    Serial.println(counterPin);
    counterPin = 0;
  }
  return counterPin;
}
//*************************************************************************************************************************************************


//*************************************************************************************************************************************************
int controlPin(byte numberRele, int counterPin, byte pinConected) {
  //  Serial.print("counterPin  ------------------------------------- ");
  //  Serial.println(counterPin);
  //    Serial.print("flagShowCounter  ------------------------------------- ");
  //  Serial.println(flagShowCounter);
  if (digitalRead(pinConected) == 1) {
    //    Serial.print("counterPin  ------------------------------------- ");
    //    Serial.println(counterPin);
    //    if (counterPin_0 == (connectedInternet ? 10 : 2) && counterPin_3 > 0 ) {
    if (counterPin_0 == 50 && counterPin_1 > 0 ) {
      counterLcdPage < numLcdShowDisplay ? counterLcdPage++ : counterLcdPage = 0;
      clearLcdChar();
      delay(300);
      flagShowCounter = true;
      //          prin("counterPin_0", counterPin_0);
      //          prin("counterPin_1", counterPin_1);
      return counterPin;


      //    } else if (counterPin_0 == (connectedInternet ? 10 : 2) && counterPin_2 > 0 ) {
    } else if (counterPin_0 == 50 && counterPin_2 > 0 ) {
      counterLcdPage  <= 0 ? counterLcdPage  = numLcdShowDisplay :  counterLcdPage--;
      clearLcdChar();
      delay(300);
      flagShowCounter = true;
      //          prin("counterPin_0", counterPin_0);
      //          prin("counterPin_1", counterPin_2);
      return counterPin;
      //    } else if (counterPin_0 == (connectedInternet ? 10 : 2) && counterPin_1 > 0 ) {
    } else if (counterPin_0 == 50 && counterPin_3 > 0 ) {
      clearLcdChar();
      delay(300);
      flagShowCounter = false;
      //          prin("counterPin_0", counterPin_0);
      //          prin("counterPin_1", counterPin_2);
      return counterPin;
      //    } else if (counterPin == (connectedInternet ? 20 : 4)) {
    } else if (counterPin == 100) {
      Serial.print("PIN_RELE_IN_2 ******************************************************************************  ");
      Serial.println(digitalRead(counterPin));
      releControl[numberRele].setManualAutoEEPROM(1, numberRele); //переводимо в ручний режим реле
      lcd.clear();                                         // Очищаем LCD дисплей
      lcd.setCursor(0, 0);
      String temp = "relay " + String(numberRele) + " manual mode";
      lcd.print(temp);

      if (digitalRead(releControl[numberRele].numberPin) == 0) { //Інвертуємо стан реле
        releControl[numberRele].setOnOffManualEEPROM(0, numberRele);
        Rele::manual_vklOtkl(releControl, 0, numberRele);//Виключаємо реле classRele.h
        lcd.setCursor(0, 1);
        lcd.print("Rele " + String(numberRele) + " OFF");
      } else {
        releControl[numberRele].setOnOffManualEEPROM(1, numberRele);
        Rele::manual_vklOtkl(releControl, 1, numberRele);// Включаємо реле classRele.h
        lcd.setCursor(0, 1);
        lcd.print("Rele " + String(numberRele) + " ON");
      }


      byte stanRele = 0;
      for (int i = 0; i < NUMBER_RELE; i++) {
        digitalRead(releControl[i].numberPin) == 0 ?  stanRele &= ~(1 << i) : stanRele |= (1 << i);//Формуємо маску бітів про стан кожного реле і відправляємо
      }
      client.publish(nameUser + "_stanRele", String(stanRele));
      //      client.publish(nameUser + "_rele-out-eprom_upr-manual", Rele::sendEEPROMDataToJSONSensor());//send name rele
      Rele::sendStanReleManualAuto(releControl);
      delay(1000);
      counterPin++;
      //    } else if (counterPin == (connectedInternet ? 30 : 6)) {
    } else if (counterPin == 250) {
      releControl[numberRele].setManualAutoEEPROM(0, numberRele); //переводимо в автоматичний режим реле
      //          client.publish(nameUser + "_rele-out-eprom_upr-manual", Rele::sendEEPROMDataToJSONSensor());//send name rele
      Rele::sendStanReleManualAuto(releControl);
      lcd.clear();                                         // Очищаем LCD дисплей
      lcd.setCursor(0, 0);

      String temp = "relay " + String(numberRele) + " in automatic";
      lcd.print(temp);
      delay(1000);


      counterPin++;
    } else {
      counterPin++;
    }

  } else if (digitalRead(pinConected) == 0 && counterPin > 0) {
    counterPin = 0;
  }
  return counterPin;
}
//*************************************************************************************************************************************************


//*************************************************************************************************************************************************
void refreshData() {
  TimerDate::readTimerEEPROMToObjeckt(dataAndTime);
  Sensor::readSensorsAddressTemp(ds18b20); //читаємо в обєкт DS18B20 адреса і температуру датчиків що є підключенні до контроллера
  Sensor::readEepromDataSensor(ds18b20EEprom); //читаємо імя, address і температуру з памяті ЕЕПРОМ  в обєкт ds18b20EEprom що є вибрані в програмі
  Sensor::searchCodeSennsorInEEPROM(ds18b20EEprom, ds18b20);//Записуємо температуру в EEPROM sensory з реальних датчиків

  Rele::readEepromNameRele(releControl);//читаємо address з памяті ЕЕПРОМ в обєкт releControl

  //  if (loopRefresh == 0) {
  //    //    TimerDate::sendDateTime(dataAndTime);
  //    loopRefresh = 2;
  //  }
  //
  //  loopRefresh--;

  //читаємо температури включення і відключення
  for (int i = START_SECTION_EEPROM_TEMP_ON_OFF, n = 0; i < START_SECTION_EEPROM_TEMP_ON_OFF + 16; i += 2, n++)
  {
    ds18b20[n].tempVkl = EEPROM.read(i) - 50;
    ds18b20[n].tempOtkl = EEPROM.read(i + 1) - 50;
  }

  for (int i = 0; i < 8; i++)
  {
    releControl[i].numberSensorControl = releControl[i].getNumberSensorControlEEPROM(i);
    prin("numberSensorControl++++++++++++++++++   ", releControl[i].numberSensorControl);

    releControl[i].bit4OneOrTwoRange = releControl[i].getOneOrTwoRangeEEPROM(i);
    releControl[i].bit5OnOffChange = releControl[i].getOnOffChangeEEPROM(i);
    releControl[i].bit6ReleError = releControl[i].getReleErrorEEPROM(i);
    releControl[i].manualAuto = releControl[i].getManualAutoEEPROM(i);
    releControl[i].onOffManual = releControl[i].getOnOffManualEEPROM(i);
    ds18b20EEprom[i].tempVkl =  EEPROM.read(START_SECTION_EEPROM_TEMP_ON_OFF + i * 2) - 50;
    ds18b20EEprom[i].tempOtkl =  EEPROM.read(START_SECTION_EEPROM_TEMP_ON_OFF + i * 2 + 1) - 50;
  }
}

//*************************************************************************************************************************************************









//*************************************************************************************************************************************************
void sendPostRequest() {
  //  const char* serverName = "https://635d74d2ea764497f0dd237e.mockapi.io/cart";
  const char* serverName = "https://635d74d2ea764497f0dd237e.mockapi.io/cart";
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    // Your Domain name with URL path or IP address with path
    http.begin(serverName);

    // If you need Node-RED/server authentication, insert user and password below
    //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");

    // Specify content-type header
    //      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    // Data to send with HTTP POST
    //      String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&value1=24.25&value2=49.54&value3=1005.14";
    // Send HTTP POST request
    //      int httpResponseCode = http.POST(httpRequestData);

    // If you need an HTTP request with a content type: application/json, use the following:
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST("{\"api_key\":\"tPmAT5Ab3j7F9\",\"sensor\":\"BME280\",\"value1\":\"24.25\",\"value2\":\"49.54\",\"value3\":\"1005.14\"}");

    // If you need an HTTP request with a content type: text/plain
    //http.addHeader("Content-Type", "text/plain");
    //int httpResponseCode = http.POST("Hello, World!");

    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}

void sendGetRequest() {
  //  const char* serverName = "https://635d74d2ea764497f0dd237e.mockapi.io/cart";
  const char* serverName = "https://635d74d2ea764497f0dd237e.mockapi.io/sneakers";
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  //Объявите объект класса HttpClient

    http.begin(serverName);  //Укажите адрес назначения запроса
    int httpCode = http.GET();                                  //Отправьте запрос

    if (httpCode > 0) { //Проверьте код возврата

      String payload = http.getString();   //Получите полезную нагрузку для ответа на запрос
      Serial.println(payload);             //Распечатайте полезную нагрузку ответа

    }

    http.end();   //Закрыть соединение
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}

//*************************************************************************************************************************************************
