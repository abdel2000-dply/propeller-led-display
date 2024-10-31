// Description: This program demonstrates how to display numbers and colon (:) on a 5x7 LED matrix.
// The numbers are represented in a 5x7 grid format, and the colon is represented in a 5x3 grid format(will be corrected).
// The program displays the numbers "12:45" digit by digit, column by column, with a delay between each column to control 
// the speed of the display. The numbers are displayed using the "displayNumberColByCol" function, and the colon is displayed using the "displayColon" function.
// The speed of the display can be adjusted by changing the "displaySpeed" variable. The program can be modified to display other numbers or characters by adding them to the "numbers" and "colon" arrays and calling the corresponding display functions.


// ====================
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

// Function to display a number column by column
void displayNumberColByCol(int number, int speed) {
  if (number < 0 || number > 9) return;  // Ensure valid number

  // Loop through each column of the number (5 columns)
  for (int col = 0; col < 5; col++) {
    // For each row in the column
    for (int row = 0; row < 7; row++) {
      // Extract the bit in the current column and print it
      if (numbers[number][row] & (1 << (4 - col))) {
        Serial.print("#");  // Simulate turning on the LED
      } else {
        Serial.print(" ");  // Simulate turning off the LED
      }
    }
    Serial.println();  // Move to the next column (new line)
    delay(speed);      // Control the speed of displaying each column
  }
}

// Function to display the colon (:) column by column
void displayColon(int speed) {
  for (int col = 0; col < 3; col++) {
    // For each row in the column
    for (int row = 0; row < 7; row++) {
      if (colon[row] & (1 << (2 - col))) {
        Serial.print("#");  // Simulate turning on the LED
      } else {
        Serial.print(" ");  // Simulate turning off the LED
      }
    }
    Serial.println();  // Move to the next column (new line)
    delay(speed);      // Control the speed of displaying each column
  }
}

void setup() {
  Serial.begin(9600);
  int displaySpeed = 500;  // Speed to control how fast columns change (milliseconds)

  // Display "12:45" digit by digit, column by column
  displayNumberColByCol(1, displaySpeed);  // Display number 1
  displayNumberColByCol(2, displaySpeed);  // Display number 2
  displayColon(displaySpeed);              // Display colon ':'
  displayNumberColByCol(4, displaySpeed);  // Display number 4
  displayNumberColByCol(5, displaySpeed);  // Display number 5
}

void loop() {
  // The loop can be used to keep repeating the display if needed | for now, it's not needed
}
