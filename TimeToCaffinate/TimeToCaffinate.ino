/*
  Author:Martha Feiler
  05-09/2015

  Grove - Serial LCD RGB Backlight
  Grove - Buzzer
  LittleBits- Pressure Sensor (Deconstructed)
  Grove - Button  used to test code before using pressure sensor which must be calibrated.

*/

#include <Wire.h>
// get this library from seedstudio
#include "rgb_lcd.h"

rgb_lcd lcd;

const int pinButton = 7;    // pin of button define here
const int colorR = 0;       //Red Color   
const int colorG = 0;       //Blue Color
const int colorB = 0;       //Green Color
int speakerPin = 3;         // Grove Buzzer connect to D3
char notes[] = "C";         //Note played by Buzzer
int beat = 1;               //Number of beats per note
int tempo = 330;            //how long beat is
int FSR_Pin = A15;          //analog pin 5
int counter = 0;            // counts coffee trips


//Function from SeedStudio's Buzzer Example
void playTone(int tone, int duration) {
    for (long i = 0; i < duration * 1000L; i += tone * 2) {
        digitalWrite(speakerPin, HIGH);
        delayMicroseconds(tone);
        digitalWrite(speakerPin, LOW);
        delayMicroseconds(tone);
    }
}

//Function from SeedStudio's Buzzer Example
void playNote(char note, int duration) {
    char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
    int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

    // play the tone corresponding to the note name
    for (int i = 0; i < 8; i++) {
        if (names[i] == note) {
            playTone(tones[i], duration);
        }
    }
}

void setup() 
{
  
    pinMode(pinButton, INPUT);    // set button INPUT                 
    lcd.begin(16, 2);     // set up the LCD's number of columns and rows:
    Serial.begin(9600);    //Open Serial Connection
     lcd.setRGB(colorR, colorG, colorB);     //set backlight color to initial color
    delay(1000);
}


void loop() 
{
  int FSRReading = analogRead(FSR_Pin);    //get a reading of the pressure sensor 
  Serial.println(FSRReading);   //Print reading to serial promt
  
  //if(digitalRead(pinButton)){    //When Button is pressed
  if(FSRReading < 50 && FSRReading > 0){    //when reading value is equal to an empty coaster 
     lcd.clear(); 
     lcd.setCursor(0,0) ; 
     lcd.print("Put coffee on me");
     lcd.setRGB(255,0,255);    //purple
    // for (int positionCounter = 0; positionCounter < 60; positionCounter++) {
      ///  lcd.scrollDisplayLeft();
        //delay(150);
    //}
    
  }else if(FSRReading < 300 && FSRReading > 50){     //when reading value is equal to an empty cup
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.setRGB(255,colorG,colorB); //red
    lcd.print("GET MORE COFFEE");
    playNote(notes[0], beat* tempo);
    delay(tempo / 2);
  
  }else{    //when coffe is in cup
    lcd.setCursor(0,0);
    lcd.print("You Have Coffee!");
    lcd.setRGB(colorR,255,colorB); //green 
  }
    
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(millis()/1000);

    delay(250);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
