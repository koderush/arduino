const int TrigPin = 6;
const int EchoPin = 7;
float range;
char buf[256];
void setup()
{
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}
void loop()
{
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  range = pulseIn(EchoPin, HIGH) / 58.0; //The echo time is converted into cm
  range = (int(range * 100.0)) / 100.0; //Keep two decimal places
  Serial.print("Distance:");
  Serial.print(range);
  Serial.print("cm");
  Serial.println();
  delay(1000);
}
