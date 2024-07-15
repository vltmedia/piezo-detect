#include <OSCMessage.h>


#include <WiFiUdp.h>
#include <ESP8266WiFi.h>



const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0

char ssid[] = "ssid"; //replace this with your WiFi network name
char pass[] = "*****"; //replace this with your WiFi network password

WiFiUDP Udp;                                // A UDP instance to let us send and receive packets over UDP
const IPAddress outIp(10,0,0,18);        // remote IP of your computer
const unsigned int outPort = 9999;          // remote port to receive OSC
const unsigned int localPort = 2390;        // local port to listen for OSC packets (not used/tested)


int sensorValue = 0;  // value read from the pot
int sensor2Value = 0;  // value read from the pot

int debounceDelay = 600;  // delay in microseconds
int currentWait = 0;  // delay in microseconds
bool ledState = false;  // ledState used to set the LED

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
    Serial.print("Local port: ");
    Serial.println(Udp.localPort());

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


void loop() {
  sensorValue = analogRead(analogInPin);
  digitalWrite(LED_BUILTIN, HIGH);  
  if(sensorValue > 6 && currentWait > debounceDelay) {
    currentWait = 0;
    sendMessage1();
    if(ledState == false) {
      ledState = true;
      digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    } else {
      ledState = false;
      digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
    }
  Serial.println(sensorValue);

  }

  currentWait += 100;
  delay(100);
}