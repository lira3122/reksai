void serialprint(int lfd, int lrd, int rfd, int rrd, int FD, int LE, int RE, int FD1, int centered)
{
Serial.print(lfd); // print out to serial the distance of all the sensors
Serial.print(" lfd, ");
Serial.print(lrd);
Serial.print(" lrd, ");
Serial.print(rfd);
Serial.print(" rfd, ");
Serial.print(rrd);
Serial.print(" rrd, ");
Serial.print(FD);
Serial.print(" Fd, ");
Serial.print(FD1);
Serial.print(" Fd1, ");
Serial.print('\n');
Serial.print(LE);
Serial.print(" Left Error,  ");
Serial.print(RE);
Serial.print(" Right Error");
Serial.print('\n');
Serial.print(centered);
Serial.print(" Centered");
Serial.print('\n');
delay(5);
};

void serialprinttest(int lfd, int lrd, int rfd, int rrd, int FD, int FD1)
{
Serial.print(lfd); // print out to serial the distance of all the sensors
Serial.print(" lfd, ");
Serial.print(lrd);
Serial.print(" lrd, ");
Serial.print(rfd);
Serial.print(" rfd, ");
Serial.print(rrd);
Serial.print(" rrd, ");
Serial.print(FD);
Serial.print(" Fd, ");
//Serial.print('\n');
Serial.print(FD1);
Serial.print(" Fd1, ");/*
Serial.print(" Left Error,  ");
Serial.print(RE);
Serial.print(" Right Error");
Serial.print('\n');
Serial.print(centered);
Serial.print(" Centered");*/
Serial.print('\n');
delay(5);
};

void arrayInfo(int array[10][3],int columns, int rows, int count, int rooms, int hallways, int turns, int RIH)
{
  Serial.print("Rooms in Hallway = ");
  Serial.println(RIH);
  for(int i=0; i < rows; i++)
  {
    for(int j=0; j<count; j++)
    {
    Serial.print("Row ");
    Serial.print(i);
    Serial.print(" Column ");
    Serial.println(j);
    Serial.print(array[i][j]);
    Serial.print('\n');  
    } 
  }
}
