void scanNework(void){
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
}

