
char inp[20];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

int i = 0;
void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
     while(Serial.available()){
      inp[i] = Serial.read();
    
      if(i==19){
        if(inp[0] == 's'){
          Serial.print("set ");
          Serial.print((int)inp[1]);
          
          Serial.println();
        }else if(inp[0] == 'g'){
          Serial.print("get ");
          Serial.print((int)inp[1]);
          
          Serial.println();
        }
      }
    
      i++;
      i%=20;
     }
  }else{
     i = 0;  
  }
}
