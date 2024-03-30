#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <TFT_eSPI.h> // Graphics and font library for ST7739 driver chip
#include <SPI.h>
#include "FS.h"
#include "win.h"

TFT_eSPI tft = TFT_eSPI();

#ifndef APSSID
#define APSSID "WiFiPump"
#define APPSK "WaterPump"
#endif

const char *ssid = APSSID;
const char *password = APPSK;
char wifi_ssid[10];
char wifi_password[15];
int statusCode;
String content;
String st;

IPAddress apIP(192, 168, 1, 1);
ESP8266WebServer server(80);

//-------------------------------------------------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  delay(1000);
  displayInit();

  //strncpy(wifi_ssid, ssid, 10);
  //strncpy(wifi_password, password, 15); 
  //saveConfig();
  
  loadConfig();
  if (strcmp(wifi_ssid, ssid) == 0 && strcmp(wifi_password, password) == 0 ) {
    WiFi.mode(WIFI_STA);
    scanNework();
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(ssid,password);
    launchWeb();
    printIPAddr();
    printConfig();
    while ((WiFi.status() != WL_CONNECTED)){
      delay(100);
      server.handleClient();
    } 
  }else{
    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi_ssid, wifi_password);
    tft.loadFont("ArialBold16"); // загрузка в память шрифта CenturyGothic (14,16,18,24,36)
    tft.setTextColor(TFT_BLACK,TFT_WHITE);
    tft.setCursor(12, 250);
    tft.print("Connect: ");   
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      tft.print(".");
    }
    printWebIp();
    launchPump();
    while((WiFi.status() != WL_CONNECTED)){
      delay(100);
      server.handleClient();
    } 
  }

 /*
 tft.loadFont("ArialBold16"); // загрузка в память шрифта CenturyGothic (14,16,18,24,36)
 tft.setTextColor(TFT_BLACK,TFT_WHITE);
 tft.setCursor(12, 80); // 

 launchWeb();
 setupAP();
 
 while ((WiFi.status() != WL_CONNECTED)){
    delay(100);
    server.handleClient();
 } 


 */
 
 /* 
 if (strcmp(wifi_ssid, ssid) == 0 && strcmp(wifi_password, password) == 0 ) {
    scanNework();
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(ssid,password);
    printIPAddr();
 } 
 //saveConfig();
 //loadConfig();
 server.on("/", handleRoot);
 server.on("/scan", handleRoot);
 server.on("/change", handleChange);
 server.begin();
 */
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void loop() {
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void launchWeb(){
  createWebServer();
  server.begin();
}

void launchPump(){
  createPumpServer();
  server.begin();
}



//-------------------------------------------------------------------------------------------------------------------------------------------
void setupAP(void){
  WiFi.mode(WIFI_STA);
  delay(100);
  int n = WiFi.scanNetworks();
    st = "";
    for (int i = 0; i < n; ++i){
      st += " => ";
      st += WiFi.SSID(i);
      st += " (";
      st += WiFi.RSSI(i);
      st += ")";
      st += (WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*";
      st += "<br/>";
    }
  delay(100);
  WiFi.softAP(wifi_ssid, wifi_password);
  launchWeb();
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void createWebServer(){
  {
    server.on("/", [](){
      content = getRootPageContent();
      server.send(200, "text/html", content);
    });
    
    server.on("/setting", []() {
      String qsid = server.arg("ssid");
      String qpass = server.arg("pass");
      int sid_str_len = qsid.length() + 1; 
      char webssid[sid_str_len];
      qsid.toCharArray(webssid, sid_str_len);
      int pass_str_len = qpass.length() + 1; 
      char webpass[pass_str_len];
      qpass.toCharArray(webpass, pass_str_len);

      if ((qsid.length() > 0) && (qpass.length() >= 8) && (qpass.length() <=15)) {  
        strncpy(wifi_ssid, webssid, 10);
        strncpy(wifi_password, webpass, 15); 
        saveConfig();   
        content = getSavePageContent();
        statusCode = 200;
        server.send(statusCode, "text/html", content);
        delay(1000);
        ESP.restart();
      } else {
        content = getErrorPageContent();
        statusCode = 404;
        server.send(statusCode, "text/html", content);
      }
    });
  } 
}

//-------------------------------------------------------------------------------------------------------------------------------------------
void createPumpServer(){
  {
    server.on("/", [](){
      content = getRootPumpContent();
      server.send(200, "text/html", content);
    });
  }
}
