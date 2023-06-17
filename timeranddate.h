

class TimerDate {
  public:
    word delaySecondStart;
    unsigned long data_datamiliseconds[10];
    word data_rik[10];
    byte data_months[10];
    byte data_dey[10];
    byte data_godyna[10];
    byte data_minut[10];
    byte data_daywikend[10];
    byte godyna[50];
    byte minut[50];
    byte dey[35];
    static byte currentRelay;


    //    static void sendDateTime(TimerDate dataAndTime[]) {  //refreshobjectToJsonDate
    //      TimerDate::readTimerEEPROMToObjeckt(dataAndTime)();
    //      //  for (int i = 0; i < NUMBER_RELE; i++) {
    //      //    for (byte numPak = 1; numPak < 5; numPak++) {
    //      //      client.publish(nameUser + "_esp_to_brouser_rele_data_time", objectToJsonDate(i, numPak));
    //      ////      prin(objectToJsonDate(i, numPak));
    //      //    }
    //      //  }
    //
    //      client.publish(nameUser + "_esp_to_brouser_rele_data_time_all", objectToJsonDateArray(dataAndTime));
    //    }

    //*************************************************************************************************************************************************
    static String objectToJsonDateArray(TimerDate dataAndTime[]) {//Відправляємо всі дати і години таймерів
      String json;
      DynamicJsonDocument doc(32000);
      const word NumberElementDate = 10;

      int counter = 0;
      for (int i = 0; i < NUMBER_RELE; i++) {
        // dateTimeInput[0].value = "2022-05-02T12:55";
        for (int k = 0; k < NumberElementDate; k++) {
          doc["DATATIME"][counter] = String(dataAndTime[i].data_rik[k]) + "-" + addZero(dataAndTime[i].data_months[k]) + "-" + addZero(dataAndTime[i].data_dey[k]) + "T" + addZero(dataAndTime[i].data_godyna[k]) + ":" + addZero(dataAndTime[i].data_minut[k]);
          counter++;
        }
      }
      const word NumberElementTime = 50;
      counter = 0;
      for (int i = 0; i < NUMBER_RELE; i++) {
        for (int k = 0; k < NumberElementTime; k++) {
          doc["TIME"][counter] = addZero(dataAndTime[i].godyna[k]) + ":" + addZero(dataAndTime[i].minut[k]);
          counter++;
        }
      }
      const word NumberElementDay = 35;
      counter = 0;
      for (int i = 0; i < NUMBER_RELE; i++) {
        for (int k = 0; k < NumberElementDay; k++) {
          doc["DEY"][counter] = dataAndTime[i].dey[k];
          counter++;
        }
      }

      serializeJson(doc, json);
       doc.clear();
//      prin("OUTPUT LENGTH", json.length());
//      prin("OUTPUT LENGTH", json);
      return json;
    }
    //*************************************************************************************************************************************************

    //*************************************************************************************************************************************************
    static String objectToJsonDate(TimerDate dataAndTime , byte num) {//Відправляємо  дати і години таймерів для конкретного реле
      String json;
      DynamicJsonDocument doc(2000);
      const word NumberElementDate = 10;


      doc["NUM"] = num;
      doc["DELAYSECONDSTART"] = String(dataAndTime.delaySecondStart);
      for (int k = 0; k < NumberElementDate; k++) {
        doc["DATATIME"][k] = String(dataAndTime.data_rik[k]) + "-" + addZero(dataAndTime.data_months[k]) + "-" + addZero(dataAndTime.data_dey[k]) + "T" + addZero(dataAndTime.data_godyna[k]) + ":" + addZero(dataAndTime.data_minut[k]);
      }
      const word NumberElementTime = 50;
      for (int k = 0; k < NumberElementTime; k++) {
        doc["TIME"][k] = addZero(dataAndTime.godyna[k]) + ":" + addZero(dataAndTime.minut[k]);
      }
      const word NumberElementDay = 35;
      for (int k = 0; k < NumberElementDay; k++) {
        doc["DEY"][k] = dataAndTime.dey[k];
      }

      serializeJson(doc, json);
       doc.clear();
      //  ////prin("OUTPUT LENGTH", json.length());
      //  //prin("OUTPUT LENGTH", json);
      return json;
    }
    //*************************************************************************************************************************************************

  public:
    static void writeEepromObjectDataTimeSendBrouser(TimerDate dataAndTime[], String json) {
      //prin("SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS", json);

      //{"RELE":3,
      //"delaySecondStart":"0",
      //"dataTime":[{"DM":1684002600,"Y":2023,"M":4,"D":13,"H":20,"MI":30,"T":6},{"DM":1684693800,"Y":2023,"M":4,"D":21,"H":20,"MI":30,"T":0},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"}],
      //"Time":[{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"H":22,"MI":30},{"H":23,"MI":33},
      //{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},
      //{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},
      //{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"}],
      //"today":[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]}

      //{"rele":0,"default":"default"}//Очищаємо всі значення для таймерів

      dataTimeJsonToObject(json,  dataAndTime);//Записуємо в  обєкт dataAndTime по індексу який приходить в строці json для конкретного реле
      EEPROM.put(START_SECTION_EEPROM_TIMERDATE + (sizeof(TimerDate) * TimerDate::currentRelay), dataAndTime[TimerDate::currentRelay]); // write objeck to EEPROM
      Eeprom::comitEprom();
      TimerDate::readTimerEEPROMToObjeckt(dataAndTime);
       if (EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT) > 0)  
       client.publish(nameUser + "_esp_to_brouser_rele_data_time", TimerDate::objectToJsonDate(dataAndTime[TimerDate::currentRelay], TimerDate::currentRelay)); // client
     
    }
     

    //*************************************************************************************************************************************************
    static  void dataTimeJsonToObject(String json, TimerDate dataAndTime[]) {//Записуємо в  обєкт dataAndTime по індексу який приходить в строці json для конкретного реле
      DynamicJsonDocument doc(4000);
      deserializeJson(doc, json);
      byte _currentRelay =  doc["RELE"];
      prin("json", json);
      prin("currentRelay  128  ******************* ",_currentRelay);
      TimerDate::currentRelay = _currentRelay;
      word delaySecondStart = doc["delaySecondStart"];
      for (byte i = 0; i < 10; i++) {
        if (doc["dataTime"][i]["N"] || doc["default"]) {
          dataAndTime[_currentRelay].data_datamiliseconds[i] = 4294967295;
          dataAndTime[_currentRelay].data_rik[i] = 65535;
          dataAndTime[_currentRelay].data_months[i] = 99;
          dataAndTime[_currentRelay].data_dey[i] = 99;
          dataAndTime[_currentRelay].data_godyna[i] = 99;
          dataAndTime[_currentRelay].data_minut[i] = 99;
          dataAndTime[_currentRelay].data_daywikend[i] = 99;
        } else {
          dataAndTime[_currentRelay].data_datamiliseconds[i] = doc["dataTime"][i]["DM"];
          dataAndTime[_currentRelay].data_rik[i] = doc["dataTime"][i]["Y"];
          dataAndTime[_currentRelay].data_months[i] = doc["dataTime"][i]["M"];
          dataAndTime[_currentRelay].data_dey[i] = doc["dataTime"][i]["D"];
          dataAndTime[_currentRelay].data_godyna[i] = doc["dataTime"][i]["H"];
          dataAndTime[_currentRelay].data_minut[i] = doc["dataTime"][i]["MI"];
          dataAndTime[_currentRelay].data_daywikend[i] = doc["dataTime"][i]["T"];
        }
      }

      for (byte i = 0; i < 50; i++) {
        if (doc["Time"][i]["N"] || doc["default"]) {
          dataAndTime[_currentRelay].godyna[i] = 99;
          dataAndTime[_currentRelay].minut[i] = 99;
        } else {
          dataAndTime[_currentRelay].godyna[i] = doc["Time"][i]["H"];
          dataAndTime[_currentRelay].minut[i] = doc["Time"][i]["MI"];
        }
      }

      for (byte i = 0; i < 35; i++) {
        if (!doc["default"]) {
          dataAndTime[_currentRelay].dey[i] = doc["today"][i];
        } else {
          dataAndTime[_currentRelay].dey[i] = 1;
        }
      }
       doc.clear();

    }
    //*************************************************************************************************************************************************


    //*************************************************************************************************************************************************
    static void readTimerEEPROMToObjeckt(TimerDate dataAndTime[]) { // Читаємо дані з памяті еепром в обєкт
      for (int i = 0; i < 8; i++) {
        EEPROM.get(START_SECTION_EEPROM_TIMERDATE + (sizeof(TimerDate)*i) , dataAndTime[i]);
      }
    }
    //*************************************************************************************************************************************************


    //*************************************************************************************************************************************************
  private:
    static String addZero(byte number) {
      //добавляє до місяця, дня,  години або хвилини 0 з переді якщо число менше 10
      if (number > 9)
      {
        return  String(number);
      } else {
        return  "0" + String(number);
      }
    }
    //*************************************************************************************************************************************************

};

byte TimerDate::currentRelay;
TimerDate dataAndTime[NUMBER_RELE];
