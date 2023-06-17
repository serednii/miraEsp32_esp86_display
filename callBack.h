//--------------------------------------callback--------------------------------
//------------------------------------------------------------------------------
void callback(const MQTT::Publish &pub) //було
{
  prin("*************************************************************************************************************************************************");
  Serial.print(pub.topic()); // выводим в сериал порт название топика
  Serial.print(" => ");
  Serial.println(pub.payload_string()); // выводим в сериал порт значение полученных данных
  String payload = pub.payload_string();
  prin("*************************************************************************************************************************************************");

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_resetFunction") // перегрузка чипа
  {
    if (payload == "resetFunction")
      resetFunc(); //вызываем reset });
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_cleareEPROM") // перегрузка чипа
  {
    // 0001-4096-255
    if (payload == "ff")
      for (int i = 1; i < 4096; i++)
      {
        EEPROM.write(i, 255);
      }
    if (payload == "00")
      for (int i = 1; i < 4096; i++)
      {
        EEPROM.write(i, 0);
      }
    Eeprom::comitEprom();
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_define_device") ////Приводимо в початковий стан всі змінні
  {
    Serial.print("GET mesage setDefineDevice  ----  ");
    //    Serial.println(payload);
    sendPostRequest();
    sendGetRequest();
    OtherFunction::defineDevice();//Приводимо в початковий стан всі змінні
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_get_name_device") // получаєм нове імя приистрою
  {
    //    EEPROM_ADRESS_NAME_DEVICE
    if (payload.length() > 0 && payload.length() < 20)
    {
    }
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_brouser_to_esp_set-rele-data-time") //прийом дати і часу
  {
    //{"RELE":3,
    //"delaySecondStart":"0",
    //"dataTime":[{"DM":1684002600,"Y":2023,"M":4,"D":13,"H":20,"MI":30,"T":6},{"DM":1684693800,"Y":2023,"M":4,"D":21,"H":20,"MI":30,"T":0},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"}],
    //"Time":[{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"H":22,"MI":30},{"H":23,"MI":33},
    //{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},
    //{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},
    //{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"},{"N":"N"}],
    //"today":[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]}
    TimerDate::writeEepromObjectDataTimeSendBrouser(dataAndTime, payload);
    kontr_temp();
    return;
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_start-data-sensor-eepromAndDevice") //при запросі відправити в топік адреса EEPROM i реальних датчиків
  {
    //    prin("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx0000000000000000000000000");
    //    refreshData();
    //    kontr_temp();

    //-------------------------------------------------------------------------

    if (payload == "ReadDate" || payload == "ALL") //NO
    {
      prin("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%$$$$$$$$$$$$$$$$$$$$$$$$$");
      prin(String(sizeof(TimerDate)));
      TimerDate::readTimerEEPROMToObjeckt(dataAndTime);
      client.publish(nameUser + "_esp_to_brouser_rele_data_time_all", TimerDate::objectToJsonDateArray(dataAndTime));
      //    prin(TimerDate::sendDateTime(dataAndTime));
      //    prin("TimerDate::sendDateTime(dataAndTime) 111111111111111111111");
    }

    //****************************************************************************************************

    if (payload == "readAddressSensor" || payload == "ALL") //OK
    {
      Sensor::sendSensorData(ds18b20EEprom, ds18b20);
      //{"obj":[{"number": 0, "address": "0000000000000000", "temp": 0.00}]}
      //{"obj":[{"number": 0, "address": "28ff6402e248ff11", "temp": 24.50}]}
      //      prin("readAddressSensor WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
    }

    //****************************************************************************************************
    //    if (payload == "NameSensor" || payload == "ALL")  //На видалення дані передаються через readAddressSensor  Sensor::sendSensorData(ds18b20EEprom, ds18b20);
    //    {
    //                client.publish(nameUser + "_sensor-name", ds18b20EEpromToJSONnameSensor());
    //      // {"obj":[{"nameSensor": "cherpadl"},{"nameSensor": "kuxyn"},{"nameSensor": "sddff"},{"nameSensor": "name4"},{"nameSensor": "name5"},{"nameSensor": "name6"},{"nameSensor": ""},{"nameSensor": ""}]}
    //      //      prin("NameSensor WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
    //    }

    //-------------------------------------------------------------------------

    if (payload == "ReadTempVklOtkl" || payload == "ALL")
    {
      client.publish(nameUser + "_sensor-vkl-otkl", Rele::releOnOffEEPROMDataToJSON()); // send temp on temp off
      //      {"obj":[{"vkl": 25,"otkl": 30},{"vkl": 25,"otkl": 30},{"vkl": 25,"otkl": 30},{"vkl": 25,"otkl": 30},{"vkl": 25,"otkl": 30},{"vkl": 25,"otkl": 30},{"vkl": 25,"otkl": 30},{"vkl": 25,"otkl": 30}]}
      //      prin("Rele::releOnOffEEPROMDataToJSON WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
      //      prin(Rele::releOnOffEEPROMDataToJSON());
    }

    //****************************************************************************************************

    if (payload == "ReleManual" || payload == "ALL")
    {
      //      client.publish(nameUser + "_rele-out-eprom_upr-manual", Rele::sendEEPROMDataToJSONSensor()); //send name rele
      Rele::sendStanReleManualAuto(releControl);
      //{"obj":[{"namberRele": 0},{"namberRele": 0},{"namberRele": 0},{"namberRele": 1},{"namberRele": 0},{"namberRele": 1},{"namberRele": 1},{"namberRele": 0}]}
      prin("ReleManual WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
      prin("**********************", Rele::objectToJSONRele(releControl));
    }

    //****************************************************************************************************

    if (payload == "releControl" || payload == "ALL")
    {
      Rele::sendEEPROMDataToJSONSensor();
      //            client.publish(nameUser + "_rele_eprom_upr", Rele::sendEEPROMDataToJSONSensor());//Номер термодатчика який керує реле
      // {"obj":[{"number": 255},{"number": 255},{"number": 255},{"number": 255},{"number": 255},{"number": 255},{"number": 255},{"number": 255}]}
      //      prin("releControl RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR");
      //      prin(Rele::sendEEPROMDataToJSONSensor());
      //      prin("releControl RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR");
    }

    //****************************************************************************************************



    if (payload == "NameRele" || payload == "ALL")
    {
      client.publish(nameUser + "_rele-name", Rele::objectToJSONRele(releControl));//send name rele
      prin("NameRele WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
      Serial.println(nameUser + "_rele-name  ---- ");
      Serial.println(Rele::objectToJSONRele(releControl));
    }
  }
  //****************************************************************************************************
  //****************************************************************************************************





  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_save-rele-name") // проверяем из нужного ли нам топика пришли данные
  {
    //   //       {//переробити
    //      "number":1,
    //      "name":"name rele"
    //        }
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    byte _currentRelay = doc["number"];//номер реле
    String nameRele = doc["name"];//Name rele
    //    byte _currentRelay = payload.substring(0, payload.indexOf("*#*")).toInt();                  //номер реле
    //    String nameRele = payload.substring(payload.indexOf("*#*") + 3, payload.indexOf("*&*")); //імя реле

    int address = _currentRelay * MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR + START_SECTION_EEPROM_RELE_NAME;

    Eeprom::writeStringEeprom(address, MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR, nameRele, 0);
    Rele::readEepromNameRele(releControl);
    prin(Rele::objectToJSONRele(releControl));
    client.publish(nameUser + "_rele-name", Rele::objectToJSONRele(releControl));//send name rele
    doc.clear();
    return;
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_brouser_to_esp__hex_address_sensor_eeprom") // проверяем из нужного ли нам топика пришли данные _brouser_to_esp__hex_address_sensor_eeprom  _save-data-sensor-eeprom
  {
    //записуємо адрес датчика і його імя вибраного  із обєкта Sensor  в EEPROM
    DynamicJsonDocument doc(4096);
    //    {"obj":{"nameSensor":["cherpadl","ira","sddff","name4","name5","name6","name7","name8"],
    //    "numberSensor":["28FF6402E24588E3","28FF6402E3DD8161",
    //    "28FF6402E248FF11","28FF640219D911AC","28FF640219A1FAA5",
    //    "28FF6402EF3A6CD5","28FF6402EFC3D131","28FF6402EF7B2B4F"]}}

    deserializeJson(doc, payload);

    prinEEPROMDebag(START_SECTION_EEPROM_SENSOR_ADDRESS, LENGTH_SECTION_EEPROM_SENSOR_ADDRESS, "START_SECTION_EEPROM_SENSOR_ADDRESS");
    for (int i = 0; i < MAX_NUMBER_SENSOR; i++)
    {
      String numberSensor = doc["obj"]["numberSensor"][i];
      String  nameSensor = doc["obj"]["nameSensor"][i];
      ds18b20EEprom[i].strAddress = numberSensor;
      ds18b20EEprom[i].nameSensor = nameSensor;
    }
    Sensor::writeEEPROMDataSensor(ds18b20EEprom); //записуємо адреса в EEPROM
    prinEEPROMDebag(START_SECTION_EEPROM_SENSOR_ADDRESS, LENGTH_SECTION_EEPROM_SENSOR_ADDRESS, "START_SECTION_EEPROM_SENSOR_ADDRESS");
    Sensor::sendSensorData(ds18b20EEprom, ds18b20);
    doc.clear();
    return;
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_brouser_to_esp_save_data_sensor_temp") // проверяем из нужного ли нам топика пришли данные
  {
    //0v255o255k
    //переробити
    //       {//переробити
    //      "number_sensor":1,
    //      "tempVkl":25,
    //      "tempOtkl":30
    //        }

    DynamicJsonDocument doc(1024);   //OK
    deserializeJson(doc, payload);
    byte _currentRelay = doc["number"];//номер реле
    byte tempVkl = doc["tempVkl"]; //Температура включеня
    byte tempOtkl = doc["tempOtkl"]; //Температура відключеня

    int a = _currentRelay * 2 + START_SECTION_EEPROM_TEMP_ON_OFF;

    EEPROM.write(a, tempVkl + 50);//50 зміщеннф температури в  байті на 50 одиниць в гору приходило було (-50 до +125) а зберігаємо в байті від (0 - 175) 
    EEPROM.write(a + 1, tempOtkl + 50);
    Eeprom::comitEprom();
    refreshData();
    kontr_temp();
    client.publish(nameUser + "_sensor-vkl-otkl", Rele::releOnOffEEPROMDataToJSON()); // send temp on temp off
    Serial.print("Send mesage ReadTempVklOtkl");
    doc.clear();
    return;
  }
  //*************************************************************************************************************************************************


  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_brouser_to_esp_rele_get_eprom_upr_manual") // проверяем из нужного ли нам топика пришли данные
  {
    //{"number":0,"data":"2"}
    DynamicJsonDocument doc(1024);   //OK
    deserializeJson(doc, payload);
    byte _currentRelay = doc["number"];//номер реле
    byte manualOrAuto = doc["data"]; //Ручний або автоматичний режим 1 або 0
    prin("_currentRelay", _currentRelay);
    prin("manualOrAuto ////////////////////*********************", manualOrAuto);
    releControl[_currentRelay].setManualAutoEEPROM(manualOrAuto, _currentRelay); //Запмсуємо в память новий стан ручний або автоматичений режим
    if (manualOrAuto == 1)
    {
      //Якщо переходимо в ручний режим то стан реле неміняємо
      Rele::manual_vklOtkl(releControl, releControl[_currentRelay].getOnOffManualEEPROM(_currentRelay), _currentRelay);
    }
    //    refreshData();
    kontr_temp();
    doc.clear();
    return;
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_brouser_to_esp_set_rele_vkl_otkl") // проверяем из нужного ли нам топика пришли данные  _set-rele-vkl-otkl
  {
    // 0x2k START_SECTION_RELE_EEPROM_FLAGS //Включаєм і виключаєм реле в ручному режимі
    //{"number":0,"data":"2"}
    //номер реле
    //Включаєм або вииключаємо реле

    DynamicJsonDocument doc(1024);  //OK
    deserializeJson(doc, payload);
    byte _currentRelay = doc["number"];//номер реле
    byte onOff = doc["data"]; //Включаєм або вииключаємо реле
    prin("_currentRelay", _currentRelay);
    prin("onOff", onOff);
    Rele::manual_vklOtkl(releControl, onOff, _currentRelay);
    Rele::sendStanReleOnOff(releControl);
    doc.clear();
    return;
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_brouser_to_esp_rele_eprom_upr_set_number_sensor") // проверяем из нужного ли нам топика пришли данные //_rele_eprom_upr-set_number_sensor
  {
    //Нoмер сенсора який управляє реле    //OK
    //  {"number":0,"data":"2"}
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    byte _currentRelay = doc["number"];
    byte numSensorControlRele = doc["data"];
    releControl[_currentRelay].setNumberSensorControlEEPROM(numSensorControlRele, _currentRelay);
    //refreshData();
    kontr_temp();
    Rele::sendEEPROMDataToJSONSensor();
    doc.clear();
    return;
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_brouser_to_esp_rele_erorr_vkl_vukl") // проверяем из нужного ли нам топика пришли данные  _brouser_to_esp_rele_erorr_vkl_vukl
  {
    DynamicJsonDocument doc(1024);    //OK
    deserializeJson(doc, payload);
    byte _currentRelay = doc["number"];
    byte errorOnOrOff = doc["data"];
    prin("errorOnOrOff _currentRelay", _currentRelay);
    prin("errorOnOrOff OnOrOff", errorOnOrOff);
    errorOnOrOff = (errorOnOrOff & ~0b10111111) >> 6;                                              //Залишаємо  тільки 6 біт і переміщаємо на нулоьовий біт
    releControl[_currentRelay].setReleErrorEEPROM(errorOnOrOff, _currentRelay);
    kontr_temp();
    Rele::sendEEPROMDataToJSONSensor();
    //    Serial.print("Rele::sendEEPROMDataToJSONSensor() ");
    //    Serial.print(Rele::sendEEPROMDataToJSONSensor());
    doc.clear();
    return;
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_brouser_to_esp_rele__set_change_on_or_off") // проверяем из нужного ли нам топика пришли данные  _brouser_to_esp_rele__set_change_on_or_off    _rele_eprom_upr-set_change_on_or_off
  {
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);    //OK
    byte _currentRelay = doc["number"];
    byte OnOrOff = doc["data"];

    prin("set_change_on_or_off _currentRelay", _currentRelay);
    prin("set_change_on_or_off OnOrOff", OnOrOff);
    OnOrOff = (OnOrOff & ~0b11011111) >> 5;//Залишаємо  тільки 5 біт і переміщаємо на нулоьовий біт
    releControl[_currentRelay].setOnOffChangeEEPROM(OnOrOff, _currentRelay);

    kontr_temp();
    Rele::sendEEPROMDataToJSONSensor();
    doc.clear();

    return;
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_brouser_to_esp_rele_set_one_or_two_range_temp") // проверяем из нужного ли нам топика пришли данные   _brouser_toesp_rele_set_one_or_two_range_temp     _rele_eprom_upr-set_one_or_two_range_temp
  {
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    byte _currentRelay = doc["number"];
    byte oneOrTworange = doc["data"];
    prin("sset_one_or_two_range _currentRelay", _currentRelay);
    prin("set_one_or_two_range OnOrOff", oneOrTworange);
    oneOrTworange = (oneOrTworange & ~0b11101111) >> 4; //Залишаємо  тільки 4 біт і переміщаємо на нулоьовий біт
    releControl[_currentRelay].setOneOrTwoRangeEEPROM(oneOrTworange, _currentRelay);
    kontr_temp();
    Rele::sendEEPROMDataToJSONSensor();
    doc.clear();
    return;
  }
  //*************************************************************************************************************************************************


}
//*************************************************************************************************************************************************
