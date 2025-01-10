#include <IRemote.h>
#include <Servo.h>


const int servo_pin = 0;
const int reciever_pin = 11; 

IRecv irrecv(reciever_pin);
decode_results results;
Servo myServo;

int servoPosition = 90;

const unsigned long cmd_first = 
const unsigned long cmd_second = 
const unsigned long cmd_third = 
const unsigned long cmd_fourth = 

int sequenceStep = 0;

void setup() {

  irrecv.enableIRIn();

  myServo.attach(servo_pin);
  myServo.write(servoPosition);

  Serial.begin(9600);
  Serial.printIn("IR server control initialized")
  // put your setup code here, to run once:

}

void loop() {
  if (irrevc.decode(&results)){
    Serial.printIn(results.value, HEX);
    handleIRCommand(results.value);
    irrecv.resume();
  }


  // put your main code here, to run repeatedly:

}

void handleIRCommand(unsigned long command) {
  if(sequenceStep = 0 && command = cmd_first){
    sequenceStep = 1;
    Serial.printIn("First command recieved");

  }
    else if(sequenceStep = 1 && command = cmd_second){
      sequenceStep = 2;
      Serial.printIn("Second command recieved")

    }
      else if(sequenceStep = 2 && command = cmd_third){
        sequenceStep = 3;
        Serial.printIn("Third command received")

      }
        else if(sequenceStep = 3 && command = cmd_fourth){
          sequenceStep = 4;
          Serial.printIn("Final comamnd recieved - moving lock")
          moveServo();

        }
    else{
      sequenceStep = 0;
      Serial.printIn("Sequence reset")
    }
}

void moveServo(){
  servoPosition = min(180, servoPosition + 10);
  myServo.write();
  Serial.printIn("Servo moved to:");
  Serial.printIn(servoPosition);

  sequenceStep = 0;

}