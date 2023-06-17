
const int TM_PAUSE = 50;// пауза між визовами TempSend();
int tm = TM_PAUSE;


void loop(void)
{

  server.handleClient();
  //************************************
  if (EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT) > 0) { // client
    if (!disableScanerSensors)
      if (WiFi.status() != WL_CONNECTED)//Якщо не підключено
      {
        while (wifiMulti.run(connectTimeoutMs) != WL_CONNECTED)
        {
          Serial.print("-3 ");
          Serial.println("\n ESP8266 Multi WiFi example loop");
          Serial.print(".");
          Serial.println("WiFi not connected!");
          Serial.print("0 ");
          Serial.println("connectTimeoutMs");
          Serial.print(connectTimeoutMs);
          connectedInternet = false;
          kontr_temp();
//          controlPins();
          controlPins();
          Serial.println("showInformation 1 ");
          OtherFunction::showInformation();
          if (disableScanerSensors) break;
        }

      } else {//Якщо підключено
        client.loop();
        connectedInternet = true;
        if (tm == 0)//Затримка в циклі
        {
          Serial.println("showInformation 2 ");
          OtherFunction::showInformation();
          OtherFunction::connectMqttTopic();
          kontr_temp();
          tm = TM_PAUSE; // пауза між визовами TempSend();
        }
      }
  } else { //Точка доступа
    if (tm == 0)//Затримка в циклі
    {
      Serial.println("showInformation 3 ");
      OtherFunction::showInformation();
      kontr_temp();
      tm = TM_PAUSE; // пауза між визовами TempSend();
    }
  }
  if (tm == 0 && disableScanerSensors)//Затримка в циклі
  {
    Serial.println("showInformation 3 ");
    OtherFunction::showInformation();
    kontr_temp();
    tm = TM_PAUSE; // пауза між визовами TempSend();
  }

  tm--;
  controlPins();
  delay(10);
}
