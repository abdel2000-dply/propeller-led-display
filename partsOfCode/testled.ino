// simple test program for the LED on the Arduino nano board
// connect the arduino nano to the led and 220 ohm resistor on pin 8

void setup() {
  pinMode(8, OUTPUT); 
}

void loop() {
  digitalWrite(8, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(8, LOW);
  delay(1000);
}
