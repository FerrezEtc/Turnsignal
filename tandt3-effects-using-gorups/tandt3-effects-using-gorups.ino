//New animations for signal, tail and day lights using groups of leds - FastLed Library, Arduino & WS2812B - Tips & Tricks FastLed Library - by Fedaceag Ionut ( Youtube - Think small, build big! )
//Arduino IDE version 1.8.9
//Arduino AVR Boards drivers version 1.8.2
#include <FastLED.h>                        //FastLed library version 3.3.3 - https://github.com/FastLED/FastLED/wiki/Overview or http://fastled.io/ with NEOPIXEL or WS2812B

//setting up the number of leds on the strips
#define NUM_LEDS_PART_A 175                  // number of leds strip one
#define NUM_LEDS_PART_B 20                   // number of leds strip two

//setting up the instaces for the led strips
CRGB ledsA[NUM_LEDS_PART_A];
CRGB ledsB[NUM_LEDS_PART_B];
 
//setting up the input pins
const int buttonPin1 = 2;                    // 
const int buttonPin2 = 3;                    // 
const int buttonPin3 = 4;                    // 
const int buttonPin4 = 5;                    // 
const int buttonPin5 = 6;                    // 
const int buttonPin6 = 7;                    // 
const int buttonPin7 = 8;                    // 
const int buttonPin8 = 9;                    // used for otherVoidFunction to simulate a brake light in the non-blocking delay function while a animation is running
const int buttonPin9 = 10;                   // used to change the turnning off animation for the signals

//setting up the variables for holding the button state, the button previous state and animation state
int buttonState1 = 0;
int stateB1 = 0;
int buttonState2 = 0;
int stateB2 = 0;
int buttonState3 = 0;
int stateB3 = 0;
int buttonState4 = 0;
int stateB4 = 0;
int buttonState5 = 0;
int stateB5 = 0;
int buttonState6 = 0;
int stateB6 = 0;
int buttonState7 = 0;
int stateB7 = 0;
int buttonState8 = 0;
int stateB8 = 0;
int prevStateB81 = 0;
int prevStateB82 = 0;
int prevStateB83 = 0;
int buttonState9 = 0;
int stateB9 = 0;

//setting up the variable for the first animation - signal 1 animation with groups for a faster animation with large number of leds (button 1)  !!!!!!!!!!  THE TOTAL NUMBER OF LEDS FOR THE SIGNAL MUST BE DIVISIBLE BY THE NUMBER OF GROUPS !!!!!!!!!
int numberOfLedsForS1 = 50; //this means that from the entire strip i'm using only 50 leds for signal !!!!!!!!!!  THE TOTAL NUMBER OF LEDS FOR THE SIGNAL MUST BE DIVISIBLE BY THE NUMBER OF GROUPS !!!!!!!!!
int ledGroupsS1 = 5; // how many groups are there !!!!!!!!!!  THE TOTAL NUMBER OF LEDS FOR THE SIGNAL MUST BE DIVISIBLE BY THE NUMBER OF GROUPS !!!!!!!!!
int ledsInGroupS1 = numberOfLedsForS1/ledGroupsS1;  // how many leds are in one group
int ledGroupsS1Start = 0; // first led from the first group (it's actually the last led from the strip)
int resetLedGroupsS1Start = ledGroupsS1Start; // reset first led from the first group
int ledGroupsS1End = ledsInGroupS1-1; // last led from the first group
int resetLedGroupsS1End = ledGroupsS1End; // reset last led from the first group
int lastLedLastGroupS1 = numberOfLedsForS1-1; // last led from the last group
int delayS11 = 10; //delay for signal animation
int delayS12 = 320; //delay to keep the on and off (used twice)
int delayS13 = 500; //delay from signal to day lights
int nrAnimAfterOffS1 = 3; //how many times the signals repeats with a single impulse
int currentAnimAfterOffS1 = 0;

//setting up the variable for the second animation - signal 2 animation with groups in a circle (button 2)
int ledGroupsS2 = 10; // how many groups are there
int ledGroupsS2Start = 0; // first led from the first group (it's actually the last led from the strip)
int resetLedGroupsS2Start = ledGroupsS2Start; // reset first led from the first group
int ledGroupsS2End = NUM_LEDS_PART_B-1; // last led from the first group
int resetLedGroupsS2End = ledGroupsS2End; // reset last led from the first group
int delayS21 = 10; //delay for signal animation
int delayS22 = 320; //delay to keep the on and off (used twice)
int delayS23 = 500; //delay from signal to day lights
int nrAnimAfterOffS2 = 3; //how many times the signals repeats with a single impulse
int currentAnimAfterOffS2 = 0;

//setting up the variable for the third animation - signal 3 animation with groups (button 3)
int ledGroupsS3 = 11; // how many groups are there
int ledsInGroupS3 = 10;  // how many leds are in one group
int ledGroupsS3Start = NUM_LEDS_PART_A-1; // first led from the first group (it's actually the last led from the strip)
int resetLedGroupsS3Start = ledGroupsS3Start; // reset first led from the first group
int ledGroupsS3End = ledGroupsS3Start-ledsInGroupS3+1; // last led from the first group
int resetLedGroupsS3End = ledGroupsS3End; // reset last led from the first group
int lastLedLastGroupS3 = (ledGroupsS3Start-(ledGroupsS3*ledsInGroupS3))+1; // last led from the last group
int delayS31 = 10; //delay for signal animation
int delayS32 = 320; //delay to keep the on and off (used twice)
int delayS33 = 500; //delay from signal to day lights
int nrAnimAfterOffS3 = 3; //how many times the signals repeats with a single impulse
int currentAnimAfterOffS3 = 0;

//setting up the variable for the forth animation - day lights anim 1 (button 4)
int ledGroupsDay = 11; // how many groups are there
int ledsInGroupDay = 10;  // how many leds are in one group
int ledGroupsDayStart = 65; // first led from the first group
int resetLedGroupsDayStart = ledGroupsDayStart; // reset first led from the first group
int ledGroupsDayEnd = ledGroupsDayStart+ledsInGroupDay-1; // last led from the first group
int resetLedGroupsDayEnd = ledGroupsDayEnd; // reset last led from the first group
int lastLedLastGroup = (ledGroupsDayStart+(ledGroupsDay*ledsInGroupDay))-1; // last led from the last group
int maxBrt31 = 80; // maxim brightness in the first pass
int maxBrt32 = 150; // maxim brightness in the second pass
int delayPass1 = 10;
int delayPass2 = 30;
int delayPass3 = 20;
int delayPass4 = 50;
int fadeToBlackDay1 = 150;
int currentPassDay = 0;

//setting up the variable for the fifth animation - day lights anim 2 (button 5)
int numberOfLedsDay2 = NUM_LEDS_PART_B; // the total number of leds for day light 2 - in this case all the leds in strip two !!!!!!!!!!  THE TOTAL NUMBER OF LEDS MUST BE DIVISIBLE BY THE NUMBER OF GROUPS !!!!!!!!!
int ledGroupsDay2 = 2; // how many groups are there
int halfLedsInDay2 = numberOfLedsDay2/ledGroupsDay2;  // how many leds are in one group also is the half of total leds
int ledGroupsDay2Start1 = 0; // first led from the first group
int ledGroupsDay2End1 = halfLedsInDay2-1; // last led from the first group
int ledGroupsDay2Start2 = halfLedsInDay2; // first led from the first group
int ledGroupsDay2End2 = numberOfLedsDay2-1; // last led from the first group
int maxBrtD21 = 70; // maxim brightness in the first pass
int maxBrtD22 = 210; // maxim brightness in the second pass
int delayPassD21 = 20;
int delayPassD22 = 20;
int currentPassDay2 = 0;

//setting up the variable for the sixth animation - day lights anim 3 (button 6)
int numberOfLedsDay3 = 50; // the total number of leds for day light 3 - in this case all the leds in strip two !!!!!!!!!!  THE TOTAL NUMBER OF LEDS MUST BE DIVISIBLE BY THE NUMBER OF GROUPS !!!!!!!!!
int ledGroupsDay3 = 5; // how many groups are there   !!!!!!!!!!  THE TOTAL NUMBER OF LEDS MUST BE DIVISIBLE BY THE NUMBER OF GROUPS !!!!!!!!!
int ledsInGroupDay3 = numberOfLedsDay3/ledGroupsDay3;  // how many leds are in one group
int ledGroupsDay3Start = 0; // first led from the first group
int resetLedGroupsDay3Start = ledGroupsDay3Start; // reset first led from the first group
int ledGroupsDay3End = ledsInGroupDay3-1; // last led from the first group
int resetLedGroupsDay3End = ledGroupsDay3End; // reset last led from the first group
int lastLedLastGroupDay3 = numberOfLedsDay3-1; // last led from the last group
int maxBrtD31 = 150; // maxim brightness 1
int maxBrtD32 = 150; // maxim brightness 2
int delayPassD31 = 25;
int delayPassD32 = 15;
int currentPassDay3 = 0;

//setting up the variable for the seventh animation - tail lights animation 1 (button 7)
int nrLedInGroup1Tail1 = 50;
int firstLedInGroup1Tail1 = 0;
int lastLedInGroup1Tail1 = 49;
int nrOfSubGroupsFromGroup1Tail1 = 10;
int nrLedInSubGroupsFromGroup1Tail1 = nrLedInGroup1Tail1/nrOfSubGroupsFromGroup1Tail1;
int startLedInGroup1Tail1 = firstLedInGroup1Tail1;
int resetStartLedInGroup1Tail1 = startLedInGroup1Tail1;
int endLedInGroup1Tail1 = firstLedInGroup1Tail1+nrLedInSubGroupsFromGroup1Tail1-1;
int resetEndLedInGroup1Tail1 = endLedInGroup1Tail1;
int nrLedInGroup2Tail1 = 15;
int firstLedInGroup2Tail1 = 50;
int lastLedInGroup2Tail1 = 64;
int nrLedInGroup3Tail1 = 110;
int firstLedInGroup3Tail1 = 65;
int lastLedInGroup3Tail1 = 174;
int nrOfSubGroupsFromGroup3Tail1 = 11;
int nrLedInSubGroupsFromGroup3Tail1 = nrLedInGroup3Tail1/nrOfSubGroupsFromGroup3Tail1;
int startLedInGroup3Tail1 = firstLedInGroup3Tail1;
int resetStartLedInGroup3Tail1 = startLedInGroup3Tail1;
int endLedInGroup3Tail1 = firstLedInGroup3Tail1+nrLedInSubGroupsFromGroup3Tail1-1;
int resetEndLedInGroup3Tail1 = endLedInGroup3Tail1;
int maxBrtT11 = 120; // maxim brightness 1 for tail lights
int maxBrtT12 = 120; // maxim brightness in the second pass
int delayPassT11 = 10;
int delayPassT12 = 20;
int fadeToBlackT1 = 180;
int currentPassT1 = 0;

//setting up the variable for otherVoidFunction
int maxBrtOVF1 = 254;

int fadeToBlackLeds = 100;

//variables for keeping track of the current and previous time for the non-blocking delay
unsigned long currentMillis = 0; 
unsigned long previousMillis = 0;

// The RGB color codes can be found here https://github.com/FastLED/FastLED/wiki/Pixel-reference
unsigned long turnColor = 0xff6a00;                            // turn signal color

void setup() {
  Serial.begin(9600);          //starting the serial begin for debugging purposes
  
  //setting up the pin modes for the buttons
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buttonPin5, INPUT);
  pinMode(buttonPin6, INPUT);
  pinMode(buttonPin7, INPUT);
  pinMode(buttonPin8, INPUT);
  pinMode(buttonPin9, INPUT);

  //starting up the instaces for the led strips and defining the output pins
  FastLED.addLeds<NEOPIXEL, 12>(ledsA, NUM_LEDS_PART_A);    //led strip one on pin 12
  FastLED.addLeds<NEOPIXEL, 13>(ledsB, NUM_LEDS_PART_B);    //led strip two on pin 13
 
  fill_solid(ledsA, NUM_LEDS_PART_A, CRGB::Black);    // some led strips are all on at power on, so let's power them off at boot
  fill_solid(ledsB, NUM_LEDS_PART_B, CRGB::Black);    // some led strips are all on at power on, so let's power them off at boot

  //sending the data to the leds
  FastLED.show();
}


void loop() {

  //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //signal 1 animation with groups for a faster animation with large number of leds (button 1)
  //reading the button 1 and setting the state
  buttonState1 = digitalRead(buttonPin1);
  if(buttonState1 == HIGH){stateB1 = 1;}
  
  //checking the state for button 1
  if(stateB1 == 1){
    
    //looping thru all the groups and creating the animation
    for(int group = 0; group < ledGroupsS1; group++) {
      
      //turning on the groups
      fill_gradient_RGB(ledsA,ledGroupsS1Start,turnColor,ledGroupsS1End,turnColor);
      //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
      otherVoidFunction();
      //sending the data to the leds
      FastLED.show();
      
      //changing the start and the end leds for the next loop
      ledGroupsS1Start = ledGroupsS1Start+ledsInGroupS1;
      ledGroupsS1End = ledGroupsS1End+ledsInGroupS1;
      
      // non-blocking delay that allows other void functions to be run
      currentMillis = previousMillis = millis();
      while(previousMillis + delayS11 >= currentMillis){
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds with the modifications from the other void function
        FastLED.show();
        currentMillis = millis();
      }
      
    }

    //resetting the start and the end leds for the next loops
    ledGroupsS1Start = resetLedGroupsS1Start;
    ledGroupsS1End = resetLedGroupsS1End;
    

    // non-blocking delay that allows other void functions to be run (used to keep the leds on for "delayS22" time)
    currentMillis = previousMillis = millis();
    while(previousMillis + delayS12 >= currentMillis){
      //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
      otherVoidFunction();
      //sending the data to the leds with the modifications from the other void function
      FastLED.show();
      currentMillis = millis();
    }

    //here i've used button 9 to change between two turning off animation
    if(digitalRead(buttonPin9) == HIGH){
      
      //looping thru all the groups and turn them off one by one
      for(int group = 0; group < ledGroupsS1; group++) {
        
        //turning off the groups
        fill_gradient_RGB(ledsA,ledGroupsS1Start,0x000000,ledGroupsS1End,0x000000);
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds
        FastLED.show();
        
        //changing the start and the end leds for the next loop
        ledGroupsS1Start = ledGroupsS1Start+ledsInGroupS1;
        ledGroupsS1End = ledGroupsS1End+ledsInGroupS1;
        
        // non-blocking delay that allows other void functions to be run
        currentMillis = previousMillis = millis();
        while(previousMillis + delayS11 >= currentMillis){
          //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
          otherVoidFunction();
          //sending the data to the leds with the modifications from the other void function
          FastLED.show();
          currentMillis = millis();
        }
        
      }
  
      //resetting the start and the end leds for the next loops
      ledGroupsS1Start = resetLedGroupsS1Start;
      ledGroupsS1End = resetLedGroupsS1End;
      
    }else{

      //turning off all the groups at once
      fill_gradient_RGB(ledsA,ledGroupsS1Start,0x000000,lastLedLastGroupS1,0x000000);
      //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
      otherVoidFunction();
      //sending the data to the leds
      FastLED.show();
      
    }

    // non-blocking delay that allows other void functions to be run (used to keep the leds off for "delayS22" time)
    currentMillis = previousMillis = millis();
    while(previousMillis + delayS12 >= currentMillis){
      //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
      otherVoidFunction();
      //sending the data to the leds with the modifications from the other void function
      FastLED.show();
      currentMillis = millis();
    }

    //increasing the current animation number
    currentAnimAfterOffS1++;

    //check the button 1 state and current animation number and if both are true the we exit, else we loop again the signal
    if(buttonState1 == LOW && currentAnimAfterOffS1 >= nrAnimAfterOffS1){

      //setting the button 1 state to be able to exit
      stateB1 = 0;
      //setting the current animation number to be able to exit
      currentAnimAfterOffS1 = 0;

      //if button 6 is pressed(day lights are on), then we set the currentPassDay to the last pass in day light animation to turn the day light back on
      if(stateB6 == 1){
        currentPassDay3 = 0;
      }

      //if button 7 is pressed(tail lights are on), then we set the currentPassT1 to the last pass in tail light animation to turn the tail light back on
      if(stateB7 == 1 && stateB6 == 0){
        currentPassT1 = 3;
      }

      // non-blocking delay that allows other void functions to be run (used to delay dylights turning on for "delayS23" time)
      currentMillis = previousMillis = millis();
      while(previousMillis + delayS13 >= currentMillis){
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds with the modifications from the other void function
        FastLED.show();
        currentMillis = millis();
      }
      
    }
  }

  //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //signal 2 animation with groups in a circle (button 2)
  //reading the button 2 and setting the state
  buttonState2 = digitalRead(buttonPin2);
  if(buttonState2 == HIGH){stateB2 = 1;}

  //checking the state for button 2
  if(stateB2 == 1){

    //looping thru all the groups and creating the animation
    for(int group = 0; group < ledGroupsS2; group++) {

      //changing the start and the end leds for the next loop
      ledGroupsS2Start++;
      ledGroupsS2End--;
      
      //turning on the group 1 (first half of the circle)
      fill_gradient_RGB(ledsB,resetLedGroupsS2Start,turnColor,ledGroupsS2Start,turnColor);
      //turning on the group 2 (second half of the circle)
      fill_gradient_RGB(ledsB,ledGroupsS2End,turnColor,resetLedGroupsS2End,turnColor);
      //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
      otherVoidFunction();
      //sending the data to the leds
      FastLED.show();

      // non-blocking delay that allows other void functions to be run
      currentMillis = previousMillis = millis();
      while(previousMillis + delayS21 >= currentMillis){
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds with the modifications from the other void function
        FastLED.show();
        currentMillis = millis();
      }
      
    }

    //resetting the start and the end leds for the next loops
    ledGroupsS2Start = resetLedGroupsS2Start;
    ledGroupsS2End = resetLedGroupsS2End;

    // non-blocking delay that allows other void functions to be run (used to keep the leds on for "delayS22" time)
    currentMillis = previousMillis = millis();
    while(previousMillis + delayS22 >= currentMillis){
      //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
      otherVoidFunction();
      //sending the data to the leds with the modifications from the other void function
      FastLED.show();
      currentMillis = millis();
    }

    //here i've used button 8 to change between two turning off animation
    if(digitalRead(buttonPin9) == HIGH){
      
      //looping thru all the groups and turn them off one by one
      for(int group = 0; group < ledGroupsS2; group++) {
  
        //changing the start and the end leds for the next loop
        ledGroupsS2Start++;
        ledGroupsS2End--;
        
        //turning on the group 1 (first half of the circle)
        fill_gradient_RGB(ledsB,resetLedGroupsS2Start,0x000000,ledGroupsS2Start,0x000000);
        //turning on the group 2 (second half of the circle)
        fill_gradient_RGB(ledsB,ledGroupsS2End,0x000000,resetLedGroupsS2End,0x000000);
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds
        FastLED.show();
  
        // non-blocking delay that allows other void functions to be run
        currentMillis = previousMillis = millis();
        while(previousMillis + delayS21 >= currentMillis){
          //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
          otherVoidFunction();
          //sending the data to the leds with the modifications from the other void function
          FastLED.show();
          currentMillis = millis();
        }
        
      }

      //resetting the start and the end leds for the next loops
      ledGroupsS2Start = resetLedGroupsS2Start;
      ledGroupsS2End = resetLedGroupsS2End;
      
    }else{

      //turning off all the groups at once
      fill_gradient_RGB(ledsB,resetLedGroupsS2Start,0x000000,resetLedGroupsS2End,0x000000);
      //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
      otherVoidFunction();
      //sending the data to the leds
      FastLED.show();
      
    }

    // non-blocking delay that allows other void functions to be run (used to keep the leds off for "delayS22" time)
    currentMillis = previousMillis = millis();
    while(previousMillis + delayS22 >= currentMillis){
      //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
      otherVoidFunction();
      //sending the data to the leds with the modifications from the other void function
      FastLED.show();
      currentMillis = millis();
    }

    //increasing the current animation number
    currentAnimAfterOffS2++;

    //check the button 2 state and current animation number and if both are true the we exit, else we loop again the signal
    if(buttonState2 == LOW && currentAnimAfterOffS2 >= nrAnimAfterOffS2){

      //setting the button 2 state to be able to exit
      stateB2 = 0;
      //setting the current animation number to be able to exit
      currentAnimAfterOffS2 = 0;

      //if button 5 is pressed(day lights are on), then we set the currentPassDay to the last pass in day light animation to turn the day light back on
      if(stateB5 == 1){
        currentPassDay2 = 1;
      }

      // non-blocking delay that allows other void functions to be run (used to delay dylights turning on for "delayS23" time)
      currentMillis = previousMillis = millis();
      while(previousMillis + delayS23 >= currentMillis){
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds with the modifications from the other void function
        FastLED.show();
        currentMillis = millis();
      }
      
    }
  }

  //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //signal anim 3 with groups of leds (button 3)
  //reading the button 3 and setting the state
  buttonState3 = digitalRead(buttonPin3);
  if(buttonState3 == HIGH){stateB3 = 1;}

  //checking the state for button 3
  if(stateB3 == 1){

    //looping thru all the groups and creating the animation
    for(int group = 0; group < ledGroupsS3; group++) {

      //turning on the group
      fill_gradient_RGB(ledsA,ledGroupsS3Start,turnColor,ledGroupsS3End,turnColor);
      //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
      otherVoidFunction();
      //sending the data to the leds
      FastLED.show();

      //changing the start and the end leds for the next loop
      ledGroupsS3Start = ledGroupsS3Start-ledsInGroupS3;
      ledGroupsS3End = ledGroupsS3End-ledsInGroupS3;

      // non-blocking delay that allows other void functions to be run
      currentMillis = previousMillis = millis();
      while(previousMillis + delayS31 >= currentMillis){
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds with the modifications from the other void function
        FastLED.show();
        currentMillis = millis();
      }
      
    }

    //resetting the start and the end leds for the next loops
    ledGroupsS3Start = resetLedGroupsS3Start;
    ledGroupsS3End = resetLedGroupsS3End;

    // non-blocking delay that allows other void functions to be run (used to keep the leds on for "delayS32" time)
    currentMillis = previousMillis = millis();
    while(previousMillis + delayS32 >= currentMillis){
      //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
      otherVoidFunction();
      //sending the data to the leds with the modifications from the other void function
      FastLED.show();
      currentMillis = millis();
    }

    //here i've used button 8 to change between two turning off animation
    if(digitalRead(buttonPin9) == HIGH){

      //looping thru all the groups and turn them off one by one
      for(int group = 0; group < ledGroupsS3; group++) {
  
        //turning on the group
        fill_gradient_RGB(ledsA,ledGroupsS3Start,0x000000,ledGroupsS3End,0x000000);
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds
        FastLED.show();
  
        //changing the start and the end leds for the next loop
        ledGroupsS3Start = ledGroupsS3Start-ledsInGroupS3;
        ledGroupsS3End = ledGroupsS3End-ledsInGroupS3;
  
        // non-blocking delay that allows other void functions to be run
        currentMillis = previousMillis = millis();
        while(previousMillis + delayS31 >= currentMillis){
          //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
          otherVoidFunction();
          //sending the data to the leds with the modifications from the other void function
          FastLED.show();
          currentMillis = millis();
        }
        
      }
  
      //resetting the start and the end leds for the next loops
      ledGroupsS3Start = resetLedGroupsS3Start;
      ledGroupsS3End = resetLedGroupsS3End;

    }else{
      //turning off all the groups
      fill_gradient_RGB(ledsA,resetLedGroupsS3Start,0x000000,lastLedLastGroupS3,0x000000);
      //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
      otherVoidFunction();
      //sending the data to the leds
      FastLED.show();      
    }


    // non-blocking delay that allows other void functions to be run (used to keep the leds off for "delayS32" time)
    currentMillis = previousMillis = millis();
    while(previousMillis + delayS32 >= currentMillis){
      //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
      otherVoidFunction();
      //sending the data to the leds with the modifications from the other void function
      FastLED.show();
      currentMillis = millis();
    }

    //increasing the current animation number
    currentAnimAfterOffS3++;

    //check the button 3 state and current animation number and if both are true the we exit, else we loop again the signal
    if(buttonState3 == LOW && currentAnimAfterOffS3 >= nrAnimAfterOffS3){

      //setting the button 3 state to be able to exit
      stateB3 = 0;
      //setting the current animation number to be able to exit
      currentAnimAfterOffS3 = 0;

      //if button 4 is pressed(day lights are on), then we set the currentPassDay to the last pass in day light animation to turn the day light back on
      if(stateB4 == 1){
        currentPassDay = 2;
      }

      // non-blocking delay that allows other void functions to be run (used to delay dylights turning on for "delayS33" time)
      currentMillis = previousMillis = millis();
      while(previousMillis + delayS33 >= currentMillis){
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds with the modifications from the other void function
        FastLED.show();
        currentMillis = millis();
      }
      
    }
  }

  //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //day lights anim 1 (button 4)
  //reading the button 4 and setting the state
  buttonState4 = digitalRead(buttonPin4);
  if(buttonState4 == HIGH){stateB4 = 1;}
  
  //checking the state for button 4 and signal on the same groups is off
  if(stateB4 == 1 && currentAnimAfterOffS3 == 0){
    
    // pass one of the animation
    if(currentPassDay == 0){

      // looping thru all the groups and keeping count of the remaining groups to be lit
      for(int remainingGroups = ledGroupsDay; remainingGroups > 0; remainingGroups--){

        // looping thru each group to create the passing animation
        for(int group = 0; group < remainingGroups; group++) {

          //turn off the rest of the leds
          fill_gradient(ledsA,resetLedGroupsDayStart,CHSV( 0, 0, 0),ledGroupsDayStart,CHSV( 0, 0, 0));
          //turn on the desired group
          fill_gradient(ledsA,ledGroupsDayStart,CHSV( 0, 0, maxBrt31),ledGroupsDayEnd,CHSV( 0, 0, maxBrt31));
          //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
          otherVoidFunction();
          //sending the data to the leds
          FastLED.show();

          //changing the start and the end leds for the next loop
          ledGroupsDayStart = ledGroupsDayStart+ledsInGroupDay;
          ledGroupsDayEnd = ledGroupsDayEnd+ledsInGroupDay;

          // non-blocking delay that allows other void functions to be run
          currentMillis = previousMillis = millis();
          while(previousMillis + delayPass1 >= currentMillis){
            //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
            otherVoidFunction();
            //sending the data to the leds with the modifications from the other void function
            FastLED.show();
            currentMillis = millis();
          }
        }
        //resetting the start and the end leds for the next loop
        ledGroupsDayStart = resetLedGroupsDayStart;
        ledGroupsDayEnd = resetLedGroupsDayEnd;
      }
      
      //increasing the current pass for the animation
      currentPassDay++;
      
    // pass two of the animation
    }else if(currentPassDay == 1){

      // looping thru each group and increasing the brightness to current group, while keeping the previous brightness to the rest of the groups
      for(int group = 0; group < ledGroupsDay; group++) {
        
        //changing the start and the end leds for the next loop
        ledGroupsDayStart = (lastLedLastGroup-(ledsInGroupDay*group))-ledsInGroupDay+1;
        ledGroupsDayEnd = lastLedLastGroup-(ledsInGroupDay*group);

        //keeping the previous brightness to the rest of the groups
        fill_gradient(ledsA,resetLedGroupsDayStart,CHSV( 0, 0, maxBrt31),lastLedLastGroup,CHSV( 0, 0, maxBrt31));
        //increasing the brightness to current group
        fill_gradient(ledsA,ledGroupsDayStart,CHSV( 0, 0, maxBrt32),ledGroupsDayEnd,CHSV( 0, 0, maxBrt32));
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds
        FastLED.show();
        
        // non-blocking delay that allows other void functions to be run
        currentMillis = previousMillis = millis();
        while(previousMillis + delayPass2 >= currentMillis){
          //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
          otherVoidFunction();
          //sending the data to the leds with the modifications from the other void function
          FastLED.show();
          currentMillis = millis();
        }
      }     
      
      //resetting the start and the end leds for the next loop/pass
      ledGroupsDayStart = resetLedGroupsDayStart;
      ledGroupsDayEnd = resetLedGroupsDayEnd;
      
      //increasing the current pass for the animation
      currentPassDay++;
      
    // pass three of the animation
    }else if(currentPassDay == 2){
      
      // looping thru each group and increasing the brightness to all groups
      for(int group = 0; group < ledGroupsDay; group++) {

        //increasing the brightness to all groups
        fill_gradient(ledsA,ledGroupsDayStart,CHSV( 0, 0, maxBrt32),ledGroupsDayEnd,CHSV( 0, 0, maxBrt32));
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds
        FastLED.show();
        
        //changing the start and the end leds for the next loop
        ledGroupsDayStart = ledGroupsDayStart+ledsInGroupDay;
        ledGroupsDayEnd = ledGroupsDayEnd+ledsInGroupDay;
        
        // non-blocking delay that allows other void functions to be run
        currentMillis = previousMillis = millis();
        while(previousMillis + delayPass3 >= currentMillis){
          //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
          otherVoidFunction();
          //sending the data to the leds with the modifications from the other void function
          FastLED.show();
          currentMillis = millis();
        }
      }     
      
      //resetting the start and the end leds for the next loop/pass
      ledGroupsDayStart = resetLedGroupsDayStart;
      ledGroupsDayEnd = resetLedGroupsDayEnd;
      
      //increasing the current pass for the animation
      currentPassDay++;
      
    }else{
      
      //keeping the brightness to all groups
      fill_gradient(ledsA,resetLedGroupsDayStart,CHSV( 0, 0, maxBrt32),lastLedLastGroup,CHSV( 0, 0, maxBrt32));
      //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
      otherVoidFunction();
      //sending the data to the leds
      FastLED.show();
      
    }

    //checking the button if it's off and setting the state to be able to exit
    if(buttonState4 == LOW){stateB4 = 0;}

  //if the button 4 is off and signal on the same groups is off, then we proceed with the turning off animation
  }else if(stateB4 == 0 && currentAnimAfterOffS3 == 0){
    
    // pass one for the off animation
    if(currentPassDay == 3){
      
      // looping thru each group and and fade to black
      for(int group = 0; group < ledGroupsDay; group++) {

        //fade to black
        fadeToBlackBy( ledsA, ledGroupsDayEnd, fadeToBlackDay1);
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds
        FastLED.show();

        //changing the start and the end leds for the next loop
        ledGroupsDayStart = ledGroupsDayStart+ledsInGroupDay;
        ledGroupsDayEnd = ledGroupsDayEnd+ledsInGroupDay;
        
        // non-blocking delay that allows other void functions to be run
        currentMillis = previousMillis = millis();
        while(previousMillis + delayPass4 >= currentMillis){
          //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
          otherVoidFunction();
          //sending the data to the leds with the modifications from the other void function
          FastLED.show();
          currentMillis = millis();
        }
        
      }     
      
      //resetting the start and the end leds for the next loop/pass
      ledGroupsDayStart = resetLedGroupsDayStart;
      ledGroupsDayEnd = resetLedGroupsDayEnd;
      
      //decreasing the current pass for the animation
      currentPassDay--;
    
    // pass two for the off animation
    }else if(currentPassDay == 2){
      
      // looping thru each group to create the passing animation and fade to black
      for(int group = 0; group < ledGroupsDay; group++) {

        //changing the start and the end leds for the next loop
        ledGroupsDayStart = (lastLedLastGroup-(ledsInGroupDay*group))-ledsInGroupDay+1;
        ledGroupsDayEnd = lastLedLastGroup-(ledsInGroupDay*group);

        //fade to black
        fadeToBlackBy( ledsA, NUM_LEDS_PART_A, fadeToBlackDay1);
        //looping thru each group
        fill_gradient(ledsA,ledGroupsDayStart,CHSV( 0, 0, maxBrt32),ledGroupsDayEnd,CHSV( 0, 0, maxBrt32));
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds
        FastLED.show();
        
        // non-blocking delay that allows other void functions to be run
        currentMillis = previousMillis = millis();
        while(previousMillis + delayPass4 >= currentMillis){
          //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
          otherVoidFunction();
          //sending the data to the leds with the modifications from the other void function
          FastLED.show();
          currentMillis = millis();
        }
      }     
      
      //resetting the start and the end leds for the next loop/pass
      ledGroupsDayStart = resetLedGroupsDayStart;
      ledGroupsDayEnd = resetLedGroupsDayEnd;
      
      //decreasing the current pass for the animation
      currentPassDay--;
      
      
    // pass three for the off animation
    }else if(currentPassDay == 1){

      // looping thru each group to give time to fade to black function to turn off all the leds in a smooth way
      for(int group = 0; group < ledGroupsDay; group++) {

        //fade to black
        fadeToBlackBy( ledsA, NUM_LEDS_PART_A, fadeToBlackDay1);
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds
        FastLED.show();
        
        // non-blocking delay that allows other void functions to be run
        currentMillis = previousMillis = millis();
        while(previousMillis + delayPass4 >= currentMillis){
          //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
          otherVoidFunction();
          //sending the data to the leds with the modifications from the other void function
          FastLED.show();
          currentMillis = millis();
        }
      }
      
      //decreasing the current pass for the animation
      currentPassDay--;
    }
    
    
  }

  //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //day lights anim 2 (button 5)
  //reading the button 5 and setting the state
  buttonState5 = digitalRead(buttonPin5);
  if(buttonState5 == HIGH){stateB5 = 1;}
  
  //checking the state for button 5 and signal on the same groups is off
  if(stateB5 == 1 && currentAnimAfterOffS2 == 0){
    
    // pass one of the animation
    if(currentPassDay2 == 0){

      // looping thru each group and turning on the leds one by one in both groups
      for(int ledInGroup = 0; ledInGroup < halfLedsInDay2; ledInGroup++) {
        
        //turning on the leds in group 1(half of the circle) groups one by one
        fill_gradient(ledsB,ledGroupsDay2Start1,CHSV( 0, 0, maxBrtD21),ledInGroup,CHSV( 0, 0, maxBrtD21));
        //turning on the leds in group 2(the second half of the circle) groups one by one
        fill_gradient(ledsB,ledGroupsDay2Start2,CHSV( 0, 0, maxBrtD21),ledGroupsDay2Start2+ledInGroup,CHSV( 0, 0, maxBrtD21));
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds
        FastLED.show();
        
        // non-blocking delay that allows other void functions to be run
        currentMillis = previousMillis = millis();
        while(previousMillis + delayPassD21 >= currentMillis){
          //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
          otherVoidFunction();
          //sending the data to the leds with the modifications from the other void function
          FastLED.show();
          currentMillis = millis();
        }
      }     
      
      //increasing the current pass for the animation
      currentPassDay2++;

    // pass two of the animation  
    }else if(currentPassDay2 == 1){

      // looping thru each group and increasing the brightness on the leds one by one in both groups
      for(int ledInGroup = 0; ledInGroup < halfLedsInDay2; ledInGroup++) {
        
        //increasing the brightness on the leds in group 1(half of the circle) groups one by one
        fill_gradient(ledsB,ledGroupsDay2End1,CHSV( 0, 0, maxBrtD22),ledGroupsDay2End1-ledInGroup,CHSV( 0, 0, maxBrtD22));
        //increasing the brightness on the leds in group 2(the second half of the circle) groups one by one
        fill_gradient(ledsB,ledGroupsDay2End2,CHSV( 0, 0, maxBrtD22),ledGroupsDay2End2-ledInGroup,CHSV( 0, 0, maxBrtD22));
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds
        FastLED.show();
        
        // non-blocking delay that allows other void functions to be run
        currentMillis = previousMillis = millis();
        while(previousMillis + delayPassD22 >= currentMillis){
          //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
          otherVoidFunction();
          //sending the data to the leds with the modifications from the other void function
          FastLED.show();
          currentMillis = millis();
        }
      }
      
      //increasing the current pass for the animation
      currentPassDay2++;
      
    }else{
      
      //keep all the leds on
      fill_gradient(ledsB,ledGroupsDay2Start1,CHSV( 0, 0, maxBrtD22),ledGroupsDay2End2,CHSV( 0, 0, maxBrtD22));
      //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
      otherVoidFunction();
      //sending the data to the leds
      FastLED.show();
      
    }
    

    //checking the button 5 if it's off and setting the state to be able to exit
    if(buttonState5 == LOW){stateB5 = 0;}
  
  }else if(stateB5 == 0 && currentAnimAfterOffS2 == 0){
    
    // pass one for the off animation
    if(currentPassDay2 == 2){

      // looping thru each group and decreasing the brightness on the leds one by one in both groups
      for(int ledInGroup = 0; ledInGroup < halfLedsInDay2; ledInGroup++) {
        
        //decreasing the brightness on the leds in group 1(half of the circle) groups one by one
        fill_gradient(ledsB,ledGroupsDay2Start1,CHSV( 0, 0, maxBrtD21),ledInGroup,CHSV( 0, 0, maxBrtD21));
        //decreasing the brightness on the leds in group 2(the second half of the circle) groups one by one
        fill_gradient(ledsB,ledGroupsDay2Start2,CHSV( 0, 0, maxBrtD21),ledGroupsDay2Start2+ledInGroup,CHSV( 0, 0, maxBrtD21));
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds
        FastLED.show();
        
        // non-blocking delay that allows other void functions to be run
        currentMillis = previousMillis = millis();
        while(previousMillis + delayPassD21 >= currentMillis){
          //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
          otherVoidFunction();
          //sending the data to the leds with the modifications from the other void function
          FastLED.show();
          currentMillis = millis();
        }
      }     
      
      //decreasing the current pass for the animation
      currentPassDay2--;

    // pass two for the off animation
    }else if(currentPassDay2 == 1){

      // looping thru each group and increasing the brightness to current group, while keeping the previous brightness to the rest of the groups
      for(int ledInGroup = 0; ledInGroup < halfLedsInDay2; ledInGroup++) {
        
        //turning off the leds in group 1(half of the circle) groups one by one
        fill_gradient(ledsB,ledGroupsDay2End1,CHSV( 0, 0, 0),ledGroupsDay2End1-ledInGroup,CHSV( 0, 0, 0));
        //turning off the leds in group 2(the second half of the circle) groups one by one
        fill_gradient(ledsB,ledGroupsDay2End2,CHSV( 0, 0, 0),ledGroupsDay2End2-ledInGroup,CHSV( 0, 0, 0));
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds
        FastLED.show();
        
        // non-blocking delay that allows other void functions to be run
        currentMillis = previousMillis = millis();
        while(previousMillis + delayPassD22 >= currentMillis){
          //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
          otherVoidFunction();
          //sending the data to the leds with the modifications from the other void function
          FastLED.show();
          currentMillis = millis();
        }
      }
      
      //decreasing the current pass for the animation
      currentPassDay2--;
      
    }
    
  }

  //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //day lights anim 3 (button 6)
  //reading the button 6 and setting the state
  buttonState6 = digitalRead(buttonPin6);
  if(buttonState6 == HIGH){stateB6 = 1;}
  
  //checking the state for button 6 and signal on the same groups is off
  if(stateB6 == 1 && currentAnimAfterOffS1 == 0){
       
    // pass one of the animation
    if(currentPassDay3 == 0){
      
      // looping thru each group and turning on one group while keeping the rest off
      for(int group = 0; group < ledGroupsDay3; group++) {

        //changing the start and the end leds for the next loop
        ledGroupsDay3Start = (lastLedLastGroupDay3-(ledsInGroupDay3*group))-ledsInGroupDay3+1;
        ledGroupsDay3End = lastLedLastGroupDay3-(ledsInGroupDay3*group);
        
        //keeping the rest of the groups off
        fill_gradient(ledsA,resetLedGroupsDay3Start,CHSV( 0, 0, 0),lastLedLastGroupDay3,CHSV( 0, 0, 0));
        //turning on one group each loop
        fill_gradient(ledsA,ledGroupsDay3Start,CHSV( 0, 0, maxBrtD31),ledGroupsDay3End,CHSV( 0, 0, maxBrtD31));
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds
        FastLED.show();
        
        // non-blocking delay that allows other void functions to be run
        currentMillis = previousMillis = millis();
        while(previousMillis + delayPassD31 >= currentMillis){
          //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
          otherVoidFunction();
          //sending the data to the leds with the modifications from the other void function
          FastLED.show();
          currentMillis = millis();
        }
      }

      //turning off all the groups
      fill_gradient(ledsA,resetLedGroupsDay3Start,CHSV( 0, 0, 0),lastLedLastGroupDay3,CHSV( 0, 0, 0));
      //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
      otherVoidFunction();
      //sending the data to the leds
      FastLED.show();

      //reseting the start and the end leds for the next pass
      ledGroupsDay3Start = resetLedGroupsDay3Start;
      ledGroupsDay3End = resetLedGroupsDay3End;
        
      //increasing the current pass for the animation
      currentPassDay3++;

    // pass two of the animation
    }else if(currentPassDay3 == 1){

      //looping thru each group and turning the on one by one
      for(int group = 0; group < ledGroupsDay3; group++) {

        //turning the groups one by one
        fill_gradient(ledsA,ledGroupsDay3Start,CHSV( 0, 0, maxBrtD31),ledGroupsDay3End,CHSV( 0, 0, maxBrtD31));
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds
        FastLED.show();

        //changing the start and the end leds for the next loop
        ledGroupsDay3Start = ledGroupsDay3Start+ledsInGroupDay3;
        ledGroupsDay3End = ledGroupsDay3End+ledsInGroupDay3;
        
        // non-blocking delay that allows other void functions to be run
        currentMillis = previousMillis = millis();
        while(previousMillis + delayPassD32 >= currentMillis){
          //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
          otherVoidFunction();
          //sending the data to the leds with the modifications from the other void function
          FastLED.show();
          currentMillis = millis();
        }
      }

      //reseting the start and the end leds for the next pass
      ledGroupsDay3Start = resetLedGroupsDay3Start;
      ledGroupsDay3End = resetLedGroupsDay3End;
      
      //increasing the current pass for the animation
      currentPassDay3++;
    }

    //checking the button 6 if it's off and setting the state to be able to exit
    if(buttonState6 == LOW){stateB6 = 0;}
    
  }else if(stateB6 == 0 && currentAnimAfterOffS1 == 0){

    // pass one of the animation for turning off
    if(currentPassDay3 == 2){

      // looping thru each group and turning off one group while keeping the rest of the groups on
      for(int group = 0; group < ledGroupsDay3; group++) {

        //keeping the rest of the groups on
        fill_gradient(ledsA,resetLedGroupsDay3Start,CHSV( 0, 0, maxBrtD31),lastLedLastGroupDay3,CHSV( 0, 0, maxBrtD31));
        //turning off group one by one
        fill_gradient(ledsA,ledGroupsDay3Start,CHSV( 0, 0, 0),ledGroupsDay3End,CHSV( 0, 0, 0));
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds
        FastLED.show();

        //changing the start and the end leds for the next loop
        ledGroupsDay3Start = ledGroupsDay3Start+ledsInGroupDay3;
        ledGroupsDay3End = ledGroupsDay3End+ledsInGroupDay3;
        
        // non-blocking delay that allows other void functions to be run
        currentMillis = previousMillis = millis();
        while(previousMillis + delayPassD31 >= currentMillis){
          //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
          otherVoidFunction();
          //sending the data to the leds with the modifications from the other void function
          FastLED.show();
          currentMillis = millis();
        }
      }

      //turning on all the groups
      fill_gradient(ledsA,resetLedGroupsDay3Start,CHSV( 0, 0, maxBrtD31),lastLedLastGroupDay3,CHSV( 0, 0, maxBrtD31));
      //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
      otherVoidFunction();
      //sending the data to the leds
      FastLED.show();
      
      //reseting the start and the end leds for the next pass
      ledGroupsDay3Start = resetLedGroupsDay3Start;
      ledGroupsDay3End = resetLedGroupsDay3End;
      
      //decreasing the current pass for the animation
      currentPassDay3--;

    // pass two of the animation for turning off
    }else if(currentPassDay3 == 1){
      
      // looping thru each group and turning them off one by one
      for(int group = 0; group < ledGroupsDay3; group++) {

        //changing the start and the end leds for the next loop
        ledGroupsDay3Start = (lastLedLastGroupDay3-(ledsInGroupDay3*group))-ledsInGroupDay3+1;
        ledGroupsDay3End = lastLedLastGroupDay3-(ledsInGroupDay3*group);
        
        //turning groups off one by one
        fill_gradient(ledsA,ledGroupsDay3Start,CHSV( 0, 0, 0),ledGroupsDay3End,CHSV( 0, 0, 0));
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds
        FastLED.show();
        
        // non-blocking delay that allows other void functions to be run
        currentMillis = previousMillis = millis();
        while(previousMillis + delayPassD32 >= currentMillis){
          //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
          otherVoidFunction();
          //sending the data to the leds with the modifications from the other void function
          FastLED.show();
          currentMillis = millis();
        }
      }

      //reseting the start and the end leds for the next pass
      ledGroupsDay3Start = resetLedGroupsDay3Start;
      ledGroupsDay3End = resetLedGroupsDay3End;
        
      //decreasing the current pass for the animation
      currentPassDay3--;

      //if button 7 is pressed(tail lights are on), then we set the currentPassT1 to the last pass in tail light animation to turn the tail light back on
      if(stateB7 == 1){
        currentPassT1 = 3;
      }

    }
  }

  //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //tail lights animation 1 (button 7)
  //reading the button 7 and setting the state
  buttonState7 = digitalRead(buttonPin7);
  if(buttonState7 == HIGH){stateB7 = 1;}
  
  //checking the state for button 7 and signal that is on the same group if it's off
  if(stateB7 == 1 && currentAnimAfterOffS1 == 0){
       
    // pass one of the animation
    if(currentPassT1 == 0){
      
      // looping thru each subgroup of group 3 to create the passing animation
      for(int remainingGroups = nrOfSubGroupsFromGroup3Tail1; remainingGroups > 0; remainingGroups--) {

        // looping thru each sub group and turn them on one by one
        for(int group = 0; group < remainingGroups; group++) {

          //keeping the subgroups off until we reach the point to turn them on, after that we exclude them and let them on
          fill_gradient(ledsA,firstLedInGroup3Tail1,CHSV( 0, 0, 0),endLedInGroup3Tail1,CHSV( 0, 0, 0));
          //turning on the subgroups
          fill_gradient(ledsA,startLedInGroup3Tail1,CHSV( 255, 255, maxBrtT11),endLedInGroup3Tail1,CHSV( 255, 255, maxBrtT11));
          //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
          otherVoidFunction();
          //sending the data to the leds
          FastLED.show();

          //changing the start and the end leds for the next loop
          startLedInGroup3Tail1 = startLedInGroup3Tail1+nrLedInSubGroupsFromGroup3Tail1;
          endLedInGroup3Tail1 = endLedInGroup3Tail1+nrLedInSubGroupsFromGroup3Tail1;

          // non-blocking delay that allows other void functions to be run
          currentMillis = previousMillis = millis();
          while(previousMillis + delayPassT11 >= currentMillis){
            //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
            otherVoidFunction();
            //sending the data to the leds with the modifications from the other void function
            FastLED.show();
            currentMillis = millis();
          }
        }

        //resetting the start and the end leds for the next pass
        startLedInGroup3Tail1 = resetStartLedInGroup3Tail1;
        endLedInGroup3Tail1 = resetEndLedInGroup3Tail1;
      }

      //increasing the current pass of the animation
      currentPassT1++;      

    // pass two of the animation
    }else if(currentPassT1 == 1){

        // looping thru each subgroup of group 1 to create the passing animation
        for(int group = 0; group < nrOfSubGroupsFromGroup1Tail1; group++) {

          //fadeing to black group 1 and group 2 for smoothing the animation, except the leds that we turn on with the next fill_gradient function
          fadeToBlackBy( ledsA, nrLedInGroup1Tail1+nrLedInGroup2Tail1, fadeToBlackT1);
          //turning on the subgroups one by one
          fill_gradient(ledsA,startLedInGroup1Tail1,CHSV( 255, 255, maxBrtT11),endLedInGroup1Tail1,CHSV( 255, 255, maxBrtT11));
          //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
          otherVoidFunction();
          //sending the data to the leds
          FastLED.show();
          
          //changing the start and the end leds for the next loop
          startLedInGroup1Tail1 = startLedInGroup1Tail1+nrLedInSubGroupsFromGroup1Tail1;
          endLedInGroup1Tail1 = endLedInGroup1Tail1+nrLedInSubGroupsFromGroup1Tail1;

          // non-blocking delay that allows other void functions to be run
          currentMillis = previousMillis = millis();
          while(previousMillis + delayPassT12 >= currentMillis){
            //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
            otherVoidFunction();
            //sending the data to the leds with the modifications from the other void function
            FastLED.show();
            currentMillis = millis();
          }  
        }

        //continuing to fade to black group 1 and group 2 for smoothing the animation, except the leds that we turn on with the next fill_gradient function
        fadeToBlackBy( ledsA, nrLedInGroup1Tail1+nrLedInGroup2Tail1, fadeToBlackT1);
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds
        FastLED.show();

        //resetting the start and the end leds for the next pass
        startLedInGroup1Tail1 = resetStartLedInGroup1Tail1;
        endLedInGroup1Tail1 = resetEndLedInGroup1Tail1;

        //increasing the current pass of the animation
        currentPassT1++;

      //pass three of the animation
      }else if(currentPassT1 == 2){

        //continuing to fade to black group 1 and group 2 for smoothing the animation, except the leds that we turn on with the next fill_gradient function
        fadeToBlackBy(ledsA, nrLedInGroup1Tail1+nrLedInGroup2Tail1-1, fadeToBlackT1);
        //turning on group 2
        fill_gradient(ledsA,firstLedInGroup2Tail1,CHSV( 255, 255, maxBrtT11),lastLedInGroup2Tail1,CHSV( 255, 255, maxBrtT11));
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds
        FastLED.show();

        //increasing the current pass of the animation
        currentPassT1++;

      //pass four of the animation
      }else if(currentPassT1 == 3){

        // looping thru each subgroup of group 1 and group2 and turning them on one by one
        for(int group = 0; group < nrOfSubGroupsFromGroup1Tail1; group++) {

          //changing the start and the end leds for the next loop
          startLedInGroup1Tail1 = lastLedInGroup1Tail1-(nrLedInSubGroupsFromGroup1Tail1*group);

          //continuing to fade to black group 1 and group 2 for smoothing the animation, but we exclude the subgroups that we turn on
          fadeToBlackBy(ledsA, nrLedInGroup1Tail1+nrLedInGroup2Tail1, fadeToBlackT1);
          //turning on group 2
          fill_gradient(ledsA,firstLedInGroup2Tail1,CHSV( 255, 255, maxBrtT11),lastLedInGroup2Tail1,CHSV( 255, 255, maxBrtT11));
          //turning on each subgroup in group 1
          fill_gradient(ledsA,startLedInGroup1Tail1,CHSV( 255, 255, maxBrtT11),lastLedInGroup1Tail1,CHSV( 255, 255, maxBrtT11));
          //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
          otherVoidFunction();
          //sending the data to the leds
          FastLED.show();
          
          // non-blocking delay that allows other void functions to be run
          currentMillis = previousMillis = millis();
          while(previousMillis + delayPassT12 >= currentMillis){
            //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
            otherVoidFunction();
            //sending the data to the leds with the modifications from the other void function
            FastLED.show();
            currentMillis = millis();
          }  
        }

        //reseting the start led for the next pass
        startLedInGroup1Tail1 = resetStartLedInGroup1Tail1;

        //increasing the current pass of the animation
        currentPassT1++;

      //keeping all the groups on
      }else{

        //if day light anim 3 is on, don't update group 1 of leds with tail lights, because that will mess up the day light animation
        if(stateB6 == 0){
          //turning on group 1 if day light animation 3 is off
          fill_gradient(ledsA,firstLedInGroup1Tail1,CHSV( 255, 255, maxBrtT11),lastLedInGroup1Tail1,CHSV( 255, 255, maxBrtT11));
        }
        
        //keeping on groups 2 and 3
        fill_gradient(ledsA,firstLedInGroup2Tail1,CHSV( 255, 255, maxBrtT11),lastLedInGroup3Tail1,CHSV( 255, 255, maxBrtT11));
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();       
        //sending the data to the leds       
        FastLED.show();                  
      }
    
    //checking the button 7 if it's off and setting the state to be able to exit
    if(buttonState7 == LOW){stateB7 = 0;}

  //if button 7 it's off and the signal that is on the same group if it's off, then we start the turning off animation
  }else if(stateB7 == 0 && currentAnimAfterOffS1 == 0){

    //pass one for the turning off animation
    if(currentPassT1 == 4){

        // looping thru each subgroup of group 1 and group 2 and turn them off
        for(int group = 0; group < nrOfSubGroupsFromGroup1Tail1; group++) {

          //fade to black group 1 and group 2, while excluding the sub groups the that we didn't reache yet
          fadeToBlackBy(ledsA, nrLedInGroup1Tail1+nrLedInGroup2Tail1, fadeToBlackT1);
          //turn off each subgroup on group 1 one by one
          fill_gradient(ledsA,startLedInGroup1Tail1,CHSV( 255, 255, maxBrtT11),endLedInGroup1Tail1,CHSV( 255, 255, maxBrtT11));
          //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
          otherVoidFunction();
          //sending the data to the leds
          FastLED.show();


          //changing the start and the end leds for the next loop
          endLedInGroup1Tail1 = lastLedInGroup1Tail1-(nrLedInSubGroupsFromGroup1Tail1*group);
          
          // non-blocking delay that allows other void functions to be run
          currentMillis = previousMillis = millis();
          while(previousMillis + delayPassT12 >= currentMillis){
            //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
            otherVoidFunction();
            //sending the data to the leds with the modifications from the other void function
            FastLED.show();
            currentMillis = millis();
          }  
        }

        //reseting the end led for the next pass
        endLedInGroup1Tail1 = resetEndLedInGroup1Tail1;
        
        //continuing to fade to black group 1 and group 2 for smoothing the animation
        fadeToBlackBy(ledsA, nrLedInGroup1Tail1+nrLedInGroup2Tail1, fadeToBlackT1);
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds
        FastLED.show();

        //decreasing the current pass of the animation
        currentPassT1--;

      //pass two for the turning off animation
      }else if(currentPassT1 == 3){

        // looping thru each group to create the passing animation
        for(int group = 0; group < nrOfSubGroupsFromGroup1Tail1; group++) {

          //continuing to fade to black group 1 and group 2 for smoothing the animation, but excluding the subgroup that we turn on
          fadeToBlackBy( ledsA, nrLedInGroup1Tail1+nrLedInGroup2Tail1-1, fadeToBlackT1);
          //turning on one group at a time one by one
          fill_gradient(ledsA,startLedInGroup1Tail1,CHSV( 255, 255, maxBrtT11),endLedInGroup1Tail1,CHSV( 255, 255, maxBrtT11));
          //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
          otherVoidFunction();
          //sending the data to the leds
          FastLED.show();
          
          //changing the start and the end leds for the next loop
          startLedInGroup1Tail1 = startLedInGroup1Tail1+nrLedInSubGroupsFromGroup1Tail1;
          endLedInGroup1Tail1 = endLedInGroup1Tail1+nrLedInSubGroupsFromGroup1Tail1;

          // non-blocking delay that allows other void functions to be run
          currentMillis = previousMillis = millis();
          while(previousMillis + delayPassT12 >= currentMillis){
            //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
            otherVoidFunction();
            //sending the data to the leds with the modifications from the other void function
            FastLED.show();
            currentMillis = millis();
          }  
        }

        //continuing to fade to black group 1 and group 2 for smoothing the animation
        fadeToBlackBy( ledsA, nrLedInGroup1Tail1+nrLedInGroup2Tail1, fadeToBlackT1);
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds
        FastLED.show();

        //resetting the start and the end leds for the next pass
        startLedInGroup1Tail1 = resetStartLedInGroup1Tail1;
        endLedInGroup1Tail1 = resetEndLedInGroup1Tail1;

        //decreasing the current pass of the animation
        currentPassT1--;

      //pass three for the turning off animation
      }else if(currentPassT1 == 2){

        //continuing to fade to black group 1 and group 2 for smoothing the animation
        fadeToBlackBy(ledsA, nrLedInGroup1Tail1+nrLedInGroup2Tail1, fadeToBlackT1);
        //turning on group 2 (and on the next pass we fade it to black)
        fill_gradient(ledsA,firstLedInGroup2Tail1,CHSV( 255, 255, maxBrtT11),lastLedInGroup2Tail1,CHSV( 255, 255, maxBrtT11));
        //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
        otherVoidFunction();
        //sending the data to the leds
        FastLED.show(); 

        //decreasing the current pass of the animation
        currentPassT1--;
      
      //pass four for the turning off animation
      }else if(currentPassT1 == 1){

        // looping thru each subgroup of group 3
        for(int remainingGroups = 0; remainingGroups <= nrOfSubGroupsFromGroup3Tail1+1; remainingGroups++) {
  
          // looping thru each subgroup of group 3 and creating the passing animation, them turn them off one by one
          for(int group = remainingGroups; group >= 0; group--) {


            //changing the start and the end leds for the next loop
            startLedInGroup3Tail1 = resetStartLedInGroup3Tail1+(nrLedInSubGroupsFromGroup3Tail1*group);
            endLedInGroup3Tail1 = resetEndLedInGroup3Tail1+(nrLedInSubGroupsFromGroup3Tail1*group);

            //continuing to fade to black group 1 and group 2 for smoothing the animation
            fadeToBlackBy(ledsA, nrLedInGroup1Tail1+nrLedInGroup2Tail1, fadeToBlackT1);  
            //keeping the subgroups that we pass off
            fill_gradient(ledsA,resetStartLedInGroup3Tail1,CHSV( 0, 0, 0),resetEndLedInGroup3Tail1+(nrLedInSubGroupsFromGroup3Tail1*remainingGroups),CHSV( 0, 0, 0));
            //keeping the subgroups that we reach on and swipe it away
            fill_gradient(ledsA,startLedInGroup3Tail1,CHSV( 255, 255, maxBrtT11),endLedInGroup3Tail1,CHSV( 255, 255, maxBrtT11));
            //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
            otherVoidFunction();
            //sending the data to the leds
            FastLED.show();
  
            // non-blocking delay that allows other void functions to be run
            currentMillis = previousMillis = millis();
            while(previousMillis + delayPassT12 >= currentMillis){
              //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
              otherVoidFunction();
              //sending the data to the leds with the modifications from the other void function
              FastLED.show();
              currentMillis = millis();
            }
          }
  
          //resetting the start and the end leds for the next pass
          startLedInGroup3Tail1 = resetStartLedInGroup3Tail1;
          endLedInGroup3Tail1 = resetEndLedInGroup3Tail1;
        }
        
        //decreasing the current pass of the animation
        currentPassT1--;      

      }
  }

  //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  //if all the animations are done/off and no button is on, then we fade to black both led strips
  if(stateB1 == 0 && currentAnimAfterOffS1 == 0 && stateB2 == 0 && currentAnimAfterOffS2 == 0 && stateB3 == 0 && currentAnimAfterOffS3 == 0 && stateB4 == 0 && currentPassDay == 0 && stateB5 == 0 && currentPassDay2 == 0 && stateB6 == 0 && currentPassDay3 == 0 && stateB7 == 0 && currentPassT1 == 0 && stateB8 == 0){
    fadeToBlackBy( ledsA, NUM_LEDS_PART_A, fadeToBlackLeds);
    fadeToBlackBy( ledsB, NUM_LEDS_PART_B, fadeToBlackLeds);
  }
  
  //Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights.
  otherVoidFunction();
  //sending the data to the leds with the modifications from the other void function  
  FastLED.show();
}


//Other void function that can be run anywhere, also in non-blocking delay for tail, brake, reverse, fog and other lights. 
void otherVoidFunction(){

  //simulate a brake light in the non-blocking delay function while a animation is running (button 8)
  //reading the button 8 and setting the state
  buttonState8 = digitalRead(buttonPin8);
  if(buttonState8 == HIGH){stateB8 = 1;}

  //if the animation on button 2 or 5 is running, then we use strip 1 to simulate a brake light
  if(stateB8 == 1 && stateB2 == 1 || stateB8 == 1 && stateB5 == 1){
    fill_gradient(ledsA,75,CHSV( 255, 255, maxBrtOVF1),94,CHSV( 255, 255, maxBrtOVF1));
    fill_gradient(ledsA,105,CHSV( 255, 255, maxBrtOVF1),124,CHSV( 255, 255, maxBrtOVF1));
    fill_gradient(ledsA,135,CHSV( 255, 255, maxBrtOVF1),164,CHSV( 255, 255, maxBrtOVF1));
    if(buttonState8 == LOW){stateB8 = 0; prevStateB81 = 1;}
  }else{
    if(prevStateB81 == 1){
        fill_gradient(ledsA,75,CHSV( 255, 255, 0),94,CHSV( 255, 255, 0));
        fill_gradient(ledsA,105,CHSV( 255, 255, 0),124,CHSV( 255, 255, 0));
        fill_gradient(ledsA,135,CHSV( 255, 255, 0),164,CHSV( 255, 255, 0));
        if(buttonState8 == LOW){stateB8 = 0; prevStateB81 = 0;}
      }
    }

  //if the animation on button 1,3,4,6 or 7 is running, then we use strip 2 to simulate a brake light
  if(stateB8 == 1 && stateB1 == 1 || stateB8 == 1 && stateB3 == 1 || stateB8 == 1 && stateB4 == 1 || stateB8 == 1 && stateB6 == 1 || stateB8 == 1 && stateB7 == 1){
      fill_gradient(ledsB,0,CHSV( 255, 255, maxBrtOVF1),1,CHSV( 255, 255, maxBrtOVF1));
      fill_gradient(ledsB,4,CHSV( 255, 255, maxBrtOVF1),6,CHSV( 255, 255, maxBrtOVF1));
      fill_gradient(ledsB,9,CHSV( 255, 255, maxBrtOVF1),11,CHSV( 255, 255, maxBrtOVF1));
      fill_gradient(ledsB,14,CHSV( 255, 255, maxBrtOVF1),16,CHSV( 255, 255, maxBrtOVF1));
      fill_gradient(ledsB,19,CHSV( 255, 255, maxBrtOVF1),19,CHSV( 255, 255, maxBrtOVF1));
      if(buttonState8 == LOW){stateB8 = 0; prevStateB82 = 1;}
    }else{
      if(prevStateB82 == 1){
        fill_gradient(ledsB,0,CHSV( 255, 255, 0),19,CHSV( 255, 255, 0));
        if(buttonState8 == LOW){stateB8 = 0; prevStateB82 = 0;}
      }
    }

  //if no animation is running, the we use strip 1 and 2 to simulate a brake light
  if(stateB8 == 1 && stateB1 == 0 && stateB2 == 0 && stateB3 == 0 && stateB4 == 0 && stateB5 == 0 && stateB6 == 0 && stateB7 == 0){
      fill_gradient(ledsB,0,CHSV( 255, 255, maxBrtOVF1),1,CHSV( 255, 255, maxBrtOVF1));
      fill_gradient(ledsB,4,CHSV( 255, 255, maxBrtOVF1),6,CHSV( 255, 255, maxBrtOVF1));
      fill_gradient(ledsB,9,CHSV( 255, 255, maxBrtOVF1),11,CHSV( 255, 255, maxBrtOVF1));
      fill_gradient(ledsB,14,CHSV( 255, 255, maxBrtOVF1),16,CHSV( 255, 255, maxBrtOVF1));
      fill_gradient(ledsB,19,CHSV( 255, 255, maxBrtOVF1),19,CHSV( 255, 255, maxBrtOVF1));
      fill_gradient(ledsA,75,CHSV( 255, 255, maxBrtOVF1),94,CHSV( 255, 255, maxBrtOVF1));
      fill_gradient(ledsA,105,CHSV( 255, 255, maxBrtOVF1),124,CHSV( 255, 255, maxBrtOVF1));
      fill_gradient(ledsA,135,CHSV( 255, 255, maxBrtOVF1),164,CHSV( 255, 255, maxBrtOVF1));
      if(buttonState8 == LOW){stateB8 = 0; prevStateB83 = 1;}
  }else{
    if(prevStateB83 == 1){
      fill_gradient(ledsB,0,CHSV( 255, 255, 0),19,CHSV( 255, 255, 0));
      fill_gradient(ledsA,75,CHSV( 255, 255, 0),94,CHSV( 255, 255, 0));
      fill_gradient(ledsA,105,CHSV( 255, 255, 0),124,CHSV( 255, 255, 0));
      fill_gradient(ledsA,135,CHSV( 255, 255, 0),164,CHSV( 255, 255, 0));
      if(buttonState8 == LOW){stateB8 = 0; prevStateB83 = 0;}
    }
  }
}
