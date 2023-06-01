



class Eeprom {


    //*************************************************************************************************************************************************
  public:
    static void comitEprom()
    {
           Serial.print("EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT**********************: ");
  Serial.println(EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT));
      if (EEPROM.commit())
      {
        Serial.println("EEPROM successfully committed");
      }
      else
      {
        Serial.println("ERROR! EEPROM commit failed");
      }
           Serial.print("EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT**************************: ");
  Serial.println(EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT));
    }
    //*************************************************************************************************************************************************

    //********************WRITE EEPROM****************************
static void writeEeprom()
{
  String ssidTemp, passTemp;
  int sectionEeprom = START_SECTION_EEPROM_SSID_AND_PASSWORD;
//Записуємо паролі і логіни
  for (int i = 0; i < NUMBER_CLIENT_CONNECT; i++)
  {
    ssidTemp = arraySsidInput[i];
    passTemp = arrayPasswordInput[i];
    //    Serial.print("passTemp  ");
    //    Serial.println(passTemp);
    //    Serial.print("ssidTemp  ");
    //    Serial.println(ssidTemp);

    for (int j = 0; j < LENGTH_SSID; j++)
    {
      if (j < ssidTemp.length())
      {
        EEPROM.write(j + sectionEeprom, ssidTemp[j]); //Записуємо в память ssid
      }
      else
      {
        EEPROM.write(j + sectionEeprom, 0);
      }
    }


    for (int j = LENGTH_SSID; j < LENGTH_SSID + LENGTH_PASSWORD; j++)
    {
      if (j - LENGTH_SSID < passTemp.length())
      {
        EEPROM.write(j + sectionEeprom, passTemp[j - LENGTH_SSID]); //Записуємо в память password
      }
      else
      {
        EEPROM.write(j + sectionEeprom, 0);
      }
    }

    sectionEeprom += LENGTH_SSID + LENGTH_PASSWORD;
  }
  Eeprom::comitEprom();
}
//*************************************************************************************************************************************************


//********************READ EEPROM******************************
static void readEeprom()
{//Читаємо паролі і логіни
  int sectionEeprom = START_SECTION_EEPROM_SSID_AND_PASSWORD;
  //-----------------------------------------

  for (int i = 0; i < NUMBER_CLIENT_CONNECT; i++)
  {
    arraySsid[i] = "";
    arrayPassword[i] = "";

    for (int j = 0; j < LENGTH_SSID; j++)
    {
      byte ss = EEPROM.read(j + sectionEeprom);
      if (!(ss == 0))arraySsid[i] += char(ss);
    }


    for (int j = LENGTH_SSID; j < LENGTH_SSID + LENGTH_PASSWORD; j++)
    {
      byte pas = EEPROM.read(j + sectionEeprom);
      if (!(pas == 0))arrayPassword[i] += char(pas);
    }



    sectionEeprom += LENGTH_SSID + LENGTH_PASSWORD;
  }
}
//*******************READ EEPROM****************************



//*************************************************************************************************************************************************
static void writeStringEeprom(word beginByteEeprom, word maxLengthString, String str, word symbol ) {
  //beginByteEeprom Початковий адресс
  //maxLengthString Виділена память під строку
  //str строка
  //symbol код символа яким заповняємо остаток памяті в EEPROM

  for (word k = 0; k < maxLengthString; k++)
  {
    if (k < str.length()) {
      String cc = str.substring(k, k + 1);
      char char_array[2];
      cc.toCharArray(char_array, 2);
      EEPROM.write(beginByteEeprom + k, (byte)char_array[0]);
    } else {
      EEPROM.write(beginByteEeprom + k, symbol);
    }
  }

  Eeprom::comitEprom();
}
//*************************************************************************************************************************************************


//*************************************************************************************************************************************************
//read eeprom string Читає с EEPROM строку певної довжини
static String readStringEeprom(int beginByteEeprom, int lengthString ) {
  String tempString;
  for (int i = 0; i < lengthString; i++)
  {
    int addd = beginByteEeprom + i;
    byte data = EEPROM.read(addd);
    if (data > 0)tempString += char(data);
  }
  return tempString;
}
//*************************************************************************************************************************************************

};
