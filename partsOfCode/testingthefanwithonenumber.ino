// Representation of numbers in 5x7 grid (8 rows for extra space)
const byte numbers[10][8] = {
  {0b01110, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b01110, 0b00000}, // 0
  {0b00100, 0b01100, 0b00100, 0b00100, 0b00100, 0b00100, 0b01110, 0b00000}, // 1
  {0b01110, 0b10001, 0b00001, 0b00110, 0b01000, 0b10000, 0b11111, 0b00000}, // 2
  {0b01110, 0b10001, 0b00001, 0b00110, 0b00001, 0b10001, 0b01110, 0b00000}, // 3
  {0b00010, 0b00110, 0b01010, 0b10010, 0b11111, 0b00010, 0b00010, 0b00000}, // 4
  {0b11111, 0b10000, 0b11110, 0b00001, 0b00001, 0b10001, 0b01110, 0b00000}, // 5
  {0b00110, 0b01000, 0b10000, 0b11110, 0b10001, 0b10001, 0b01110, 0b00000}, // 6
  {0b11111, 0b00001, 0b00001, 0b00010, 0b00100, 0b01000, 0b10000, 0b00000}, // 7
  {0b01110, 0b10001, 0b10001, 0b01110, 0b10001, 0b10001, 0b01110, 0b00000}, // 8
  {0b01110, 0b10001, 0b10001, 0b01111, 0b00001, 0b00010, 0b01100, 0b00000}  // 9
};

int hallPin = 12;  // Hall sensor pin
int currentColumn = 0;  // Current column to be displayed

// Function to send column data to pins D2-D9
void sendToPins(byte colData) {
  PORTD = (PORTD & 0b00000011) | ((colData << 2) & 0b11111100);  // Send bits to D2-D7
  PORTB = (PORTB & 0b11111100) | (colData >> 6);  // Send bits to D8 and D9
}

// Function to display a single digit's column
void displayDigitColumn(int number, int col) {
  byte colData = 0;
  for (int row = 0; row < 7; row++) {
    colData |= ((numbers[number][row] >> (4 - col)) & 0x01) << row;
  }
  sendToPins(colData);
}

// Setup function
void setup() {
  DDRD |= 0b11111100;  // Set D2-D7 as output
  DDRB |= 0b00000011;  // Set D8 and D9 as output
  pinMode(hallPin, INPUT_PULLUP);  // Enable internal pull-up resistor on Hall sensor pin
  Serial.begin(9600);  // Optional for debugging
}

// Main loop
void loop() {
  int number = 5;  // Display the number 5
  
  if (digitalRead(hallPin) == LOW) {  // Magnet detected (Hall sensor gives LOW)
    displayDigitColumn(number, currentColumn);  // Display the current column of the number
    delay(2);  // Small delay to synchronize with rotation speed
    currentColumn = (currentColumn + 1) % 5;  // Move to the next column (5 columns per digit)
  }
}
