


void kontr_temp()
{
  byte ChangeLow, ChangeHIGH;
  //  Serial.print(" СonnectedInternet ");
  //  Serial.println(connectedInternet);
  Serial.println();
  Serial.println();
  Serial.println("disableScanerSensors");
  Serial.println(disableScanerSensors);
  Serial.println();
  Serial.println();
  if (EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT) > 0)getDate = GetDate::getDateTime(); // client
  printObjectTime();

  //  Sensor::readSensorsAddressTemp(ds18b20); //читаємо в обєкт DS18B20 адреса і температуру датчиків що є підключенні до контроллера
  //  Sensor::readEepromDataSensor(ds18b20EEprom); //читаємо імя, address і температуру з памяті ЕЕПРОМ  в обєкт ds18b20EEprom що є вибрані в програмі
  //  Sensor::searchCodeSennsorInEEPROM(ds18b20EEprom, ds18b20);//Записуємо температуру в EEPROM sensory з реальних датчиків


  if (!disableScanerSensors)Sensor::sendSensorData(ds18b20EEprom, ds18b20); //при нажиманні на кнопки віключаємо сканування сенсора

  //  Serial.print("nameSensor ");
  //  Serial.print(ds18b20EEprom[0].nameSensor);
  //  Serial.print(" strAddress ");
  //  Serial.print(ds18b20EEprom[0].strAddress);
  //  Serial.print(" temp  ");
  //  Serial.println(ds18b20EEprom[0].temp);

  byte  stanRele = 0;
  //  Serial.println();
  //  Serial.println();
  for (int numberRele = 0; numberRele < NUMBER_RELE; numberRele++)// перебираємо всі реле
  {
    if (releControl[numberRele].manualAuto == 0) {
      //Якщо неручний режим
      //********************Реверс реле************************
      if (releControl[numberRele].bit5OnOffChange == 0) {//Реверс реле
        ChangeLow = 1;
        ChangeHIGH = 0;
      } else if (releControl[numberRele].bit5OnOffChange == 1) {
        ChangeLow = 0;
        ChangeHIGH = 1;
      }
      //      prin("releControl[numberRele].numberSensorControl", releControl[numberRele].numberSensorControl);
      //********************Реверс реле**************************************************************************
      //      prin("releNumber", numberRele);
      //      prin("releControl[numberRele].numberSensorControl", releControl[numberRele].getNumberSensorControlEEPROM(numberRele) );
      //********************CONTROL TERMO SENSOR************************
      if ( releControl[numberRele].getNumberSensorControlEEPROM(numberRele) < 255 )//Якщо керуємо термодатчиком то в змінну буле записано номер термодатчика від 0 до 8 замість числа 15 - неуправляємо нічим
      {
        //Превірка чи підключений термодатчик яким управляємо реле, що записаний в памяті EEPROM

        boolean flag = true;
        for (int k = 0; k < Sensor::deviceCountSensor; k++) {
          if (ds18b20EEprom[releControl[numberRele].numberSensorControl].strAddress == ds18b20[k].strAddress) { //Найдено сенсор який є в памяті EEPROM
            //            Serial.print("Kontrol sensor rele ");
            //            Serial.println(numberRele);
            releControl[numberRele].errorSensor = false;
            //prin("ds18b20[k].temp", ds18b20[k].temp);
            //prin("ds18b20[numberRele].tempVkl", ds18b20[numberRele].tempVkl);
            //prin("ds18b20[numberRele].tempOtkl", ds18b20[numberRele].tempOtkl);
            if (releControl[numberRele].bit4OneOrTwoRange == 0) {//Один діапазон
              releControl[numberRele].flagsTermo = ds18b20[k].temp > ds18b20[numberRele].tempVkl;
            } else if (releControl[numberRele].bit4OneOrTwoRange == 1) {//Два діапазони
              releControl[numberRele].flagsTermo = ds18b20[k].temp > ds18b20[numberRele].tempVkl && ds18b20[k].temp < ds18b20[numberRele].tempOtkl;
            }
            //prin("releControl[numberRele].flagsTermo contr Temp 81", releControl[numberRele].flagsTermo);
            break;
          } else {
            //            Serial.print("NOT SENSOR ");
            //            Serial.println(numberRele);
            releControl[numberRele].errorSensor = true;
          }
        }
        //      if (flag)Serial.println("Send messeg not sensor");
      }
      else {
      }
      //********************CONTROL TERMO SENSOR************************

      boolean  timersFlagSections[5]  {false, false, false, false, false};
      //**********************************************************************************
      for (byte numberDataTime = 0; numberDataTime < 9; numberDataTime += 2  ) { //numberDataTime 0 2 4 6 8     0 10 20 30 40

        if (dataAndTime[numberRele].data_datamiliseconds[numberDataTime] != 4294967295  &&  dataAndTime[numberRele].godyna[numberDataTime * 5] < 24)//Якщо в секції вибрано і  дата і година
        {
//          prin("NUMBER RELE selesct data and time", numberRele);
//          prin("data and time");


          timersFlagSections[numberDataTime / 2] = GetDate::controlRangeDate(getDate, numberRele, numberDataTime) && GetDate::controlRangeHour(getDate, numberRele, numberDataTime);

        } else if (dataAndTime[numberRele].data_datamiliseconds[numberDataTime] != 4294967295)//Якщо в секції вибрана дата
        {
//          prin("NUMBER RELE selesct data and time", numberRele);
//          prin("data");
//          prin("controlRangeDate(numberRele, numberDataTime)", GetDate::controlRangeDate(getDate, numberRele, numberDataTime));
//          prin("GetDate::controlRangeHour(getDate, numberRele, numberDataTime)", GetDate::controlRangeDate(getDate, numberRele, numberDataTime));
          timersFlagSections[numberDataTime / 2] = GetDate::controlRangeDate(getDate, numberRele, numberDataTime);
        } else if (dataAndTime[numberRele].godyna[numberDataTime * 5] != 99) //Якщо в секції вибрана година
        {
          //          prin("GetDate::controlRangeHour(getDate, numberRele, numberDataTime );", GetDate::controlRangeHour(getDate, numberRele, numberDataTime ));
          timersFlagSections[numberDataTime / 2] = GetDate::controlRangeHour(getDate, numberRele, numberDataTime );
        } else
        {
          //            releControl[numberRele].timerControl = 0;
        }
        //Провіряємо флаги всіх блоків даного реле і якщо хоща б один дорівнює true то  flagsTimer = true
        releControl[numberRele].flagsTimer = timersFlagSections[0] ||  timersFlagSections[1] ||  timersFlagSections[2] ||  timersFlagSections[3] ||  timersFlagSections[4];

      }
      //**********************************************************************************

      //**********************************************************************************

      releControl[numberRele].timerControl = dataAndTime[numberRele].data_datamiliseconds[0] != 4294967295 ||
                                             dataAndTime[numberRele].data_datamiliseconds[2] != 4294967295 ||
                                             dataAndTime[numberRele].data_datamiliseconds[4] != 4294967295 ||
                                             dataAndTime[numberRele].data_datamiliseconds[6] != 4294967295 ||
                                             dataAndTime[numberRele].data_datamiliseconds[8] != 4294967295 ||
                                             dataAndTime[numberRele].godyna[0] < 24 ||
                                             dataAndTime[numberRele].godyna[10] < 24 ||
                                             dataAndTime[numberRele].godyna[20] < 24 ||
                                             dataAndTime[numberRele].godyna[30] < 24 ||
                                             dataAndTime[numberRele].godyna[40] < 24;
      //**********************************************************************************

      //      prin("releControl[numberRele].timerControl", releControl[numberRele].timerControl);



      //********************CONTROL TIMER*******************************

      //********************CONTROL DELAY*******************************
      //      if (releControl[numberRele].timerControl > 0 )//Затримка при включенні якщо значення паузи 0 то постфйно включене якщо ні то чекаємо
      //      {
      //        releControl[numberRele].flagsTimer = false;
      //      }
      //********************CONTROL DELAY*******************************

      //********************CONTROL FLAGS*******************************
      if (releControl[numberRele].numberSensorControl < 255 && releControl[numberRele].timerControl == 1)   //Якщо реле регул двома
      {
        //        Serial.println("CONTROL  TIME AND SENSOR::::::::::::  ");
        //        Serial.println("numberSensorControl::::::::::::  ");
        //        Serial.println(releControl[numberRele].numberSensorControl);
        //        Serial.println("CONTROL  TIME AND SENSOR::::::::::::  ");

        if (!releControl[numberRele].errorSensor  && connectedInternet) {// Якщо датчик присутній  і є година з інтернету
          if (releControl[numberRele].flagsTermo &&  releControl[numberRele].flagsTimer) {
            digitalWrite(releControl[numberRele].numberPin, ChangeLow);
          } else {
            digitalWrite(releControl[numberRele].numberPin, ChangeHIGH);
          }
        } else {// Якщо датчик помилка
          if (releControl[numberRele].bit6ReleError == 1)
            digitalWrite(releControl[numberRele].numberPin, ChangeLow);
          else if (releControl[numberRele].bit6ReleError == 0)
            digitalWrite(releControl[numberRele].numberPin, ChangeHIGH);
        }

      } else if (releControl[numberRele].numberSensorControl < 255) {   //Якщо реле регул termo
        //        Serial.println("CONTROL  SENSOR ::::::::::::  ");

        if (!releControl[numberRele].errorSensor) {// Якщо датчик присутній
          if (releControl[numberRele].flagsTermo) {
            digitalWrite(releControl[numberRele].numberPin, ChangeLow);
          } else {
            digitalWrite(releControl[numberRele].numberPin, ChangeHIGH);
          }
        } else {// Якщо датчик помилка
          if (releControl[numberRele].bit6ReleError == 1)
            digitalWrite(releControl[numberRele].numberPin, ChangeLow);
          else if (releControl[numberRele].bit6ReleError == 0)
            digitalWrite(releControl[numberRele].numberPin, ChangeHIGH);
        }
      } else if (releControl[numberRele].timerControl == 1) {   //Якщо реле регул timer
        if (connectedInternet) {// Якщо є година з інтернету
          //          Serial.println("CONTROL  TIME ::::::::::::  ");
          //          prin("releControl[numberRele].flagsTimer", releControl[numberRele].flagsTimer);
          if (releControl[numberRele].flagsTimer) {
            digitalWrite(releControl[numberRele].numberPin, ChangeLow);
          } else {
            digitalWrite(releControl[numberRele].numberPin, ChangeHIGH);
          }
        } else {// Якщо година з інтернету помилка непрацює інтернет
          if (releControl[numberRele].bit6ReleError == 1)
            digitalWrite(releControl[numberRele].numberPin, ChangeLow);
          else if (releControl[numberRele].bit6ReleError == 0)
            digitalWrite(releControl[numberRele].numberPin, ChangeHIGH);
        }
      } else { //Якщо реле нічого не регулює то ми його відключаємо
        //        Serial.println("NOT CONTROL RELE ::::::::::::  ");
        digitalWrite(releControl[numberRele].numberPin, 1);
      }
      //********************CONTROL FLAGS*******************************
      //        deleteAndMovingSection(numberRele);// Очистка пустої або простроченої дати
      //      Serial.println();
      //      Serial.println("*********************************************************");
    } else { //при ручному режимі
      //      Serial.print(" MANUAL MANUAL  ");
      if (releControl[numberRele].onOffManual == 0)
        digitalWrite(releControl[numberRele].numberPin, 1);
      else
        digitalWrite(releControl[numberRele].numberPin, 0);
    }
    digitalRead(releControl[numberRele].numberPin) == 0 ?  stanRele &= ~(1 << numberRele) : stanRele |= (1 << numberRele);//Для кожного реле читаємо в якому воно стані і записуємо певний біт
    //    digitalRead(releControl[numberRele].numberPin) == 0 ? releControl[numberRele].setOnOffManualEEPROM(1, numberRele) : releControl[numberRele].setOnOffManualEEPROM(0, numberRele);
  }

  //  Serial.println();
  //  Serial.println();
  //Відправляємо стани всіх реле
  //  client.publish(nameUser + "_stanRele", String(stanRele));
  Rele::sendStanReleOnOff(releControl);
  if (EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT) > 0)client.publish(nameUser + "analogInputA0", String(analogRead(A0))); // client
  //  Serial.print(" stanRele>>>>>>>>>>>><<<<<<<<<<<  ");
  //  Serial.println(stanRele, BIN);
}
