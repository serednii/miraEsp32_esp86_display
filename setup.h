//----------------------SETUP---------------------

void setup()
{
#ifdef ESP8266
  Serial.begin(500000);
  timeClient.begin();//Годинник
#else
  Serial.begin(500000);
#endif


  EEPROM.begin(4096);
//  prinEEPROMDebag(START_SECTION_EEPROM_SENSOR_ADDRESS, LENGTH_SECTION_EEPROM_SENSOR_ADDRESS, "START_SECTION_EEPROM_SENSOR_ADDRESS");
  delay(500);

  lcd.begin();
  lcd.clear();
  lcd.backlight();      // Make sure backlight is on
  // Print a message on both lines of the LCD.
  lcd.setCursor(2, 0);  //Set cursor to character 2 on line 0
  lcd.print("Hello world!");
  lcd.setCursor(2, 1);  //Move cursor to character 2 on line 1
  lcd.print("LCD Tutorial");

setupFunction();

  //  EEPROM.write(EEPROM_ADRESS_CLIENT_OR_ACCESS_POINT, 0);
  //      for (int i = 1; i < 4096; i++) {
  //          EEPROM.write(i, 0);
  //        }
  //  Eeprom::comitEprom();

}
