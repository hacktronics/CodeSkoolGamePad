#include "GamePad.h"
#include <ArduinoJson.h>

WebSocketsClient webSocket;
DynamicJsonDocument doc(128);

CodeSkoolGamePad::CodeSkoolGamePad(const char *serverIp)
{
  this->serverIp = serverIp;
}

void CodeSkoolGamePad::begin()
{
  // connect to mobile gamepad websocket
  webSocket.begin(this->serverIp, MOBILE_GAMEPAD_PORT, MOBILE_GAMEPAD_URL);
  // event handler
  webSocket.onEvent([&](WStype_t type, uint8_t *payload, size_t length) {
    this->webSocketEvent(type, payload, length);
  });
  // try ever 1000 again if connection has failed
  webSocket.setReconnectInterval(1000);
}

void CodeSkoolGamePad::loop()
{
  webSocket.loop();
}

bool CodeSkoolGamePad::isConnected()
{
  return webSocket.isConnected();
}

GamePadKey CodeSkoolGamePad::getKey()
{
  return this->key;
}

String CodeSkoolGamePad::getKeyString() {
  switch (this->key)
  {
  case GAMEPAD_KEY_NORTH:
    return "North";
  case GAMEPAD_KEY_SOUTH:
    return "South";
  case GAMEPAD_KEY_EAST:
    return "East";
  case GAMEPAD_KEY_WEST:
    return "West";
  case GAMEPAD_KEY_TRIANGLE:
    return "Triangle";
  case GAMEPAD_KEY_CIRCLE:
    return "Circle";
  case GAMEPAD_KEY_CROSS:
    return "Cross";
  case GAMEPAD_KEY_SQUARE:
    return "Square";
  case GAMEPAD_KEY_SELECT:
    return "Select";
  case GAMEPAD_KEY_START:
    return "Start";
  case GAMEPAD_KEY_JOYSTICK:
    return "Joystick";
  default:
    return "";
  }
}

GamePadKeyState CodeSkoolGamePad::getKeyState()
{
  return this->keyState;
}

String CodeSkoolGamePad::getKeyStateString() {
  switch (this->keyState)
  {
  case GAMEPAD_KEY_UP:
    return "Up";
  case GAMEPAD_KEY_DOWN:
    return "Down";
  default:
    return "";
  }
}

JoyStickPosition CodeSkoolGamePad::getLeftJoyStickPos()
{
  return this->leftJoyStickPos;
}

void CodeSkoolGamePad::clearKey() {
  this->key = GAMEPAD_KEY_NONE;
}

void CodeSkoolGamePad::processGamePadMessage(const char *message)
{
  deserializeJson(doc, message);
  if (!doc.containsKey("key")) {
    return;
  }
  const char *value = doc["key"];
  if (value != nullptr && strcmp(value, "LeftJoystick") == 0) {
    this->key = GAMEPAD_KEY_JOYSTICK;
    this->leftJoyStickPos.x = doc["x"].as<float>();
    this->leftJoyStickPos.y = doc["y"].as<float>();
    return;
  }
  switch (value[0])
  {
  case 'N':
    this->key = GAMEPAD_KEY_NORTH;
    break;
  case 'S':
    this->key = GAMEPAD_KEY_SOUTH;
    break;
  case 'E':
    this->key = GAMEPAD_KEY_EAST;
    break;
  case 'W':
    this->key = GAMEPAD_KEY_WEST;
    break;
  case 'T':
    this->key = GAMEPAD_KEY_TRIANGLE;
    break;
  case 'C':
    this->key = GAMEPAD_KEY_CIRCLE;
    break;
  case 'X': 
    this->key = GAMEPAD_KEY_CROSS;
    break;
  case 'Q':
    this->key = GAMEPAD_KEY_SQUARE;
    break;
  case 'L':
    this->key = GAMEPAD_KEY_SELECT;
    break;
  case 'R':
    this->key = GAMEPAD_KEY_START;
    break;
  default:
    this->key = GAMEPAD_KEY_NONE;
    break;
  }
  switch (value[1])
  {
  case '1':
    this->keyState = GAMEPAD_KEY_UP;
    break;
  case '0':
    this->keyState = GAMEPAD_KEY_DOWN;
    break;
  default:
    break;
  }
}

void CodeSkoolGamePad::webSocketEvent(WStype_t type, uint8_t *payload, size_t length)
{
  switch (type)
  {
  case WStype_DISCONNECTED:
    // Serial.printf("[GamePad] Disconnected!\n");
    break;
  case WStype_CONNECTED:
    // Serial.printf("[GamePad] Connected!\n");
    break;
  case WStype_TEXT:
    this->processGamePadMessage((const char *)payload);
    break;
  case WStype_BIN:
  case WStype_ERROR:
  case WStype_FRAGMENT_TEXT_START:
  case WStype_FRAGMENT_BIN_START:
  case WStype_FRAGMENT:
  case WStype_FRAGMENT_FIN:
    break;
  }
}
