Arducar
=======

*Arduino RC Car over IP suite*

Communicate to an Arduino to control a robot over the Internet.

Features
---
* Simple single byte instructions to Arduino
* Servo motor control from mouse input from the client

Usage
---
**Arduino**

Upload contents of ```arduino/arduino.c``` to the microcontroller.

**Server**

```
cd server
make
./server [/dev/USB0] #default arduino device name
```

Server listens on TCP port 9090 by default.

**License**

 MIT
