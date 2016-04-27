void mod_HallNav(int &Speed, int turnArray[][3], int &AC, int col, int row, int &RC, int &HW, int &HT, int &RIH)
{
  //ie = 0;    // ie = e + ie
  //de = 0;    // de = e - pe
Serial.println("STARTING MOD_HALLNAV");
  int RE = 0;
  int tempRight = getRightFront();
  delay(60);
  int tempLeft = getLeftFront();
  delay(60);
arrayInfo(turnArray, col, row, AC, RC ,HW, HT, RIH);



if(tempRight > 25 || tempLeft > 25)//RIH > 0 && HT ==1
{
  Serial.println("RIH > 0 && HT ==1");
  if((tempRight > 30) && (tempLeft < 30)) //opening to the right
  {
    Serial.println("RIGHT OPENING checking array");
    if((turnArray[AC-1][1] == 1) && (turnArray[AC-1][0]==0) && HT ==1)
    {
      clearOpeningFrontSensor(Speed, 1);//forward until front sensor <25, count--; RIH--;
      AC--;
      RIH--;
    }
    else
    {
    Serial.println("Opening to the right only");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Opening Right");  
    centerOpening(1, Speed); // center opening with opening on the right
    // forward(Speed/3, Speed/3);
     delay(1000);
    selectAlign(HT, Speed);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Aligned w/front");
    Serial.println("Aligned");
    delay(1000);
    //check if front wall is less than 10
    int tempFront = getFrontD();
    int tempWall;
    if(tempFront < 20)
    {
      tempWall = 1;
    }
    else
    {
      tempWall = 0;
    }
    Serial.println("Turning Right");
    turnRight(Speed);
    turnArray[AC][0] = 1;
    int tempRH = roomOrHallway(Speed, tempWall, 1, HT, RIH); //returned 1 for room, or 0 for hallway
    turnArray[AC][1] = tempRH;
      if(tempRH ==0)
      {
       HW++;
       Serial.println("HALLWAY RIGHT OPENING ONLY");
      }
      else {
        delay(1000);
        Serial.println("FOUND ROOM RIGHT OPENING ONLY");
        RC++;
        exploreRoom();
        //scan room
        backOutRoom(Speed);
        lastTurn(Speed, 1);
      }
    
    AC++; //update array counter
    delay(1000);
    }
    int tempFront = getFrontD();
    int tempW;
    if(tempFront < 20)
    {
      tempW = 1;
    }
    else
    {
      tempW = 0;
    }
    if(tempW)
    {
      turnAround(Speed, HT);//turn around
    }
    else
    {
      clearOpeningFrontSensor(Speed, 1);
    }
  }
  else if((tempRight < 30) && (tempLeft> 30)) //opening on the left
  {
    Serial.println("LEFT OPENING");
    if((turnArray[AC-1][1] ==1) && (turnArray[AC-1][0] ==1) && HT ==1)
    {
      Serial.println("LEFT OPENING Checking Array");
      clearOpeningFrontSensor(Speed, 0);//forward until front Left sensor <25, count--; RIH--;
      AC--;
      RIH--;
    }
    else
    {
    Serial.println("Opening to the left only");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Opening Left");
    centerOpening(0, Speed);
    delay(1000);
    determineAlign(Speed);
     Serial.println("Aligned");
    delay(1000);
    //check if front wall is less than 10
    int tempFront = getFrontD();
    int tempWall;
    if(tempFront < 20)
    {
      tempWall = 1;
    }
    else
    {
      tempWall = 0;
    }
    Serial.println("Turning Left");
    turnLeft(Speed);
    turnArray[AC][0] = 0; // passing in turn took to array
    int tempRH = roomOrHallway(Speed, tempWall, 0, HT, RIH); //returned 1 for room, or 0 for hallway
    turnArray[AC][1] = tempRH;
     if(tempRH ==0)
      {
       HW++;
       Serial.println("HALLWAY LEFT OPENING ONLY");
      }
      else {
        delay(1000);
        Serial.println("FOUND ROOM LEFT OPENING ONLY");
        RC++;
        exploreRoom();
        //scan room   
         backOutRoom(Speed);
        lastTurn(Speed, 0);    
      }
    AC++; //update array counter
    delay(1000);
     int tempF = getFrontD();
    int tempW;
    if(tempF < 20)
    {
      tempW = 1;
    }
    else
    {
      tempW = 0;
    }
    if(tempW)
    {
     turnAround(Speed, HT);
      
    }
    else
    {
      clearOpeningFrontSensor(Speed, 0);
    }
    }
  }
  else if( (tempRight > 30)&& (tempLeft > 30)) // right side priority/ open left & right
  {
    Serial.println("LEFT & RIGHT OPENING");
    if(AC > 1)
    {
      if((turnArray[AC-1][1] ==1) && (turnArray[AC-2][1] ==1) && HT ==1)
      {
        Serial.println("LEFT & RIGHT OPENING Checking Array");
        clearOpeningFrontSensor(Speed, 2);//forward until both sensors read < 25
        AC = AC-2;
        RIH = RIH-2;
      }
      else
       {
        Serial.println("Opening to the right & Left");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Opening Left & Right"); 
        centerOpening(1, Speed);
        determineAlign(Speed);
        Serial.println("Aligned");
        delay(1000);
        //check if front wall is less than 10
        //turn into right room
        int tempFront = getFrontD();
        int tempWall;
        if(tempFront < 20)
          {
          tempWall = 1;
          }
        else 
          {
          tempWall = 0;
           }
        Serial.println("Turning Right");
        turnRight(Speed);
        turnArray[AC][0] = 1; // passing in turn took to array
        int tempRH = roomOrHallway(Speed, tempWall, 1,HT, RIH); //returned 1 for room, or 0 for hallway
        turnArray[AC][1] = tempRH;
        AC++; //update array counter
          if(tempRH ==0)
          {
            HW++;
            Serial.println("HALLWAY LEFT & RIGHT OPENING ONLY");
          }
          else
          {
            delay(1000);
            Serial.println("FOUND ROOM LEFT & RIGHT OPENING ONLY");
            RC++;
            //scan room
            exploreRoom();
            //if (flame)
            //extinguish();
            //else//check right room if no flame go in the left
            Serial.println("backing out of room");
            backOutRoom(Speed);//back out of right room
            lastTurn(Speed, 1);
            delay(1000);
            //turn into left room
            tempFront = getFrontD();
            tempWall;
            if(tempFront < 20)
             {
              tempWall = 1;
             }
            else
             {
              tempWall = 0;
             }
            Serial.println("Turning Left");
            turnLeft(Speed);
            turnArray[AC][0] = 0; // passing in turn took to array
            tempRH = roomOrHallway(Speed, tempWall, 0, HT, RIH); //returned 1 for room, or 0 for hallway
            turnArray[AC][1] = tempRH;
            if(tempRH ==0)
             {
              HW++;
              Serial.println("HALLWAY LEFT & RIGHT OPENING ONLY(lEFT SIDE)");
             }
            else 
             {
              delay(1000);
              Serial.println("FOUND ROOM LEFT & RIGHT OPENING ONLY ( LEFT SIDE)");
              RC++;
              //scan room
              exploreRoom();
              //if (no flame backout)
              Serial.println("Backing out");
              backOutRoom(Speed);
              lastTurn(Speed, 0);
              delay(1000);
             }
            AC++; //update array counter
            delay(1000);
            turnAround(Speed, HT);//turn 180 degrees, no more rooms down this hallway.
            HT++;
          }
      }
  }
  else
   {
    Serial.println("Opening to the right & Left");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Opening Left & Right"); 
    centerOpening(1, Speed);
    delay(1000);
    determineAlign(Speed);
     Serial.println("Aligned");
    delay(1000);
    //check if front wall is less than 10
    //turn into right room
    int tempFront = getFrontD();
    int tempWall;
     if(tempFront < 20)
     {
      tempWall = 1;
     }
     else 
     {
      tempWall = 0;
     }
    Serial.println("Turning Right");
    int frontleft = getFrontD();
    int frontright = getFront1D();
    if((frontright - frontleft) > 50)
    {
      oneTimeRight(Speed);
    }
    else
    {
      turnRight(Speed);
    }
    turnArray[AC][0] = 1; // passing in turn took to array
    int tempRH = roomOrHallway(Speed, tempWall, 1, HT, RIH); //returned 1 for room, or 0 for hallway
    turnArray[AC][1] = tempRH;
    AC++; //update array counter
    
     if(tempRH ==0)
      {
        HW++;
        Serial.println("HALLWAY LEFT & RIGHT OPENING ONLY");
      }
      else
      {
        delay(1000);
        Serial.println("FOUND ROOM LEFT & RIGHT OPENING ONLY");
        RC++;
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
           if(tempFront < 20)
             {
              tempWall = 1;
             }
          else
            {
              tempWall = 0;
            }
           Serial.println("Turning Left");
           turnLeft(Speed);
           turnArray[AC][0] = 0; // passing in turn took to array
           tempRH = roomOrHallway(Speed, tempWall, 0, HT, RIH); //returned 1 for room, or 0 for hallway
           turnArray[AC][1] = tempRH;
           if(tempRH ==0)
             {
             HW++;
             Serial.println("HALLWAY LEFT & RIGHT OPENING ONLY(lEFT SIDE)");
             }
             else 
             {
              delay(1000);
              Serial.println("FOUND ROOM LEFT & RIGHT OPENING ONLY ( LEFT SIDE)");
               RC++;
               exploreRoom();
               //scan room
               //if (no flame backout)
               backOutRoom(Speed);
               lastTurn(Speed, 1);
               delay(1000);
              }
           AC++; //update array counter
           delay(1000);
           //turn 180 degrees, no more rooms down this hallway.
           HT++;
        } 
     }
  }
}
  else // continue hall navigation
  {
    Serial.print("hallnav no openings");
     RE = calc_error(Speed); //PID calc
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Hall Nav");
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
