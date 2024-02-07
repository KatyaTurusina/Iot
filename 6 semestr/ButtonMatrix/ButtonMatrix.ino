#define ROWS 2
#define COLS 2
#define BOUNCE_TIME 50

int rowPins[ROWS] = {2, 3};
int colPins[COLS] = {4, 5};

char keys[ROWS][COLS] = {
  {'1', '2'},
  {'3', '4'}
};

bool buttonState[ROWS][COLS] = {0};

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }
  for (int i = 0; i < COLS; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }
}

void loop() {
  for (int i = 0; i < ROWS; i++) {
    digitalWrite(rowPins[i], LOW);
    for (int j = 0; j < COLS; j++) {
      bool currentState = digitalRead(colPins[j]);
      if (currentState != buttonState[i][j]) {
        delay(BOUNCE_TIME);
        currentState = digitalRead(colPins[j]);
        if (currentState != buttonState[i][j]) {
          buttonState[i][j] = currentState;
          if (currentState == LOW) {
            Serial.print("Pushed button ");
            Serial.println(keys[i][j]);
          }
        }
      }
    }
    digitalWrite(rowPins[i], HIGH);
    delay(10);
  }
}
