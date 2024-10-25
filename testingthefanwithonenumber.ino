// Define LED pins for segments of the 7-segment display
const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9}; // Pins connected to LEDs

// Hall sensor pin
const int hallSensorPin = 12;

bool hallSensorState = false;
bool previousHallSensorState = false;

unsigned long previousMillis = 0;
const long interval = 2; // Small delay between column refreshes for better visualization

// The binary matrix for displaying the number '5'
byte digit5[5] = {
  0b1111, // Row 1: ####
  0b1000, // Row 2: #
  0b1111, // Row 3: ####
  0b0001, // Row 4:    #
  0b1111  // Row 5: ####
};

void setup() {
  // Initialize LED pins
  for (int i = 0; i < 8; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Initialize Hall sensor pin
  pinMode(hallSensorPin, INPUT);
}

void loop() {
  // Read Hall sensor state
  hallSensorState = digitalRead(hallSensorPin);

  // If the sensor detects a change (magnet passing by), synchronize the display
  if (hallSensorState && !previousHallSensorState) {
    // Synchronize: Reset to the first column
    displayDigit5();
  }

  // Update the previous Hall sensor state
  previousHallSensorState = hallSensorState;
}

// Function to display the number '5'
void displayDigit5() {
  for (int col = 0; col < 5; col++) {
    unsigned long currentMillis = millis();
    
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      // Set the appropriate LEDs based on the binary matrix for column 'col'
      for (int row = 0; row < 4; row++) {
        bool ledState = bitRead(digit5[col], row); // Get the bit for this column and row
        digitalWrite(ledPins[row], ledState);      // Set the corresponding LED on or off
      }

      delay(5); // Short delay to let the LEDs light up before moving to the next column
    }
  }
}

