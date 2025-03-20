#include <SevSeg.h>

SevSeg sevseg; 

// int latch = 9;
// int clock = 10;
// int data = 8; 

const int stop_button = 11;
const int start_button = 12;

unsigned long previousMillis = 0;
const long interval = 1000;

int sec = 0;
int min = 0;

bool isRunning = false; 


void setup() {
  // put your setup code here, to run once:

  byte numDigits = 4;

  byte numDigits[] = {6, 7, 8, 9};
  byte digitPins[] = {10, 11, 12, 13}; 

  resistorsOnSegments = true; 

  byte hardwareConfig = COMMON_CATHODE;

  // pinMode(latch, OUTPUT)
  // pinMode(clock, OUTPUT)
  // pinMode(data, OUTPUT)

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);

  pinMode(stop_button, INPUT_PULLUP);

  pinMode(start_button, INPUT_PULLUP);
  
  sevseg.setBrightness(90);
  serial.Begin(9600);

}


void DisplayTime(){
  int displayValue = (minutes * 100) + seconds; 
  sevseg.setNumber(displayValue, 2); 

}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(start_button) == LOW)
  {
    delay(200);
    isRunning = !isRunning; 
    
  }
  if (digitalRead(stop_button) == LOW)
  {
    delay(200);
    isRunning = false; 
    minutes = 0;
    seconds = 0; 

  }
  if (isRunning){
    unsigned long currentMillis = millis() 

    if (currentMillis - previousMillis >= interval){
      previousMillis = currentMillis;

      if (minutes < 59 || seconds < 59){
        seconds++
        if (seconds == 60){
          seconds = 0;
          minutes++;
        }
      } else {
        isRunning = false; 

      }

    }

  }

  displayTime();
  sevseg.refreshDisplay(); 

}



