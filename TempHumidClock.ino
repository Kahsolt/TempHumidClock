#include "config.h"
#include "MG45.h"
#include "DHT11.h"
#include "DigitalTube.h"

void setup() {
  Serial.begin(SERIAL_BAUDRATE);
  
  Tube_Init();
  MG45_Init();
  DHT11_Init();

  Tube_Test();
  Serial.println("[App] Tube test OK");
  
  MG45_Read(); MG45_Print();
  Serial.println("[App] MG45 test OK");

  DHT11_Read(); /* dummy for init */
  DHT11_Read(); DHT11_Print();
  Serial.println("[App] DHT11 test OK");
}

void loop() {
  int data[TUBE_CONTROL_PIN_NUM];
  
  MG45_Read(); MG45_Print();
  if (MG45_Analog_Value > MG45_THRESHOLD) {
    Tube_Off();
    delay(1000);
  } else {
    DHT11_Read(); DHT11_Print();

    // Show Temperature
    data[0] = DHT11_Temperature / 10;
    data[1] = DHT11_Temperature % 10;
    data[2] = 10; // '.'
    data[3] = 11; // 'C'
    Tube_Display(data, DISPLAY_TIME);

    // Show Humidity
    data[0] = DHT11_Humidity / 10;
    data[1] = DHT11_Humidity % 10;
    data[2] = 10; // '.'
    data[3] = 12; // 'H'
    Tube_Display(data, DISPLAY_TIME);
  }
}
