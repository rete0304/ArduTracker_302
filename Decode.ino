void decode(void) 
{
  static char buffer[250]; //The traditional SERIAL buffer.
  static int counter=0; //Traditional counter

  while(mySerial.available() > 0) //Check and loop while any byte is in the Serial Buffer. 
  {
  
    buffer[counter]=mySerial.read();//Reading the byte
    if(buffer[counter]==0x0A)//Looks for \F, if not jump and continue receveing. 
    {

      if (strncmp (buffer,"!!!",3) == 0) //Looks for the !!! header
      {
        pan=Search_Float(buffer,"PCH:");//Pan Servo Value 
        tilt=Search_Float(buffer,"RLL:"); //Tilt Servo Value
        data_update_event|=0x01; //This is a manual flag to indicate new data has arrived.
      }
       
      for(int a=0; a<=counter; a++)//restarting the buffer
      {
        buffer[a]=0; //Clearing the buffer.
      } 
      counter=0; //Restarting the counter. 
    }
    else
    {
      counter++;//Incrementing the counter
    }
    
    if(counter >= 250)
    {
       for(int a=0; a<=counter; a++)//restarting the buffer
      {
        buffer[a]=0; //Clearing the buffer.
      } 
      counter=0; //Restarting the counter. 
      break;
    }
  }
  //  

}




//Very important functions:
float Search_Float(char buffer[],char looking[])
{
  char *BufferPointer=buffer;
  char *SearchString;
  SearchString= strstr (BufferPointer,looking); 
  return atof(SearchString+4);
}

int Search_Int(char buffer[],char looking[])
{
  char *BufferPointer=buffer;
  char *SearchString;
  SearchString= strstr (BufferPointer,looking); 
  return atoi(SearchString+4);
}

long Search_Long(char buffer[],char looking[])
{
  char *BufferPointer=buffer;
  char *SearchString;
  SearchString= strstr (BufferPointer,looking); 
  return atol(SearchString+4);
}

