  int getFrontD();
  int getLeftFront();
  int getRightFront();
  int getFront1D();
  int getLeftRear(); 
  int getRightRear();
  
  int getError()
  {
  long LFD,LRD,RFD,RRD,LE,RE,FD,F1D,centered;
  
    FD= getFrontD();
    delay(60);
    LRD= getLeftRear();
    delay(60);  
    RFD= getRightFront();
    delay(60);
    LFD= getLeftFront();
    delay(60);
     F1D= getFront1D();
    delay(60);
    RRD= getRightRear();
    delay(60);
  
  LE = LFD - LRD; // left error
  RE = RFD - RRD; // right error
  centered = LFD - RFD;
  
  serialprint(LFD, LRD, RFD, RRD, FD, LE, RE, F1D, centered);
  
  return centered;
  };
  
  int getLeftError() //returns the left error Left Front - Left Rear
  {
    int LFD = getLeftFront();
    delay(60);
    int LRD = getLeftRear();
    delay(60);
    int LE = LFD - LRD;
    return LE;
  };
  
  int getRightError() // returns the right error Right Front - Right Rear
  {
   int RFd = getRightFront();
   delay(60);
   int RRd = getRightRear();
   delay(60);
   int RE = RFd - RRd;
   return RE; 
  };
  
  int getFrontError() // returns the front error front left - front right
  {
    int FDL = getFrontD();
    delay(60);
    int FDR = getFront1D();
    int FE = FDL - FDR;
    Serial.print(FDL);
    Serial.print(" Front left  ");
    Serial.print(FDR);
    Serial.print(" Front Right");
    Serial.print('\n');
    
    return FE;
  };
 
  int getFrontD() //returns the distance of front left
  {
    long FD, FT;
    FT = sonar1.ping();
    FD =  sonar1.convert_cm(FT);
    return FD;
  };
  
   int getLeftFront()  // returns the distance of left front
  {
    long LFD, LFT;
    LFT = sonar2.ping();
    LFD =  sonar2.convert_cm(LFT);
    return LFD;
  };
  
  int getLeftRear()  // returns the distance of left Rear
   {
    long LRD, LRT;
    LRT = sonar3.ping();
    LRD =  sonar3.convert_cm(LRT);
    return LRD;
  };
  
  int getFront1D() // returns the distance of front right
  {
    long FD1, FT1;
    FT1 = sonar4.ping();
    FD1 =  sonar4.convert_cm(FT1);
    return FD1;
  };
  
  int getRightFront() //returns the distance of right front
  {
    long RFD, RFT;
    RFT = sonar5.ping();
    RFD =  sonar5.convert_cm(RFT);
    return RFD;
  };
 
  int getRightRear()  // returns the distance of right rear
  {
    long RRD, RRT;
    RRT = sonar6.ping();
    RRD =  sonar6.convert_cm(RRT);
    return RRD;
  };
  
  int getDE(int currentError) // returns value of derivative
  {
    int value;
    calDE[1] = calDE[0];
    calDE[0] = currentError;
    value = calDE[0]-calDE[1];
      
    return value;
  };
  
  int calc_error(int Speed) // used to calculate speed differnce using pid calculation
{  
  int currentError = getError();
  int speed_diff = (currentError * KP) + (KD * getDE(currentError)); //pid
  if(speed_diff > Speed)
  {
    speed_diff = Speed;
   return speed_diff; 
  }
  else if(speed_diff < -Speed)
  {
    speed_diff = -Speed; 
   return speed_diff; 
  }
  else
 {
   return speed_diff;
 }
};

int getReadings()
{
  int RF, LF, RR, LR, F, F1;

  F= getFrontD();
  delay(60);
  LF= getLeftFront();
  delay(60);
  RF= getRightFront();
  delay(60);
  F1= getFront1D();
  delay(60);
  LR= getLeftRear();
  delay(60);
  RR= getRightRear();
  delay(60);
  serialprinttest(LF, LR, RF, RR, F, F1);
  lcd.clear();
  //checkfeedback(LF, RF, LR, RR);

};


