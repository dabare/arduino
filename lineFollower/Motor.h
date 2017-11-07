#include <arduino.h>
class Motor{
  private:
    byte F;
    byte B; 
  public:
    Motor(byte f,byte b);
    void forward();
    void backward();
    void stop();
};

Motor::Motor(byte f,byte b){
  F = f, B = b;
  pinMode(f, OUTPUT);
  pinMode(b, OUTPUT);
}

inline void Motor::forward(){
  digitalWrite(F,HIGH);
  digitalWrite(B,LOW);
}

inline void Motor::backward(){
  digitalWrite(B,HIGH);
  digitalWrite(F,LOW);
}

inline void Motor::stop(){
  digitalWrite(B,LOW);
  digitalWrite(F,LOW);
}
