// Representation of numbers in 5x7 grid
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

// Function to send column data to pins D2-D9
void sendToPins(byte colData) {
  // Apply data to D2-D7 (Port D)
  PORTD = (PORTD & 0b00000011) | ((colData << 2) & 0b11111100);  // Send bits to D2-D7

  // Apply data to D8 and D9 (Port B)
  PORTB = (PORTB & 0b11111100) | (colData >> 6);  // Send remaining bits to D8 and D9
}

// Variables for Hall sensor and timing
const int hallPin = 12;   // Hall sensor connected to pin D12
volatile bool hallTriggered = false; // Hall sensor interrupt flag
unsigned long lastTriggerTime = 0;   // Time of last trigger (for calculating speed)
unsigned long columnDuration = 0;    // Duration for each column to display
int currentColumn = 0;               // Current column being displayed
int numberToDisplay = 5;             // The number to display (5 in this case)

// Interrupt service routine for the Hall sensor
void hallSensorISR() {
  unsigned long currentTime = micros();
  // Calculate the time between two sensor triggers (time to complete one full rotation)
  unsigned long rotationTime = currentTime - lastTriggerTime;

  // Calculate the duration to display each column based on the rotation speed
  columnDuration = rotationTime / 5; // 5 columns per number

  lastTriggerTime = currentTime;
  hallTriggered = true; // Set flag to indicate hall sensor was triggered
}

// Function to display the next column of the number
void displayNextColumn() {
  if (hallTriggered) {
    hallTriggered = false; // Reset the flag

    // Get column data for the current column
    byte colData = 0;
    for (int row = 0; row < 7; row++) {
      colData |= ((numbers[numberToDisplay][row] >> (4 - currentColumn)) & 0x01) << row;
    }

    // Send column data to the pins
    sendToPins(colData);

    // Move to the next column
    currentColumn++;
    if (currentColumn >= 5) {
      currentColumn = 0; // Wrap around to the first column
    }
  }
}

void setup() {
  // Set D2 to D7 as OUTPUT (on Port D), leave D0 and D1 unchanged
  DDRD |= 0b11111100;  // 11111100 sets D2-D7 as output

  // Set D8 and D9 as OUTPUT (on Port B)
  DDRB |= 0b00000011;  // 00000011 sets D8 and D9 as output

  // Hall sensor setup
  pinMode(hallPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(hallPin), hallSensorISR, FALLING);

  Serial.begin(9600);  // Optional for debugging purposes
}

void loop() {
  // Display the next column when the Hall sensor detects the magnet
  displayNextColumn();
}
