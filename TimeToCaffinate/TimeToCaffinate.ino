/*
  Author:Martha Feiler
  05-09/2015

  Grove - Serial LCD RGB Backlight
  Grove - Buzzer
  LittleBits- Pressure Sensor (Deconstructed)
  Grove - Button  used to test code before using pressure sensor which must be calibrated.

*/
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int pinButton = 7;                        // pin of button define here
const int colorR = 0;
const int colorG = 0;
const int colorB = 0;
int speakerPin = 3;// Grove Buzzer connect to D3
char notes[] = "C";
int beat = 1;
int tempo = 330;
int FSR_Pin = A15; //analog pin 5

void playTone(int tone, int duration) {
    for (long i = 0; i < duration * 1000L; i += tone * 2) {
        digitalWrite(speakerPin, HIGH);
        delayMicroseconds(tone);
        digitalWrite(speakerPin, LOW);
        delayMicroseconds(tone);
    }
}

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
  
    pinMode(pinButton, INPUT);                  // set button INPUT
    
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
     Serial.begin(9600);
    lcd.setRGB(colorR, colorG, colorB);
    
    // Print a message to the LCD.
    //lcd.print("hello, world!");

    delay(1000);
}

void loop() 
{
   int FSRReading = analogRead(FSR_Pin); 

  Serial.println(FSRReading);
   
   // if(digitalRead(pinButton)){
    if(FSRReading < 50 && FSRReading > 0){
     lcd.clear();
     lcd.print("Put coffee on me");
     lcd.setRGB(255,0,255);
    // for (int positionCounter = 0; positionCounter < 60; positionCounter++) {
      ///  lcd.scrollDisplayLeft();
        //delay(150);
    //}
    }
    else if(FSRReading < 300 && FSRReading > 50){
    lcd.clear();
    lcd.print("GET MORE COFFEE");
    lcd.setRGB(255,colorG,colorB); 
    playNote(notes[0], beat* tempo);
    delay(tempo / 2);
  }else{
    lcd.setCursor(0,0);
    lcd.print("You Have Coffee!");
    lcd.setRGB(colorR,255,colorB);
  }
    
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(millis()/1000);

    delay(250);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
