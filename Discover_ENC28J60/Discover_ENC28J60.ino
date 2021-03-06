/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 *
 * This example shows how to use ENC28J60 (UIPEthernet library)
 * to connect your project to Blynk.
 *
 * For this example you need UIPEthernet library:
 *   https://github.com/ntruchsess/arduino_uip
 *
 * Typical wiring would be:
 *  VCC -- 5V
 *  GND -- GND
 *  CS  -- D10
 *  SI  -- D11
 *  SCK -- D13
 *  SO  -- D12
 *  INT -- D2
 *
 * Feel free to apply it to any other example. It's simple!
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <UIPEthernet.h>
#include <BlynkSimpleUIPEthernet.h>

char auth[] = "6457680142ad4714b2d38da6feda1ef4";

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth);
 
}

void loop()
{
  Blynk.run();
}

