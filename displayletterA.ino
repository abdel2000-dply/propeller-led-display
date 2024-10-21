// use this to display the letter A on the 6 LEDs
// for the Arduino Uno/nano board

int led1 = 8;
int led2 = 9;
int led3 = 10;
int led4 = 11;
int led5 = 12;
int led6 = 13;


int letter[6][4] = {
  {0, 1, 1, 0},
  {1, 0, 0, 1},
  {1, 0, 0, 1},
  {1, 1, 1, 1},
  {1, 0, 0, 1},
  {1, 0, 0, 1}
};


void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
}

void loop()
{
  
  for (int col = 0; col < 4; col++) {
    for (int row = 0; row < 6; row++) {
      digitalWrite(led1 + row, letter[row][col]);
    }
    delay(1000);
  }
  delay(1000); // Wait for 1000 millisecond(s)
/*
  digitalWrite(led1, HIGH);
  delay(100);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  delay(100);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  delay(100);
  digitalWrite(led3, LOW);
  digitalWrite(led4, HIGH);
  delay(100);
  digitalWrite(led4, LOW);
  digitalWrite(led5, HIGH);
  delay(100);
  digitalWrite(led5, LOW);
  digitalWrite(led6, HIGH);
  delay(100);
  digitalWrite(led6, LOW);  
  
 
  delay(1000); // Wait for 1000 millisecond(s)
  */
}
