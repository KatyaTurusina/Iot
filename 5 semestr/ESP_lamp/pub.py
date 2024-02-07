import time
import paho.mqtt.client as paho
import questionary 

broker = 'broker.emqx.io'
client = paho.Client("client-isu-003")

print("Connecting to broker ", broker)
client.connect(broker)
client.loop_start()
topic = 'dashakatya'
#print(topic)
counter_start = 0
counter_end = 0 
while True:
    current_sec = int(time.time() % 60)
    if current_sec == 20 + counter_start:
        print(current_sec, "sec")
        print("Led is turned on")
        client.publish(topic, "1")
        time.sleep((40 - counter_end)-(20 + counter_start))
    elif current_sec == 40 - counter_end:
        print(current_sec, "sec")
        print("Led is turned off")
        client.publish(topic, "0")
        if counter_end % 2 == 1:
            counter_start += 1

        counter_end += 1
        if counter_end == 6:
            counter_end = 0

        if counter_start == 6:
            counter_start = 0
        time.sleep(59 - ((40 - counter_end) - (20 + counter_start)))
    else:
        time.sleep(1) 

client.disconnect()
client.loop_stop()
