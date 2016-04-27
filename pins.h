#include <Servo.h>
Servo myservo;

int e=0,de=0,ie=0,pe=0, speed_diff=0, previousError=0;
 float KP=2.5, KD=.8, KI=0;
 int calDE[2]={0,0};
 
const int trigger1 = 53; // pin to send trigger to sensor Front Left
const int echo1 =52; // echo pin for Front Left
const int trigger2 = 51; // pin to send trigger to sensor Left Front
const int echo2 =50; // echo pin for Left Front
const int trigger3 = 49; // pin to send trigger to sensor Left Rear
const int echo3 =48; // echo pin for Left Rear
const int trigger4 = 47; // pin to send trigger to sensor Front Right
const int echo4 =46; // ehco pin for Front Right
const int trigger5 = 45; // pin to send trigger to sensor Right Front
const int echo5 =44; // echo pin for Right Front
const int trigger6 = 43; // pin to send trigger to sensor Right Rear
const int echo6 =42; // echo- pin for Right Rear
const int s1 = 10; //speed of motor 1 (right side)
const int s2 = 11; //speed of motor 2 (left side)
const int d1 = 23; //motor 1 direction (forward/reverse)
const int d2 = 22; //motor 2 direction (reverse/forwards)
//color sensors
const int S0 = 24; // Select 0
const int S1 = 25; // Select 1

//Extingishing part
const int sprayer = 8;
const int statusFire= 12;
const int noFire = 4;

//NewPing sonar(trigger, echo, max_distance);
NewPing sonar1(trigger1, echo1, 400);
NewPing sonar2(trigger2, echo2, 400);
NewPing sonar3(trigger3, echo3, 400);
NewPing sonar4(trigger4, echo4, 400);
NewPing sonar5(trigger5, echo5, 400);
NewPing sonar6(trigger6, echo6, 400);

#define TCAADDR 0x70

 byte gammatable[256];
  Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void tcaselect(uint8_t i) {
  if (i > 4) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

void setup()
{
 Serial.begin(9600); //serial communication
 pinMode(trigger1, OUTPUT); //signal out to ultrasonic sensors
 pinMode(trigger2, OUTPUT); 
 pinMode(trigger3, OUTPUT);
 pinMode(trigger4, OUTPUT);
 pinMode(trigger5, OUTPUT);
 pinMode(trigger6, OUTPUT);
 pinMode(echo1, INPUT);  //echo back for sensors
 pinMode(echo2, INPUT);
 pinMode(echo3, INPUT);
 pinMode(echo4, INPUT);
 pinMode(echo5, INPUT);
 pinMode(echo6, INPUT);
 pinMode(s1, OUTPUT); // MOTOR speed pin modes
 pinMode(s2, OUTPUT);
 pinMode(d1, OUTPUT); //MOTOR directon pin modes
 pinMode(d2, OUTPUT);
 pinMode(S0, OUTPUT); // set digital pin to output for S0
 pinMode(S1, OUTPUT); // set digital pin to output for S1
 lcd.begin(16,2);

   //Extinguishing pins
 myservo.attach(9);
 pinMode(sprayer, OUTPUT);
 digitalWrite(sprayer,LOW);
 pinMode(statusFire, OUTPUT);
 pinMode(noFire, OUTPUT);
 

 Wire.begin();
  Serial.begin(9600);
  tcaselect(0);
  tcs.begin();
  tcaselect(1);
  tcs.begin();
  tcaselect(2);
  tcs.begin();
  tcaselect(3);
  tcs.begin();
}

 


