#include <SoftwareSerial.h>

#define START_PIN 2
#define END_PIN 9


SoftwareSerial next_node(10, 11);
int num_node = 0;
 
// 2 3 4 5 6 7 8 9 
// A B . C D E G F
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
  for(int i=START_PIN; i <=END_PIN; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  Serial.begin(9600);
  next_node.begin(9600);
  num_node = 3;
}

void loop() {
  if(Serial.available() >= 1){
    delay(20);
    if(Serial.available() >= num_node) {
      char user_input = Serial.read();
      int digit = (int)(user_input - '0');
      show_digit(digit);
      while(Serial.available()) {
        next_node.write(Serial.read());
      }
    }
    else{
      for(int i = num_node; i >= 1; i--){
        if(Serial.available() >= i){
          for(int j = 0; j < i; j++){
            next_node.write(Serial.read());
          }
          turn_off();
          show_digit(0);
        }
      }
    } 
  }
}

void show_digit(int digit) {
  if (digit < 0 or digit > 9) {
    return;
  }
  for(int i = START_PIN; i <= END_PIN; i++) {
    digitalWrite(i, !digits[digit][i-START_PIN]);
  }
}

void turn_off() {
  for(int i = 2; i < 10; i++) {
    digitalWrite(i, HIGH);
  }
}
