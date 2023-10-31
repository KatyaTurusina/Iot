#include "Config.h"
#include "WiFi.h"
#include "MQTT.h"
#include "server.h"

void setup() {

  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  bool is_ap_on = start_AP_mode();
  if(is_ap_on) {
    server_init();
  }
}

void loop() {

  server.handleClient();
  if (mqtt_client.connected()){
    mqtt_client.loop();
  }
  delay(100);
}
