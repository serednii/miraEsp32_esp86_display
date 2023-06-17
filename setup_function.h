//----------------------SETUP---------------------

void setupFunction()
{
  
  //  EEPROM.write(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT, 0);
  //      for (int i = 1; i < 4096; i++) {
  //          EEPROM.write(i, 0);
  //        }
  //  Eeprom::comitEprom();


  TimerDate::readTimerEEPROMToObjeckt(dataAndTime);
//  printObjectTime();
//  prin("TOTAL_LENGTH_SECTION_900", TOTAL_LENGTH_SECTION_END);


#ifdef ESP32
  //Настройка входів
  pinMode(PIN_RELE_IN_0, INPUT);
  pinMode(PIN_RELE_IN_1, INPUT);
  pinMode(PIN_RELE_IN_2, INPUT);
  pinMode(PIN_RELE_IN_3, INPUT);
  pinMode(PIN_RELE_IN_4, INPUT);
  pinMode(PIN_RELE_IN_5, INPUT);
  pinMode(PIN_RELE_IN_6, INPUT);
  pinMode(PIN_RELE_IN_7, INPUT);
  pinMode(PIN_RELE_IN_8, INPUT);
  //Настройка виходів
  releControl[0].numberPin = PIN_RELE_OUT_0;
  releControl[1].numberPin = PIN_RELE_OUT_1;
  releControl[2].numberPin = PIN_RELE_OUT_2;
  releControl[3].numberPin = PIN_RELE_OUT_3;
  releControl[4].numberPin = PIN_RELE_OUT_4;
  releControl[5].numberPin = PIN_RELE_OUT_5;
  releControl[6].numberPin = PIN_RELE_OUT_6;
  releControl[7].numberPin = PIN_RELE_OUT_7;

  for (int i = 0; i < NUMBER_RELE; i++) {
    pinMode(releControl[i].numberPin, OUTPUT);
    digitalWrite(releControl[i].numberPin, HIGH);
  }
#endif

  //  pinMode(PIN_LED_KONTROL, OUTPUT);
  //  digitalWrite(PIN_LED_KONTROL, HIGH);

  //  prinEEPROMDebag(EEPROM_ADRESS_STRING_NAME_DEVICE, 1, "EEPROM_ADRESS_STRING_NAME_DEVICE");
  //  prinEEPROMDebag(START_SECTION_EEPROM_SSID_AND_PASSWORD, LENGTH_SECTION_SSID_ADN_PASSWORD, "START_SECTION_EEPROM_SSID_AND_PASSWORD");
  //  prinEEPROMDebag(START_SECTION_RELE_EEPROM_SENSOR, LENGTH_RELE_EEPROM_SENSOR, "START_SECTION_RELE_EEPROM_SENSOR");
  //  prinEEPROMDebag(START_SECTION_RELE_EEPROM_FLAGS, LENGTH_RELE_EEPROM_FLAGS, "START_SECTION_RELE_EEPROM_FLAGS");
  //  prinEEPROMDebag(START_SECTION_EEPROM_TEMP_ON_OFF, LENGTH_TEMP_ON_OFF, "START_SECTION_EEPROM_TEMP_ON_OFF");

  refreshData();
  prin("EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT: ", EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT));


  //-------------------------------------------------------------------------------
  if (EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT) == 0) { //точка доступа
    /* Create a WiFi access point and provide a web server on it. */
    WiFi.softAP(ssid, password);
    Serial.println();
    prin("Configuring access point...");
    myIP = WiFi.softAPIP();
    prin("AP IP address: ", myIP);
    //    connectedInternet = false;
    //    digitalWrite(PIN_LED_KONTROL, HIGH);

    //*************************lcd***************************
    lcd.clear();
    lcd.setCursor(0, 0);  //Set cursor to character 2 on line 0
    lcd.print("ACCESS_POINT");
    lcd.setCursor(0, 1);  //Set cursor to character 2 on line 0
    lcd.print("IP " + myIP.toString());
    lcd.setCursor(0, 2);  //Set cursor to character 2 on line 0
    lcd.print("ssid ");
    lcd.setCursor(0, 3);  //Set cursor to character 2 on line 0
    lcd.print("pass ");
    lcd.setCursor(5, 2);  //Set cursor to character 2 on line 0
    lcd.print(APSSID);
    lcd.setCursor(5, 3);  //Set cursor to character 2 on line 0
    lcd.print(APPSK);
    //*************************lcd***************************
    delay(1000);
  }

  else if (EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT) > 0) { // client
    //  if (true) { // client

    //***************************************************
    WiFi.persistent(false); // multi
    Serial.println("\n ESP8266 Multi WiFi example 00");
    // WiFi.mode(WIFI_OFF);
    //  Set WiFi to station mode
    WiFi.mode(WIFI_STA);
    //    wifiMulti.addAP("DIR-825-8e26", "Mdcvsww0805197922");
    wifiMulti.addAP("TP-LINK_4A0934", "12719181");
    Serial.println("\n ESP8266 Multi WiFi example 11");
    //    wifiMulti.addAP("Tenda_B4C7B0", "@0805197922@");
    //    wifiMulti.addAP("Tenda_B4C7B0", "0805197922");
    //    wifiMulti.addAP("Wireless 2.4G_SLAVE", "080519792");
    //    wifiMulti.addAP("Wireless 2.4G_MASTER", "080519792");
    //    wifiMulti.addAP("TP-Link_AFC2", "080519792");
    //    wifiMulti.addAP("UKrtelecom_7BE3E4", "080519792");
    //    wifiMulti.addAP("DIR-825-5G-8E26", "Mdcvsww0805197922");
    //    wifiMulti.addAP("Mira", "8660024230");
    //    wifiMulti.addAP("Benesovi", "8660024230");
    //    wifiMulti.addAP("SIAP2", "@rFv753ZhN$159iK@");
    //    wifiMulti.addAP("TP-LINK_DFA38E", "43645343");

    Eeprom::readEeprom();
    char Buf[20];
    char Buf1[20];
    //    digitalWrite(PIN_LED_KONTROL, LOW);
    // Register multi WiFi networks
    for (int i = 0; i < 6; i++)
    {
      arraySsid[i].toCharArray(Buf, 20);
      arrayPassword[i].toCharArray(Buf1, 20);
      wifiMulti.addAP(Buf, Buf1);

      prin("ssid: ");
      Serial.print(i);
      Serial.print("  ");
      Serial.print(Buf);

      Serial.print("pasword: ");
      Serial.print(i);
      Serial.print("  ");
      Serial.print(Buf1);
    }

    byte counterConnect = 0;
    while (wifiMulti.run(connectTimeoutMs) != WL_CONNECTED)
    {
      Serial.print("-3 ");
      Serial.println("\n ESP8266 Multi WiFi example setup");
      Serial.print(".");
      Serial.println("WiFi not connected!");
      Serial.print("0 ");
      Serial.println("connectTimeoutMs");
      Serial.print(connectTimeoutMs);
      connectedInternet = false;
      kontr_temp();
      controlPins();
      Serial.println("showInformation 4 ");
      OtherFunction::showInformation();
      if(disableScanerSensors) break;
    }

    Serial.println("");
    Serial.print("WiFi connected: ");
    Serial.print(WiFi.SSID());
    Serial.print(" ");
    Serial.println(WiFi.localIP());
    Serial.print("-2");
    connectedInternet = true;

    //*************************lcd***************************
    lcd.clear();                                         // Очищаем LCD дисплей
    lcd.setCursor(3, 0);
    lcd.print("WiFi connected!");
    lcd.setCursor(0, 1);
    String temp = "SSID=" + WiFi.SSID();
    lcd.print(temp);
    lcd.setCursor(0, 2);
    temp = "IP=" + WiFi.localIP().toString();
    lcd.print(temp);
    delay(3500);
    //*************************lcd***************************
  }
  //---------------------------------------------------------------------------------------

  //******************************************************
  server.on("/checkedClient", []() {
    EEPROM.write(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT, 255);
    checkClientAccessPointRom = 255;
    Eeprom::comitEprom();
    Serial.println("connect to Client");
    server.send(200, "text/html", pageClient);
    delay(500);
    //    WiFi.disconnect(true);
    //    setup();
    //    resetFunc(); //вызываем reset });
  });

  server.on("/checkedAccesPoint", []() {
    EEPROM.write(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT, 0);
    checkClientAccessPointRom = 0;
    Eeprom::comitEprom();
    Serial.println("connect to Access Point");
    server.send(200, "text/html", pageAccessPoint);
    delay(500);
    //    WiFi.disconnect(true);
    //    setup();
    //    resetFunc(); //вызываем reset });
  });
  server.on("/", handleRoot);
  server.on("/router/", router);
  server.onNotFound(router);
  server.begin();

  Serial.println("HTTP server started");
  // MDNS.addService("http", "tcp", 80); //ставимо свій IP address
}
