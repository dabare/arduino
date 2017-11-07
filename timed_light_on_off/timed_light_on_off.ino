

#include <DS3231.h>
#define light 6
DS3231  rtc(SDA, SCL);

void setup()
{
  Serial.begin(115200);
  pinMode(light, OUTPUT);
  rtc.begin();
  digitalWrite(light, HIGH);
}
Time t;
int fullTime = 0;
void loop()
{
  t = rtc.getTime();
  fullTime = t.hour * 100 + t.min;
  Serial.print(t.dow);
  Serial.println(fullTime);
  switch (t.dow) {
    case FRIDAY:
      if (fullTime >= 1830 && fullTime < 2215) {
        digitalWrite(light, LOW);
      } else {
        digitalWrite(light, HIGH);
      }
      break;
    case SUNDAY:
      if (fullTime >= 1830 && fullTime < 2230) {
        digitalWrite(light, LOW);
      } else {
        digitalWrite(light, HIGH);
      }
      break;
    default:
      if (fullTime >= 1830 && fullTime < 2200) {
        digitalWrite(light, LOW);
      } else {
        digitalWrite(light, HIGH);
      }
      break;
  }
  delay (900);
}

