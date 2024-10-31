#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

// Timing constants - adjust these for your rotation speed
#define COLUMN_DELAY 2      // Delay between columns (ms)
#define DIGIT_SPACE 3       // Number of blank columns between digits
#define DIGIT_WIDTH 5       // Width of each digit pattern

// Column patterns for all numbers (0-9)
const byte numbers[10][5] = {
  { // 0
    0b01111100,
    0b10000010,
    0b10000010,
    0b10000010,
    0b01111100
  },
  { // 1
    0b00000000,
    0b10000100,
    0b11111110,
    0b10000000,
    0b00000000
  },
  { // 2
    0b11000100,
    0b10100010,
    0b10010010,
    0b10001010,
    0b10000100
  },
  { // 3
    0b01000100,
    0b10000010,
    0b10010010,
    0b10010010,
    0b01101100
  },
  { // 4
    0b00011000,
    0b00010100,
    0b00010010,
    0b11111110,
    0b00010000
  },
  { // 5
    0b10110110,
    0b10010010,
    0b10010010,
    0b10010010,
    0b01100010
  },
  { // 6
    0b01111100,
    0b10010010,
    0b10010010,
    0b10010010,
    0b01100100
  },
  { // 7
    0b00000110,
    0b00000010,
    0b11111010,
    0b00001010,
    0b00000110
  },
  { // 8
    0b01101100,
    0b10010010,
    0b10010010,
    0b10010010,
    0b01101100
  },
  { // 9
    0b01001100,
    0b10010010,
    0b10010010,
    0b10010010,
    0b01111100
  }
};

void setup() {
  // Initialize RTC
  if (!rtc.begin()) {
    // If RTC fails, flash all LEDs as warning
    while (1) {
      for (int i = 2; i <= 9; i++) {
        digitalWrite(i, HIGH);
      }
      delay(500);
      for (int i = 2; i <= 9; i++) {
        digitalWrite(i, LOW);
      }
      delay(500);
    }
  }

  // Set pin modes
  for (int i = 2; i <= 9; i++) pinMode(i, OUTPUT);
  pinMode(12, INPUT);
  
  // Enable internal pull-up resistor on D12
  digitalWrite(12, HIGH);
  
  // Uncomment the following line to set the time (only once!)
   rtc.adjust(DateTime(2024, 10, 31, 11, 52, 0)); // Year, Month, Day, Hour, Minute, Second
}

void loop() {
  // Get current time from RTC
  DateTime now = rtc.now();
  
  // Check Hall sensor
  if (digitalRead(12) == LOW) {
    displayTime(now.hour(), now.minute());
  } else {
    clearLEDs();
  }
}

void displayTime(int hour, int minute) {
  // Always display two digits for hour (00-23)
  if (hour < 10) {
    displayNumber(0);
    addSpace();
    displayNumber(hour);
  } else {
    displayNumber(hour / 10);
    addSpace();
    displayNumber(hour % 10);
  }
  addSpace();
  
  displayColon();
  addSpace();
  
  // Always display two digits for minute (00-59)
  if (minute < 10) {
    displayNumber(0);
    addSpace();
    displayNumber(minute);
  } else {
    displayNumber(minute / 10);
    addSpace();
    displayNumber(minute % 10);
  }
}

void displayNumber(byte num) {
  if (num > 9) return;
  
  for (int col = 0; col < DIGIT_WIDTH; col++) {
    clearLEDs();
    sendToPins(numbers[num][col]);
    delay(COLUMN_DELAY);
  }
}

void addSpace() {
  // Add space between digits
  for (int i = 0; i < DIGIT_SPACE; i++) {
    clearLEDs();
    delay(COLUMN_DELAY);
  }
}

void displayColon() {
  // Display two dots for the colon (:)
  byte colonPattern = 0b00100100;  // Changed pattern: two separated dots
  clearLEDs();
  sendToPins(colonPattern);
  delay(COLUMN_DELAY * 2);
}

void sendToPins(byte colData) {
  PORTD = (PORTD & 0b00000011) | ((colData << 2) & 0b11111100); // Send bits to D2-D7
  PORTB = (PORTB & 0b11111100) | (colData >> 6);                // Send bits to D8-D9
}

void clearLEDs() {
  PORTD &= 0b00000011;  // D2-D7 off
  PORTB &= 0b11111100;  // D8 and D9 off
}

/*
This code controls an LED matrix display to show the time in digital format.

Key functions:
- displayNumber(): Displays a single digit (0-9) using LED patterns stored in numbers[][]
- addSpace(): Adds spacing between digits by briefly turning off all LEDs
- displayColon(): Shows the colon separator between hours and minutes
- sendToPins(): Directly writes LED states to Arduino pins using port manipulation
- clearLEDs(): Turns off all LEDs by clearing the relevant pins

The display works by rapidly cycling through columns of LEDs to create persistence 
of vision. Port manipulation (PORTD/PORTB) is used for faster pin control compared 
to digitalWrite().

Pin usage:
- D2-D7: Connected to PORTD bits 2-7
- D8-D9: Connected to PORTB bits 0-1
*/