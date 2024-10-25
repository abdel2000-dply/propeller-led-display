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

// Time representation for 12:45 as 5x7 matrix (left to right: '1', '2', '4', '5')
const int timeDigits[4] = {1, 2, 4, 5};

volatile bool hallSensorTriggered = false; // Flag for Hall sensor detection

// Function to send column data to pins D2-D9
void sendToPins(byte colData) {
  // Apply data to D2-D7 (Port D)
  PORTD = (PORTD & 0b00000011) | ((colData << 2) & 0b11111100);  // Send bits to D2-D7

  // Apply data to D8 and D9 (Port B)
  PORTB = (PORTB & 0b11111100) | (colData >> 6);  // Send remaining bits to D8 and D9
}

// Function to display a single digit's column
void displayDigitColumn(int number, int col, int speed) {
  byte colData = 0;

  // Create the column data for the vertical LEDs
  for (int row = 0; row < 7; row++) {
    colData |= ((numbers[number][row] >> (4 - col)) & 0x01) << row;
  }

  // Send the column data to the pins
  sendToPins(colData);

  // Delay based on the speed
  delay(speed);
}

// Function to display the entire time on the LED matrix (4 digits: '12:45')
void displayTime(int speed) {
  // Loop through each digit in the time '12:45'
  for (int i = 0; i < 4; i++) {
    int currentDigit = timeDigits[i];

    // Display each column of the digit
    for (int col = 0; col < 5; col++) {
      displayDigitColumn(currentDigit, col, speed);
    }

    // Add space between digits
    delay(speed);
  }
}

// Hall sensor interrupt service routine (ISR)
void hallSensorISR() {
  hallSensorTriggered = true; // Set the flag when Hall sensor is triggered
}

void setup() {
  // Set D2 to D7 as OUTPUT (on Port D), leave D0 and D1 unchanged
  DDRD |= 0b11111100;  // 11111100 sets D2-D7 as output

  // Set D8 and D9 as OUTPUT (on Port B)
  DDRB |= 0b00000011;  // 00000011 sets D8 and D9 as output

  // Set Hall sensor pin (D12) as INPUT
  pinMode(12, INPUT);

  // Attach an interrupt to the Hall sensor pin (D12)
  attachInterrupt(digitalPinToInterrupt(12), hallSensorISR, RISING);

  Serial.begin(9600);  // Optional for debugging purposes
}

void loop() {
  int displaySpeed = 500;  // Speed to control how fast columns change (milliseconds)

  // Check if Hall sensor was triggered
  if (hallSensorTriggered) {
    hallSensorTriggered = false; // Reset the flag

    // Display '12:45' on the propeller display
    displayTime(displaySpeed);
  }
}
