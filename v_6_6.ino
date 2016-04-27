#include "Wire.h"
#include "Adafruit_TCS34725.h" //header file for color sensor
#include "Adafruit_Sensor.h"
#include "LiquidCrystal.h"
LiquidCrystal lcd(7,6,5,4,3,2);
#include "NewPing.h"
#include "pins.h"
#include "color_sensors.h"
#include "serialprint.h"
#include "readings.h"
#include "turns.h"
#include "extinguish.h"
#include "movement.h"
#include "mod_movement.h"


//motor 1 is right side
//motor 2 is left side

int columns =10;
int rows = 3;
int turnHistory [10][3];// ={000,000,000,110,110,110,220,220,220,330,330,330,440,440,440};
int arrayCount = 0;
int roomCount = 0;
int hallways = 0;
int halfTurns = 0;
int roomsInHallway =0;

void loop()
{
 int Speed = 150 - (halfTurns * 25);

 //int tmp = whiteline();

 //Serial.println(tmp);
 //getReadings();
 
//forward(Speed, Speed);
//HallNav(Speed,turnHistory,arrayCount,columns,rows,roomCount,hallways,halfTurns,roomsInHallway);
// roomOrHallway(Speed, 0,1);
 //delay(5000);
 /*
  forward(Speed, Speed);
  Serial.print("array Count= ");
  Serial.println(arrayCount);
 */

  if(arrayCount < 1)
    {
      Serial.println("HALLNAV");
    HallNav(Speed, turnHistory, arrayCount, columns, rows, roomCount,hallways, halfTurns,roomsInHallway);
    }
    else
    {
      Serial.println("MOD_HALLNAV");
    mod_HallNav(Speed,turnHistory,arrayCount,columns,rows,roomCount,hallways,halfTurns,roomsInHallway);
    }

//getReadings();
//determineAlign(Speed);
//  backwards(Speed/2, Speed/2);
  //arrayCount = 0;
  //getReadings();
  
  // defining all variables needed
 /*int temp = getFrontD();
 if(temp < 11 && temp > 0)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Wall Front");
     stop(); 
    }
    else
    {*/
     // getError();
      //forward(Speed/2, Speed/2);
    // rotateRight(Speed/2);
    // alignFront(Speed);
    // delay(2000);
   // align(Speed);
     //stop();
     //stop();
     //stop();

     

 //int tmpRH= roomOrHallway(Speed,1,0);
  /*
  int tmpRH = roomOrHallway(Speed, 1, 0);
  int lastturn = 0;

  if(tmpRH == 0)
  {
    //this is a hallway continue nav

    Serial.println("HALLWAY TEST");
  }
  else
  {
    Serial.println("ROOM TEST");
    delay(1000);
    backOutRoom(Speed);
    Serial.println("FRONT SENSOR DETECTED OUT OF ROOM");
    delay(1000);

    //get last turn from array and turn opposite
    //if lastturn = 1 >> turn left
    //if lastturn = 0 >> turn right

    if(lastturn == 0) // last turn was right
    {
      turnLeft(Speed);
    }
    else //last turn was left
    {
      turnRight(Speed);
    }
    delay(10000);
    //this is a room with no flame
    //backout until front sensors > 20
    //back out just a bit more to get to middle of hallway
    //depending on last turn turn 90 degrees opposite
  }

*/
 // backwards(Speed/2, Speed/2);
   //rotateRight(Speed/2);
  //stop();
  
     // alignFront(Speed);
      /*
      delay(3000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("turning right"); */
      //turnRight(Speed);
    // getReadings();
    // align(Speed);
     
    // rotateRight(Speed);
    //align(Speed);
     
   // rotateLeft(Speed);
   //  align(Speed);
   //  delay(5000);
   //Serial.print("Color Sensor reading = ");
   //colorSensor();  
     /*
     for(int i =0; i < 10; i++)
     {
      getReadings(); 
     }
     rotateRight(Speed);
     delay(1000);
     */
   /*  while(whiteline())
     {
      stop();
     }
     forward(Speed/2, Speed/2);*/
   // }
   
  /* while(!(whiteline() || getLeftRear() < 30) || getRightRear() < 30)
  {
   forward(Speed/2, Speed/2); 
  }
  stop();*/
  //arrayInfo(turnHistory, columns, rows, arrayCount, roomCount ,hallways,halfTurns);
/*
 myservo.write(56); 
 adjustFlame();
const int analogInPin1 = A1;
const int analogInPin2 = A2;
const int analogInPin3 = A3;
const int analogInPin4 = A4;
const int analogInPin5 = A5;

  int uv1 = analogRead(analogInPin1);
  int uv2 = analogRead(analogInPin2);
  int uv3 = analogRead(analogInPin3);
  int uv4 = analogRead(analogInPin4);
  int uv5 = analogRead(analogInPin5);

  Serial.print("uv1 = ");
  Serial.println(uv1);
  Serial.print("uv2 = ");
  Serial.println(uv2);
  Serial.print("uv3 = ");
  Serial.println(uv3);
  Serial.print("uv4 = ");
  Serial.println(uv4);
  Serial.print("uv5 = ");
  Serial.println(uv5);
  Serial.println( " ");
  delay(500);
  
 
  delay(5000);
  */
}



