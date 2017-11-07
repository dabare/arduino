//Written by Ahmet Burkay KIRNIK
//TR_CapaFenLisesi //Measure Angle with a MPU-6050(GY-521)

#include <Wire.h>

const int MPU_addr = 0x68; int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

int minVal = 265; int maxVal = 402;

int x; double y; double z;

int old = 0;
void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
}

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
byte r,i=1,lf=0,rt=0;
void loop() {
  r=0;
  Wire.beginTransmission(MPU_addr); Wire.write(0x3B); Wire.endTransmission(false); Wire.requestFrom(MPU_addr, 14, true); AcX = Wire.read() << 8 | Wire.read(); AcY = Wire.read() << 8 | Wire.read(); AcZ = Wire.read() << 8 | Wire.read(); int xAng = map(AcX, minVal, maxVal, -90, 90); int yAng = map(AcY, minVal, maxVal, -90, 90); int zAng = map(AcZ, minVal, maxVal, -90, 90);

  //x = 100*(atan2(-yAng, -zAng) + PI); y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI); z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);
  x = 15.0 * (atan2(-yAng, -zAng) + PI); y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI); z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

  if ((old - x) > 0) {
    r=1;//L
    i++;
  }
  if ((x - old) > 0) {
    r=2;//R
    i++;
  }
  
  if(r){
    if(r==2){
      rt++;  
    }else{
      lf++;  
    }  
  }
  
  if(i==15){
    i=1;
    if(rt>lf ){
      Serial.println("R");  
    }
    if(rt<lf ){
      Serial.println("L");  
    }
    rt=0;
    lf=0;
  }
  old = x;
}
