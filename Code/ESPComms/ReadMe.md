# Why is ESP-Now used and not mobile network?

It is quite simple.

Using mobile network would require a SIM card and a data plan, these are not easy to aquire in Norway as it is regulated by the government.
Not to mention the additional hardware that is required like the SIM800L module which we do not have available.
ESP-Now is a protocol that is built into the ESP32 and is a lot easier to use and set up.

However, there might be an extra module created to suit the needs of mobile network users, however, this is not a priority at the moment.