int x_pin = A0;
int y_pin = A1;
int sw_pin = 2;

int up_led = 3;
int left_led = 11;
int down_led = 9;
int right_led = 10;

void setup() 
{
  Serial.begin(9600);
  pinMode(sw_pin, INPUT_PULLUP);
  pinMode(up_led, OUTPUT);
  pinMode(left_led, OUTPUT);
  pinMode(down_led, OUTPUT);
  pinMode(right_led, OUTPUT);

  // put your setup code here, to run once:
}

void loop()
{
  int x_data = analogRead(x_pin);
  int y_data = analogRead(y_pin);
  int sw_data = digitalRead(sw_pin);

  Serial.print("x_data:");
  Serial.print(x_data);
  Serial.print("\t");
  Serial.print("y_data:");
  Serial.print(y_data);
  Serial.print("\t");
  Serial.print("sw_data:");
  Serial.print(sw_data);
  Serial.print("\t");

  int zone_min = 500;
  int zone_max = 550;

  if(sw_data == LOW)
  {
    digitalWrite(up_led, HIGH);
    digitalWrite(left_led, HIGH);
    digitalWrite(down_led, HIGH);
    digitalWrite(right_led, HIGH);
  }
  else
  {
     if(y_data < zone_min)
    {
    int brightness_up = map(y_data, zone_min, 0, 0, 255);
    analogWrite(up_led, brightness_up);
    }
    else
    { 
    analogWrite(up_led, 0);
    }

    if(y_data > zone_max)
    {
    int brightness_down = map(y_data, zone_max, 1023, 0, 255);
    analogWrite(down_led, brightness_down);
    }
    else
    {
    analogWrite(down_led, 0);
    }
    
    if(x_data > zone_max)
    {
    int brightness_right = map(x_data, zone_max, 1023, 0, 255);
    analogWrite(right_led, brightness_right);
    }
    else
    {
    analogWrite(right_led, 0);
    }

    if(x_data < zone_min)
    {
    int brightness_left = map(x_data, zone_min, 0, 0, 255);
    analogWrite(left_led, brightness_left);
    }
    else
    {
    analogWrite(left_led, 0);
    }
  }

  delay(100);
}

