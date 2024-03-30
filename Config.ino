//-------------------------------------------------------------------------------------------------------------------------------------------
bool loadConfig() {
  tft.setCursor(12, 160);
  tft.setTextColor(TFT_RED,TFT_WHITE);
  File configFile = SPIFFS.open("/config.json", "r");
  if(!configFile) {
    tft.println("Failed to open config file:");
    return false;
  }
  size_t size = configFile.size();
  if(size > 256){
    tft.println("Config file size is to large");
     return false;
  }
  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);
  StaticJsonBuffer<256> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());
  if(!json.success()){
    tft.println("Failed to parse config file");
    return false; 
  }
  const char* json_ssid = json["json_ssid"];
  strncpy(wifi_ssid, json_ssid, 10);
  const char* json_paswd = json["json_paswd"];
  strncpy(wifi_password, json_paswd, 15);
  configFile.close();
  return true;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
bool saveConfig() {
  StaticJsonBuffer<256> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["json_ssid"] = wifi_ssid;  json["json_paswd"] = wifi_password;
  File configFile = SPIFFS.open("/config.json", "w");
  if(!configFile) {
    tft.println("Failed to open config file:");
    return false;
  }
  json.printTo(configFile);
  configFile.close();
  return true;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
