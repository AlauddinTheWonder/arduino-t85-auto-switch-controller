/*
   Alauddin Ansari
   2020-03-28
   ATtiny85 Low-Powered Automate 3 switches
   Dependencies:
     TinyRTC : https://github.com/AlauddinTheWonder/arduino-tiny_rtc.git

   Build Size (ATtiny85, 8MHz):
   With drift: 3106 bytes
   W/o  drift: 1908 bytes
*/

#include "Watchdog.h"
#include "functions.h"
#include "TimeFunctions.h"


// Watchdog Settings
#define watchdog_mode 9  // 6=1sec (0.5sec), 7=2sec (1sec), 8=4sec (3.2sec), 9=8sec (7.4sec)
#define wtd_cnt_reset 75 // Actual task will be executed after this counter.
byte wtd_cnt = 0;        // Counter for task execution comparision.


/*
   Pins Setting
   -------------------------
   Pin0 - RTC SDA (Phy Pin5) - occupied
   Pin2 - RTC SCL (Phy Pin7) - occupied
*/

#define TOTAL_SWT 3     // 3 Switch controller

// Time schedule (in Hour) -- Same on and off value means disable
// Switches                    = { Pin, OnHour, OffHour }
uint8_t Switches[TOTAL_SWT][3] = { {1, 6, 23}, {3, 9, 18}, {4, 8, 0} };
uint8_t driftSecond = 2;      // To adjust RTC time drift every hour in seconds. Many RTC drift time.


int last_hour = -1;           // Last hour to compare current hour change, used in sync time drift.
boolean initialized = false;  // Flag to check whether running first time after powering up, used in sync time drift.


void setup() {
  for (uint8_t r = 0; r < TOTAL_SWT; r++)
  {
    uint8_t pin = Switches[r][0];

    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }

  connectRTC();

  setup_watchdog(watchdog_mode);

  delay(500);
}

void loop() {
  if (wtd_cnt == 0) {

    tmElements_t tm = getTime();

    delay(100);

    if (validateTime(tm)) {

      byte _hour = tm.Hour;

      for (uint8_t r = 0; r < TOTAL_SWT; r++)
      {
        uint8_t pin = Switches[r][0];
        uint8_t on = Switches[r][1];
        uint8_t off = Switches[r][2];

        byte switch_status = getOnOffStatus(_hour, on, off);
        digitalWrite(pin, switch_status);
        delay(100);
      }

      delay(500);


      // Delay time to sync drifted time in RTC module
      if (_hour != last_hour) {
        if (initialized) { // Ignore initial call.

          /**
             Sync drifted time
             This will correct drifted second in every hour
             Second must be less than 60 seconds.
          */
          if (driftSecond > 0) {
            // Update RTC module time with adjusted time
            // In TimeFunctions.h file
            syncDriftedTime(driftSecond);
          }
        }
        last_hour = _hour;
      }

      initialized = true;
    }
  }

  wtd_cnt++;

  if (wtd_cnt >= wtd_cnt_reset) {
    wtd_cnt = 0;
  }

  system_sleep();
}
