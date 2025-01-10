#include <IRremote.hpp>
#include <Servo.h>

// defining pins 

const int servo_pin = 9;
const int reciever_pin = 11; 

IRrecv irrecv(reciever_pin);
decode_results results;
Servo myServo;

// initial servo position 

int servoPosition = 90;

// password for lock

const unsigned long cmd_first = 0xE718FF00; // 2
const unsigned long cmd_second = 0xBD42FF00; // 7
const unsigned long cmd_third = 0xA15EFF00; // 3
const unsigned long cmd_fourth = 0xAD52FF00; // 8

// sequence state 

int sequenceStep = 0;

void setup() {

  irrecv.enableIRIn();

  myServo.attach(servo_pin);
  myServo.write(servoPosition);

  Serial.begin(9600);
  Serial.println("IR server control initialized");
  // put your setup code here, to run once:

}

void loop() {
  if (irrecv.decode()){
    unsigned long command = irrecv.decodedIRData.decodedRawData;
    Serial.print("Command received: ");
    Serial.println(command, HEX);

    handleIRCommand(results.value);
    irrecv.resume(); // receive the next value
    delay(300);
  }

}

void handleIRCommand(unsigned long command) {
  if(sequenceStep == 0 && command == cmd_first){
    sequenceStep = 1;
    Serial.println("First command recieved");

  } else if(sequenceStep == 1 && command == cmd_second){
    sequenceStep = 2;
    Serial.println("Second command recieved");

  } else if(sequenceStep == 2 && command == cmd_third){
    sequenceStep = 3;
    Serial.println("Third command received");

  } else if(sequenceStep == 3 && command == cmd_fourth){
    sequenceStep = 4;
    Serial.println("Final comamnd recieved - moving lock");
    moveServo();

  } 
    else if(command != cmd_first && command != cmd_second && command != cmd_third && command != cmd_fourth){
    sequenceStep = 0;
    Serial.println("Sequence reset - incorrect passcode");
  }
}

void moveServo(){
  if(servoPosition == 90){
    servoPosition = 0;
    } else {
    servoPosition = 90;
  }
  myServo.write(servoPosition);
  Serial.println("Servo moved to:");
  Serial.println(servoPosition);

// reset the sequence step

  sequenceStep = 0;

}