#include <Wire.h>

unsigned char id = 1; //address of the first slave
int sender_id = 0;

unsigned char sendTo;
const String names[] = {"Slave1", "Slave2", "Slave3"};
const unsigned char addresses[] = {1, 2, 3};

void setup() {
  Serial.begin(9600);   
  Wire.begin(id);
  Wire.onReceive(receiveEvent);
}

void loop() {
    if (Serial.available()) {
      String input = Serial.readStringUntil('\n');
      sendTo = input.charAt(0) - '0';
      if (sendTo == 'r' - '0') { //respond
        sendTo = sender_id;
      }
      else {
        for (int i = 0; i < sizeof(names)/sizeof(names[0]); i++) {
          if (names[i] == input.substring(0, input.indexOf(" "))) {
            sendTo = addresses[i];
            break;
          }
        }
      }
      
      String message = input.substring(input.indexOf(" ") + 1);
      
      Serial.print("Message to ");
      Serial.print(names[sendTo-1]);
      Serial.print(": ");
      Serial.print(message);
      
      Wire.beginTransmission(sendTo);
      Wire.write(id);
      Wire.write(message.c_str());
      Wire.endTransmission(); 
      Serial.println();
    }
}

void receiveEvent(int byteCount) {
  sender_id = Wire.read();
  Serial.print("Message from ");
  Serial.print(names[sender_id - 1]);
  Serial.print(": ");
  while (Wire.available()) {
    char messageText = Wire.read();
    Serial.write(messageText);
  }  
  Serial.println();     
}
