#ifndef MOBILE_GAMEPAD
#define MOBILE_GAMEPAD
#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <WebSocketsClient.h>

#define MOBILE_GAMEPAD_PORT 8080
#define MOBILE_GAMEPAD_URL "/gamepad"

enum GamePadKey {
  GAMEPAD_KEY_NONE,
  GAMEPAD_KEY_NORTH,
  GAMEPAD_KEY_SOUTH,
  GAMEPAD_KEY_EAST,
  GAMEPAD_KEY_WEST,
  GAMEPAD_KEY_TRIANGLE,
  GAMEPAD_KEY_CIRCLE,
  GAMEPAD_KEY_CROSS,
  GAMEPAD_KEY_SQUARE,
  GAMEPAD_KEY_SELECT,
  GAMEPAD_KEY_START,
  GAMEPAD_KEY_JOYSTICK
};

enum GamePadKeyState {
  GAMEPAD_KEY_UP,
  GAMEPAD_KEY_DOWN
};

struct JoyStickPosition
{
  float x;
  float y;
};

class CodeSkoolGamePad
{
private:
  const char *serverIp;
  GamePadKey key = GAMEPAD_KEY_NONE;
  GamePadKeyState keyState = GAMEPAD_KEY_UP;
  JoyStickPosition leftJoyStickPos = {0, 0};
  void webSocketEvent(WStype_t type, uint8_t *payload, size_t length);
  void processGamePadMessage(const char *message);

public:
  CodeSkoolGamePad(const char *serverIp);
  void begin();
  void loop();
  bool isConnected();
  GamePadKey getKey();
  String getKeyString();
  GamePadKeyState getKeyState();
  String getKeyStateString();
  void clearKey();
  JoyStickPosition getLeftJoyStickPos();
};

#endif
