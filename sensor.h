
class Sensor           // название класса
{
  public:
    String nameSensor;
    String strAddress;
    byte number;
    float temp;
    int tempVkl;
    int tempOtkl;
    static int deviceCountSensor; //КІЛЬКІСТЬ ПІДКЛЮЧЕНИХ ДАТЧИКІВ

    //****************************************************************************************************
    static String objectToJSON(Sensor obj[], int n)
    {
      DynamicJsonDocument doc(2000);

      String json;
      for (int i = 0; i < n; i++)
      {
        doc["obj"][i]["number"] = i;
        doc["obj"][i]["address"] = obj[i].strAddress;
        doc["obj"][i]["temp"] = obj[i].temp;
      }

      serializeJson(doc, json);
      //    prin("OUTPUT LENGTH", json.length());
      //    prin("OUTPUT LENGTH", json);
      doc.clear();
      return json;
    }
    //****************************************************************************************************

    //****************************************************************************************************
    static void readSensorsAddressTemp(Sensor ds18b20[]) {
      // read device address and temperature in class Sensors object ds18b20 arrays
      //  oneWireBus = 12;//14
      //  OneWire oneWire(oneWireBus);
      //  DallasTemperature sensors(&oneWire);
      sensors.begin();
      sensors.requestTemperatures(); // от датчика получаем значение температуры
      DeviceAddress Thermometer;
      deviceCountSensor = sensors.getDeviceCount();
      if (deviceCountSensor > MAX_NUMBER_SENSOR)deviceCountSensor = MAX_NUMBER_SENSOR; //Якщо кількість підключених термодатчиків є більше як MAX_NUMBER_SENSOR то ількість встановлюємо MAX_NUMBER_SENSOR

      for (byte i = 0; i < deviceCountSensor; i++)
      {
        sensors.getAddress(Thermometer, i);
        ds18b20[i].strAddress = sensorDeviceAddress(Thermometer);
        ds18b20[i].temp = sensors.getTempCByIndex(i);
        ds18b20[i].number = i;
        //            Serial.print("strAddress YYYYYYYYYYYYYYYYYYYYYYYY  ");
        //            Serial.print(ds18b20[i].strAddress);
        //            Serial.print(" temp  ");
        //            Serial.println(ds18b20[i].temp);
      }
    }
    //****************************************************************************************************

    //*************************************************************************************************************************************************
    static void searchCodeSennsorInEEPROM(Sensor ds18b20EEprom[], Sensor ds18b20[])
    {
      for (int i = 0; i < MAX_NUMBER_SENSOR; i++)
      {
        for (int k = 0; k < deviceCountSensor; k++)
        {
          if (ds18b20EEprom[i].strAddress == ds18b20[k].strAddress) //Якщо в памяті є адрес датчика який підключений реально
          {
            ds18b20EEprom[i].temp = ds18b20[k].temp; //То присвоюємо температуру номеру, що записаний в памяті
            break;
          }
        }
      }
    }

    //****************************************************************************************************
    static String sensorDeviceAddress(DeviceAddress deviceAddress)
    {
      uint64_t address = 0;
      String strAddress = "";
      for (uint8_t i = 0; i < 8; i++)
      {
        address = address + deviceAddress[i];
        if (deviceAddress[i] > 0)
        {
          if (deviceAddress[i] < 8)
            strAddress += "0" + String(deviceAddress[i], HEX);
          else
            strAddress += String(deviceAddress[i], HEX);
        }
        else
          strAddress += "00";
        if (i < 7)
          address = address << 8;
      }
      return strAddress;
    }
    //****************************************************************************************************

    //****************************************************************************************************
    static  void writeEEPROMDataSensor(Sensor ds18b20EEprom[])
    {
      String strAddress = "";
      for (int i = 0; i < MAX_NUMBER_SENSOR; i++)
      {
        //    strAddress = "";
        strAddress = ds18b20EEprom[i].strAddress;
        for (int k = 7, d = 16; k >= 0; k--, d -= 2)
        {
          int addd = START_SECTION_EEPROM_SENSOR_ADDRESS + k + (i * 8);
          String cc = strAddress.substring(d - 2, d);
          char char_array[3];
          cc.toCharArray(char_array, 3);
          //Write address sensor
          EEPROM.write(addd, (byte)strtol(char_array, NULL, 16));
          //Write name Sensor
          word StartAdress = START_SECTION_EEPROM_SENSOR_NAME  + (i * MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR);//Вираховуємо адрес для запису
          Eeprom::writeStringEeprom(StartAdress, MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR, ds18b20EEprom[i].nameSensor, 0);
        }
      }
      Eeprom::comitEprom();
      //  Sensor::readEepromDataSensor(ds18b20EEprom); //читаємо імя, address і температуру з памяті ЕЕПРОМ  в обєкт ds18b20EEprom що є вибрані в програмі
    }
    //****************************************************************************************************

    //****************************************************************************************************
    static  void writeEEPROMNameSensor(Sensor sensor[])// ніде неіикористовується
    {
      for (int i = 0; i < 8; i++)
      {
        word StartAdress = START_SECTION_EEPROM_SENSOR_NAME  + (i * MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR);//Вираховуємо адрес для запису
        Eeprom::writeStringEeprom(StartAdress, MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR, sensor[i].nameSensor, 0);
      }
      //---------------------------------------------------------------------
    }
    //****************************************************************************************************

    //****************************************************************************************************
    //Формуємо мас адрес датчика в обєкт із памяті ЕЕПРОМ
    static void readEepromDataSensor(Sensor ds18b20EEprom[])
    {
      //читаємо address і температуру з памяті ЕЕПРОМ
      //читаємо імя з памяті ЕЕПРОМ в обєкт ds18b20EEprom
      String strAddress = "";
      //Формуємо мас адрес датчика в обєкт із памяті ЕЕПРОM
      for (int i = 0; i < MAX_NUMBER_SENSOR; i++)
      {
        strAddress = "";
        for (int k = 0; k < 8; k++)
        {
          byte temp = EEPROM.read(START_SECTION_EEPROM_SENSOR_ADDRESS + k + (i * 8));
          if (temp > 0)
          {
            if (temp < 10)
              strAddress += "0" + String(temp, HEX);
            else
              strAddress += String(temp, HEX);
          }
          else
            strAddress += "00";
        }
        ds18b20EEprom[i].nameSensor = Eeprom::readStringEeprom(START_SECTION_EEPROM_SENSOR_NAME + (i * MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR), MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR);
        ds18b20EEprom[i].strAddress = strAddress;
        ds18b20EEprom[i].temp = 0;

        //    Serial.print("nameSensor ");
        //    Serial.print(ds18b20EEprom[i].nameSensor);
        //     Serial.print("strAddress ");
        //    Serial.print(ds18b20EEprom[i].strAddress);
        //    Serial.print(" temp  ");
        //    Serial.println(ds18b20EEprom[i].temp);
      }
    }
    //****************************************************************************************************



    //*************************************************************************************************************************************************

    //*************************************************************************************************************************************************
    static void sendSensorData(Sensor ds18b20EEprom[], Sensor ds18b20[])
    {

      //Якщо в памяті є записаний реальний мас адрес датчика то присвоюємо йому температуру датчика
      readSensorsAddressTemp(ds18b20);    //читаємо в обєкт адреса і температуру датчиків в обєкт ds18b20
      readEepromDataSensor(ds18b20EEprom); //читаємо імя, address і температуру з памяті ЕЕПРОМ  в обєкт ds18b20EEprom що є вибрані в програмі
      searchCodeSennsorInEEPROM(ds18b20EEprom, ds18b20); //Записуємо температуру в EEPROM sensory з реальних датчиків

      DynamicJsonDocument doc(3000);

      //---------------------------------------------------------------------
      for (int i = 0; i < MAX_NUMBER_SENSOR; i++) {
        doc["obj"][i]["number"] = i;
        doc["obj"][i]["nameSensor"] = ds18b20EEprom[i].nameSensor;
        doc["obj"][i]["address"]   = ds18b20EEprom[i].strAddress;
        doc["obj"][i]["temp"] = ds18b20EEprom[i].temp;;
      }

      String json;
      serializeJson(doc, json);
      //      Serial.println("AAAAAAAAAAAAAAAAAAAAAAAAA  json  9999999  json  99999999999 ");
      //      Serial.println(json);
      //формуємо в формат JSON дані з памяті EEPROM і відправляємо в топік
      client.publish(nameUser + "_esp_to_brouser_eeprom_sensor_data", json);//_esp_to_brouser_eeprom_sensor_data  _eepromSensorData
      //    client.publish(nameUser + "_eepromSensorData", Sensor::objectToJSON(ds18b20EEprom, 8));
      //      Serial.println(Sensor::objectToJSON(ds18b20EEprom, MAX_NUMBER_SENSOR));

      //{"obj":[{"number": 0, "address": "0000000000000000", "temp": 0.00},{"number": 1, "address": "0000000000000000", "temp": 0.00},
      //{"number": 2, "address": "28ff640219a1faa5", "temp": 24.50},{"number": 3, "address": "28ff640219d911ac", "temp": 24.44},
      //{"number": 4, "address": "28ff6402e3dd8161", "temp": 24.75},{"number": 5, "address": "0000000000000000", "temp": 0.00},
      //{"number": 6, "address": "0000000000000000", "temp": 0.00},{"number": 7, "address": "0000000000000000", "temp": 0.00}]}
      json = "";
      doc.clear();

      for (int i = 0; i < deviceCountSensor; i++) {
        doc["obj"][i]["nameSensor"] = "";
        doc["obj"][i]["number"] = i;
        doc["obj"][i]["address"] = ds18b20[i].strAddress;
        doc["obj"][i]["temp"] = ds18b20[i].temp;
      }

      serializeJson(doc, json);
      //      Serial.println("BBBBBBBBBBBBBBBBBBBBBBB  json  9999999  json  99999999999 ");
      //      Serial.println(json);

      client.publish(nameUser + "_esp_to_brouser_device_sensor_data", json); //  _esp_to_brouser_device_sensor_data    _deviceSensorData

      //  client.publish(nameUser + "_deviceSensorData", Sensor::objectToJSON(ds18b20, deviceCountSensor));

      prin("Sensor::objectToJSON", Sensor::objectToJSON(ds18b20, MAX_NUMBER_SENSOR));

      //{"obj":[{"number": 0, "address": "28ff6402e248ff11", "temp": 24.50},{"number": 1, "address": "28ff6402e24588e3", "temp": 24.87},
      //{"number": 2, "address": "28ff640219a1faa5", "temp": 24.50},{"number": 3, "address": "28ff640219d911ac", "temp": 24.44},
      //{"number": 4, "address": "28ff6402e3dd8161", "temp": 24.75},{"number": 5, "address": "28ff6402ef3a6cd5", "temp": 24.44},
      //{"number": 6, "address": "28ff6402efc3d131", "temp": 24.25},{"number": 7, "address": "28ff6402ef7b2b4f", "temp": 24.44}]}

      json = "";
      //doc["obj"]="";

      for (int i = 0; i < MAX_NUMBER_SENSOR; i++) {
        doc["obj"][i]["number"] = 0;
        doc["obj"][i]["address"] = "";
        doc["obj"][i]["temp"] = 0;
        doc["obj"][i]["nameSensor"] = ds18b20EEprom[i].nameSensor;
      }
      //      Serial.println("CCCCCCCCCCCCCCCCCCC json  333333333  json  33333333333333333333333333333333 ");
      //      serializeJson(doc, json);
      //      Serial.println(json);
      //  Serial.println(ds18b20EEpromToJSONnameSensor());
      //  client.publish(nameUser + "_sensor-name", json);// ds18b20EEpromToJSONnameSensor()
      //    client.publish(nameUser + "_sensor-name", ds18b20EEpromToJSONnameSensor());// ds18b20EEpromToJSONnameSensor()
      // {"obj":[{"nameSensor": "cherpadl"},{"nameSensor": "kuxyn"},{"nameSensor": "sddff"},{"nameSensor": "name4"},{"nameSensor": "name5"},{"nameSensor": "name6"},{"nameSensor": ""},{"nameSensor": ""}]}
    }
    //*************************************************************************************************************************************************


};
int Sensor::deviceCountSensor;
Sensor ds18b20[MAX_NUMBER_SENSOR];
Sensor ds18b20EEprom[MAX_NUMBER_SENSOR];



//записуємо адрес датчика вибраного  із обєкта Sensor  в EEPROM
