
////////////////////////////////////////////////////////////////////////////
// Circuit Playground Capacitive Touch Tones
//
// Play a tone for each touch pad.
// Using 4th octave note frequencies, to nearest 1Hz.
// https://www.seventhstring.com/resources/notefrequencies.html
//
// Author: Carter Nelson
// MIT License (https://opensource.org/licenses/MIT)


#include <Adafruit_CircuitPlayground.h>

int pads[8] = {3, 2, 0, 1, 12, 6, 9, 10};
int input[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
int checkAmt = 0;

bool correct =false; 

float threshhold = 600;

//claim note of pitches for each touch pad
float pitches[8] = {262, 294, 330, 349, 392, 440, 494, 523};

void setup() {
  // Initialize serial.
  Serial.begin(9600);
  
  // Initialize Circuit Playground library.
  CircuitPlayground.begin();
}

void loop() {

 //Loop over every pad & make each capcitance sensor play a different note
 for (int i = 0; i<8; i++){
  
  int x = CircuitPlayground.readCap(pads[i]);

  
   // Check if capacitive touch exceeds threshold.
  if(x > threshhold){
    
    CircuitPlayground.playTone(pitches[i], 100);
    input[checkAmt] = pads[i];
    checkAmt ++;
      
    for (int m=0; m<10; m++) 
      {
      CircuitPlayground.setPixelColor(m, 0, 255, 255);
      }
      delay(10); // Update rate.
  }
  
  else 
  {
    for (int m=0;m<10; m++)
    {
      CircuitPlayground.setPixelColor(m,0, 0, 0);
     
      }
      delay(10); // Update rate.
  }
 }
}
