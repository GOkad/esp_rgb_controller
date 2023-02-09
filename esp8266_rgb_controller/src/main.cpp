#include <Arduino.h>
/**
 * NOTE: remove the '.' 
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