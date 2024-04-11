# Why is ESP-Now used and not mobile network?

It is quite simple.

Using mobile network would require a SIM card and a data plan, these are not easy to aquire in Norway as it is regulated by the government. Not to mention the additional hardware that is required like the SIM800L module which we do not have available. ESP-Now is a protocol that is built into the ESP32 and is a lot easier to use and set up.

However, there might be an extra module created to suit the needs of mobile network users, however, this is not a priority at the moment.

# How does the ESP-Now protocol work?

The ESP-Now protocol is a built in protocol provided by Espressif for the ESP32. It boasts a maximum range of 200 meters in open air and a low latency of 2ms, which is ideal for our use case. It communicates through the 2.4GHz frequency band, and acts like a low power WiFi connection. Not to mention that the connection is persistent, and will reconnect automatically if the connection is lost.

# What will it be used for?

The ESP-Now protocol will be used to give commands to the cars wirelessly from one main ESP32 which is connected to the internet.