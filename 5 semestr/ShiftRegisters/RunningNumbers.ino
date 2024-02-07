int latchPin = 5;      
int clockPin = 3;
int dataPin = 7;

byte digits[10] = {
  B11011101,  // 0
  B01010000,  // 1
  B11001110,  // 2
  B11011010,  // 3
  B01010011,  // 4
  B10011011,  // 5
  B10111111,  // 6
  B11010000,  // 7
  B11011111,  // 8
  B11111011   // 9
};

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  digitalWrite(clockPin, LOW);
  Serial.begin(9600);
  for (int digit = 9; digit >= 0; digit--) {
      show_number(digit);
      delay(1000);
  	}
}

void loop() 
{
  if (Serial.available()) {
    char user_input = Serial.read();
	int digit = (int)(user_input - '0');
	show_number(digit);
  }
}

void show_number(int digit) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, digits[digit]);
  digitalWrite(latchPin, HIGH);
}
