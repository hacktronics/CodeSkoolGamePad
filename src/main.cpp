#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include "WifiConfig.h"
#include "GamePad.h"

WiFiMulti WiFiMulti;
CodeSkoolGamePad gamePad(MOBILE_GAMEPAD_SERVER_IP);

void setup()
{
  Serial.begin(115200);
  // connect to wifi
  WiFiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
  while (WiFiMulti.run() != WL_CONNECTED) {
    delay(100);
  }

  // connect to mobile gamepad websocket
  gamePad.begin();
}

void loop()
{
  gamePad.loop();
  if(!gamePad.isConnected()) {
    return;
  }
  if (gamePad.getKey() == GAMEPAD_KEY_NONE) {
    return;
  }
  if (gamePad.getKey() == GAMEPAD_KEY_JOYSTICK) {
    Serial.printf("key: %s, x: %f, y: %f\n", gamePad.getKeyString().c_str(), gamePad.getLeftJoyStickPos().x, gamePad.getLeftJoyStickPos().y);
    gamePad.clearKey();
  } else {
    Serial.printf("key: %s, state: %s\n", gamePad.getKeyString().c_str(), gamePad.getKeyStateString().c_str());
    gamePad.clearKey();
  }
}
