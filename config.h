#ifndef CONIFG_H
#define CONIFG_H

/**********************/
/* Functional Options */
/**********************/

// Serial
#define SERIAL_ENABLE       true
#define SERIAL_BAUDRATE     115200

// MG45
#define MG45_THRESHOLD      400.0   // test your env

// Tube
#define DISPLAY_TIME        15      // > 0, timspan to switch tempature and humidity display in seconds
#define TUBE_REFRESH_RATE   75      // > 0, refresh rate in Hz, samller value causes blink
#define TUBE_BRIGHTNESS     0.35    // 0 ~ 1.0, bigger is brighter

/*****************/
/* Pins & Wiring */
/*****************/

// DHT11
#define DHT11_PIN   13

// MG45
#define MG45_PIN    A7

// Tube
#define W1          A5
#define W2          A2
#define W3          A1
#define W4          12
#define a           A4
#define b           A0
#define c           10
#define d           8
#define e           7
#define f           A3
#define g           11
#define dp          9         

#endif  // CONIFG_H
