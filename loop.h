
const int TM_PAUSE = 50;// пауза між визовами TempSend();
int tm = TM_PAUSE; 

int showCounter =-1;
void loop(void)
{


  controlPins();

  server.handleClient();
  analoReadA0();//other_fanction.h
#ifdef ESP32
//  prin("counterPin_0  ", counterPin_0);//debugerFunction
//  prin("counterPin_1  ", counterPin_1);
//  prin("counterPin_2  ", counterPin_2);
//  prin("counterPin_3  ", counterPin_3);
//  prin("counterPin_4  ", counterPin_4);
//  prin("counterPin_5  ", counterPin_5);
//  prin("counterPin_6  ", counterPin_6);
//  prin("counterPin_7  ", counterPin_7);
#endif

  //************************************


  if (EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT) > 0)  // client
    if (WiFi.status() != WL_CONNECTED)
    {

      if (wifiMulti.run(connectTimeoutMs) == WL_CONNECTED)
      {
        String ssid = WiFi.SSID();
        String localip = WiFi.localIP().toString();
        Serial.print("WiFi connected: ");
        Serial.print(ssid);
        Serial.print(" ");
        Serial.println(localip);
        Serial.print("-1 ");
        connectedInternet = true;
        //*************************lcd***************************
        lcd.clear();
        lcd.setCursor(0, 0);  //Set cursor to character 2 on line 0
        lcd.print("ACCESS_POINT");
        lcd.setCursor(0, 1);  //Set cursor to character 2 on line 0
        //lcd.print("IP " + String(myIP));

        //*************************lcd***************************
      }
      else
      {
        Serial.println("WiFi not connected!");
        Serial.print("0 ");
        connectedInternet = false;
        OtherFunction::ledBlink(8, 250);
        kontr_temp();
        counterAnalogInput += 650;
        analoReadA0();//other_fanction.h
      }
    }
  //    else {


  String ssid;
  String localip;
  if (tm == 0)
  {
    Serial.print("Configuring access point...");
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    if (EEPROM.read(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT) > 0)  // client
      if (WiFi.status() == WL_CONNECTED)
      {
        ssid = WiFi.SSID();
        localip = WiFi.localIP().toString();
        Serial.print("WiFi CONNECTED: ");
        Serial.print(ssid);
        Serial.print(" ");
        Serial.print(localip);
        Serial.print("WiFi.status()--- ");
        Serial.println(WiFi.status());

        
        showCounter++;
        
if(showCounter==0){
        //*************************lcd***************************
        lcd.clear();                                         // Очищаем LCD дисплей
        lcd.setCursor(0, 0);
        String temp = "SSID=" + WiFi.SSID();
        lcd.print(temp);
        lcd.setCursor(0, 1);
        temp = "IP=" + WiFi.localIP().toString();
        lcd.print(temp);
        lcd.setCursor(0, 2);
        lcd.print("Name Deice");
        lcd.setCursor(0, 3);
        lcd.print(nameUser);
        //*************************lcd***************************
}else if(showCounter == 1){
        //*************************lcd***************************
                  lcd.clear();                                         // Очищаем LCD дисплей
                for (int i = 0; i < 4; i++) {
                  lcd.setCursor(0, i);
                  String temp = String(i+1)+"-" + ds18b20EEprom[i].nameSensor;
                  lcd.print(temp);
                  lcd.setCursor(14, i);
                  lcd.print(ds18b20[i].temp);
                }
}else if(showCounter == 2){
        //*************************lcd***************************
                lcd.clear();                                         // Очищаем LCD дисплей
                for (int i = 4, l=0; i < 8; i++, l++) {
                  lcd.setCursor(0, l);
                 String temp = String(i+1)+"-" + ds18b20EEprom[i].nameSensor;
                  lcd.print(temp);
                  lcd.setCursor(14, l);
                  lcd.print(ds18b20[i].temp);
                }
}else if(showCounter == 3){
  showCounter = 0;
}

//char json[] = "{\"obj\":[{\"number\": 255},{\"number\": 255},{\"number\": 255},{\"number\": 255},{\"number\": 255},{\"number\": 255},{\"number\": 255},{\"number\": 255}]}";

//char json[] = "{\"obj\":[{\"number\": 255},{\"number\": 255},{\"number\": 255},{\"number\": 255},{\"number\": 255},{\"number\": 255},{\"number\": 255},{\"number\": 255}]}";




//char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
//char json[] = "{\"obj\":[ 186, 2, 8, 255, 255, 255, 255, 255]}";
//deserializeJson(doc, json);

//deserializeJson(doc, json);
//int obj = doc["obj"][0]["number"];

//const char* sensor = doc["sensor"];
//long time          = doc["time"];
//double latitude    = doc["data"][0];
//double longitude   = doc["data"][1];
//
//
//Serial.println("0000000000int obj = doc[\"obj\"][0];000000000000000000000000000000");
//        Serial.println(obj);
//        Serial.println(time);
//        Serial.println(latitude);
//        Serial.println(longitude);
        
        //*************************lcd***************************
//      Serial.println("0000000000000000000000000000000000000000");
//        Serial.println(ds18b20EEprom[0].nameSensor);
//        Serial.println(ds18b20EEprom[0].number);
//        Serial.println(ds18b20EEprom[0].strAddress);
//        Serial.println(ds18b20EEprom[0].temp);
//        Serial.println(ds18b20EEprom[0].tempVkl);
//        Serial.println(ds18b20EEprom[0].tempOtkl);
//        Serial.println("******************/////-----------------*****************");




        connectedInternet = true;
        if (!client.connected()) {
          if (client.connect(MQTT::Connect("Lviv")
                             .set_auth(mqtt_user, mqtt_pass)))
          {
            Serial.println("Connected to MQTT server secssesful");
            Serial.println(nameUser);
            Serial.println(mqtt_server);
            Serial.println(mqtt_port);
            Serial.println("Connected to MQTT server secssesful");

            lcd.setCursor(0, 2);
            lcd.print("Connected to MQTT");
            lcd.setCursor(0, 3);
            lcd.print("server secssesful");

            client.set_callback(callback);
            client.subscribe(nameUser + "_rele-temp");
            client.subscribe(nameUser + "_rele-all");
            client.subscribe(nameUser + "_start-data-sensor-eepromAndDevice");
            client.subscribe(nameUser + "_deviceSensorData");
            client.subscribe(nameUser + "_eepromSensorData");
            client.subscribe(nameUser + "_brouser_to_esp__hex_address_sensor_eeprom");
            client.subscribe(nameUser + "_flagRele");
            client.subscribe(nameUser + "_brouser_to_esp_rele_eprom_upr_set_number_sensor");
            client.subscribe(nameUser + "_brouser_to_esp_rele_erorr_vkl_vukl");
            client.subscribe(nameUser + "_brouser_to_esp_rele_set_one_or_two_range_temp");
            client.subscribe(nameUser + "_brouser_to_esp_rele__set_change_on_or_off");
            client.subscribe(nameUser + "_save-rele-name");
            client.subscribe(nameUser + "_brouser_to_esp_rele_get_eprom_upr_manual");
            client.subscribe(nameUser + "_brouser_to_esp_set_rele_vkl_otkl");
            client.subscribe(nameUser + "_set-rele-data-time");
            client.subscribe(nameUser + "_brouser_to_esp_save_data_sensor_temp");
            client.subscribe(nameUser + "_define_device");
            client.subscribe(nameUser + "_resetFunction");
            client.subscribe(nameUser + "_get_name_device");
            client.subscribe(nameUser + "_cleareEPROM");

            client.publish(nameUser + "_ssid", ssid); // отправляем в топик для термодатчика значение температуры
            client.publish(nameUser + "_ip", localip); // отправляем в топик для термодатчика значение температуры
          }
          else
          {
            Serial.println("Could not connect to MQTT server");
            Serial.println(nameUser);
            Serial.println(mqtt_server);
            Serial.println(mqtt_port);
            Serial.println("Could not connect to MQTT server");

            lcd.setCursor(0, 2);
            lcd.print("Could not connect");
            lcd.setCursor(0, 3);
            lcd.print("to MQTT server");
          }
        }
      }
    tm = TM_PAUSE; // пауза між визовами TempSend();
    Serial.println("Miro Benech");
    client.publish("name_user_esp_wifi", nameUser); // отправляем в топик для термодатчика значение температуры
    client.publish(nameUser + "_ssid", ssid); // отправляем в топик для термодатчика значение температуры
    client.publish(nameUser + "_ip", localip); // отправляем в топик для термодатчика значение температуры

    kontr_temp();

    //    prinEEPROMDebag(START_SECTION_RELE_EEPROM_SENSOR, LENGTH_RELE_EEPROM_SENSOR, "START_SECTION_RELE_EEPROM_SENSOR");
    //    prinEEPROMDebag(START_SECTION_RELE_EEPROM_UPR, LENGTH_RELE_EEPROM_UPR, "START_SECTION_RELE_EEPROM_UPR");
  }

  tm--;
  delay(10);

  if (WiFi.status() == WL_CONNECTED)
  {
    // Serial.println("client.loop");
    client.loop();
  }
  //    }
}





void controlPins() {
#ifdef ESP32
  counterPin_0 = controlPin( 0,  counterPin_0,  PIN_RELE_IN_0);
  counterPin_1 = controlPin( 1,  counterPin_1,  PIN_RELE_IN_1);
  counterPin_2 = controlPin( 2,  counterPin_2,  PIN_RELE_IN_2);
  counterPin_3 = controlPin( 3,  counterPin_3,  PIN_RELE_IN_3);
  counterPin_4 = controlPin( 4,  counterPin_4,  PIN_RELE_IN_4);
  counterPin_5 = controlPin( 5,  counterPin_5,  PIN_RELE_IN_5);
  counterPin_6 = controlPin( 6,  counterPin_6,  PIN_RELE_IN_6);
  counterPin_7 = controlPin( 7,  counterPin_7,  PIN_RELE_IN_7);
#endif
}


int controlPin(byte numberRele, int counterPin, byte pinConected) {

  if (digitalRead(pinConected) == 1) {
    //        Serial.print("counterPin  ------------------------------------- ");
    //        Serial.println(counterPin);
    if (counterPin == 50) {
      //      Serial.print("PIN_RELE_IN_2 ******************************************************************************  ");
      //      Serial.println(digitalRead(counterPin));
      releControl[numberRele].setManualAutoEEPROM(1, numberRele); //переводимо в ручний режим реле
      lcd.clear();                                         // Очищаем LCD дисплей
      lcd.setCursor(0, 0);
      String temp = "relay " + String(numberRele) + " manual mode";
      lcd.print(temp);

      if (digitalRead(releControl[numberRele].numberPin) == 0) { //Інвертуємо стан реле
        releControl[numberRele].setOnOffManualEEPROM(0, numberRele);
        Rele::manual_vklOtkl(releControl, 0, numberRele);//Виключаємо реле classRele.h
        lcd.setCursor(0, 1);
        lcd.print("Rele " + String(numberRele) + " OFF");
      } else {
        releControl[numberRele].setOnOffManualEEPROM(1, numberRele);
        Rele::manual_vklOtkl(releControl, 1, numberRele);// Включаємо реле classRele.h
        lcd.setCursor(0, 1);
        lcd.print("Rele " + String(numberRele) + " ON");
      }


      byte stanRele = 0;
      for (int i = 0; i < NUMBER_RELE; i++) {
        digitalRead(releControl[i].numberPin) == 0 ?  stanRele &= ~(1 << i) : stanRele |= (1 << i);//Формуємо маску бітів про стан кожного реле і відправляємо
      }
      client.publish(nameUser + "_stanRele", String(stanRele));
      client.publish(nameUser + "_rele-out-eprom_upr-manual", Rele::objectToJSONRele(releControl));
      delay(3000);
      counterPin++;
    } else if (counterPin == 250) {
      releControl[numberRele].setManualAutoEEPROM(0, numberRele); //переводимо в автоматичний режим реле
      client.publish(nameUser + "_rele-out-eprom_upr-manual", Rele::objectToJSONRele(releControl));
      lcd.clear();                                         // Очищаем LCD дисплей
      lcd.setCursor(0, 0);

      String temp = "relay " + String(numberRele) + " in automatic";
      lcd.print(temp);



      counterPin++;
    } else {
      counterPin++;
    }

  } else if (digitalRead(pinConected) == 0 && counterPin > 0) {
    counterPin = 0;
  }
  return counterPin;
}
