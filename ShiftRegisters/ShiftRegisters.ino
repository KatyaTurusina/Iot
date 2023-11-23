int latchPin = 5;      
int clockPin = 3;
int dataPin = 7;       

int minutes = 0;
int seconds = 0;
unsigned long lastUpdate = 0;
bool start = false;

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
}

void loop() 
{
  if (Serial.available() >= 4) {
    minutes = (Serial.read() - '0') * 10; 
    minutes += (Serial.read() - '0');
    seconds = (Serial.read() - '0') * 10;
    seconds += (Serial.read() - '0');
    lastUpdate = millis();
    start = true;
  }
  
  if(start == true){
    int secondsPassed = (millis() - lastUpdate) / 1000;
  	lastUpdate += secondsPassed * 1000;
  	seconds += secondsPassed;
  
    if(seconds >= 60) {
      minutes++;
      seconds -= 60;
    }

    if(minutes < minutes + 1) {
      show_number(minutes / 10);
      show_number(minutes % 10);
      show_number(seconds / 10);
      show_number(seconds % 10);
      delay(1000);
    }
  } 
}

void show_number(int digit) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, digits[digit]);
  digitalWrite(latchPin, HIGH);
}
