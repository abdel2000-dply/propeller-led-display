// Variables for real-time count
unsigned long Real_time_millis = 0;
unsigned long Previous_real_time_millis = 0;
int SEC = 0;
int MIN = 45;
int HOUR = 2;

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
    0b01001110,
    0b10001010,
    0b10001010,
    0b10001010,
    0b01110010
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
  // Set pin modes
  for (int i = 2; i <= 9; i++) pinMode(i, OUTPUT);
  pinMode(12, INPUT);
  
  // Enable internal pull-up resistor on D12
  digitalWrite(12, HIGH);
}

void loop() {
  // Time update logic
  Real_time_millis = millis();
  if (Real_time_millis - Previous_real_time_millis >= 1000) {
    Previous_real_time_millis += 1000;
    SEC++;
    if (SEC > 59) { SEC = 0; MIN++; }
    if (MIN > 59) { MIN = 0; HOUR++; }
    if (HOUR > 23) { HOUR = 0; }
  }

  // Check Hall sensor
  if (digitalRead(12) == LOW) {
    displayTime();
  } else {
    clearLEDs();
  }
}

void displayTime() {
  // Display hours
  displayNumber(HOUR / 10);  // Tens
  addSpace();
  displayNumber(HOUR % 10);  // Ones
  addSpace();
  
  // Optional: Display colon between hours and minutes
  displayColon();
  addSpace();
  
  // Display minutes
  displayNumber(MIN / 10);   // Tens
  addSpace();
  displayNumber(MIN % 10);   // Ones
}

void displayNumber(byte num) {
  if (num > 9) return;  // Safety check
  
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