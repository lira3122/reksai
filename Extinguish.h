void roomTurnLeft(int s)
{
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  analogWrite(s1, s);
  analogWrite(s2, s);
}


void roomForward(int s)
{
  digitalWrite(d1, LOW);
  digitalWrite(d2, HIGH);
  analogWrite(s1, s);
  analogWrite(s2, s);
}
void roomTurnRight(int s)
{
    digitalWrite(d1, HIGH);
    digitalWrite(d2, HIGH);
    analogWrite(s1, s);
    analogWrite(s2, s);
}
int maxValue()
{

  const int analogInPin5 = A5;
  const int analogInPin4 = A4; 
  const int analogInPin3 = A3; 
  const int analogInPin2 = A2;
  const int analogInPin1 = A1; 
       int outputValue5 = analogRead(analogInPin5); 
      int outputValue4 = analogRead(analogInPin4); 
      int outputValue3 = analogRead(analogInPin3); 
      int outputValue2 = analogRead(analogInPin2); 
      int outputValue1 = analogRead(analogInPin1); 
  
      int FlameMAX = outputValue1;
      int sensorMAX = 1;
      
      if(outputValue2>FlameMAX)
      {
        FlameMAX = outputValue2;
        sensorMAX=2;
      }
      if(outputValue3>FlameMAX)
      {
        FlameMAX = outputValue3;
        sensorMAX=3;
      }
      if(outputValue4>FlameMAX)
      {
        FlameMAX = outputValue4;
        sensorMAX=4;  
      }
      if(outputValue5>FlameMAX)
      {
        FlameMAX = outputValue5;
        sensorMAX=5;
      }

      return FlameMAX;
}

void adjustFlame()
{
  const int analogInPin5 = A5;
  const int analogInPin3 = A3;
  const int analogInPin1 = A1;
  const int analogInPin2 = A2;
  const int analogInPin4 = A4;
  int out1 = analogRead(analogInPin1);
  int out2 = analogRead(analogInPin2);
  int out3 = analogRead(analogInPin3);
  int out4 = analogRead(analogInPin4);
  int out5 = analogRead(analogInPin5);

  if((out1>out3)||(out2>out3))
  {
    do
    {
      roomTurnRight(65);
      out1 = analogRead(analogInPin1);
      delay(60);
      out2 = analogRead(analogInPin2);
      delay(60);
      out3 = analogRead(analogInPin3);
      
    }while(out2>out3);
  }
  else if((out4>out3)||(out5>out3))
  {
    do
    {
      roomTurnLeft(65);
      out3 = analogRead(analogInPin3);
      delay(60);
      out4 = analogRead(analogInPin4);
      delay(60);
      out5 = analogRead(analogInPin5);
    }while(out4>out3);
  }
  else
  {
    
  }
  stop();
}

bool getFlameValue()
{
  const int analogInPin3 = A3;
  int out3 = analogRead(analogInPin3);
  if(out3>350)
  {
    return true;
  }
  else
  {
    return false;
  }
}
void Dance(int danceSpeed)
{
  int counter =0;
  int flame = 0;
  //Serial.println("Sprayer ON");
  do
  {
    adjustFlame();
    digitalWrite(sprayer, HIGH);
    roomTurnLeft(danceSpeed);
    delay(400);
    roomTurnRight(danceSpeed);
    delay(800);
    roomTurnLeft(danceSpeed);
    delay(800);
    roomTurnRight(danceSpeed);
    delay(400);
    digitalWrite(sprayer,LOW);
    delay(1000);
    flame = maxValue();
    counter++;
  }while((flame>350)&&(counter<3));
  
}



void Extinguish(int angle, int sensornum, int flamemax, int RLWall)
{
  const int analogInPin5 = A5;
  const int analogInPin3 = A3;
  const int analogInPin1 = A1;
  const int analogInPin2 = A2;
  const int analogInPin4 = A4;
  int out1 = analogRead(analogInPin1);
  int out2 = analogRead(analogInPin2);
  int out3 = analogRead(analogInPin3);
  int out4 = analogRead(analogInPin4);
  int out5 = analogRead(analogInPin5);
  
  int f1D=100;
  int fD=100;
  //digitalWrite(statusFire, HIGH);
  int threshold = (sensornum-1)*24;

  Serial.print("angle: ");
  Serial.print(angle);
  int angleTotal = angle + (sensornum-2)*30;
  Serial.print(" angleTotal: ");
  Serial.print(angleTotal);
  if(RLWall==1)// if left wall is closer
  {
    Serial.print(" Left Front: ");
    Serial.println(getLeftFront());
   if((angleTotal>=20)&&(angleTotal<=80))
   {
    Serial.println("Going forward to clear entrance");
    roomForward(100);
    delay(1000);
    do 
    {
     roomTurnRight(50);
    }while (analogRead(analogInPin3) < (flamemax+200));
    do{
        roomForward(75);
        f1D=getFront1D();
        delay(60);
        fD=getFrontD();
    }while((f1D>15)||(!frontWhiteLine())||(fD>15));
    
    adjustFlame();
   }

  else if(angleTotal>80)
  {
    Serial.println("Forward");
   //go Forward
   //int f1D = 100;
   roomTurnRight(50);
   delay(750);
   roomTurnRight(0);
   int fixF1D = getFront1D();
   
   do
   {
    roomForward(100);
    f1D=getFront1D();
    delay(60);
   }while(f1D>=fixF1D/2); 

    do
   {
    roomTurnLeft(50);
    
     Serial.print("sensor3=");
     Serial.println(analogRead(analogInPin3)); 
   }while(analogRead(analogInPin3) < 990);
     do
   {
    roomForward(60);
    f1D=getFront1D();
    delay(60);
   }while((f1D>=18)||(!(frontWhiteLine())));//avoid hitting front wall
   stop();
   Serial.print("Front1D: ");
   Serial.print(getFront1D());
   //Serial.print(", ");
   //Serial.println(getFront1D());
  
   
  }
  else
  {
    roomForward(100);
    delay(1000);
    do 
    {
     roomTurnRight(50);
    }while (analogRead(analogInPin3) < (flamemax+100));
    do
    {
    roomForward(100);
    f1D=getFront1D();
    delay(60);
    }while((f1D>=10)||(!frontWhiteLine()));
    delay(1500);
    
  }
  }

  
  else if(RLWall==0)  //if right wall is closer
  {
    Serial.print("Right Front: ");
    Serial.println(getRightFront());
  if(angleTotal<= 95)
   {
    Serial.println("Forward ");
    int f1D = 100;
    do
   {
    roomForward(75);
    f1D = getFront1D();
    delay(60);
    Serial.println("Looking for white line...");
    Serial.println(frontWhiteLine());
   }while(!frontWhiteLine()); //avoid hitting front wall
   stop();
   Serial.print("Front1D: ");
   Serial.print(getFront1D());
   //roomForward(0);
   //Serial.print(", ");
   //Serial.println(getFront1D());
   do
   {
    roomTurnRight(50);
    Serial.print("sensor3=");
    Serial.println(analogRead(analogInPin3)); 
   }while(analogRead(analogInPin3) < 990);
   }

  else if((angleTotal>95)&&(angleTotal<=155))
  {
    Serial.println("Turn left");
    roomForward(100);
    delay(1000);
    do 
    {
     roomTurnLeft(50);
    }while (analogRead(analogInPin3) < (flamemax+25));
    do{
        roomForward(100);
        f1D=getFront1D();
        delay(60);
    }while((f1D>10)||(!frontWhiteLine()));//for testing (must be until hits white line)
  }
  else
  {
    roomForward(100);
    delay(1750);
    do 
    {
     roomTurnLeft(50);
    }while (analogRead(analogInPin3) < (flamemax));
    do{
    roomForward(100);
    f1D=getFront1D();
    delay(60);
    }while((f1D>=20)||(!frontWhiteLine()));
  }
}

   roomForward(0); 
   Dance(75);
   roomForward(0);
   digitalWrite(statusFire,LOW);
   

   //BackOut();
}



void exploreRoom() 
{
  int i=0;
  int threshold=350;
  int statusExtinguish=0;
  const int analogInPin5 = A5;
  const int analogInPin4 = A4; 
  const int analogInPin3 = A3; 
  const int analogInPin2 = A2;
  const int analogInPin1 = A1; 

  int externalAngle=0;
  int externalSensorNum=0;
  int externalFlameMAX=0;
  int externalRLWall=0;

  int RLWall=0;
  int LF = getLeftFront();
  

  if(LF < 20)
  {
    RLWall=1;
  }
  else
  {
    RLWall=0;
  }
 
  if(RLWall) //Left wall is closer 
  {
    myservo.write(0);
    delay(500);
  for(i=0;i<=36;i+=12)
  {
      myservo.write(i);
      delay(15);
      // (FUNCTION) read each of the flame sensors renge (0-255) 
      // read the analog in value: 

      int outputValue5 = analogRead(analogInPin5); 
      int outputValue4 = analogRead(analogInPin4); 
      int outputValue3 = analogRead(analogInPin3); 
      int outputValue2 = analogRead(analogInPin2); 
      int outputValue1 = analogRead(analogInPin1); 

     
      Serial.print("\t output 1 = "); 
      Serial.println(outputValue1); 
      Serial.print("\t output 2 = "); 
      Serial.println(outputValue2); 
      Serial.print("\t output 3 = "); 
      Serial.println(outputValue3); 
      Serial.print("\t output 4 = "); 
      Serial.println(outputValue4); 
      Serial.print("\t output 5 = "); 
      Serial.println(outputValue5);
      Serial.print("\t angle= "); 
      Serial.println(i); 
      
      //compare the values read in
     
      int FlameMAX = outputValue1;
      int sensorMAX = 1;
      
      if(outputValue2>FlameMAX)
      {
        FlameMAX = outputValue2;
        sensorMAX=2;
      }
      if(outputValue3>FlameMAX)
      {
        FlameMAX = outputValue3;
        sensorMAX=3;
      }
      if(outputValue4>FlameMAX)
      {
        FlameMAX = outputValue4;
        sensorMAX=4;  
      }
      if(outputValue5>FlameMAX)
      {
        FlameMAX = outputValue5;
        sensorMAX=5;
      }
      
      Serial.print("Left wall FlameMax = ");
      Serial.println(FlameMAX);
      
      if(FlameMAX>threshold)
      {
        int angle = i;
        myservo.write(56);
        delay(250);
        
        externalAngle=angle;
        externalSensorNum=sensorMAX;
        externalFlameMAX=FlameMAX;
        externalRLWall=RLWall;
        //getVariables(angle, sensorMAX, FlameMAX, RLWall);
        //Extinguish(angle, sensorMAX, FlameMAX, RLWall);
        
        digitalWrite(statusFire,HIGH); 
       
        //delay(10000);
        //digitalWrite(7,LOW);
        //break;

        Extinguish(externalAngle, externalSensorNum, externalFlameMAX, externalRLWall);
           delay(3000000);
      }
      else if(FlameMAX<threshold)
      {
        digitalWrite(noFire,HIGH);
        delay(1000);
        digitalWrite(noFire,LOW);
        statusExtinguish=0;
        //display FlameMAX and sensorMAX in LCD
      }
  }
  }
  else// if(getRightFront()<20) //Right wall is closer
  {
    myservo.write(130);
    delay(500);
    
    for(i=130;i>=94;i-=12)
  {
      myservo.write(i);
      delay(15);
      // (FUNCTION) read each of the flame sensors renge (0-255) 
      // read the analog in value: 

      int outputValue5 = analogRead(analogInPin5); 
      int outputValue4 = analogRead(analogInPin4); 
      int outputValue3 = analogRead(analogInPin3); 
      int outputValue2 = analogRead(analogInPin2); 
      int outputValue1 = analogRead(analogInPin1); 

     
      Serial.print("\t output 1 = "); 
      Serial.println(outputValue1); 
      Serial.print("\t output 2 = "); 
      Serial.println(outputValue2); 
      Serial.print("\t output 3 = "); 
      Serial.println(outputValue3); 
      Serial.print("\t output 4 = "); 
      Serial.println(outputValue4); 
      Serial.print("\t output 5 = "); 
      Serial.println(outputValue5);
      Serial.print("\t angle= "); 
      Serial.println(i); 
      
      //compare the values read in
     
      int FlameMAX = outputValue1;
      int sensorMAX = 1;
      
      if(outputValue2>FlameMAX)
      {
        FlameMAX = outputValue2;
        sensorMAX=2;
      }
      if(outputValue3>FlameMAX)
      {
        FlameMAX = outputValue3;
        sensorMAX=3;
      }
      if(outputValue4>FlameMAX)
      {
        FlameMAX = outputValue4;
        sensorMAX=4;  
      }
      if(outputValue5>FlameMAX)
      {
        FlameMAX = outputValue5;
        sensorMAX=5;
      }
      Serial.print("Right wall FlameMax = ");
      Serial.println(FlameMAX);
      
      if(FlameMAX>threshold)
      {
        int angle = i;
        myservo.write(56);
        delay(250);
        
        externalAngle=angle;
        externalSensorNum=sensorMAX;
        externalFlameMAX=FlameMAX;
        externalRLWall=RLWall;

        //Extinguish(angle, sensorMAX, FlameMAX, RLWall);
        digitalWrite(statusFire,HIGH); 
       
        //delay(10000);
        //digitalWrite(7,LOW);
        //break;
         
          Extinguish(externalAngle, externalSensorNum, externalFlameMAX, externalRLWall);
           delay(3000000);
      }
      else if(FlameMAX<threshold)
      {
        digitalWrite(noFire,HIGH);
        delay(1000);
        digitalWrite(noFire,LOW);
        
        //display FlameMAX and sensorMAX in LCD
      }
  }

}
}


