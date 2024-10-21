// Purpose: Display the current time on the Serial Monitor
// will be used in the full code latter on with propeller led display
// the clock starts at 12:45:00 and it will increment the seconds
// directly after the arduino is powered on

unsigned long previousMillis = 0;
const unsigned long interval = 1000; // Update every second
int currentHour = 12;
int currentMinute = 45;
int currentSecond = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  updateCurrentTime();  // Call the function to update time
  displayTime();        // Call the function to display time
}

// Function to update time based on millis
void updateCurrentTime() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Increment seconds
    currentSecond++;
    
    if (currentSecond >= 60) {
      currentSecond = 0;
      currentMinute++;
      
      if (currentMinute >= 60) {
        currentMinute = 0;
        currentHour++;
        
        if (currentHour >= 24) {
          currentHour = 0;  // Reset hours after 23
        }
      }
    }
  }
}

// Function to display the current time
void displayTime() {
  Serial.print("Current Time: ");
  
  if (currentHour < 10) {
    Serial.print('0');  // Add leading zero for hour
  }
  Serial.print(currentHour);
  Serial.print(":");
  
  if (currentMinute < 10) {
    Serial.print('0');  // Add leading zero for minute
  }
  Serial.print(currentMinute);
  Serial.print(":");
  
  if (currentSecond < 10) {
    Serial.print('0');  // Add leading zero for second
  }
  Serial.println(currentSecond);
}
