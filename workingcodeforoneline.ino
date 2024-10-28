// Variables for real-time count
unsigned long Real_time_millis = 0;
unsigned long Previous_real_time_millis = 0;
float SEC;
float MIN = 45;
float HOUR = 2;

// LED state
bool ledState = false;

void setup() {
  // Set pin modes
  pinMode(2, OUTPUT);  // D2 as output  
  pinMode(3, OUTPUT);  // D3 as output  
  pinMode(4, OUTPUT);  // D4 as output  
  pinMode(5, OUTPUT);  // D5 as output  
  pinMode(6, OUTPUT);  // D6 as output  
  pinMode(7, OUTPUT);  // D7 as output  
  pinMode(8, OUTPUT);  // D8 as output  
  pinMode(9, OUTPUT);  // D9 as output  
  pinMode(12, INPUT);  // D12 (Hall sensor) as input

  // Enable internal pull-up resistor on D12
  digitalWrite(12, HIGH);  // Enable pull-up resistor on D12

  // Initialize outputs to LOW
  PORTD &= B00000011;  // D2 to D7 LOW
  PORTB &= B11111100;  // D8 and D9 LOW
}

void loop() {
  // Calculate seconds, minutes, and hours
  Real_time_millis = millis();  
  
  if (Real_time_millis - Previous_real_time_millis >= 1000) {
    Previous_real_time_millis += 1000;
    
    SEC++;
    if (SEC > 59) {
      SEC = 0;
      MIN++;
    }
  
    if (MIN > 59) {
      MIN = 0;
      HOUR++;
    }
  }

  // Check Hall sensor state
  if (digitalRead(12) == LOW) { // Check if the Hall sensor pin (D12) is LOW
    ledState = true; // Set the LED state to on
  }

  // Turn on all LEDs when ledState is true
  if (ledState) {
    PORTB |= B00000011; // D8 and D9 HIGH
    PORTD |= B11111100; // D2, D3, D4, D5, D6, D7 HIGH
    ledState = false; // Reset the LED state after turning on
  } else {
    PORTB &= B11111100; // Turn off D8 and D9
    PORTD &= B00000011; // Keep D2 to D7 LOW
  }
}
