// #include <SevSeg.h>

// SevSeg sevseg; 

int data = 8;
int latch = 9;
int clock = 10; 

const int start_button = 11;
const int reset_button = 12;

unsigned long previousMillis = 0;
const long interval = 1000;

int seconds = 0;
int minutes = 0;

bool isRunning = false; 

const byte digitPatterns[10] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

const byte digitSelect[4] = {
    0b00000001, // First digit (rightmost)
    0b00000010, // Second digit
    0b00000100, // Third digit
    0b00001000  // Fourth digit (leftmost)
};



void setup() {

  // put your setup code here, to run once:

  // byte numDigits = 4;

  // byte shiftRegisterPins[] = {8, 9, 10}; // latch, clock, data
  // byte digitPins[] = {}; 

  // bool resistorsOnSegments = false; 
  // bool updateWithDelays = false;
  // bool leadingZeros = false;
  // bool disableDecPoint = true;

  // byte hardwareConfig = COMMON_CATHODE;


  // // pinMode(latch, OUTPUT)
  // // pinMode(clock, OUTPUT)
  // // pinMode(data, OUTPUT)

  // sevseg.begin(hardwareConfig, numDigits, digitPins, shiftRegisterPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);

  //  sevseg.setBrightness(90);

  pinMode(data, OUTPUT);

  pinMode(latch, OUTPUT);

  pinMode(clock, OUTPUT);

  pinMode(reset_button, INPUT_PULLUP);

  pinMode(start_button, INPUT_PULLUP);

}

void DisplayTime(){
  int displayValue = (minutes * 100) + seconds; 
  
  int digit[4] = 
  {
    (displayValue / 1000) % 10,
    (displayValue / 100) % 10,
    (displayValue / 10) % 10,
    displayValue % 10

  };

  for (int i = 0; i < 4; i++){
    shiftOut(data, clock, MSBFIRST, digitPatterns[digit[i]]);
    shiftOut(data, clock, MSBFIRST, digitSelect[i]);

    digitalWrite(latch, HIGH);
    delay(5);
    digitalWrite(latch, LOW);
  }

}


void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(start_button) == LOW)
  {
    delay(200);
    isRunning = !isRunning; 
    
  }
  if (digitalRead(reset_button) == LOW)
  {
    delay(200);
    isRunning = false; 
    minutes = 0;
    seconds = 0; 

  }
  if (isRunning){
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval){
      previousMillis = currentMillis;

      if (minutes < 59 || seconds < 59){
        seconds++;
        if (seconds == 60){
          seconds = 0;
          minutes++;
        }
      } else {
        isRunning = false; 

      }

    }

  }

  DisplayTime();

}




