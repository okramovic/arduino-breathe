#include <pcmConfig.h>
#include <pcmRF.h>
#include <TMRpcm.h>

#include <SD.h>
#include <SPI.h>
#define SD_ChipSelectPin 53

#include <TimeLib.h>


#define Sd2Card card;
#define SdVolume volume;
#define SdFile root;

//#define
TMRpcm sound;

//#define 
time_t t;

int back = 2;
int enter= 3;
int prev = 4;
int next = 5;

/*  previ5db   next5db  enter5db
//String Sprev = "previ5db.wav";
//String Snext = "next5db.wav";
//String Senter = "enter5db.wav";

//String names[]={Senter,Sprev,Snext};*/
/* sound names   
            bowlde5.wav
            kori_5db / kori_15
            woodcool /   wdcl10db
*/

String addT = "add timer";
String chooseT = "choose timer";

String mainItems[]={addT, chooseT};

String selSound = "selSound";
String selInter = "selInter";
String selRep   = "selRep";
String confTmr   = "confTmr";

String newTimerSets[]={selSound, selInter, selRep, confTmr};

String loc = "main";
int item = 0;




void setup()  {
  Serial.begin(9600);

  sound.speakerPin = 12;
  
  setTime(13,06,00,15,12,2017);
  t = now();

  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    //return;   // don't do anything more if not
  } else Serial.println("SD card OK");

  pinMode(back, INPUT);
  pinMode(enter, INPUT);
  pinMode(prev, INPUT);
  pinMode(next, INPUT);
  if (loc=="main") sound.play("mainmenu.wav");
}

void loop() {
  if (digitalRead(back) == HIGH){
      
      //Serial.println("show secs 1");
      Serial.println("BACK");
      exitItem();

      delay(500);
      
  } else if (digitalRead(enter) == HIGH){
      
      Serial.println("ENTER");
      
        //sound.play("enter5db.wav");
      enterItem();
      delay(500);

      
  } else if (digitalRead(prev) == HIGH){ //sound.play("previ5db.wav");
    
      Serial.println("PREV");
      chooseItem(-1);
      
      delay(500);
      
  } else if (digitalRead(next) == HIGH){  //sound.play("next5db.wav");
    
      Serial.println("NEXT");
      chooseItem(1);
      delay(500);
      
  }
}
void chooseItem(int n){
    item+=n;
    
    
    if (loc=="main"){
      
          if (item>1) item = 0;
          else if (item<0) item = 1;

          saySelection(mainItems[item]);

    } else if (loc=="new timer settings"){

          if (item>3) item = 0;
          else if (item<0) item = 3;

          saySelection(newTimerSets[item]);

    } else if (loc=="choose running timer"){

          Serial.println("choose running timer ->  NO CHOICES HERE");
    }
    Serial.println("item: ");
    Serial.print(item);

    
}
void saySelection(String choice){
      Serial.println("saySelection: ");
      Serial.print(choice);
      Serial.println();


      if (choice=="add timer"){
                sound.play("adnewtmr.wav");
                delay(1200);
      }
      else if (choice== "choose timer"){
                sound.play("chruntmr.wav");
                delay(1200);
      }

        // in adding new timer  
      else if (choice== "selSound"){
                sound.play("selsound.wav");
                delay(1200);
      }

      else if (choice== "selInter"){ 
                sound.play("selinter.wav");
                delay(1200);
      }

      else if (choice== "selRep"){
                sound.play("selrpts.wav");
                delay(1200);
      }

      else if (choice==  "confTmr"){
                sound.play("conftmr.wav");
                delay(1200);
      }
}
void announceLoc(String loc){
      Serial.println("location to announce: ");
      Serial.print(loc);
      Serial.println();
      
      if         ( loc=="main"){
                  sound.play("mainmenu.wav");
                  delay(1200);
                  
      } else if  ( loc=="new timer settings"){
                  sound.play("ntmrsets.wav");
                  delay(1500);
    
      } else if  ( loc== "choose running timer"){
                  sound.play("chruntmr.wav");
                  Serial.println("not set: choose running timer");
                  delay(1200);
      }

  
}


void enterItem(){
    Serial.println("enter item: ");
    //Serial.print(loc);

    if (loc=="main"){ 

        if (item==0){
                        loc="new timer settings";
          
        } else if (item==1){

                        loc="choose running timer";
        }
        announceLoc(loc);
        //enterItem();
    } //else if (loc == )
}

void exitItem(){
            Serial.println("exit item: ");

    if (loc=="main" || loc=="new timer settings"){
                Serial.println("IN MAIN MENU");
                delay(200);
                sound.play("mainmenu.wav");
        
    } else if (loc=="new timer settings"){

    } else if (loc=="choose running timer"){
    } //else if (loc==){}


}