void backOutRoom(int Speed);

void forward(int L_Speed, int R_Speed) // Spins the motors in the same direction to move 
{                                      // the robot forward at Left & right motor speed
  digitalWrite(d1, LOW);
  digitalWrite(d2, HIGH);
  analogWrite(s1, R_Speed);
  analogWrite(s2, L_Speed);
  //delay(5);
};

void backwards(int L_Speed, int R_Speed) // Spins the motors in the same direction to move 
{                                      // the robot backwards at Left & right motor speed
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  analogWrite(s1, R_Speed);
  analogWrite(s2, L_Speed);
  //delay(5);
};

void stop()                          //stops the motors from spinning
{
  digitalWrite(d1, LOW);
  digitalWrite(d2, HIGH);
  analogWrite(s1, 0);
  analogWrite(s2, 0);
};

void pause()                        // stops the motors from spinnning with a 100ms delay
{
  digitalWrite(d1, LOW);
  digitalWrite(d2, HIGH);
  analogWrite(s1, 0);
  analogWrite(s2, 0);
  delay(100);
};

void alignFront(int Speed)        //use the front sensors to align/straighten with the wall in front
{
  int FE = getFrontError();        //get error front the 2 front sensors
  Serial.print("FE ");            //print error to screen
  Serial.println(FE);
  while ( !(FE >=-1 && FE <= 1) )   //checks if sensors readings are -1,0,1 if not enter look
  {
    if (FE > 1)                    //error greater than 1, align Right ( left side is further from wall)
    {
      digitalWrite(d1, HIGH);
      digitalWrite(d2, HIGH);
      analogWrite(s1, Speed/3);    //controls speed of adjustment
      analogWrite(s2, Speed/3);
      FE = getFrontError();  
      Serial.println("aligning right");
    }
    else //if (FE < -1)          //Error wil be less than -1 so it will align left( right side further from wall)
    {
      digitalWrite(d1, LOW);
      digitalWrite(d2, LOW);
      analogWrite(s1, Speed/3);  //contrls speed of adjustment
      analogWrite(s2, Speed/3);
      FE = getFrontError(); 
      Serial.println("alignting left");   
    }
  }
  analogWrite(s1, 0);    //once error is -1,0,1 will stop the motors from turning
  analogWrite(s2, 0);
  Serial.println("stop");  
  stop();                //stops the motors from spinning with a delay of 10 seconds
};

void align(int Speed)  //function used to align with side walls  NOT WORKING WELL
{

  int alignSpeed = 40;
  
  //check if left or right is closer and use closer to align
  int centered = getError();
  int alignerror;
  int side; // 1 = right , 0 = left
  Serial.println(centered);

  if(centered < 1)
  {
    alignerror = getLeftError();
    Serial.println("using left error ");
    side = 0;
  }
  else
  {
    alignerror = getRightError(); 
    Serial.println("using right error ");
    side =1;
  }

 
  Serial.print(alignerror);
  Serial.println(" alignError");
  Serial.print(side);
  Serial.println(" side");

  while( !(alignerror >=-1&& alignerror <=1)) //(alignerror >=-1 && alignerror <= 1)
  {
    Serial.println(alignerror);    
    if(side==0) //left wall closer
    {
      if(alignerror >=1) //front part of robot closer to wall  1
      {
        Serial.println(" needs to move left");
        digitalWrite(d1, LOW);
        digitalWrite(d2, LOW);
        analogWrite(s1, alignSpeed);//left reverse speed/4
        analogWrite(s2, alignSpeed);//right forward speed/4
        alignerror = getLeftError(); 
        
      }
      else if(alignerror <= -1) //-1
      {
         Serial.println(" needs to move right");
        digitalWrite(d1, HIGH);
        digitalWrite(d2, HIGH);
        analogWrite(s1, alignSpeed);//left forwared speed/4
        analogWrite(s2, alignSpeed);//right reverse speed/4
        alignerror = getLeftError();  
       
      }
      else
      {
        analogWrite(s1, 0);
        analogWrite(s2, 0);
        Serial.println("stopping");
        alignerror = getLeftError();
      }
    }
   else//right wall closer
    {
      if(alignerror >= 1) // front part of robot is closer to wall  1
      {
        Serial.println( " needs to move right");
        digitalWrite(d1, HIGH);
        digitalWrite(d2, HIGH);
        analogWrite(s1, alignSpeed);//left reverse speed/4
        analogWrite(s2, alignSpeed);//right forward speed/4
        alignerror = getRightError();  
      }
      else if(alignerror <= -1) //-1
      {
        Serial.println( " needs to move left");
        digitalWrite(d1, LOW);
        digitalWrite(d2, LOW);
        analogWrite(s1, alignSpeed);//left forwared speed/4
        analogWrite(s2, alignSpeed);//right reverse speed/4
        alignerror = getRightError();  
      }
      else
      {
        analogWrite(s1, 0);
        analogWrite(s2, 0);
        Serial.println("stopping");
        alignerror = getRightError();
      }
    }
  }
  analogWrite(s1, 0);
  analogWrite(s2, 0);
};

void selectAlign(int HT, int Speed)
{
  if(HT == 1)
  {
    Serial.println("Using Align");
    align(Speed);
  }
  else
  {
     Serial.println("Using Align FRONT");
    alignFront(Speed);
  }
};

void determineAlign(int Speed)
{
 int fError, lError, rError;

    fError = getFrontError();
    lError = getLeftError();
    rError = getRightError();

    if(fError > 20 && fError < -20)
    {
      align(Speed);
    }
    else
    {
      if(fError < lError && fError < rError)
      {
        alignFront(Speed);
      }
      else
      {
        align(Speed);
      }
    }
};

void centerOpening(int side, int Speed)  //move forward a bit when an opening is detected.
{                                        //optimize so it can use sensors to detect where it's at
  if(side == 1) // opening to right
  {
    while(getRightRear() < 30)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("RIGHT REAR");
      Serial.println("right rear wall");
      forward(Speed/2, Speed/2);
    }
    Serial.println("cleared right rear wall");
    forward(Speed/3, Speed/3); // move forward a bit to be in hallway
    delay(740);
    stop();
  }
  else 
  {
    while(getLeftRear() < 30)
    {

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("left rear");
      forward(Speed/2, Speed/2);
    }
     Serial.println("cleared left rear wall");
    forward(Speed/3, Speed/3);//move forward a bit to be in hallway
    delay(750);
    stop();
  }
};

void center(int Speed)
{
  forward(Speed/3, Speed/3); // move forward a bit to be in hallway
    delay(500);
    stop();
}

void clearOpeningFrontSensor(int Speed, int side)
{
    //side =1 right side
    //side =0 left side
   if(side == 1) // opening to right
  {
    while(getRightFront() > 25)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("RIGHT Opening");
      Serial.println("RIGHT Opening");
      forward(Speed/2, Speed/2);
    }
    Serial.println("Right wall detected");
    delay(10);
    //forward(Speed/3, Speed/3); // move forward a bit to be in hallway
    //delay(500);
    stop();
  }
  else if(side ==0)
  {
    while(getLeftFront() > 25)
    {

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("LEFT Opening");
      Serial.println("Left Opening");
      forward(Speed/2, Speed/2);
    }
     Serial.print("Left wall detected");
     delay(10);
    //forward(Speed/3, Speed/3);//move forward a bit to be in hallway
    //delay(850);
    stop();
  }
  else // both sides are open
  {
    while((getLeftFront() > 25) && (getRightFront() > 25))
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("LEFT & Right Opening");
      Serial.println("Left & Right Opening");
      forward(Speed/2, Speed/2);
    }
     Serial.print("Left & Right wall detected");
    //forward(Speed/3, Speed/3);//move forward a bit to be in hallway
    //delay(850);
    stop();
  }
};

void HallNav(int &Speed, int turnHistory[][3], int &arrayCount, int columns, int rows, int &roomCount, int &hallways, int &halfTurns, int &RIH)
{
  //ie = 0;    // ie = e + ie
  //de = 0;    // de = e - pe

  int RE = 0;

  // RE = calc_error(Speed); //PID calc
 
  int tempRight = getRightFront();
  delay(60);
  int tempLeft = getLeftFront();
  delay(60);

//arrayInfo(turnHistory, columns, rows, arrayCount, roomCount ,hallways,halfTurns);

Serial.print("tempRight= " );
Serial.println(tempRight);
Serial.print("tempLeft= ");
Serial.println(tempLeft );
  

  if((tempRight > 30) && (tempLeft < 30)) //opening to the right
  {
    Serial.println("opening to the right only");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("opening Right");  
    centerOpening(1, Speed); // center opening with opening on the right
    // forward(Speed/3, Speed/3);
     delay(1000);
    align(Speed);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("aligned w/front");
    Serial.println("aligned");
    delay(1000);
    //check if front wall is less than 10
    int tempFront = getFrontD();
    int tempWall;
    if(tempFront < 15)
    {
      tempWall = 1;
    }
    else
    {
      tempWall = 0;
    }
    Serial.println("turning right");
    turnRight(Speed);
    turnHistory[arrayCount][0] = 1;
    Serial.println("checking if room or hallway");
    int tempRH = roomOrHallway(Speed, tempWall, 1, halfTurns, RIH); //returned 1 for room, or 0 for hallway
    turnHistory[arrayCount][1] = tempRH;
      if(tempRH ==0)
      {
       hallways++;
       Serial.println("hallway after turning right only");
      }
      else {
        delay(1000);
        Serial.println("room after turning right only");
        roomCount++;
        RIH++;
        exploreRoom();
        //scan room
        backOutRoom(Speed);
        lastTurn(Speed, 1);
      }
    arrayCount++; //update array counter
    delay(1000);
     int tempF = getFrontD();
    int tempW;
    if(tempF < 10)
    {
      tempW = 1;
    }
    else
    {
      tempW = 0;
    }
    if(tempW)
    {
      //turn around
    }
    else
    {
     //centerOpening(1, Speed);
    }
  }
  else if((tempRight < 30) && (tempLeft> 30)) //opening on the left
  {
    Serial.println("opening to the left only");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("opening left");
    centerOpening(0, Speed);
    delay(1000);
    align(Speed);
     Serial.println("aligned");
    delay(1000);
    //check if front wall is less than 10
    int tempFront = getFrontD();
    int tempWall;
    if(tempFront < 15)
    {
      tempWall = 1;
    }
    else
    {
      tempWall = 0;
    }
    Serial.println("turning left");
    turnLeft(Speed);
    turnHistory[arrayCount][0] = 0; // passing in turn took to array
    int tempRH = roomOrHallway(Speed, tempWall, 0, halfTurns, RIH); //returned 1 for room, or 0 for hallway
    turnHistory[arrayCount][1] = tempRH;
     if(tempRH ==0)
      {
       hallways++;
       Serial.println("hallway after turning left only");
      }
      else {
        delay(1000);
        Serial.println("room after turning left only");
        roomCount++;
        RIH++;
        exploreRoom();
        //scan room   
         backOutRoom(Speed);
        lastTurn(Speed, 0);    
      }
    arrayCount++; //update array counter
    delay(1000);
     int tempF = getFrontD();
    int tempW;
    if(tempF < 10)
    {
      tempW = 1;
    }
    else
    {
      tempW = 0;
    }
    if(tempW)
    {
      //turn around
    }
    else
    {
    //centerOpening(0, Speed);
    }
  }
  else if( (tempRight > 30)&& (tempLeft > 30)) // right side priority/ open left & right
  {
    Serial.println("opening to the right & left");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("opening left & right"); 
    centerOpening(1, Speed);
    delay(1000);
    align(Speed);
     Serial.println("aligned");
    delay(1000);
    //check if front wall is less than 10
    //turn into right room
    int tempFront = getFrontD();
    int tempWall;
     if(tempFront < 15)
     {
      tempWall = 1;
     }
     else 
     {
      tempWall = 0;
     }
    Serial.println("turning right");
    turnRight(Speed);
    turnHistory[arrayCount][0] = 1; // passing in turn took to array
    int tempRH = roomOrHallway(Speed, tempWall, 1, halfTurns, RIH); //returned 1 for room, or 0 for hallway
    turnHistory[arrayCount][1] = tempRH;
    arrayCount++; //update array counter
    
     if(tempRH ==0)
      {
        hallways++;
        Serial.println("hallway after left & right opening only(turned right)");
      }
      else
      {
        delay(1000);
        Serial.println("found room after left & right opening only(turned left)");
        roomCount++;
       RIH++;
       exploreRoom();
        //scan room
        //if (flame)
        //extinguish();
        //else//check right room if no flame go in the left
        
           backOutRoom(Speed);//back out of right room
           lastTurn(Speed, 1);
           delay(1000);
           //turn into left room
           tempFront = getFrontD();
           tempWall;
           if(tempFront < 15)
             {
              tempWall = 1;
             }
          else
            {
              tempWall = 0;
            }
           Serial.println("turning left");
           turnLeft(Speed);
           turnHistory[arrayCount][0] = 0; // passing in turn took to array
           tempRH = roomOrHallway(Speed, tempWall, 0, halfTurns, RIH); //returned 1 for room, or 0 for hallway
           turnHistory[arrayCount][1] = tempRH;
           if(tempRH ==0)
             {
             hallways++;
             Serial.println("hallway left & right opening only (left side)");
             }
             else 
             {
              delay(1000);
              Serial.println("found room left & right opening only (left side)");
               roomCount++;
               RIH++;
               exploreRoom();
               //scan room
               //if (no flame backout)
               backOutRoom(Speed);
               lastTurn(Speed, 1);
               delay(1000);
              }
           arrayCount++; //update array counter
           delay(1000);
           //turn 180 degrees, no more rooms down this hallway.
           halfTurns++;
      }
  } 
  else // continue hall navigation
  {
     RE = calc_error(Speed);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("hall nav");
    Serial.println("hall nav forward");
    if(RE < 0)
    {
      forward(Speed - RE, Speed);
    }
    else if(RE > 0)
    {
      forward(Speed, Speed + RE);
    }
    else
    {
      forward(Speed, Speed);
    } 
  }
};

void backOutFine(int Speed)
{
  backwards(Speed/2, Speed/2);
    delay(1650);
    stop();
};

void backOutRoom(int Speed)
{
  backwards(Speed/2, Speed/2);
  while(frontWhiteLine());
  {
    //do nothing until white line detected/ continue going backwards
  }
  stop();
  backOutFine(Speed);
};
