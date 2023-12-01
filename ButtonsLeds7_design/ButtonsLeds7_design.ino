#define BUTTON_PIN 2
#define LED_PIN 3
#define BOUNCE_TIME 50
#define PRESSED HIGH
#define START_PIN 4
#define END_PIN 11

volatile long int press_time = 0;
volatile bool pressed_candidate = false;
volatile long int hold_time = 0;
volatile int press_count = 0;
bool button_pressed = false;

bool ledOn = false;
int ledBrightness = 0;
bool increasingBrightness = true;

bool digits[10][8] = {
  {1,1,0,1,1,1,0,1},  // 0
  {0,1,0,1,0,0,0,0},  // 1
  {1,1,0,0,1,1,1,0},  // 2
  {1,1,0,1,1,0,1,0},  // 3
  {0,1,0,1,0,0,1,1},  // 4
  {1,0,0,1,1,0,1,1},  // 5
  {1,0,1,1,1,1,1,1},  // 6
  {1,1,0,1,0,0,0,0},  // 7
  {1,1,0,1,1,1,1,1},  // 8
  {1,1,1,1,1,0,1,1}   // 9
};

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  for(int i=START_PIN; i <=END_PIN; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), process_button_click, RISING);
}

void loop() {
  if (pressed_candidate == true) {
    if (millis() - press_time >= BOUNCE_TIME) {
      button_pressed = true;
      pressed_candidate = false;
    }
  }

  if (button_pressed) {
    button_pressed = false;

    if (!ledOn) {
      ledOn = true;
      ledBrightness = 255;
      analogWrite(LED_PIN, ledBrightness);
    } else {
      ledOn = false;
      ledBrightness = 0;
      analogWrite(LED_PIN, ledBrightness);
    }
  }

  if (ledOn && digitalRead(BUTTON_PIN) == PRESSED) {
    if (millis() - hold_time >= 200) {
      hold_time = millis();
      if (increasingBrightness) {
        ledBrightness += 20;
        if (ledBrightness >= 255) {
          increasingBrightness = false;
          ledBrightness = 255;
        }
        analogWrite(LED_PIN, ledBrightness);
      } else {
        ledBrightness -= 20;
        if (ledBrightness <= 0) {
          increasingBrightness = true;
          ledBrightness = 0;
        }
        analogWrite(LED_PIN, ledBrightness);
      }
      show_number(round((hold_time) / 3000));
    }
  }
}

void process_button_click() {
  if (pressed_candidate == false) {
    press_time = millis();
    pressed_candidate = true;
    press_count++;
    hold_time = 0;
  }
}
void show_number(int digit) {
  if (digit < 0 or digit > 9) {
    return;
  }
  for(int i = START_PIN; i <= END_PIN; i++) {
    digitalWrite(i, !digits[digit][i-START_PIN]);
  }
}
