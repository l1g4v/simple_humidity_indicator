#include <Arduino.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


Adafruit_SSD1306 display(128, 32, &Wire, -1);
DHT_Unified dht(PD2, DHT11);


void setup() {
  wdt_enable(WDTO_8S);
  //Serial.begin(57600);
  dht.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }
  delay(500);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.display();   
}

void loop() {
  //display.clearDisplay();
  sensors_event_t event;

  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    display.print("NaN");
  }
  else {
    display.setCursor(0, 0);
    display.print(event.temperature);
    display.setTextSize(1);
    display.print("*");
    display.setTextSize(2);
    display.print("C\n");

    
  }

  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    display.print("NaN");
  }
  else {
    display.print(event.relative_humidity);
    display.print("%");
  }
  display.display(); 
  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  //delay(250);
}