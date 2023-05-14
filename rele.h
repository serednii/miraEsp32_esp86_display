#include <ArduinoJson.h>
class Rele // название класса
{
  public:
    String nameRele; //імя реле
    byte numberPin;           //номер піна до якого підключено реле 1

    //START_SECTION_RELE_EEPROM_UPR
    byte manualAuto;            // вкл або виключено
    byte onOffManual; //при ручному режимі реле включено чи виключено  bit - 0
    //    byte termoControl;     // Буде чи ні реле керуватися термодатчиком
    byte timerControl;        // Якщо 0 то реле не контролюється таймером, якщо 1 то контролюємо

    //   byte temp = EEPROM.read(START_SECTION_RELE_EEPROM_SENSOR + i);
    //    releControl[i].bit4OneOrTwoRange = (temp & ~0b11101111) >> 4;
    //    releControl[i].bit5OnOffChange = (temp & ~0b11011111) >> 5;
    //    releControl[i].bit6ReleError = (temp & ~0b10111111) >> 6;

    //START_SECTION_RELE_EEPROM_SENSOR
    byte numberSensorControl; // bit 0-3 номер датчика який управляє даним реле
    byte bit4OneOrTwoRange;  //1-два діапазона температур включенн і відключеня 0-один діапазон температур  включення або відключення
    byte bit5OnOffChange; //при переключенні реле включається або виключається
    byte bit6ReleError; //при несправності термодатчика або неможливість управляти таймером реле залишаємо вкл 1 або відключеним -0

    boolean errorSensor; //Якщо пропав датчик флаг ставимо в true
    boolean flagsTermo;//  якщо спрацювала умова включення для термодатчика
    boolean flagsTimer;//  якщо спрацювала умова включення для таймера
    boolean flagsDelaystart;// якщо є затримка при включенні

  public:
    //*****************************************************************
    // Setter
    void setManualAutoEEPROM(byte stan, byte numberRele) {
      manualAuto = stan;//РУЧНИЙ АБО АВТОМАТ
      int address = numberRele + START_SECTION_RELE_EEPROM_UPR;
      prin("address", address);
      prin("numberRele", numberRele);
      prin("stan", stan);
      prin("manualAuto+++++++++++++++++++++++++++", manualAuto);
      setOrResetBitEEPROM(address, 0, stan);
      kontr_temp();
    }

    void setOnOffManualEEPROM(byte stan, byte numberRele) {
      onOffManual = stan; //ВКЛ ВИКЛ РЕЛЕ В РУЧНОМУ РЕЖИМІ
      int address = numberRele + START_SECTION_RELE_EEPROM_UPR;
      prin("address", address);
      prin("numberRele", numberRele);
      prin("stan", stan);
      prin("onOffManual+++++++++++++++++++++++++++", onOffManual);
      setOrResetBitEEPROM(address, 1, stan);
    }

    void setNumberSensorControlEEPROM(byte numSensorControlRele, byte numberRele) {//Не використовується для EEPROM
      numberSensorControl = numSensorControlRele;
      int address = numberRele + START_SECTION_RELE_EEPROM_SENSOR;
      byte temp = EEPROM.read(address);
      temp &= ~0b00001111;//reset bit 0-3
      temp = temp + (numSensorControlRele);
      prin("numberRele", temp);
      prin("numberRele", temp & ~0b11110000);
      EEPROM.write(address, temp);
      Eeprom::comitEprom();
    }

    void setOneOrTwoRangeEEPROM(byte stan, byte numberRele) {
      //      Serial.print("stan ---------------  ");
      //      Serial.println(stan);
      //      Serial.print("numberRele ---------------  ");
      //      Serial.println(numberRele);
      bit4OneOrTwoRange = stan;
      int address = numberRele + START_SECTION_RELE_EEPROM_SENSOR;
      setOrResetBitEEPROM(address, 4, stan);
    }

    void setOnOffChangeEEPROM(byte stan, byte numberRele) {
      //      Serial.print("stan ---------------  ");
      //      Serial.println(stan);
      //      Serial.print("numberRele ---------------  ");
      //      Serial.println(numberRele);
      bit5OnOffChange = stan;
      int address = numberRele + START_SECTION_RELE_EEPROM_SENSOR;
      setOrResetBitEEPROM(address, 5, stan);
    }

    void setReleErrorEEPROM(byte stan, byte numberRele) {
      //      Serial.print("stan ---------------  ");
      //      Serial.println(stan);
      //      Serial.print("numberRele ---------------  ");
      //      Serial.println(numberRele);
      bit6ReleError = stan;
      int address = numberRele + START_SECTION_RELE_EEPROM_SENSOR;
      setOrResetBitEEPROM(address, 6, stan);
    }

    //*****************************************************************

    //*****************************************************************
    // Getter
    byte getManualAutoEEPROM(byte numberRele) {
      int address = numberRele + START_SECTION_RELE_EEPROM_UPR;
      return getBitEEPROM(address, 0);
    }

    byte getOnOffManualEEPROM(byte numberRele) {
      int address = numberRele + START_SECTION_RELE_EEPROM_UPR;
      return getBitEEPROM(address, 1);
    }

    //       byte getTermoControlEEPROM(byte numberRele) {//Не використовується взагалі
    //      int address = numberRele + START_SECTION_RELE_EEPROM_UPR;
    //      return getBitEEPROM(address, 2);
    //    }

    //        byte getTimerControlEEPROM(byte numberRele) {//Не використовується для EEPROM
    //      int address = numberRele + START_SECTION_RELE_EEPROM_UPR;
    //      return getBitEEPROM(address, 3);
    //    }


    byte getNumberSensorControlEEPROM(byte numberRele) {
      int address = numberRele + START_SECTION_RELE_EEPROM_SENSOR;
      byte temp = EEPROM.read(address);
      prin("numberRele", temp);
      prin("numberRele", temp & ~0b11110000);

      return temp & ~0b11110000;
    }

    byte getOneOrTwoRangeEEPROM( byte numberRele) {
      int address = numberRele + START_SECTION_RELE_EEPROM_SENSOR;
      return getBitEEPROM(address, 4);
    }

    byte getOnOffChangeEEPROM( byte numberRele) {
      int address = numberRele + START_SECTION_RELE_EEPROM_SENSOR;
      return getBitEEPROM(address, 5);
    }

    byte getReleErrorEEPROM( byte numberRele) {
      int address = numberRele + START_SECTION_RELE_EEPROM_SENSOR;
      return getBitEEPROM(address, 6);
    }

    //*************************************************************************************************************************************************


    //*************************************************************************************************************************************************
    void setOrResetBitEEPROM(int address, byte numBit, byte setOrReset) {
      byte data = EEPROM.read(address);

      //      prin("sizeof(LENGTH_SECTION_SSID_ADN_PASSWORD)  ", data);

      if (setOrReset == 0) {
        data &= ~(1 << numBit);//reset bit
      } else if (setOrReset == 1) {
        data |= (1 << numBit);//set bit
      }
      EEPROM.write(address, data);
      Eeprom::comitEprom();

      data = EEPROM.read(address);
      //      prin("sizeof(LENGTH_SECTION_SSID_ADN_PASSWORD)  ", data);
    }


    byte getBitEEPROM(int address, byte numBit) {
      byte data = EEPROM.read(address);
      if (data & (1 << numBit)) return 1;
      else return 0;
      //      return ((data & ~0b11111101) >> numBit);
    }
    //*************************************************************************************************************************************************


    //STATIC METHOD
    //*************************************************************************************************************************************************
    static void sendStanRele(Rele obj[])  //Відправляємо стани всіх реле
    {
      DynamicJsonDocument doc(1024);  //OK
      String stanRele;
      for (int i = 0; i < NUMBER_RELE; i++) {
        digitalRead(obj[i].numberPin) == 0 ? doc["data"][i] = 1 : doc["data"][i] = 0; //Формуємо маску бітів про стан кожного реле і відправляємо
      }
      serializeJson(doc, stanRele);
      prin("stanRele SSSSSSSSSSSSSSSSSSSSSSSSSS", stanRele);
      //digitalRead(releControl[i].numberPin) == 0 ? stanRele &= ~(1 << i) : stanRele |= (1 << i); //Формуємо маску бітів про стан кожного реле і відправляємо
      client.publish(nameUser + "_esp_to_brouser_stan_rele", stanRele);
    }
    //*************************************************************************************************************************************************




    //*************************************************************************************************************************************************
    static void EEPROMDataToJSONSensor() {
      //   byte numberSensorControl; // bit 0-3 номер датчика який управляє даним реле
      //    byte bit4OneOrTwoRange;  //1-два діапазона температур включенн і відключеня 0-один діапазон температур  включення або відключення
      //    byte bit5OnOffChange; //при переключенні реле включається або виключається
      //    byte bit6ReleError; //при несправності термодатчика або неможливість управляти таймером реле залишаємо вкл 1 або відключеним -0
      DynamicJsonDocument doc(1024);
      for (int i = 0; i < NUMBER_RELE; i++)
      {
        prin("objecToJson 198 ", EEPROM.read(START_SECTION_RELE_EEPROM_SENSOR + i));
        doc["obj"][i] = EEPROM.read(START_SECTION_RELE_EEPROM_SENSOR + i);
      }

      String json;
      serializeJson(doc, json);
      //  prin("objecToJson 204 ", json);

      client.publish(nameUser + "_esp_to_brouser_rele_eprom_upr", json);   //_rele_eprom_upr
    }
    //*************************************************************************************************************************************************



    //*************************************************************************************************************************************************
    static void readEepromNameRele(Rele releControl[])
    {

      //читаємо address з памяті ЕЕПРОМ в обєкт releControl
      //  const byte kilkistyBukv = 20;
      //Формуємо мас адрес датчика в обєкт із памяті ЕЕПРОM
      for (int i = 0; i < NUMBER_RELE; i++)
      {
        releControl[i].numberSensorControl = (EEPROM.read(START_SECTION_RELE_EEPROM_SENSOR + i));//Номер термодатчика який керує реле
        releControl[i].nameRele = readStringEeprom(START_SECTION_EEPROM_RELE_NAME + (i * MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR), MAX_LENNGTH_TEXT_NAME_RELE_AND_SENSOR);
      }

    }
    //*************************************************************************************************************************************************


    //*************************************************************************************************************************************************
    static String objectToJSONRele(Rele obj[]) //send rele name
    {
      String json;
      DynamicJsonDocument doc(1024);
      for (int i = 0; i < NUMBER_RELE; i++)
      {
        doc["obj"][i] = obj[i].nameRele;
      }
      serializeJson(doc, json);
      prin("objectToJSONRele", json);
      return json;
    }
    //*************************************************************************************************************************************************

    //*************************************************************************************************************************************************
    static String releOnOffEEPROMDataToJSON() { //send temp on off
      String json;
      DynamicJsonDocument doc(1024);
      for (int i = 0; i < NUMBER_RELE; i++)
      {
        doc["obj"][i]["vkl"] = EEPROM.read(START_SECTION_EEPROM_TEMP_ON_OFF + i * 2) - 50;
        doc["obj"][i]["otkl"] = EEPROM.read(START_SECTION_EEPROM_TEMP_ON_OFF + i * 2 + 1) - 50;
      }
      serializeJson(doc, json);
      prin("Rele::releOnOffEEPROMDataToJSON", json);
      return json;
      //  {"obj":[{"vkl": 25,"otkl": 27},{"vkl": 25,"otkl": 30},{"vkl": 25,"otkl": 32},{"vkl": 25,"otkl": 30},{"vkl": 25,"otkl": 30},{"vkl": 25,"otkl": 30},{"vkl": 25,"otkl": 30},{"vkl": 25,"otkl": 30}]}
    }
    //*************************************************************************************************************************************************

    //*************************************************************************************************************************************************
   static void manual_vklOtkl(Rele releControl[], int onOff, int numRele ) {
      if (onOff == 0) { //Виключаємо реле
        releControl[numRele].setOnOffManualEEPROM(onOff, numRele);
        digitalWrite(releControl[numRele].numberPin, HIGH);
      } else if (onOff == 1) { //Включаємо реле
        releControl[numRele].setOnOffManualEEPROM(onOff, numRele);
        digitalWrite(releControl[numRele].numberPin, LOW);
      }
    }
    //*************************************************************************************************************************************************

};


//String objectToJSONRele(Rele obj[]);

Rele releControl[NUMBER_RELE];






















//=================================================================================
