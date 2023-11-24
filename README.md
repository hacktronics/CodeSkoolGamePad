# CodeSkool GamePad

CodeSkool GamePad is an android application that allows you to use your android mobile phone as a GamePad to control your robotics project. It is a simple application that uses the gyroscope sensors of your mobile phone to control the movement of your robot. It also has various buttons to control the various functions of your robot. The application sends the data to the robot via websockets. The android application starts a websocket server to which your JS webpage or ESP32 based microcontroller can connect to. The robot receives the data and moves accordingly.

The application can be downloaded from the android store [here](https://play.google.com/store/apps/details?id=cc.codeskool.gamepad).

## How to use with ESP32
This is a sample ESP32 project with a utility class that can be used to connect to the websocket server of the android application. The utility class is written in C++ and can be used with the ESP32 Arduino framework. You need to modify the WiFiConfig.h.sample file and rename it to WiFiConfig.h. You need to add your WiFi credentials in the file. You also need to add the IP address of your android phone in the file. The IP address of the websocket server is shown when the gamepad application starts as a toast message. The port is fixed with a value: 8080.

You need to create an instance of the GamePad class and call the begin method to start the websocket client. You can then call the getKey method to get the key pressed by the user. The key is returned as a enum (integer). You can use the key to control your robot. You have to also call, the `gamePad.loop()` method in the loop function to update the websocket client.
