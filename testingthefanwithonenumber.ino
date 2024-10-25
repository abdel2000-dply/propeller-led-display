// Pin assignments
const int hallSensorPin = 12;
const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9}; // D2 to D9 for the LEDs

// Variables for time calculations
volatile unsigned long lastDetectionTime = 0;
volatile unsigned long timePerRevolution = 0;
unsigned long currentTime = 0;

// Binary matrix representation of the number 5
// Each row represents an LED column (from D2 to D9)
// '1' = LED on, '0' = LED off
byte number5[8] = {
  B11111000, // #####
  B10000000, // #    
  B10000000, // #    
  B11110000, // #### 
  B00001000, //     #
  B00001000, //     #
  B10001000, // #   #
  B01110000  //  ###
};

// Interrupt service routine for Hall sensor detection
void hallSensorISR() {
  unsigned long detectionTime = millis(); // Get the current time
  timePerRevolution = detectionTime - lastDetectionTime; // Calculate the time for one full revolution
  lastDetectionTime = detectionTime; // Update the last detection time
}

void setup() {
  // Set LED pins as OUTPUT
  for (int i = 0; i < 8; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  
  // Set up Hall sensor pin
  pinMode(hallSensorPin, INPUT);
  
  // Attach interrupt to Hall sensor pin
  attachInterrupt(digitalPinToInterrupt(hallSensorPin), hallSensorISR, FALLING);
  
  // Initialize the last detection time
  lastDetectionTime = millis();
}

void loop() {
  // If the timePerRevolution is calculated (not zero), display the number
  if (timePerRevolution > 0) {
    // Calculate the time interval for each column (8 columns in total for the number 5)
    unsigned long columnInterval = timePerRevolution / 8;
    
    // Display each column in sync with the rotation
    for (int col = 0; col < 8; col++) {
      // Display the column based on the binary matrix for the number 5
      for (int row = 0; row < 8; row++) {
        digitalWrite(ledPins[row], bitRead(number5[col], row)); // Set LED state
      }
      
      // Wait for the next column based on the rotation speed
      delayMicroseconds(columnInterval);
    }
  }
}
