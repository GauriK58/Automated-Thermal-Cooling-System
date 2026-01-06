#include <Wire.h>
#include <Adafruit_TMP117.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal.h>

Adafruit_TMP117  tmp117;
const int rs = 3, en = 2, d4 = 4, d5 = 5, d6 = 6, d7 = 7;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup(void) {
  lcd.begin(16,2);
  pinMode(13, OUTPUT); //fan
  pinMode(12, OUTPUT); //water pump
  Serial.begin(115200);

  lcd.clear();

  if (!tmp117.begin()) {
    Serial.println("Failed to find TMP117 chip");
    while (1) { delay(10); }
  }

}
void loop() {

  sensors_event_t temp; // creates a variable temp of type sensors_event_t, which is a structure used to store sensor data
  tmp117.getEvent(&temp); //The getEvent() method reads the current temperature from the TMP117 sensor and stores the result in the temp structure. 
  Serial.print("Temperature  "); Serial.print(temp.temperature);
  Serial.println(" degrees C");
  Serial.println("");
  float val = temp.temperature;
  lcd.print(temp.temperature);
  delay(3000);
  lcd.clear();
  if(val>42){
      digitalWrite(13,LOW);
      digitalWrite(12,LOW);
  }
  if(val<35){
    digitalWrite(13,HIGH);
  }
  if(val<38){
    digitalWrite(12,HIGH);
  }
  
}
