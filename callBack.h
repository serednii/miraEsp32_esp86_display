//--------------------------------------callback--------------------------------
//-----------------------------------------------------------------------------
// boolean blockGetMessega = false;
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
    //    if(payload == "setDefineDevice"){
    Serial.print("GET mesage setDefineDevice  ----  ");
    //    Serial.println(payload);
    sendPostRequest();
    sendGetRequest();
    OtherFunction::defineDevice();//Приводимо в початковий стан всі змінні
    //    }
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
  if (String(pub.topic()) == nameUser + "_set-rele-data-time") //прийом дати і часу
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

    //    TimerDate::dataTimeJsonToObject(payload,  dataAndTime);
    //    EEPROM.put(START_SECTION_EEPROM_TIMERDATE + (sizeof(TimerDate) * TimerDate::numberRele), dataAndTime[TimerDate::numberRele]); // write objeck to EEPROM
    //    Eeprom::comitEprom();
    //    TimerDate::readTimerEEPROMToObjeckt(dataAndTime);
    //    client.publish(nameUser + "_esp_to_brouser_rele_data_time", TimerDate::objectToJsonDate(dataAndTime[TimerDate::numberRele], TimerDate::numberRele));

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
      //client.publish(nameUser + "_eepromSensorData", objectToJSON(ds18b20EEprom, NUMBER_RELE));
      //{"obj":[{"number": 0, "address": "0000000000000000", "temp": 0.00}]}
      //client.publish(nameUser + "_deviceSensorData", objectToJSON(ds18b20, Sensor::deviceCountSensor));
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
    //    const byte kilkistyBukv = 20;
    // 0vname1k START_SECTION_EEPROM_RELE_NAME //Зберігаємо імя реле
    //   //       {//переробити
    //      "number":1,
    //      "name":"name rele"
    //        }
    //    Serial.println(payload);

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    byte numberRele = doc["number"];//номер реле
    String nameRele = doc["name"];//Name rele
    //    byte numberRele = payload.substring(0, payload.indexOf("*#*")).toInt();                  //номер реле
    //    String nameRele = payload.substring(payload.indexOf("*#*") + 3, payload.indexOf("*&*")); //імя реле

    int address = numberRele * MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR + START_SECTION_EEPROM_RELE_NAME;

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
    byte numberRele = doc["number"];//номер реле
    byte tempVkl = doc["tempVkl"]; //Температура включеня
    byte tempOtkl = doc["tempOtkl"]; //Температура відключеня



    // 0v255o255k START_SECTION_EEPROM_TEMP_ON_OFF //температура вкл і відкл  для реле по термодатчику
    //    String s = payload.substring(0, payload.indexOf('v'));                         //номер термодатчика
    //    String s1 = payload.substring(payload.indexOf('v') + 1, payload.indexOf('o')); //перша температура
    //    String s2 = payload.substring(payload.indexOf('o') + 1, payload.indexOf('k')); //друга температура
    int a = numberRele * 2 + START_SECTION_EEPROM_TEMP_ON_OFF;
    //    EEPROM.write(a, s1.toInt() + 50);
    //    EEPROM.write(a + 1, s2.toInt() + 50);

    EEPROM.write(a, tempVkl + 50);
    EEPROM.write(a + 1, tempOtkl + 50);



    Eeprom::comitEprom();
    //    refreshData();
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
    byte numberRele = doc["number"];//номер реле
    byte manualOrAuto = doc["data"]; //Ручний або автоматичний режим 1 або 0

    prin("numberRele", numberRele);
    //    manualOrAuto &= ~0b11111110; // reset bit 7-1
    prin("manualOrAuto ////////////////////*********************", manualOrAuto);
    releControl[numberRele].setManualAutoEEPROM(manualOrAuto, numberRele); //Запмсуємо в память новий стан ручний або автоматичений режим

    if (manualOrAuto == 1)
    {
      //Якщо переходимо в ручний режим то стан реле неміняємо
      Rele::manual_vklOtkl(releControl, releControl[numberRele].getOnOffManualEEPROM(numberRele), numberRele);
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
    //    byte numRele = payload.substring(0, payload.indexOf('x')).toInt();                      //номер реле
    //    byte onOff = payload.substring(payload.indexOf('x') + 1, payload.indexOf('k')).toInt(); //Включаєм або вииключаємо реле

    DynamicJsonDocument doc(1024);  //OK
    deserializeJson(doc, payload);
    byte numberRele = doc["number"];//номер реле
    byte onOff = doc["data"]; //Включаєм або вииключаємо реле
    prin("numberRele", numberRele);
    prin("onOff", onOff);
    Rele::manual_vklOtkl(releControl, onOff, numberRele);
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
    byte numberRele = doc["number"];
    byte numSensorControlRele = doc["data"];
    releControl[numberRele].setNumberSensorControlEEPROM(numSensorControlRele, numberRele);
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
    byte numberRele = doc["number"];
    byte errorOnOrOff = doc["data"];
    prin("errorOnOrOff numberRele", numberRele);
    prin("errorOnOrOff OnOrOff", errorOnOrOff);
    // 0x2k START_SECTION_RELE_EEPROM_SENSOR біт 6 при несправності термодатчика або не можливості керувати таймером  в якому стані залишаємо реле
    //    {
    //      "0":1//біт 6 при несправності термодатчика або не можливості керувати таймером  в якому стані залишаємо реле
    //    }
    //    prin("_rele_eprom_upr-set_erorr_rele_vkl_vukl----------------=================", pub.topic());
    //    byte numberRele = payload.substring(0, payload.indexOf('x')).toInt();                          //номер реле
    //    byte errorOnOrOff = payload.substring(payload.indexOf('x') + 1, payload.indexOf('k')).toInt(); //
    errorOnOrOff = (errorOnOrOff & ~0b10111111) >> 6;                                              //Залишаємо  тільки 6 біт і переміщаємо на нулоьовий біт
    releControl[numberRele].setReleErrorEEPROM(errorOnOrOff, numberRele);
    kontr_temp();
    Rele::sendEEPROMDataToJSONSensor();
    //    client.publish(nameUser + "_esp_to_brouser_rele_eprom_upr", Rele::sendEEPROMDataToJSONSensor());
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
    byte numberRele = doc["number"];
    byte OnOrOff = doc["data"];

    prin("set_change_on_or_off numberRele", numberRele);
    prin("set_change_on_or_off OnOrOff", OnOrOff);
    // 0x2k START_SECTION_RELE_EEPROM_SENSOR біт 5 при переключенні реле включається або виключається
    //    {
    //      "0":1//біт 5 при переключенні реле включається або виключається
    //    }
    //    byte numberRele = payload.substring(0, payload.indexOf('x')).toInt();                     //номер реле
    //    byte OnOrOff = payload.substring(payload.indexOf('x') + 1, payload.indexOf('k')).toInt(); //
    OnOrOff = (OnOrOff & ~0b11011111) >> 5;//Залишаємо  тільки 5 біт і переміщаємо на нулоьовий біт
    releControl[numberRele].setOnOffChangeEEPROM(OnOrOff, numberRele);

    kontr_temp();
    Rele::sendEEPROMDataToJSONSensor();
    doc.clear();

    return;
  }
  //*************************************************************************************************************************************************

  //*************************************************************************************************************************************************
  if (String(pub.topic()) == nameUser + "_brouser_to_esp_rele_set_one_or_two_range_temp") // проверяем из нужного ли нам топика пришли данные   _brouser_toesp_rele_set_one_or_two_range_temp     _rele_eprom_upr-set_one_or_two_range_temp
  {

    // 0x2k START_SECTION_RELE_EEPROM_SENSOR біт 4 1-два діапазона температур включенн і відключеня 0-один діапазон температур  включення або відключення
    //    {
    //      "0":1//біт 4 1-два діапазона температур включенн і відключеня 0-один діапазон температур  включення або відключення
    //    }

    //{number: 0,  data: 243}         //OK



    //    byte numberRele = payload.substring(0, payload.indexOf('x')).toInt();                           //номер реле
    //    byte oneOrTworange = payload.substring(payload.indexOf('x') + 1, payload.indexOf('k')).toInt(); //
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    byte numberRele = doc["number"];
    byte oneOrTworange = doc["data"];
    prin("sset_one_or_two_range numberRele", numberRele);
    prin("set_one_or_two_range OnOrOff", oneOrTworange);
    oneOrTworange = (oneOrTworange & ~0b11101111) >> 4; //Залишаємо  тільки 4 біт і переміщаємо на нулоьовий біт

    releControl[numberRele].setOneOrTwoRangeEEPROM(oneOrTworange, numberRele);

    kontr_temp();
    Rele::sendEEPROMDataToJSONSensor();
    //  client.publish(nameUser + "_esp_to_brouser_rele_eprom_upr", Rele::sendEEPROMDataToJSONSensor());   //_rele_eprom_upr
    doc.clear();
    return;
  }
  //*************************************************************************************************************************************************


}
//*************************************************************************************************************************************************












//*************************************************************************************************************************************************
int parseStringToData(String stringData)
{ //пошук наступного елемента в строці якщо кінець повертає -1

  symbolStart = stringData.indexOf('RELE') + 3;
  symbolEnd = stringData.indexOf('-');
  int numRele = stringData.substring(symbolStart, symbolEnd).toInt(); //номер реле

  symbolStart = symbolEnd;
  symbolEnd = stringData.indexOf('-', symbolStart + 1);

  dataAndTime[numRele].delaySecondStart = stringData.substring(symbolStart + 1, symbolEnd).toInt(); //Затримка в секундах для включення реле

  for (int i = 0; i < 10; i++)
  {
    unsigned long temp = nextElement(stringData);
    if (temp >= 0)
      dataAndTime[numRele].data_datamiliseconds[i] = temp;

    temp = nextElement(stringData);
    if (temp >= 0)
      dataAndTime[numRele].data_rik[i] = temp;

    temp = nextElement(stringData);
    if (temp >= 0)
      dataAndTime[numRele].data_months[i] = temp;

    temp = nextElement(stringData);
    if (temp >= 0)
      dataAndTime[numRele].data_dey[i] = temp;

    temp = nextElement(stringData);
    if (temp >= 0)
      dataAndTime[numRele].data_godyna[i] = temp;

    temp = nextElement(stringData);
    if (temp >= 0)
      dataAndTime[numRele].data_minut[i] = temp;

    temp = nextElement(stringData);
    if (temp >= 0)
      dataAndTime[numRele].data_daywikend[i] = temp;
  }

  for (int i = 0; i < 50; i++)
  {
    int temp = nextElement(stringData);
    if (temp >= 0)
      dataAndTime[numRele].godyna[i] = temp;
    temp = nextElement(stringData);
    if (temp >= 0)
      dataAndTime[numRele].minut[i] = temp;
  }

  for (int i = 0; i < 35; i++)
  {
    int temp = nextElement(stringData);
    if (temp >= 0)
      dataAndTime[numRele].dey[i] = temp;
  }
  return numRele;
}
//*************************************************************************************************************************************************

//*************************************************************************************************************************************************
unsigned long nextElement(String s)
{ //пошук наступного елемента в строці якщо кінець повертає -1
  symbolStart = symbolEnd;
  symbolEnd = s.indexOf('-', symbolStart + 1);
  if (!(symbolStart < 0 || symbolEnd < 0))
  {
    String s2 = s.substring(symbolStart + 1, symbolEnd); //номер реле
    //     Serial.print("SSSS22222 ");
    //    Serial.println(s2);
    unsigned long a = 0;
    for (byte i = 0; i < s2.length(); i++)
    {
      a = a * 10;
      String s3 = s2.substring(i, i + 1);
      //   Serial.print("SSSS333 ");
      //    Serial.println(s3);
      int b = s3.toInt();
      a = a + b;
    }
    //    Serial.println(a);
    return a;
  }
  else
    return -1;
}
//*************************************************************************************************************************************************
