#define TOTAL_SWT 3     // 3 Switch controller

// AtTiny85 I/O pins
#define SWT_1 1
#define SWT_2 3
#define SWT_3 4

/**
 * Pins Setting
 * -------------------------
 * Pin0 - RTC SDA (Phy Pin5) - occupied
 * Pin2 - RTC SCL (Phy Pin7) - occupied
*/

/** 
 * Time schedule (in Hour) -- Same on and off value means disable
 * Switches                    = { Pin, OnHour, OffHour }
 */


/* Configure settings below */
uint8_t Switches[TOTAL_SWT][3] = { {SWT_1, 6, 22}, {SWT_2, 10, 18}, {SWT_3, 8, 0} };

uint8_t driftSecond = 2;      // To adjust RTC time drift every hour in seconds. Many RTC drift time.
