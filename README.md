# TempHumidClock

    A simple clock for measuring Temperature and Humidity using Arduino Nano, DHT11, and MG45.

----

### Quickstart
  - Hardware
    + [Arduino](https://www.arduino.cc/) Nano or Uno
    + DHT11 sensor to measure temperature and humidity
    + MG45 sensor to save energy during night
    + four-segmental digital tube for display
  - Software
    + Arduino IDE to burn it
  - Configuration
    + `DISPLAY_TIME` in [TempHumidClock.ino](/TempHumidClock.ino)

### Pin Mapping & Wiring
  - DHT11: 13
  - MG45: A7
  - Tube:
    + W1: A5
    + W2: A2
    + W3: A1
    + W4: 12
    + a: A4
    + b: A0
    + c: 10
    + d: 8
    + e: 7
    + f: A3
    + g: 11
    + dp: 9

### Wiring

![demo1](/demo1.jpg)
![demo2](/demo2.jpg)

----

by Armit
2019/10/04 
