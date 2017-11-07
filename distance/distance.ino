int tp =10;
int ep =9;
long duration, inches, cm;
void setup() {
  // put your setup code here, to run once:
Serial.begin(57600);
pinMode(tp,OUTPUT);
pinMode(ep,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(tp,0);
delayMicroseconds(5);
digitalWrite(tp,1);
delayMicroseconds(10);
digitalWrite(tp,0);

  duration = pulseIn(ep, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.println(inches);
  //Serial.print("in, ");
  //Serial.print(cm);
  //Serial.print("cm");
  //Serial.println();

  delay(500);
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
