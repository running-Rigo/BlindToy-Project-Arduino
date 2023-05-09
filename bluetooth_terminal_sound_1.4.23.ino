#include <SoftwareSerial.h>
#include "pitches.h"
SoftwareSerial BTserial(10, 9); // RX, TX
int melodyDoremi[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};

int durationFast = 50;
int pauseFast = 500;

int durationMedium = 100;
int pauseMedium = 1000;

int durationSlow = 200;
int pauseSlow = 2000;

int pitchDeep = NOTE_C3;
int pitchMedium = NOTE_C5;
int pitchHigh = NOTE_C7;

//default:
int chosenPitch = NOTE_C1;
int chosenDuration;
int chosenPause;


char data;

void setup()
{
 BTserial.begin(9600);
 pinMode(6,  OUTPUT);
}

void loop()
{
  delay(15);
 // Read from the Bluetooth module and send to the Arduino SerialMonitor
 if(BTserial.available()>0)
 {   
   data = BTserial.read();
   switch(data)
   {
     // a,b,c define pitch-height
     case 'a':
     {
       chosenPitch = pitchDeep;
       break;
     }

     case 'b':
     {
       chosenPitch = pitchMedium;
       break;
     }

     case 'c':
     {
       chosenPitch = pitchHigh;
       break;
     }

     //d,e,f define beeping-speed

       case 'd':
     {
       chosenDuration = durationSlow;
       chosenPause = pauseSlow;
       break;
     }

        case 'e':
     {
       chosenDuration = durationMedium;
       chosenPause = pauseMedium;
       break;
     }

        case 'f':
     {
       chosenDuration = durationFast;
       chosenPause = pauseFast;
       break;
     }


  //numbers define the melody:
    //Doremi: played when starting successful connection   
     case '0':
     {
       for (int thisNote = 0; thisNote < 8; thisNote++) {
    // pin8 output the voice, every scale is 0.5 sencond
        tone(6, melodyDoremi[thisNote], durationFast);
        delay(500);
        }
       break;
     }

    //single Peep
     case '1':
    { bool continues = true;
      int melodyPeep[] = {
      chosenPitch
      };
      while(continues){
        tone(6, melodyPeep[0], chosenDuration);
        data = BTserial.read();
        if(data=='x'){
          continues = false;
        }
        delay(chosenPause);
      }   
      break;
     }

     // double Peep-Peep
     case '2':
     {
       bool continues = true;
       int melodyPeepPeep[] = {
       chosenPitch, chosenPitch
        };
       while(continues){
         for (int thisNote = 0; thisNote < 2; thisNote++) {
        tone(6, melodyPeepPeep[thisNote], chosenDuration);
        delay(200);
        }
        data = BTserial.read();
        if(data=='x'){
          continues = false;
        }
        delay(chosenPause);
       }
     }


     // double Peep-Beeeep = seconed tone is lasts twice as long
     case '3':
     {
       bool continues = true;
       int melodyPeepPeep[] = {
       chosenPitch, chosenPitch
        };
       while(continues){
         for (int thisNote = 0; thisNote < 2; thisNote++) {
           if(thisNote == 1){
             tone(6, melodyPeepPeep[thisNote], chosenDuration*2);
           }
           else{
             tone(6, melodyPeepPeep[thisNote], chosenDuration);
           }
        delay(200);
        }
        data = BTserial.read();
        if(data=='x'){
          continues = false;
        }
        delay(chosenPause);
       }
     }

     
     // double Beeep-Beeeep = both sounds last twice as long
     case '4':
     {
       bool continues = true;
        int melodyPeepPeep[] = {
       chosenPitch, chosenPitch
        };       
       while(continues){
         for (int thisNote = 0; thisNote < 2; thisNote++) {
            tone(6, melodyPeepPeep[thisNote], chosenDuration*3);
            delay(chosenDuration*5);
           }
        data = BTserial.read();
        if(data=='x'){
          continues = false;
        }
        delay(chosenPause*2);
       }
    
     default: break;
      }  
    }
  }
}

