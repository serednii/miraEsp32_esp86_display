//void TimerDate::readTimerEEPROMToObjeckt(dataAndTime)();

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
    static byte numberRele;


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
    static String objectToJsonDateArray(TimerDate dataAndTime[]) {
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
      prin("OUTPUT LENGTH", json.length());
      prin("OUTPUT LENGTH", json);
      return json;
    }
    //*************************************************************************************************************************************************

    //*************************************************************************************************************************************************
    static String objectToJsonDate(TimerDate dataAndTime , byte num) {
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
      //  prin("OUTPUT LENGTH", json.length());
      //  prin("OUTPUT LENGTH", json);
      return json;
    }
    //*************************************************************************************************************************************************


    //*************************************************************************************************************************************************
    static  void dataTimeJsonToObject(String json, TimerDate dataAndTime[]) {
      DynamicJsonDocument doc(2000);
      deserializeJson(doc, json);
      byte numberRele =  doc["rele"];
      TimerDate::numberRele = numberRele;
      word delaySecondStart = doc["delaySecondStart"];
      for (byte i = 0; i < 10; i++) {
        if (doc["dataTime"][i]["N"] || doc["default"]) {
          dataAndTime[numberRele].data_datamiliseconds[i] = 4294967295;
          dataAndTime[numberRele].data_rik[i] = 65535;
          dataAndTime[numberRele].data_months[i] = 99;
          dataAndTime[numberRele].data_dey[i] = 99;
          dataAndTime[numberRele].data_godyna[i] = 99;
          dataAndTime[numberRele].data_minut[i] = 99;
          dataAndTime[numberRele].data_daywikend[i] = 99;
        } else {
          dataAndTime[numberRele].data_datamiliseconds[i] = doc["dataTime"][i]["DM"];
          dataAndTime[numberRele].data_rik[i] = doc["dataTime"][i]["Y"];
          dataAndTime[numberRele].data_months[i] = doc["dataTime"][i]["M"];
          dataAndTime[numberRele].data_dey[i] = doc["dataTime"][i]["D"];
          dataAndTime[numberRele].data_godyna[i] = doc["dataTime"][i]["H"];
          dataAndTime[numberRele].data_minut[i] = doc["dataTime"][i]["MI"];
          dataAndTime[numberRele].data_daywikend[i] = doc["dataTime"][i]["T"];
        }
      }

      for (byte i = 0; i < 50; i++) {
        if (doc["Time"][i]["N"] || doc["default"]) {
          dataAndTime[numberRele].godyna[i] = 99;
          dataAndTime[numberRele].minut[i] = 99;
        } else {
          dataAndTime[numberRele].godyna[i] = doc["Time"][i]["H"];
          dataAndTime[numberRele].minut[i] = doc["Time"][i]["MI"];
        }
      }

      for (byte i = 0; i < 35; i++) {
        if (!doc["default"]) {
          dataAndTime[numberRele].dey[i] = doc["today"][i];
        } else {
          dataAndTime[numberRele].dey[i] = 1;
        }
      }
      printObjectTime();

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


    //*************************************************************************************************************************************************
    //static void clearEepromDate(byte relayNumber) {
    //  byte x = 99;
    //  dataAndTime[relayNumber].delaySecondStart = 65535;
    //  for (int i = 0; i < 10; i++) {
    //    dataAndTime[relayNumber].data_datamiliseconds[i] = 4294967295;
    //    dataAndTime[relayNumber].data_rik[i] = 65535;
    //    dataAndTime[relayNumber].data_months[i] = x;
    //    dataAndTime[relayNumber].data_dey[i] = x;
    //    dataAndTime[relayNumber].data_godyna[i] = x;
    //    dataAndTime[relayNumber].data_minut[i] = x;
    //    dataAndTime[relayNumber].data_daywikend[i] = x;
    //  }
    //
    //  for (int i = 0; i < 50; i++) {
    //    dataAndTime[relayNumber].godyna[i] = x;
    //    dataAndTime[relayNumber].minut[i] = x;
    //  }
    //
    //  for (int i = 0; i < 35; i++) {
    //    dataAndTime[relayNumber].dey[i] = x;
    //  }
    //
    //  EEPROM.put(START_SECTION_EEPROM_TIMERDATE + (sizeof(TimerDate)*relayNumber), dataAndTime[relayNumber]); //write objeck to EEPROM
    //  Eeprom::comitEprom();
    //}
    //*************************************************************************************************************************************************



};

byte TimerDate::numberRele;
TimerDate dataAndTime[NUMBER_RELE];




//*************************************************************************************************************************************************


//*************************************************************************************************************************************************


//*************************************************************************************************************************************************
