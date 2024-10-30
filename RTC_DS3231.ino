/*
  use the commented two line in the setup function to set the time
  and then comment them again to avoid resetting the time every time the arduino is powered on
*/

#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // rtc.adjust(DateTime(2024, 10, 30, 13, 1, 0)); // Year, Month, Day, Hour, Minute, Second
  // Serial.println("Time reset successfully.");
}

void loop() {
  DateTime now = rtc.now();
  
  int hour = now.hour();
  int minute = now.minute();
  
  //To ensure hour and minute are two digits
  String formattedTime = (hour < 10 ? "0" : "") + String(hour) + ":" + (minute < 10 ? "0" : "") + String(minute);
  
  Serial.print("Current Time: ");
  Serial.println(formattedTime);

  delay(1000);
}