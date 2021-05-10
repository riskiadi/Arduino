#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

#define TRIGGER_PIN 0 //NODEMCU FLASH BUTTON

WiFiManager wm;

void setup() {
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP  
  Serial.begin(9600);
  Serial.setDebugOutput(true);  
  delay(3000);
  Serial.println("\n Starting");
  pinMode(TRIGGER_PIN, INPUT);

  std::vector<const char *> menu = {"wifi","sep","restart"};
  wm.setMenu(menu);
  
  wm.setClass("invert"); // set dark theme
  wm.setConnectTimeout(20); // how long to try to connect for before continuing

  bool res;
  res = wm.autoConnect(); // auto generated AP name from chipid
  
  if(!res) {
    Serial.println("Failed to connect or hit timeout");
    ESP.restart();
  } 
  else {
    Serial.println("Wifi Connected...");
  }
}

void checkButton(){
  if ( digitalRead(TRIGGER_PIN) == LOW ) {
    // poor mans debounce/press-hold, code not ideal for production
    delay(50);
    if( digitalRead(TRIGGER_PIN) == LOW ){
      Serial.println("Button Pressed");
      // still holding button for 3000 ms, reset settings, code not ideaa for production
      delay(3000); // reset delay hold
      if( digitalRead(TRIGGER_PIN) == LOW ){
        Serial.println("Button Held");
        Serial.println("Erasing Config, restarting");
        wm.resetSettings();
        ESP.restart();
      }
    }
  }
}

void loop() {
  checkButton();
  // put your main code here, to run repeatedly:
}
