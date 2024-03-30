//----------------------------------------------------------------------------------------------------------------------------------------------------
void printConfig(){
  tft.loadFont("ArialBold16"); // загрузка в память шрифта CenturyGothic (14,16,18,24,36)
  tft.setTextColor(TFT_BLACK,TFT_WHITE);
  tft.setCursor(12, 180);
  tft.print("SSID: ");
  tft.setTextColor(TFT_RED,TFT_WHITE);
  tft.println(wifi_ssid);
  tft.setTextColor(TFT_BLACK,TFT_WHITE);
  tft.setCursor(12, 200);
  tft.print("Password: ");
  tft.setTextColor(TFT_RED,TFT_WHITE);
  tft.println(wifi_password); 
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void displayInit(){
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setSwapBytes(true);
  tft.pushImage(0,0,240,320,Win);
  if (!SPIFFS.begin()) { while (1) yield(); }  
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void printIPAddr(){
  tft.loadFont("ArialBold16"); // загрузка в память шрифта CenturyGothic (14,16,18,24,36)
  tft.setCursor(12, 80); // 
  tft.setTextColor(TFT_BLACK,TFT_WHITE);
  tft.print("Точка доступа: ");
  tft.setTextColor(TFT_RED,TFT_WHITE);
  tft.println(WiFi.softAPIP());
  tft.loadFont("ArialBold18");
  tft.setTextColor(0x03E0,TFT_WHITE); // GRB565
  tft.setCursor(12, 120);
  tft.println("HTTP SERVER STARTED");
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
void printWebIp(){
  tft.loadFont("Arial18"); // загрузка в память шрифта CenturyGothic (14,16,18,24,36)
  tft.setCursor(12, 80); // 
  tft.setTextColor(TFT_BLACK,TFT_WHITE);
  tft.print("Web сервер: ");
  //tft.fillRect(12, 80, tft.textWidth("Че-то там: "), tft.fontHeight(), );
  tft.setTextColor(TFT_RED,TFT_WHITE);
  tft.println(WiFi.localIP());
  tft.loadFont("ArialBold18");
  tft.setTextColor(0x03E0,TFT_WHITE); // GRB565
  tft.setCursor(12, 120);
  tft.println("HTTP SERVER STARTED");
}
//----------------------------------------------------------------------------------------------------------------------------------------------------


