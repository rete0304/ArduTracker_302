#include <avr/io.h>
#include <Servo.h> 
#include <SoftwareSerial.h>
// ArduTracker v1.0 - 01/10/2010
// By HappyKillmore (Paul Mather) and Diego Colonnello
// Most of this source comes from ArduPilot 2.3.1 by Chris Anderson & Jordi Munoz
// Current Implementation designed to work with "PanTilt" Output Mode on HappyKillmore's GCS
// http://code.google.com/p/happykillmore-gcs/

// Designed for use with ArduPilot original (not Mega) - http://www.sparkfun.com/search/results?term=ardupilot&what=products
// Connected via FTDI cable - http://www.sparkfun.com/search/results?term=ftdi&what=products
// Pan servo connected to Out 1
// Tilt servo connected to Out 2

long timeNow=0; // Hold the milliseond value for now
long timer=0;   //general purpuse timer
long timer_old;

int pan=1500;
int tilt=1500; 
byte data_update_event=1;//New data flag 
Servo myservo1;
Servo myservo2;
SoftwareSerial mySerial(2, 3); // RX, TX

void setup()
{
    Serial.begin(38400); //Serial  
    myservo1.attach(9);
    myservo2.attach(10);
    mySerial.begin(38400);
}

void loop()
{
timeNow = millis();
 
  if((timeNow-timer)>=20)  // Main loop runs at 50Hz
  {
    timer_old = timer;
    timer = timeNow;
    int vaar=0;
    

    
    decode(); //Decoding data comming from ArduIMU
    
    if((data_update_event&0x01)==0x01)
    {
        //pith->pan
        //roll->tilt;
        data_update_event=0;
        Serial.print(pan);
        Serial.print(",");
        Serial.print(tilt);
        Serial.println();
        myservo1.write(pan+90);
        myservo2.write(tilt+90); 
         
    }
  }
}

