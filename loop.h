
const int TM_PAUSE = 50;// пауза між визовами TempSend();
int tm = TM_PAUSE;

int showCounter = -1;
void loop(void)
{

  server.handleClient();
  OtherFunction::controlPins();
  analoReadA0();//other_fanction.h


  //************************************


  if (EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT) > 0)  // client
    if (WiFi.status() != WL_CONNECTED)
    {
      if (wifiMulti.run(connectTimeoutMs) == WL_CONNECTED)
      {
        String ssid = WiFi.SSID();
        String localip = WiFi.localIP().toString();
        //        Serial.print("WiFi connected: ");
        //        Serial.print(ssid);
        //        Serial.print(" ");
        //        Serial.println(localip);
        //        Serial.print("-1 ");
        connectedInternet = true;
        //*************************lcd***************************
        IPAddress myIP = WiFi.softAPIP();
        lcd.clear();
        lcd.setCursor(0, 0);  //Set cursor to character 2 on line 0
        lcd.print("CLIENT");
        lcd.setCursor(0, 1);  //Set cursor to character 2 on line
        lcd.print("IP " + String(myIP));
        //*************************lcd***************************
      }
      else
      {
        //        Serial.println("WiFi not connected!");
        //        Serial.print("0 ");
        connectedInternet = false;
        //      OtherFunction::ledBlink(8, 250);
        kontr_temp();
        counterAnalogInput += 650;
        analoReadA0();//other_fanction.h
        OtherFunction::controlPins();
      }
    }
    else { //(WiFi.status() == WL_CONNECTED)
      client.loop();
      if (tm == 0)//Затримка в циклі
      {
        //    Serial.print("Configuring access point...");
        //    IPAddress myIP = WiFi.softAPIP();
        //    Serial.print("AP IP address: ");
        //    Serial.println(myIP);
        //    if (EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT) > 0)  // client
        //      if (WiFi.status() == WL_CONNECTED)
        //      {
        //    String ssid;
        //    String localip;
        //    ssid = WiFi.SSID();
        //    localip = WiFi.localIP().toString();
        //        Serial.print("WiFi CONNECTED: ");
        //        Serial.print(ssid);
        //        Serial.print(" ");
        //        Serial.print(localip);
        //        Serial.print("WiFi.status()--- ");
        //        Serial.println(WiFi.status());

        OtherFunction::showInformation();
        connectedInternet = true;
        OtherFunction::connectMqttTopic();
        kontr_temp();
        tm = TM_PAUSE; // пауза між визовами TempSend();
        Serial.println("Miro Benech");
        Serial.print("EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT: ");
        Serial.println(EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT));
      }
    }
  tm--;
  delay(10);
  //  if (WiFi.status() == WL_CONNECTED)
  //  {
  //    // Serial.println("client.loop");
  //    client.loop();
  //  }
  //    }
}
