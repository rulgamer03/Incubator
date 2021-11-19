// include the library code:
#include <LiquidCrystal.h> // LCD display 
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#include "DHT.h"
#define DHTPIN 2     // what digital pin we're connected to
// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);
int motor = 7;
int ledblue = 10;
int ma = 9;
int mr = 13;
unsigned long time, previoTime = 0;
boolean statusMotor = false;  // direction of rotation 
#define trotacionhuevos  8000 // Time to the rotation in milliseconds 

void rotacionhuevos  ()  {
time = millis();
    if( time - previoTime > trotacionhuevos ) {
    previoTime = time;
    lcd.clear(); 
    lcd.setCursor(0, 0);
    lcd.print("Rotating eggs ");
    if (statusMotor == false){
      digitalWrite(ma,HIGH);
      digitalWrite(mr,LOW);
      delay(1000);
    }
    if (statusMotor == true){
      digitalWrite(ma,LOW);
      digitalWrite(mr,HIGH);
      delay(1000);
    
    }
    statusMotor = !statusMotor;
    }
    else{
      digitalWrite(ma,LOW);
      digitalWrite(mr,LOW);
      delay(100);
    }
}

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600); 
  Serial.println("DHTxx test!");
  pinMode(8, OUTPUT);
  pinMode(motor,OUTPUT);
  pinMode(ledblue,OUTPUT);
  pinMode(ma,OUTPUT);
  pinMode(mr,OUTPUT);
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  
  delay(100);
  

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  
  //Serial.println("success");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
  
  lcd.setCursor(0, 0);
  lcd.print("HUMIDITY : ");
  lcd.setCursor(10, 0);
  lcd.print(h);
  lcd.setCursor(0, 1);
  lcd.print("TEMPERAT : ");
  lcd.setCursor(10, 1);
  lcd.print(t);
  // t and h conditions 
  if (t < 37)
   {
    digitalWrite(8,HIGH);
    analogWrite(motor,0);
    delay(100);
   }
  else if (t>=37 && t <=38) 
   {
    digitalWrite(8,LOW);
    analogWrite(motor,0);
   }
   else if (t > 38){
    digitalWrite(8,LOW);
    analogWrite(motor,255);
    delay(100);
   }

   if (h < 50){
    digitalWrite(ledblue,HIGH); // turn on the led that represents the  humidifier 
    delay(100);
   }
   else if (h > 55){
    analogWrite(motor,255); // turn on the ventilator
    digitalWrite(ledblue,LOW); // turn off led that represents the humidifier
   }
   else if (h >=50 && h <= 55){
    //Normal rank of h
    digitalWrite(ledblue,LOW); // turn off led that represents the humidifier
   }
   
   rotacionhuevos();
    
    
   
   
}
