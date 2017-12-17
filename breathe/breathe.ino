//#include <Metro.h>
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

int back = 2; int enter= 3; int prev = 4; int next = 5; int unis = 6;

/*  previ5db   next5db  enter5db
//String Sprev = "previ5db.wav"; String Snext = "next5db.wav";String Senter = "enter5db.wav";
//String names[]={Senter,Sprev,Snext};*/

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

String alarmName = "1";
String alarmSound="";
int alarmInterval=1;
int alarmRepeats=3;
int alarmRemains=-1;

//#define 
time_t mySystemTime;
time_t t1;

////////////////////////////////////////////////////////////////////
void setup()  {
  Serial.begin(9600);

  sound.speakerPin = 12;
  
  setTime(17,02,00,17,12,2017);
  mySystemTime = now();
  
  // see if the card is present and can be initialized:
  if (!SD.begin(SD_ChipSelectPin)) {  
    Serial.println("SD fail");  
    //return;   // don't do anything more if not
  } else Serial.println("SD card OK");

  pinMode(back, INPUT);
  pinMode(enter,INPUT);
  pinMode(prev, INPUT);
  pinMode(next, INPUT);
  pinMode(unis, INPUT);
  
  //  nmwc  units   tens
  if (loc=="main") sound.play("okbeep1.wav");     // okbeep1    mainmenu
}
// new sounds:   no.wav    ee  okbeep1 okbeep2  selinpls   selrepls   setting- srynordy
// tmrwsset tmrdelet

void loop() {
  mySystemTime = now();
  
  //char state = shouldRing(t1);
  if (alarmRemains>=0){
    
          if ( shouldRing(t1) ==true ){
                  
                             Serial.println();
                             Serial.println("-----------    alarm!!    -----------");
                             runAlarm(alarmName);
                             Serial.print("remains "); Serial.println(alarmRemains);
        
                             if (alarmRemains==0){
                                      
                                    Serial.println();
                                    Serial.println("-----------  alarm ended  -----------");
                                    
                                    resetNewTimerSettings();
                             }   
          }  
  }

  

  if (digitalRead(unis) == HIGH){

      if (loc=="select interval" || loc=="select repeats"){
        
          // for now turned off to begin more easily
          sound.play("srynordy.wav");
          return;
          
          delay(300);
          
          if (units=="units") units="tens";
          else units = "units";
    
          Serial.print("UNITS: "); Serial.println(units);

          // to start choosing numbers from 0 (seems logical)
          item = 0;
          
          sayUnits(units);
          
      } else illegal();

      
  }
  else if (digitalRead(back) == HIGH){
      
      
      //Serial.println("BACK");
      exitItem(true);
        
      delay(500);
      
  } else if (digitalRead(enter) == HIGH){
      
      //Serial.println("ENTER");
      
      enterItem();
      delay(500);

      
  } else if (digitalRead(prev) == HIGH){ //sound.play("previ5db.wav");
      //Serial.println("PREV");
      chooseItem(-1);
      delay(300);
      
  } else if (digitalRead(next) == HIGH){  //sound.play("next5db.wav");
      //Serial.println("NEXT");
      chooseItem(1);
      delay(300);
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

          // on ENTER choice will be made and announced    
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


      //  reacting on PREV or NEXT
      else if (loc=="confirm timer"){

                  //item = 0;
                  //saySelection("confirm timer");

          
      }

    Serial.print("item now: ");
    Serial.println(item);

    
}


                                  ////     ENTER    ////


void enterItem(){
    //Serial.println("enter item: ");

    if (loc=="main"){ 

        if (item==0){
                        loc="new timer settings";
                        announceLoc(loc);
        } else if (item==1){

                        //loc="choose running timer";
                        sound.play("srynordy.wav");
                        delay(500);
        }
        

    //    after ENTER is pressed:
        
    } else if (loc == "new timer settings"){

                    // select sound
                    if (item==0){
                            loc="select sound";
                      }
                    
                    // select interval
                    else if (item==1){
                            item = 0;
                            loc="select interval";
                            
                            alarmInterval=0;
                      }
        
                    // select repeats
                    else if (item==2){
                            item = 0;
                            loc="select repeats";

                            alarmRepeats=0;
                      }
        
                    // confirm timer
                    else if (item==3){
                      
                            item = 0;
                            confirmTimer();
                            return;
                            
                            //sound.play("srynordy.wav");
                            //delay(1700);
                            //return;
                            
                            //loc="confirm timer";
                      }
                      
                    announceLoc(loc);
                    delay(500);
                    announce1stItem(loc); // saySelection(soundChoices[item]);

                    
           // after pressed ENTER in 'select sound' confirms the choice
           
            } else if (loc=="select sound"){
      
                        alarmSound = soundChoices[item];
                        
                        delay(400);
                        sound.play("sound-.wav");
                        delay(600);
                        saySelection(soundChoices[item]);

                        sound.play("okbeep1.wav");
                        delay(600);
                        
                        exitItem(false);
                        item=0;


          // after pressing ENTER ->
            } else if (loc=="select interval"){

                      // it already said which num was chosen from array

                      if (units=="units") alarmInterval += intervalChoicesUnits[item];
                      else alarmInterval += intervalChoicesTens[item];

                      // switch to tens automatically
                      if (units=="units") { units="tens";
                                            sayUnits(units);
                                            
                      // units==tens confirmed ->
                      } else {
                        
                            if (alarmInterval==0){
      
                                  sound.play("selinpls.wav");
                                  delay(1200);

                                  item=0;
                                  units="units";
                                  sayUnits(units);
                              return;
                            }
                            //units = "units";
                            
                            // sum up what number he chose
                            sayDigits("alarmInterval");
                            
                            sound.play("okbeep1.wav");
                            delay(600);
                            
                            exitItem(false);
                            units="units";
                      }
                      item=0;
                      
                      // if he presses back, say chosen number /sum up
                      // after selection announce
                      
                      Serial.print("----  alarmInterval: ");
                      Serial.println(alarmInterval);


           // after pressing ENTER ->           
            } else if (loc=="select repeats"){

                      // it already said which num was chosen from array

                      if (units=="units") alarmRepeats += intervalChoicesUnits[item];
                      else alarmRepeats += intervalChoicesTens[item];

                      // switch to tens automatically
                      if (units=="units") { units="tens";         
                                            sayUnits(units);
                                            
                      // units==tens are confirmed                 
                      } else {
                        
                            if (alarmRepeats==0){
      
                                  sound.play("selrepls.wav");
                                  delay(1000);
                                  item=0;
                                  units="units";
                                  sayUnits(units);
                              return;
                            }
                            //units = "units";
                            
                            // sum up what number he chose
                            sayDigits("alarmRepeats");
                            
                            sound.play("okbeep1.wav");
                            delay(600);
                            
                            exitItem(false);
                            units="units";
                      }
                      item=0;
                      
                      // if he presses back, say chosen number /sum up
                      // after selection announce
                      
                      Serial.print("----  alarmRepeats: ");
                      Serial.println(alarmRepeats);
                      //Serial.println("test test");

                      
            }

            
            // pressed ENTER ->           
            // moved elsewhere else if (loc=="confirm timer") confirmTimer();

                    
                    
            
}


                                   /////   EXIT

void exitItem(bool loud){

      //Serial.println("exit item");

      if (loc=="main"){ 
              //Serial.println("IN MAIN MENU");
              
              //announceLoc(loc);
      }

      // if in first level
      else if (loc=="new timer settings" || loc=="choose running timer"){
                  loc = "main";  
                  
      }

      // after exit:  any of new timer setting subs
      else if (loc=="select sound" || loc=="select interval" || 
               loc=="select repeats" || loc=="confirm timer"){
                  loc = "new timer settings";  


                  if (loc=="select interval" || loc=="select repeats"){
                          // resets num to 0 (now this is the only option to do so)
                          item=0;
                          units="units";
                          // say interval or repeats set to zero
                          sound.play("setting-.wav");
                          delay(500);
                          sayNumber(0);
                  }
      }
      
      if(loud) announceLoc(loc);
  
}

                    /////////////////////////////////////////////


void announce1stItem(String loc){


      if (loc=="select sound"){
                //Serial.println();
                //Serial.print("1st item: "); Serial.println(soundChoices[0]);
                saySelection(soundChoices[0]);  //was: [item]
                
            
      } else if (loc=="select interval" || loc=="select repeats"){

                  sayNumber(0);

                  
      } else if (loc=="confirm timer"){
      }
}




void sayNumber(int num){
        Serial.print("say num: ");  Serial.println(num);

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

            default: sound.play("num0000.wav");
                      break;
        }
        //Serial.println("test test");
        delay(500);
}



void sayDigits(String prop){
      int num;
      
      if (prop=="alarmInterval") num = alarmInterval;
      else num = alarmRepeats;

      if (num>=1 && num<=9){

                    sound.play("setting-.wav");
                    delay(700);
                    sayNumber(num);
                    
      } else if (num>=10 && num<=69){

                    sound.play("setting-.wav");
                    delay(700);

                    int copy = num;
                    char one = String(copy).charAt(0);
                    char two = String(copy).charAt(1);

                    //Serial.print("chars divided to pronounce");
                    Serial.print(one); Serial.println(two);

                    // say them   int(x)-48

                    sayNumber((int(one)-48)*10);
                    delay(300);
                    if (two!='0') sayNumber(int(two)-48);
        
      } else { sound.play("ee.wav"); delay(400);
      }
      
}


void announceLoc(String loc){
      Serial.print("location to announce: ");
      Serial.println(loc);
      
      
      if         ( loc=="main"){
                  sound.play("mainmenu.wav");
                  delay(800);
                  
      } else if  ( loc=="new timer settings"){
                  sound.play("ntmrsets.wav");
                  delay(800);
    
      } else if  ( loc== "choose running timer"){
                  sound.play("chruntmr.wav");
                  Serial.println("not set: choose running timer");
                  delay(800);
      }

  
}

void saySelection(String choice){
      Serial.print("saySelection: ");
      Serial.println(choice);
      


      if (choice=="add timer"){
                sound.play("adnewtmr.wav");
                delay(1000);
      }
      else if (choice== "choose timer"){
                sound.play("chruntmr.wav");
                delay(1200);
      }

   // in adding new timer  
            else if (choice== "selSound"){
                      sound.play("selsound.wav");
                      delay(800);
            }
      
            else if (choice== "selInter"){ 
                      sound.play("selinter.wav");
                      delay(800);
            }
      
            else if (choice== "selRep"){
                      sound.play("selrpts.wav");
                      delay(800);
            }
      
            else if (choice==  "confTmr"){
                      sound.play("conftmr.wav");
                      delay(1200);
            }


            // in selecting alarm sound   
            //soundChoices[]={"korimako"), String("bowl deep"), "wood cool"};
            
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



void illegal(){
    delay(150);
    sound.play("no.wav");
    delay(300);
}



void sayUnits(String uns){

      sound.play("setting-.wav");
      delay(400);
      
      if (uns=="units") sound.play("units.wav");
      else sound.play("tens.wav");
      delay(300);
}



// when new timer is confirmed (set) should she repeat its settings?

void confirmTimer(){

              Serial.print("----  alarmInterval: ");
              Serial.println(alarmInterval);
              Serial.print("----  alarmRepeats: ");
              Serial.println(alarmRepeats);
              

                    if (alarmSound==""){

                          alarmSound="korimako";
                    }
                    
                    if (alarmInterval==0 || alarmRepeats==0){

                          if (alarmInterval==0) sound.play("selinpls.wav");
                          else if(alarmRepeats==0) sound.play("selrepls.wav");
                          
                          delay(1700);
                          sound.play("okbeep1.wav"); delay(300);
                          //exitItem(true);
                          return;
                    }
                    
                    sound.play("tmrwsset.wav"); delay(1200);

                    alarmRemains = alarmRepeats;
                    
                    // sound:
                    saySelection(alarmSound);
                    
                    // interval:
                    sound.play("interv-.wav"); delay(750);
                    sayDigits("alarmInterval"); 

                    delay(700);
                    
                    // repeats:
                    sound.play("repeats-.wav"); delay(800);
                    sayDigits("alarmRepeats");

                    
                    
              Serial.println();
              Serial.println("timer set as follows:");
              Serial.println(alarmSound);
              Serial.println(alarmInterval);
              Serial.println(alarmRepeats);
              Serial.println(alarmRemains);

              setNewTimer();
}

void setNewTimer(){
    int milis = alarmInterval * 60L * 1000;
        //Serial.print("milis: "); //Serial.println(milis);
        
    t1 = now();
    
          Serial.println("timer set @"); 
          Serial.print(hour(t1));   Serial.print(" ");
          Serial.print(minute(t1)); Serial.print(" ");
          Serial.println(second(t1));


          
    sound.play("okbeep1.wav"); delay(400);
                    
    loc="main";
    announceLoc("main"); 

    //delay(1000);       
}


bool shouldRing(time_t t){
      // R for ring   D Done  N no
      
      int secs; int mins; int hrs;
      hrs  = hour  (mySystemTime) - hour  (t) *1L;
      mins = minute(mySystemTime) - minute(t) *1L;
      secs = second(mySystemTime) - second(t) *1L;

      int secsTotal = hrs*3600 + mins*60 + secs *1L;
      
      //Serial.println(secs); 
      
      // when it should ring
      if( secs==0   && alarmRemains>=1){
        
                delay(1000); //Serial.println(secsTotal); 
                
                int minsDiff = hrs*60 + mins;
                if (minsDiff % alarmInterval==0){
                              return true;
                }
          
      } //else if (alarmRemains<=0) return 'D';
          
      return false;
}



void runAlarm(String alname){      
      if (alarmSound=="korimako"){ 
                                alarmRemains--;
                                sound.play("alkorima.wav");
                                //delay(5000);
                                
      } else if (alarmSound=="bowl deep"){
                                alarmRemains--;
                                sound.play("albowdee.wav");
                                //delay(13000);
                                
      } else if (alarmSound=="wood cool"){
                                alarmRemains--;
                                sound.play("alwoocoo.wav");
                                //delay(2500);
      }

}

void resetNewTimerSettings(){
    alarmName = "1";
    //alarmSound="";
    alarmInterval=0;
    alarmRepeats=0;
    alarmRemains=-1;  
    
              Serial.println();
              Serial.println("timer reset to:");
              Serial.println(alarmSound);
              Serial.println(alarmInterval);
              Serial.println(alarmRepeats);
              Serial.println(alarmRemains);

              
}

