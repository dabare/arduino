int a = 0,k=0;
void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
a = analogRead(0);
if(a!=k){
  k=a;
Serial.println(a);
}
delay(100);
}
