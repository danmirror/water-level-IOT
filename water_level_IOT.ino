//-----------------------IOT  INITIAL------------------
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


// You should get Auth Token in the Blynk App.

char auth[] = "U593hrI-ELBdSJBygFvAwdmLzQEzEAb-";
char ssid[] = "Redmi Note 9 Pro";
char pass[] = "enterprise";

BlynkTimer timer;
WidgetLCD lcd_widget(V0);
// ----------------------END IOT --------------

//-------------------ARDUINO HEADER INITIAL------------
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);

#include <Wire.h> 

//
//// Set the LCD address to 0x27 for a 16 chars and 2 line display
//LiquidCrystal_I2C lcd(0x27, 16, 2);

#define echoPin D6 //Echo Pin
#define trigPin D5 //Trigger Pin

#define relay 5

long duration, distance; //waktu untuk kalkulasi jarak
float jarak;
float ultrasonic(); //deklarasi function
////--------------------END ARDUINO HEADER------------

void setup() {

  Serial.begin(115200);

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("HELLO WORLD!");
 

  Blynk.begin(auth, ssid, pass);
  lcd_widget.clear();
  lcd_widget.print(0, 0, "TOPANj");

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relay, OUTPUT);
//  timer.setInterval(1000L, sendSensor);/

}

 
void loop(){
  
  Blynk.run();

////  -------------ARDUINO RUNNING-------------
  jarak = ultrasonic();
  Serial.println(jarak);
  lcd_widget.print(0, 0, jarak);
  if (jarak <= 10){
    digitalWrite(relay, HIGH);
  }
  else{
    digitalWrite(relay, LOW);
  }
  
}

float ultrasonic(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
   
  //perhitungan untuk dijadikan jarak
  distance = duration * 0.034 / 2;   //Calculating actual/real distance
   
  return distance;
}
