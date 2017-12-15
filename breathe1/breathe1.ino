#include <SD.h>                      // need to include the SD library
//#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#define SD_ChipSelectPin 53  //using digital pin 4 on arduino nano 328, can use other pins
#include <TMRpcm.h>           //  also need to include this library...
#include <SPI.h>
// time stuff
#include <TimeLib.h>

TMRpcm sound;

Sd2Card card;
SdVolume volume;
SdFile root;



int show = 2;
int prev = 3;
int next = 4;

/* sound names   
 *          bowlde5.wav
            kori_5db / kori_15
            woodcool /   wdcl10db
*/

//  previ5db
//  next5db
//  enter5db

char Sprev = "previ5db.wav";
char Snext = "next5db.wav";
char Senter = "enter5db.wav";

//char names[]={Senter,Sprev,Snext};
time_t t;

void setup() {
  sound.speakerPin = 12; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc

  setTime(13,06,00,15,12,2017);
  t = now();
  
  Serial.begin(9600);

  Serial.println(hour());
  
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    //Serial.println("SD fail");  
    //return;   // don't do anything more if not
  } else Serial.println("SD card OK");
  
  pinMode(show, INPUT);
  pinMode(prev, INPUT);
  pinMode(next, INPUT);
  //sound.play("bowlde5.wav");

  // testing time
  
  
}

void loop() {

  if (digitalRead(prev) == HIGH){
      Serial.println("PREV pressed");
        sound.play("previ5db.wav");
      delay(2000);
      
  } else if (digitalRead(next) == HIGH){
      Serial.println("NEXT pressed");
        sound.play("next5db.wav");
      delay(2000);
      
  } else if (digitalRead(show) == HIGH){
      showTime();
      //Serial.println("show secs 1");
      Serial.println("SHOW pressed");
      
        sound.play("enter5db.wav");
      delay(2000);
  }
}


void showTime(){
    t = now();
    
    Serial.println("------");
    Serial.print(hour(t));
    Serial.print(":");
    Serial.print(minute(t));
    Serial.print(":");
    Serial.print(second(t));
    
    //Serial.println(timeStatus());
}


