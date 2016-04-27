void forward(int x, int y);
void align(int Speed);
void pause();
void alignFront(int Speed);
void stop();
void lTurn(int Speed);

void rotateLeftTimed(int pwm)
{
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  analogWrite(s1, pwm);
  analogWrite(s2, pwm);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Turning LEFT");
  delay(950);
  analogWrite(s1, 0);
  analogWrite(s2, 0);
};

int checkLeftTurn()
{
  int tmpLeft, tmpFront;
  
  tmpLeft = getLeftFront();
  delay(60);
  tmpFront = getFrontD();
  delay(60);

  if(tmpLeft < tmpFront)
  {
    return 0;//use left---> front
  }
  else
  {
    return 1;//use front-->right
  }
};

int checkRightTurn()
{
  int tmpRight, tmpFront;

  tmpRight = getRightFront();
  delay(60);
  tmpFront = getFrontD();
  delay(60);

  if(tmpRight < tmpFront)
  {
    return 0; //use Right---> front
  }
  else
  {
    return 1;//use front-->left
  }
}

void rotateLeft(int pwm)
{
   //get and store front reading
  //rotate right until left sensors pick up reading
  //align using front sensors
    int CSide;
    CSide = checkLeftTurn();

    if(CSide == 1) //Front ---> Right
    {
    int tempFront = getFrontD();
    delay(60);
    int tempRightFront = getRightFront();
    delay(60);
    int tempRightRear = getRightRear();
    delay(60);
   // int tempRightFront = getRightFront();
    Serial.print(tempFront);
    Serial.print(" tempFront ");
    Serial.print(tempRightFront);
    Serial.print(" Left Front ");
    Serial.print(tempRightRear);
    Serial.print(" Left Rear ");
    Serial.print('\n');
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("FrontD= ");
    lcd.setCursor(10,0);
    lcd.print(tempFront);
    rotateLeftTimed(pwm/2);
  do 
  {
    digitalWrite(d1, LOW);
    digitalWrite(d2, LOW);
    analogWrite(s1, pwm/2.5);
    analogWrite(s2, pwm/2.5);
    tempRightFront = getRightFront();
    delay(60);
    tempRightRear = getRightRear();
    delay(60);
    Serial.print(tempFront);
    Serial.print(" tempFront ");
    Serial.print(tempRightFront);
    Serial.print(" Right Front ");
    Serial.print(tempRightRear);
    Serial.print(" Right Rear ");
    Serial.print('\n');
     lcd.setCursor(0,1);
    lcd.print("RF= ");
    lcd.setCursor(4,1);
    lcd.print(tempRightFront);
     lcd.setCursor(7,1);
    lcd.print("RR= ");
    lcd.setCursor(12,1);
    lcd.print(tempRightRear);
  } while(! (((((tempRightFront-4) - tempFront) >= -5 && ((tempRightFront-4) - tempFront) <= 5)) && ((tempRightRear-4) - tempFront) >= -5 && ((tempRightRear-4) - tempFront) <= 5));
    }
    else // Left--->Front
    {
         {
    int tempLeft = getLeftFront();
    delay(60);
    int tempFrontL = getFrontD();
    delay(60);
    int tempFrontR = getFront1D();
    delay(60);
   // int tempRightFront = getRightFront();
    Serial.print(tempLeft);
    Serial.print(" tempLeft ");
    Serial.print(tempFrontL);
    Serial.print(" FrontL ");
    Serial.print(tempFrontR);
    Serial.print(" FrontR ");
    Serial.print('\n');
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("FrontD= ");
    lcd.setCursor(10,0);
   // lcd.print(tempFront);
    rotateLeftTimed(pwm/2);
  do 
  {
    digitalWrite(d1, LOW);
    digitalWrite(d2, LOW);
    analogWrite(s1, pwm/2.5);
    analogWrite(s2, pwm/2.5);
    tempFrontL = getFrontD();
    delay(60);
    tempFrontR = getFront1D();
      Serial.print(tempLeft);
    Serial.print(" tempLeft ");
    Serial.print(tempFrontL);
    Serial.print(" FrontL ");
    Serial.print(tempFrontR);
    Serial.print(" FrontR ");
    Serial.print('\n');
     lcd.setCursor(0,1);
    lcd.print("RF= ");
    lcd.setCursor(4,1);
    //lcd.print(tempRightFront);
     lcd.setCursor(7,1);
    lcd.print("RR= ");
    lcd.setCursor(12,1);
   // lcd.print(tempRightRear);
  } while(! (((((tempFrontL+4) - tempLeft) >= -5 && ((tempFrontL+4) - tempLeft) <= 5)) && ((tempFrontR+4) - tempLeft) >= -5 && ((tempFrontR+4) - tempLeft) <= 5));
   }
   }
  analogWrite(s1, 0);
  analogWrite(s2, 0);
  Serial.print(getRightFront());
  Serial.print(" Right Front ");
};


void rotateRightTimed(int pwm)
{
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  analogWrite(s1, pwm);
  analogWrite(s2, pwm);
  delay(750);
  //delay(1565); //almost perfect right turn
  analogWrite(s1, 0);
  analogWrite(s2, 0);
};

void rotateRight(int pwm)
{
  int CSide = checkRightTurn();
  //get and store front reading
  //rotate right until left sensors pick up reading
  //align using front sensors

  if(CSide == 1)
  {
    int tempFront = getFrontD();
    delay(60);
    int tempLeftFront = getLeftFront();
    delay(60);
    int tempLeftRear = getLeftRear();
    delay(60);
  //  int tempRightFront = getRightFront();
    Serial.print(tempFront);
    Serial.print(" tempFront ");
    Serial.print(tempLeftFront);
    Serial.print(" Left Front ");
    Serial.print(tempLeftRear);
    Serial.print(" Left Rear ");
    Serial.print('\n');
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("FrontD= ");
    lcd.setCursor(10,0);
    lcd.print(tempFront);
    rotateRightTimed(pwm/2);
  do 
  {
    digitalWrite(d1, HIGH);
    digitalWrite(d2, HIGH);
    analogWrite(s1, pwm/2.5);
    analogWrite(s2, pwm/2.5);
    tempLeftFront = getLeftFront();
    delay(60);
    tempLeftRear = getLeftRear();
    Serial.print(tempFront);
    Serial.print(" tempFront ");
    Serial.print(tempLeftFront);
    Serial.print(" Left Front ");
    Serial.print(tempLeftRear);
    Serial.print(" Left Rear ");
    Serial.print('\n');
     lcd.setCursor(0,1);
    lcd.print("LF= ");
    lcd.setCursor(4,1);
    lcd.print(tempLeftFront);
     lcd.setCursor(7,1);
    lcd.print("LR= ");
    lcd.setCursor(12,1);
    lcd.print(tempLeftRear);
  } while(! (((((tempLeftFront-4) - tempFront) >= -5 && ((tempLeftFront-4) - tempFront) <= 5)) && ((tempLeftRear-4) - tempFront) >= -5 && ((tempLeftRear-4) - tempFront) <= 5));
  }
  else
  {
     int tempRight = getRightFront();
    delay(60);
    int tempFrontL = getFrontD();
    delay(60);
    int tempFrontR = getFront1D();
    delay(60);
  //  int tempRightFront = getRightFront();
    Serial.print(tempRight);
    Serial.print(" tempRight ");
    Serial.print(tempFrontL);
    Serial.print(" Front Left ");
    Serial.print(tempFrontR);
    Serial.print(" Front Right ");
    Serial.print('\n');
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("FrontD= ");
    lcd.setCursor(10,0);
    lcd.print(tempRight);
    rotateRightTimed(pwm/2);
  do 
  {
    digitalWrite(d1, HIGH);
    digitalWrite(d2, HIGH);
    analogWrite(s1, pwm/2.5);
    analogWrite(s2, pwm/2.5);
    tempFrontL = getFrontD();
    delay(60);
    tempFrontR = getFront1D();
     Serial.print(tempRight);
    Serial.print(" tempRight ");
    Serial.print(tempFrontL);
    Serial.print(" Front Left ");
    Serial.print(tempFrontR);
    Serial.print(" Front Right ");
    Serial.print('\n');;
     lcd.setCursor(0,1);
    lcd.print("LF= ");
    lcd.setCursor(4,1);
   // lcd.print(tempLeftFront);
     lcd.setCursor(7,1);
    lcd.print("LR= ");
    lcd.setCursor(12,1);
   // lcd.print(tempLeftRear);
  } while(! (((((tempFrontL+4) - tempRight) >= -5 && ((tempFrontL+4) - tempRight) <= 5)) && ((tempFrontR+4) - tempRight) >= -5 && ((tempFrontR+4) - tempRight) <= 5));
  }
  analogWrite(s1, 0);
  analogWrite(s2, 0);
  Serial.print(getLeftFront());
  Serial.print(" Left Front "); 
};

void turnLeft(int Speed)
{
   rotateLeft(Speed);
   delay(1000);
   align(Speed);
   delay(1000);
  //while (getLeftRear() > 30)  //move forwared until Right rear < 30
 // {
  //  forward(Speed/3, Speed/3);  //slow down UNTIL
 // }
};

void turnRight(int Speed)
{
  rotateRight(Speed);
  delay(1300);
  align(Speed);
  delay(1000);
};

void rotateRightOneTime(int pwm)
{
  //get and store right reading
  //rotate right until front sensors pick up reading
  //
    int tempRight = getRightFront();
    delay(60);
    int tempFront = getFrontD();
    delay(60);
    
  //  int tempRightFront = getRightFront();
    Serial.print(tempRight);
    Serial.print(" tempRight ");
    Serial.print(tempFront);
    Serial.println(" Front ");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("FrontD= ");
    lcd.setCursor(10,0);
    lcd.print(tempFront);
    rotateRightTimed(pwm/2);
  do 
  {
    digitalWrite(d1, HIGH);
    digitalWrite(d2, HIGH);
    analogWrite(s1, pwm/2.5);
    analogWrite(s2, pwm/2.5);
    tempFront = getFrontD();
    delay(60);
    Serial.print(tempRight);
    Serial.print(" tempRight ");
    Serial.print(tempFront);
    Serial.println(" Front ");
  } while(! ((((tempFront+4) - tempRight) >= -5 && ((tempFront+4) - tempRight) <= 5)));//; && ((tempLeftRear-4) - tempFront) >= -4 && ((tempLeftRear-4) - tempFront) <= 4));
  analogWrite(s1, 0);
  analogWrite(s2, 0);
  Serial.print(getLeftFront());
  Serial.print(" Left Front "); 
};

void oneTimeRight(int Speed)
{
  rotateRightOneTime(Speed);
  delay(1300);
  alignFront(Speed);
  delay(1000);
}

int roomOrHallway(int Speed, int wall, int turnDirection, int &HT, int &RIH)
{
  Serial.print(Speed);
  Serial.print(" ");
  Serial.print(wall);
  Serial.print(" ");
  Serial.println(turnDirection);
  
  int modSpeed = Speed/2.7;
if(turnDirection ==1) //turning right
{
  if(wall ==1)//wall in front before turning,  ignore left wall
  {
    Serial.println(" WALL = 1");
    while(!((frontWhiteLine() || getRightRear() < 20)))  //(!(whiteline() || getLeftRear() < 30 || getRightRear() < 30))
        {
         forward(modSpeed, modSpeed); 
        }
        if(frontWhiteLine())
        {
          Serial.println("Found white line");
          while(!(backWhiteLine()))
          {
            forward(modSpeed, modSpeed);
          }
          stop();
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("ROOM DETECTED");
          Serial.println("Room");
          RIH++;
          return 1; //if room
        }
        else
        {
        stop();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("HALLWAY"); 
        Serial.println("Hallway");
        HT=0;
        RIH = 0;
        return 0; //if hallway
        }
        // alignFront(Speed);
        stop();
   }
   else // no wall in the front
   {
    Serial.println(" WALL = 0");
    bool whiteline = frontWhiteLine();
    //int leftRear = getLeftRear();
    int rightRear = getRightRear();
    while(!(whiteline || rightRear < 20))  //(!(whiteline() || getLeftRear() < 30 || getRightRear() < 30))
        {
        Serial.print("White line= ");
         Serial.println(whiteline);
         Serial.print("Right Rear ");
         Serial.println(rightRear);
          
          whiteline = frontWhiteLine();
          //delay(60);
          rightRear = getRightRear();
          //delay(60);
         forward(modSpeed, modSpeed); 
         
        }
        if(frontWhiteLine())
        {
          Serial.println("Front line detected");
          while(!(backWhiteLine()))
          {
            forward(modSpeed,modSpeed);
         Serial.println("detecting back whiteline");
          }
          Serial.println("FOUND back whiteline");
        stop();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ROOM DETECTED");
        Serial.println("Room");
        RIH++;
        return 1; //if room
        }
        else
        {
          stop();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("HALLWAY"); 
        Serial.println("Hallway");
        RIH = 0;
        return 0; //if hallway
        }
   }
}
else // turning left
 if(wall ==1)//wall in front before turning,  ignore right wall
  {
    Serial.println(" WALL =1");
    while(!((frontWhiteLine() || getLeftRear() < 20)))  //(!(whiteline() || getLeftRear() < 30 || getRightRear() < 30))
        {
         forward(modSpeed, modSpeed); 
        }
        if(frontWhiteLine())
        {
          while(!(backWhiteLine()))
          {
            forward(modSpeed,modSpeed);
          }
          stop();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ROOM DETECTED");
        Serial.println("Room");
        RIH ++;
        return 1; //if room
        }
        else
        {
          stop();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("HALLWAY"); 
        Serial.println("Hallway");
        RIH = 0;
        return 0; //if hallway
        }
        stop();
   }
   else // no wall in the front
   {
    Serial.println(" WALL =0");
    while(!(frontWhiteLine() || getLeftRear() < 30))  //(!(whiteline() || getLeftRear() < 30 || getRightRear() < 30))
        {
         forward(modSpeed, modSpeed); 
        }
        if(frontWhiteLine())
        {
          while(!(backWhiteLine()))
          {
            forward(modSpeed,modSpeed);
          }
          stop();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ROOM DETECTED");
        Serial.println("Room");
        RIH++;
        return 1; //if room
        }
        else
        {
        stop();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("HALLWAY"); 
        Serial.println("Hallway");
        RIH =0;
        return 0; //if hallway
        }
        stop();
   }
};

void spin(int pwm)
{
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  analogWrite(s1, pwm);
  analogWrite(s2, pwm);
  delay(2350);
  //delay(1165); //almost perfect right turn
  analogWrite(s1, 0);
  analogWrite(s2, 0);
};

void turnAround(int Speed, int &HT) // add more if not working right
{
  spin(Speed/2);
  align(Speed);
  HT=1;
};

void lastTurn(int Speed, int lTurn)
{
  if(lTurn == 1) // last turn was right
    {
      turnLeft(Speed);
    }
    else //last turn was left
    {
      turnRight(Speed);
    }

}


