​import time
import paho.mqtt.client as mqtt_client
import random

broker="broker.emqx.io"

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")
    else:
        print("Failed to connect, return code %d\n", rc)


client= mqtt_client.Client(f'lab_{random.randint(10000, 99999)}')
client.on_connect = on_connect
client.connect(broker) 

for _ in range(10):
    state = "on" if random.randint(0,1) else "off"
    rnd = random.randint(4, 10)
    client.publish("katya", state)
    print(f"publish state is {state}")
    val = str(random.randint(100, 999))
    client.publish("katya", val)
    print(f"publish value is {val}")
    time.sleep(random.randint(4, 10))
    
client.disconnect()
