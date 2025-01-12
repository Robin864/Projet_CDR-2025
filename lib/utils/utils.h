#include <Arduino.h>

#define STOP_ERROR(reason) for (;;) Serial.println("[ERROR] " + String(__FILE__) + ":" + String(__LINE__) + ": " + reason)
#define ERROR(reason) Serial.println("[ERROR] " + String(__FILE__) + ":" + String(__LINE__) + ": " + reason)
#define DEBUG(reason) Serial.println("[DEBUG] " + String(__FILE__) + ":" + String(__LINE__) + ": " + reason)