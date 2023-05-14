
void scanWifi();



void refreshData();

void kontr_temp();
void analoReadA0(); 
  
//void ();

void writeStringEeprom(word beginByteEeprom, word maxLengthString, String str, word symbol);
//void readEepromNameRele();



//void refreshobjectToJsonDate();

void controlPins();
//String objectToJsonDateAll();
//void EEPROMDataToJSONSensor();

boolean controlRangeDate(byte numberRele, byte numberDataTime);
void printObjectTime();
//String releOnOffEEPROMDataToJSON();
//String ds18b20EEpromToJSONnameSensor();
//void dataTimeJsonToObject(String json);
 int controlPin(byte numberRele, int counterPin, byte pinConected);
void prin(String s, byte a); 
void prin(String s, word a); 
void prin(String s, int a); 
void prin(String s, double a); 
void prin(String s, float a); 
void prin(String s, char a); 
void prin(String s, String a); 
void prinString(String s);
void prin(String s);
void prinEEPROMDebag(int starting, int lengthSection, String nameSection);
int parseStringToData(String stringData);
unsigned long nextElement(String s);
String readStringEeprom(int beginByteEeprom, int lengthString );
void writeStringEeprom(word beginByteEeprom, word maxLengthString, String str, word symbol );
