// motor one
int enA = 10;
int in1 = 9;
int in2 = 8;

void setup()
{
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}
void demoOne()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 100);
  delay(2000);
  
  // now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  

  delay(2000);
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  

}

void loop()
{
  demoOne();
  delay(1000);

}

