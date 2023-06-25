#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x26,20,4);  // set the LCD address to 0x3F for a 16 chars and 2 line display
#include <PubSubClient.h> //mqtt
#include <EEPROM.h>
#include <NTPClient.h>//Годинник
#include <WiFiUdp.h>//Годинник
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 7200 , 60000);
IPAddress myIP;
//*****************************
//  HH:MM:SS
//******************************
void (*resetFunc)(void) = 0; // объявляем функцию reset



//#define ESP8266
#define ESP32

#ifdef ESP8266
//ESP8266
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#else
//ESP32
#include <WiFi.h> 
#include <HTTPClient.h>
#include <WebServer.h>     
#include <WiFiMulti.h>   
WiFiMulti wifiMulti;             
#endif





#include "declaration.h"
#include "memory_allocation_EEPROM.h"
#include "const.h"
#include "const_pin.h"
#include "var_global.h"



const String nameUser = "mykola";
boolean connectedInternet = false;



void callback(const MQTT::Publish & pub);
#include <OneWire.h>
#include <DallasTemperature.h>
// GPIO where the DS18B20 is connected to
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);


const char *mqtt_server = "broker.hivemq.com"; // Имя сервера MQTT
const int mqtt_port = 1883;                    // Порт для подключения к серверу MQTT
const char *mqtt_user = "";                    // Логин от сервер
const char *mqtt_pass = "";                    // Пароль от сервера

//#define MQTT_MAX_PACKET_SIZE 1024
WiFiClient wclient;
PubSubClient client(wclient, mqtt_server, mqtt_port);

IPAddress ip(192, 168, 0, 17); //статический IP
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
const char *ssid1 = "DIR-825-8e26";
const char *password1 = "Mdcvsww0805197922";

#ifndef APSSID
#define APSSID "ESPap"
#define APPSK "thereisn"
#endif



/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

#ifdef ESP8266
ESP8266WebServer server(80);
#endif

#ifdef ESP32
WebServer server(80);       // ESP32WebServer server(80);
#endif





//const int led = LED_BUILTIN;


boolean disableScanerSensors = false;





#include "setup.h"
#include "eeprom.h"
#include "sensor.h"
#include "rele.h"
#include"timeranddate.h"
#include "classGetDateInternet.h"
#include "other_functions.h"
#include "web.h"
#include "setup_function.h"
#include "loop.h"
#include "callBack.h"
#include "contrTemp.h"
#include "dateFunctions.h"
#include "debugerFunctions.h"
//*****************************************************************************
