#include <OSCMessage.h>


#include <WiFiUdp.h>
// #include <ESP8266WiFi.h>
#include <WiFi.h>


const int LED_BUILTIN = 2;
// const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0
const int analogInPin = 34;  // ESP8266 Analog Pin ADC0 = A0
const int analogInPin2 = 35;  // ESP8266 Analog Pin ADC0 = A0

int sensorValue = 0;  // value read from the pot
int sensorValue2 = 0;  // value read from the pot

int debounceDelay = 200;  // delay in microseconds
int currentWait = 0;  // delay in microseconds
int currentWait2 = 0;  // delay in microseconds
bool ledState = false;  // ledState used to set the LED

char ssid[] = "Bravo Brain"; //replace this with your WiFi network name
char pass[] = "greenscreen12"; //replace this with your WiFi network password

WiFiUDP Udp;                                // A UDP instance to let us send and receive packets over UDP
const IPAddress outIp(10,0,0,9);        // remote IP of your computer
const unsigned int outPort = 9999;          // remote port to receive OSC
const unsigned int localPort = 2390;        // local port to listen for OSC packets (not used/tested)



void setup() {
  Serial.begin(115200);

 WiFi.begin(ssid, pass);
  Serial.println();
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("success!");
  Serial.print("IP Address is: ");
  Serial.println(WiFi.localIP());

    Serial.println("Starting UDP");
    Udp.begin(localPort);
    Serial.println("Connected To UDP!");


  pinMode(LED_BUILTIN, OUTPUT);  // Initialize the LED_BUILTIN pin as an output
}

void sendMessage1() {
    OSCMessage msg("/sensor1");
    msg.add("Knock1");
    Udp.beginPacket(outIp, outPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.empty();
}

void sendMessage2() {
    OSCMessage msg("/sensor2");
    msg.add("Knock2");
    Udp.beginPacket(outIp, outPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.empty();
}


void readSensor1() {
  sensorValue = analogRead(analogInPin);
  if(sensorValue > 16 && currentWait > debounceDelay) {
    currentWait = 0;
  sendMessage1();
  Serial.println(sensorValue);

  }

  currentWait += 100;
}

void readSensor2() {
  sensorValue2 = analogRead(analogInPin2);
  if(sensorValue2 > 16 && currentWait2 > debounceDelay) {
    currentWait2 = 0;
  Serial.println(sensorValue2);
  sendMessage2();
  }
  currentWait2 += 100;

}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  
  readSensor1();
  readSensor2();
  digitalWrite(LED_BUILTIN, LOW);  
  
  delay(500);

}