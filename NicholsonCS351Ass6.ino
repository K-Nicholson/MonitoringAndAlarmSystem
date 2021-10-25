//Kylie Nicholson Assignment 6 CS 351

#include <TimeLib.h>
#include <DHT.h>
#include <DHT_U.h>


#include <LiquidCrystal.h> // includes the LiquidCrystal Library
#define DHTPIN 7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);

const int hourPin = 9;
const int minPin = 10;
const int secPin = 13;
const int buzzerPin = 8;

void setup() {
  lcd.clear();
  lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
  dht.begin();
  Serial.begin(9600);
  pinMode(buzzerPin,OUTPUT);
  pinMode(hourPin,INPUT);
  pinMode(minPin,INPUT);
  pinMode(secPin,INPUT);



}
void loop() {
  time_t time = now();
  setTime(hour(time),minute(time),second(time),21,3,2021);

  int readData = dht.read(DHTPIN);
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  t=(t*9/5)+32;
  
  if(digitalRead(hourPin)==LOW){
    adjustTime(3600);
  }
  
  if(digitalRead(minPin)==LOW){
    adjustTime(60);
  }
  
  if(digitalRead(secPin)==LOW){
    setTime(hour(time),minute(time),0,21,3,2021);
  }
  
  lcd.clear();
  lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
  lcd.print(hour(time));
  lcd.print(":");
  lcd.print(minute(time));
  lcd.print(":");
  lcd.print(second(time));

  lcd.setCursor(0,1); // Sets the location at which subsequent text written to the LCD will be displayed
  lcd.print("T="); // Prints string "T." on the LCD
  lcd.print(t,1); // Prints the temperature value from the sensor
  lcd.print(" H=");
  lcd.print(h,1);
  lcd.print(" %");

    
  if(h>=85){
    while(true){
        lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
        lcd.print(hour(time));
        lcd.print(":");
        lcd.print(minute(time));
        lcd.print(":");
        lcd.print(second(time));
        tone(buzzerPin, 100);
    }
  }
  
  delay(1000);
}
