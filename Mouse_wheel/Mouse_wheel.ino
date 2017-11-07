void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(A3,INPUT_PULLUP);
  pinMode(A4,INPUT_PULLUP);
}
byte o;
byte v[3]={0,0,0};
byte c = 0;
byte cm = 0;
byte ccm = 0;
byte mc=0;
int count = 0;
byte f=0;
void loop() {
  // put your main code here, to run repeatedly:
  byte r = digitalRead(A4) + digitalRead(A3);

  if(r!=o){
    v[c] = r;
    c++;
    
    if(c==3){
      f=0;
      byte val = v[0]+v[1]*10+v[2]*100;
      Serial.print(count);
      Serial.print(" ");
      count++;
      if(mc==3){
         mc=0;
         if(cm>ccm){
          cm=1;
          ccm=0; 
         }else{
           cm=0;
           ccm=1;
         }
      }
      if(val==12||val==201||val==120){
        f=1;
        ccm++;
        mc++;
      }else if(val==210||val==102||val==21){
        f=2;
        cm++;
        mc++;
      }else{
        if(cm>ccm){
          f=2;
        }else{
          f=1;
        }
      }
      if(f==2){
        Serial.print("c");
      }else{
        Serial.print("cc");
      }
      
      Serial.println();
    }
    c%=3;
  }
  o=r;
  delay(1);
}
