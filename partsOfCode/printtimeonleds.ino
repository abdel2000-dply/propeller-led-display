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

// Custom representation for colon (':') (5 rows, 3 columns)
const byte colon[8] = {
  0b00000,
  0b00100,
  0b00000,
  0b00000,
  0b00100,
  0b00000,
  0b00000,
  0b00000
};

// Function to send a column of data to Port D (D0 to D7)
void sendColumnToPortD(byte colData) {
  PORTD = colData;  // Send the column data to the 8 pins on Port D (D0 to D7)
}

// Function to display a number column by column
void displayNumberColByCol(int number, int speed) {
  if (number < 0 || number > 9) return;  // Ensure valid number

  // Loop through each column of the number (5 columns)
  for (int col = 0; col < 5; col++) {
    byte colData = 0;
    // Create the column data for the 8 pins (7 bits for LED display, 1 bit unused)
    for (int row = 0; row < 7; row++) {
      // Shift the row data and set the bits accordingly
      colData |= ((numbers[number][row] >> (4 - col)) & 0x01) << row;
    }

    // Send the column data to the LED line (D0-D7)
    sendColumnToPortD(colData);

    delay(speed);  // Control the speed of displaying each column
  }
}

// Function to display the colon (:) column by column
void displayColon(int speed) {
  for (int col = 0; col < 3; col++) {
    byte colData = 0;
    for (int row = 0; row < 7; row++) {
      colData |= ((colon[row] >> (2 - col)) & 0x01) << row;
    }

    // Send the column data to Port D (D0-D7)
    sendColumnToPortD(colData);

    delay(speed);  // Control the speed of displaying each column
  }
}

void setup() {
  Serial.begin(9600);

  // Set pins D0 to D7 as OUTPUT (Port D on Arduino Nano)
  DDRD = 0xFF;  // 0xFF = 11111111, sets all pins of Port D as output

  int displaySpeed = 500;  // Speed to control how fast columns change (milliseconds)

  // Display "12:45" digit by digit, column by column
  displayNumberColByCol(1, displaySpeed);  // Display number 1
  displayNumberColByCol(2, displaySpeed);  // Display number 2
  displayColon(displaySpeed);              // Display colon ':'
  displayNumberColByCol(4, displaySpeed);  // Display number 4
  displayNumberColByCol(5, displaySpeed);  // Display number 5
}

void loop() {
  // The loop can be used to keep repeating the display if needed
}
