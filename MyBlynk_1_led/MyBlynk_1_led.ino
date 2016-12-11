/**************************************************************
  * Эксперименты с Blynk для дачи   04.11.2016
  * Поддерживает 2 датчика, можно больше
  * Подключен watch_dog
 **************************************************************/

#include <UIPEthernet.h>
#include <BlynkSimpleUIPEthernet.h>
#include <OneWire.h>
#include <avr/wdt.h>

char auth[] = "6457680142ad4714b2d38da6feda1ef4";
OneWire  ds(6);  // on pin 6 (a 4.7K resistor is necessary)
int s_qnt = 1;
int relaystatus = 4;
boolean relay_led = LOW;

void setup() {
//  Serial.begin(9600);
  Blynk.begin(auth);
  delay(5000);
  wdt_enable (WDTO_8S);
  pinMode(relaystatus, INPUT_PULLUP);
}

void loop() {
  Blynk.run();
  if (millis() / 500 % 2) {
    CelsiusForChanal();
    led();
  }
  
  wdt_reset();
}

void led(){
  boolean led_tmp = digitalRead(relaystatus);
    if (led_tmp && !relay_led) {
      relay_led = HIGH;
      Blynk.virtualWrite(V10, HIGH);
    }
     if (!led_tmp && relay_led) {
      relay_led = LOW;
      Blynk.virtualWrite(V10, LOW);
    }
}


void CelsiusForChanal() {
  byte i;
  //byte present = 0;
  byte data[12];
  byte addr[8];
  float celsius;
 
 if ( !ds.search(addr)) {
    ds.reset_search();
    s_qnt = 1;
    return;
  }
 
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);       
  ds.reset();
  //present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);       

  for ( i = 0; i < 9; i++) {         
    data[i] = ds.read();
   }
 int16_t raw = (data[1] << 8) | data[0];
     byte cfg = (data[4] & 0x60);
     if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
     else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
     else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
     celsius = (float)raw / 16.0;
     if (s_qnt == 1) {
      Blynk.virtualWrite(V1, celsius);
     }
     if (s_qnt == 2) {
      Blynk.virtualWrite(V2, celsius);
     }
     s_qnt++;
  }

