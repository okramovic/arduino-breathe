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
int unis = 6;


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

String soundChoices[]={String("korimako"), String("bowl deep"), String("wood cool")};

String units = "units";
int intervalChoicesUnits[]={0,1,2,3,4,5,6,7,8,9};
int intervalChoicesTens[]={0,10,20,30,40,50,60};

String loc = "main";
int item = 0;

String alarmSound;
int alarmInterval;
int alarmRepeats;
int alarmRemains;



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
  pinMode(enter,INPUT);
  pinMode(prev, INPUT);
  pinMode(next, INPUT);
  pinMode(unis, INPUT);
  
  //  nmwc  units   tens
  if (loc=="main") sound.play("mainmenu.wav");  //sound.play("num04.wav");//
}


void loop() {

  if (digitalRead(unis) == HIGH){
      
      delay(500);
      
      if (units=="units") units="tens";
      else units = "units";

      Serial.print("UNITS: "); Serial.println(units);
      
        
      
      
  }
  else if (digitalRead(back) == HIGH){
      
      
      Serial.println("BACK");
      exitItem();
        
      delay(500);
      
  } else if (digitalRead(enter) == HIGH){
      
      Serial.println("ENTER");
      
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


////////////////////////////////////////////

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



    //  sel sound
     else if (loc=="select sound"){

          if (item>2) item = 0;
          else if (item<0) item = 2;

          saySelection(soundChoices[item]);

              alarmSound = soundChoices[item];
      }

      //  reacting on PREV or NEXT
      else if (loc=="select interval"){
        
                        if (units =="units"){
                        
                              if (item>9) item = 0;
                              else if (item<0) item = 9;

                              sayNumber(intervalChoicesUnits[item]);
                              delay(300);
                              
                        } else if (units=="tens"){
              
                              if (item>6) item = 0;
                              else if (item<0) item = 6;

                              sayNumber(intervalChoicesTens[item]);
                              delay(300);
                        }
                        
                        //alarmInterval = 
      }
      
      //  reacting on PREV or NEXT
      else if (loc=="select repeats"){

                        if (units =="units"){
                        
                              if (item>9) item = 0;
                              else if (item<0) item = 9;

                              sayNumber(intervalChoicesUnits[item]);
                              delay(300);
                              
                        } else if (units=="tens"){
              
                              if (item>6) item = 0;
                              else if (item<0) item = 6;

                              sayNumber(intervalChoicesTens[item]);
                              delay(300);
                        }
      }

      else if (loc=="confirm timer"){

                  item = 0;
                  saySelection( String("confirm timer") );

          
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


            // in selecting alarm sound   
            //  soundChoices[]={String("korimako"), String("bowl deep"), String("wood cool")};
            
                    else if (choice==  "korimako"  ){
                                sound.play("nmkorimk.wav");
                                delay(1200);
        
                                
                    } else if (choice==  "bowl deep"  ){
                              sound.play("nmbowdee.wav");
                              delay(1200);
        
                              
                    } else if (choice==  "wood cool"  ){
                              sound.play("nmwc.wav");
                              delay(1200);
                              
                    }
                    
            //  confirming new timer
                    else if (choice==  "confirm timer"  ){
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

                                      ////  ENTER


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

        
    } else if (loc == "new timer settings"){

                    // select sound
                    if (item==0){
                            loc="select sound";
                      }
                    
                    // select interval
                    else if (item==1){
                            loc="select interval";
                      }
        
                    // select repeats
                    else if (item==2){
                            loc="select repeats";
                      }
        
                    // confirm timer
                    else if (item==3){
                            loc="confirm timer";
                      }
                      
                    announceLoc(loc);  
      }
}


                                   /////   EXIT

void exitItem(){

      Serial.println("exit item");

      if (loc=="main"){ 
              Serial.println("IN MAIN MENU");
              
              //announceLoc(loc);
      }

      // if in first level
      else if (loc=="new timer settings" || loc=="choose running timer"){
                  loc = "main";  
                  
      }

      // any of new timer setting subs
      else if (loc=="select sound" || loc=="select interval" || loc=="select repeats" || loc=="confirm timer"){
                  loc = "new timer settings";  
                  
      }
      
      announceLoc(loc);
  
}









void sayNumber(int num){
        Serial.println("num: ");  Serial.print(num);

        switch(num){
            case 0: sound.play("num00.wav"); break;
            case 1: sound.play("num01.wav"); break;
            case 2: sound.play("num02.wav"); break;
            case 3: sound.play("num03.wav"); break;
            case 4: sound.play("num04.wav"); break;
            case 5: sound.play("num05.wav"); break;
            case 6: sound.play("num06.wav"); break;
            case 7: sound.play("num07.wav"); break;
            case 8: sound.play("num08.wav"); break;
            case 9: sound.play("num09.wav"); break;

            case 10: sound.play("num10.wav"); break;
            case 20: sound.play("num20.wav"); break;
            case 30: sound.play("num30.wav"); break;
            case 40: sound.play("num40.wav"); break;
            case 50: sound.play("num50.wav"); break;
            case 60: sound.play("num60.wav"); break;
        }
}
















