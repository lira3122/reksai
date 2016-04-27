bool whiteline()
{
  uint16_t clear, red, green, blue;
  tcs.setInterrupt(false);      // turn on LED
  delay(60);  // takes 50ms to read 
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);  // turn off LED
  //Serial.print("C:\t "); Serial.print(clear);Serial.print(" Red "); Serial.print(red);Serial.print(" green "); Serial.print(green);Serial.print(" blue "); Serial.println(blue);
  
  if (clear<600)
    {
  return false;  
    }
else if (clear>600)
    {
  return true;
    }
};

bool frontWhiteLine()
{
        tcaselect(0);
        bool tmp = whiteline();
        Serial.println(tmp);

         if(tmp == 1)
          {
            return 1;
          }
         else
         {
          return 0;
         }
};

/* Function: backWhiteLine
 * Summary: Uses back two sensors to detect white line
 *          Return 1 if white line detected
 *          Return 0 if no white line detected
*/
bool backWhiteLine()            
{
  bool tmp1=0, tmp2=0;
  
  for(int j = 3; j <= 4 ; j++) 
  {
    if(j==3)
      {
        tcaselect(2);
        tmp1 = whiteline();
        if(tmp1 == 1)
          {
            return 1;
          }
         else{}
      }
      else if(j==4)
      {
        tcaselect(3);
       tmp2 = whiteline();
       if(tmp2 == 1)
          {
           return 1;
          }
         else{}
      }
  }
  return 0;
    
};
