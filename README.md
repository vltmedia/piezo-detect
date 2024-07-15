# Piezo Detect OSC - ESP8266
An arduino sketch that sends OSC messages when a piezo sensor is hit. 

# Setup
1. Set the ```ssid``` and ```pass``` variables in the ```piezo_detect_osc.ino``` file to your wifi network's ssid and password.

# FAQ
1. Why is connection slow?
   1. UDP Creation on ESP8266 is very slow. Sorry. 