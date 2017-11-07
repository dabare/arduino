

#include <EEPROM.h>

#include <IRremote.h>


#define addR  0
#define addB  1
#define addG  2
#define addW  3

#define pinR  10
#define pinB  5
#define pinG  6
#define pinW  9


#define defVal  100


int RECV_PIN = 7;

boolean powR = 0;
boolean powB = 0;
boolean powG = 0;
boolean powW = 0;

boolean flash = 0;
boolean smooth = 0;

byte selected = 0;
int val  =0;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  analogWrite(pinR,EEPROM.read(addR));
  analogWrite(pinB,EEPROM.read(addB));
  analogWrite(pinG,EEPROM.read(addG));
  analogWrite(pinW,EEPROM.read(addW));
  irrecv.enableIRIn(); // Start the receiver
  //EEPROM.write(addr, 2);
  //value = EEPROM.read(addr);

}
int temp = 0;

void dim(byte pin){
  allColDim();
  analogWrite(pinW,255);
  delay(10);
  analogWrite(pin,defVal);
  delay(100);
  analogWrite(pin,255);
  delay(100);
  analogWrite(pin,defVal);
  delay(100);
  analogWrite(pin,255);
  delay(100);
allPutBack();
}

void loop()
{ 
  if (irrecv.decode(&results)) {
    val =results.value;
    if(val == 16){
      selected = 1;
      dim(pinR);
    }else if(val == 2064){
      selected = 2;
      dim(pinB);
    }else if(val == 1040){
      selected = 3;
      dim(pinG);
    }else if(val == 3088){
      selected = 4;
      dim(pinW);
    }else if(val == 2320){
      selected = 0;
      dim(pinW);
      dim(pinW);
    }
    
    else if(val ==3216 ){
      if(selected == 1){
        temp = EEPROM.read(addR) + 1;
        if(temp<256){
          EEPROM.write(addR, temp);
          analogWrite(pinR,temp);
        }
      }else if(selected == 2){
        temp = EEPROM.read(addB) + 1;
        if(temp<256){
          EEPROM.write(addB, temp);
          analogWrite(pinB,temp);
        }
      }else if(selected == 3){
        temp = EEPROM.read(addG) + 1;
        if(temp<256){
          EEPROM.write(addG, temp);
          analogWrite(pinG,temp);
        }
      }else if(selected == 4){
        temp = EEPROM.read(addW) + 1;
        if(temp<256){
          EEPROM.write(addW, temp);
          analogWrite(pinW,temp);
        }
      }else if(selected == 0){
        temp = EEPROM.read(addR) + 1;
        if(temp<256){
          EEPROM.write(addR, temp);
          analogWrite(pinR,temp);
        }
        
        temp = EEPROM.read(addB) + 1;
        if(temp<256){
          EEPROM.write(addB, temp);
          analogWrite(pinB,temp);
        }
        
        temp = EEPROM.read(addG) + 1;
        if(temp<256){
          EEPROM.write(addG, temp);
          analogWrite(pinG,temp);
        }
        
        temp = EEPROM.read(addW) + 1;
        if(temp<256){
          EEPROM.write(addW, temp);
          analogWrite(pinW,temp);
        }
      }
    }else if(val == 1168){
      if(selected == 1){
        temp = EEPROM.read(addR) - 1;
        if(temp>-1){
          EEPROM.write(addR, temp);
          analogWrite(pinR,temp);
        }
      }else if(selected == 2){
        temp = EEPROM.read(addB) - 1;
        if(temp>-1){
          EEPROM.write(addB, temp);
          analogWrite(pinB,temp);
        }
      }else if(selected == 3){
        temp = EEPROM.read(addG) - 1;
        if(temp>-1){
          EEPROM.write(addG, temp);
          analogWrite(pinG,temp);
        }
      }else if(selected == 4){
        temp = EEPROM.read(addW) - 1;
        if(temp>-1){
          EEPROM.write(addW, temp);
          analogWrite(pinW,temp);
        }
      }else if(selected == 0){
        temp = EEPROM.read(addR) - 1;
        if(temp>-1 && temp != 2){
          EEPROM.write(addR, temp);
          analogWrite(pinR,temp);
        }
        
        temp = EEPROM.read(addB) - 1;
        if(temp>-1){
          EEPROM.write(addB, temp);
          analogWrite(pinB,temp);
        }
        
        temp = EEPROM.read(addG) - 1;
        if(temp>-1){
          EEPROM.write(addG, temp);
          analogWrite(pinG,temp);
        }
        
        temp = EEPROM.read(addW) - 1;
        if(temp>-1){
          EEPROM.write(addW, temp);
          analogWrite(pinW,temp);
        }
      }
    }
    
    
    else if(val == 2704){
      if(selected == 1){
        powR = !powR;
        if(powR){
          analogWrite(pinR,0);
          EEPROM.write(addR, 0);
        }else{
          analogWrite(pinR,255);
          EEPROM.write(addR, 255);
        }
      }else if(selected == 2){
        powB = !powB;
        if(powB){
          analogWrite(pinB,0);
          EEPROM.write(addB, 0);
        }else{
          analogWrite(pinB,255);
          EEPROM.write(addB, 255);
        }
      }else if(selected == 3){
        powG = !powG;
        if(powG){
          analogWrite(pinG,0);
          EEPROM.write(addG, 0);
        }else{
          analogWrite(pinG,255);
          EEPROM.write(addG, 255);
        }
      }else if(selected == 4){
        powW = !powW;
        if(powW){
          analogWrite(pinW,0);
          EEPROM.write(addW, 0);
        }else{
          analogWrite(pinW,255);
          EEPROM.write(addW, 255);
        }
      }
      delay(150);
    }
    //--------------------flash-------------------------
    else if(val == 144){
      flash = !flash;
      if(!flash){
        smooth = 0;
      }else{
        analogWrite(pinW, EEPROM.read(addW));
      }
      delay(150);
    }
    
    //-----------------------smooth color change--------------
    else if(val == 2192){
      smooth = !smooth;
      
      if(smooth){
        flash = 0;
      }else{
        analogWrite(pinR, EEPROM.read(addR));
        analogWrite(pinB, EEPROM.read(addB));
        analogWrite(pinG, EEPROM.read(addG));
      }
      delay(150);
    }
    Serial.println(val);
    
    irrecv.resume(); // Receive the next value
  }
  
     if(flash){
      flashDisco();
    }
    if(smooth){
     
    }
}
byte k = 1;
byte w = 100;
void flashDisco(){
  k  = random(0, 3);
  if(k == 1){
    k = pinR;
    w = addR;
  }else if(k == 2){
     k = pinB;
     w = addB;
  }else{
    k = pinG;
    w = addG;
  }
  analogWrite(pinW, EEPROM.read(addW));
  delay(4);
  analogWrite(pinW, 255);
  allColDim();
  analogWrite(k, random(EEPROM.read(w) , 255) );
  delay(130);
  analogWrite(k, 255);
  delay(40);
}
void allColDim(){
  analogWrite(pinR, 255);
  analogWrite(pinB, 255);
  analogWrite(pinG, 255);
}

void allPutBack(){
  analogWrite(pinR, EEPROM.read(addR));
  analogWrite(pinB, EEPROM.read(addB));
  analogWrite(pinG, EEPROM.read(addG));
  analogWrite(pinW, EEPROM.read(addW));
}
