#include <Arduino.h>
/**
 * NOTE: remove the '.' in front of 'WebServerConfig.h'  
 * Update 'config/WebServerConfig.h' with your credentials 
 */
#include "config/.WebServerConfig.h"
#include "AppCore.h"

void setup() {
  Serial.begin(115200);
  Serial.println("");
}

void loop() {
  static AppCore core(WebServerConfig{});
}
