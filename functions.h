/* 
 * Alauddin Ansari
 * 2018-11-20
 * General Functions
 */

int getOnOffStatus(int currentHour, int onTime, int offTime)
{
    if (onTime == offTime) {
        return 0;
    }

    if (onTime < offTime) {
        if (currentHour >= onTime && currentHour < offTime) {
            return 1;
        }
        return 0;
    }

    if (onTime > offTime) {
        if (currentHour >= onTime && currentHour <= 23) {
            return 1;
        }
        else if (currentHour < offTime) {
            return 1;
        }
        return 0;
    }
}

void blinkLed(byte LedPin, int times)
{
  if (times > 0) {
    for (int i = 0; i < times; i++) {
      digitalWrite(LedPin, HIGH);
      delay(200);
      digitalWrite(LedPin, LOW);
      delay(350);
    }
  } else {
    digitalWrite(LedPin, HIGH);
    delay(100);
    digitalWrite(LedPin, LOW);
    delay(350);
  }
}
