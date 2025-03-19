int latch = 9
int clock = 10
int data = 8
int stop_button = 11
int start_button = 12


void setup() {
  // put your setup code here, to run once:
  pinMode(latch, OUTPUT)
  pinMode(clock, OUTPUT)
  pinMode(data, OUTPUT)
  pinMode(stop_button, INPUT_PULLUP)
  pinMode(start_button, INPUT_PULLUP)

}


void Display(){
  digitalWrite(latch, LOW)
  shiftOut(data, clock, MSBFIRST, table[num])
  digitalWrite(latch, HIGH)



}
void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(start_button) == LOW)
  {
    digitalWrite()

  }
  if (digitalRead(stop_button) == LOW)
  {
    digitalWrite()

  }

}


