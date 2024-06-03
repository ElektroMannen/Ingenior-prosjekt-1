import paho.mqtt.client as mqtt
import serial

ser = serial.Serial('/dev/ttyS0', 115200) #9600 is baud rate(must be same with that of NodeMCU)
ser.flush()

def on_connect(client, userdata, flags, reason_code, properties):
    print(f"Connected with result code {reason_code}")
    client.subscribe("info/test")


def on_subscribe(client, userdata, mid, reason_code_list, properties):
    if reason_code_list[0].is_failure:
        print(f"Broker rejected you subscription: {reason_code_list[0]}")
    else:
        print(f"Broker granted the following QoS: {reason_code_list[0].value}")

def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

def on_publish(client, userdata, mid, reason_code, properties):
    try:
        userdata.remove(mid)
    except KeyError:
        print("on_publish() is called with a mid not present in unacked_publish")
    

unacked_publish = set()
mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
mqttc.on_publish = on_publish

mqttc.on_connect = on_connect
mqttc.connect("localhost")

mqttc.user_data_set(unacked_publish)
#mqttc.loop_start()


mqttc.loop_start()
while True:
    line = ser.readline().decode("utf-8").rstrip()
    msg_info2 = mqttc.publish("info/test", line, qos=1)
    unacked_publish.add(msg_info2.mid)
    msg_info2.wait_for_publish()