
void scanWifi();



void refreshData();

void kontr_temp();
void analoReadA0(); 
  
//void controlPins();
boolean controlRangeDate(byte numberRele, byte numberDataTime);
void printObjectTime();
// int controlPin(byte numberRele, int counterPin, byte pinConected);
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
