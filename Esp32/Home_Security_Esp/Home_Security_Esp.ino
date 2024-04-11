#include <WiFi.h>
#include <SoftwareSerial.h>
#include <PubSubClient.h>
#include <string.h>

using namespace std;

#define FIRE_TRIGGERED 0x41
#define FIRE_HANDLED 0x01
#define GAS_TRIGGERED 0x42
#define GAS_HANDLED 0x02
#define FLOOD_TRIGGERED 0x43
#define FLOOD_HANDLED 0x03
#define MOTION_TRIGGERED 0x44
#define MOTION_HANDLED 0x04
#define DOOR_OPENED 0x45
#define DOOR_CLOSED 0x05

#define MOTION_ON 0xC6
#define MOTION_OFF 0x86
#define PANIC_ON 0xC7
#define PANIC_OFF 0x87
#define DISARM_ON 0xC8
#define DISARM_OFF 0x88
#define DOOR_OPEN 0xC9
#define DOOR_CLOSE 0x89

// Wi-Fi Credentials:
#define SSID "WE_992B10"     // Enter Wi-Fi name
#define PASSWORD "#100200#"  // Enter Wi-Fi password

// MQTT Credentails:
#define MQTT_SERVER "broker.emqx.io"
#define MQTT_PORT 1883

// ESP Client Configuration:
WiFiClient espClient;
const char* systemID = String("HSS@" + String(WiFi.macAddress())).c_str();
PubSubClient client(MQTT_SERVER, MQTT_PORT, espClient);

#define RX 1 
#define TX 2
SoftwareSerial avrSerial(RX, TX);

/***************************************************************************************************
  Function Prototypes
 ***************************************************************************************************/
void WIFI_Init();
void MQTT_Init();
void MQTT_Callback(char* topic, byte* payload, unsigned int length);
void MQTT_Reconnect();
void AvrToApp(uint8_t rData);
void AppToAvr(char* topic, char* payload);

void setup() {
  Serial.begin(9600);  // Set Uart for Serial Monitor communication
  avrSerial.begin(9600);
  WIFI_Init();
  MQTT_Init();
}

void loop() {
  if (!client.loop()) {
    MQTT_Reconnect();
  }
  if (avrSerial.available()) {
    uint8_t rData = avrSerial.read();  // Read value received from AVR UART
    AvrToApp(rData);
  }
}

/***************************************************************************************************
  Function Definitions
 ***************************************************************************************************/
void WIFI_Init() {
  // Attempt to connect to Wifi network:
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to WEP network, SSID: ");
    Serial.println(SSID);
    delay(3000);  // Wait 3 seconds for connection
  }
  Serial.print("Connected to WEP network successfully!, SSID: ");
  Serial.println(SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void MQTT_Init() {
  client.setCallback(MQTT_Callback);
  client.subscribe((char*)String(systemID).concat("/MotionEnable"));
  client.subscribe((char*)String(systemID).concat("/PanicMode"));
  client.subscribe((char*)String(systemID).concat("/DisarmMode"));
  client.subscribe((char*)String(systemID).concat("/DoorLock"));
  MQTT_Reconnect();
}

//print any message received for subscribed topic
void MQTT_Callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  AppToAvr(topic, (char*)payload);
}

void MQTT_Reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Failed to reconnect MQTT, WiFi connection lost!");
      WIFI_Init();
    }
    Serial.println("Attempting MQTT connection...");
    if (client.connect(systemID)) {
      Serial.println("MQTT connection established, Client ID: " + String(systemID));
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(", try again in 3 seconds");
      delay(3000);  // Wait 3 seconds before retrying
    }
  }
}

void AvrToApp(uint8_t rData) {
  Serial.println(rData, HEX);
  switch (rData) {
    case FIRE_TRIGGERED:
      client.publish((char*)String(systemID).concat("/FireSystem"), "Triggered");
      break;
    case FIRE_HANDLED:
      client.publish((char*)String(systemID).concat("/FireSystem"), "Handled");
      break;
    case GAS_TRIGGERED:
      client.publish((char*)String(systemID).concat("/GasSystem"), "Triggered");
      break;
    case GAS_HANDLED:
      client.publish((char*)String(systemID).concat("/GasSystem"), "Handled");
      break;
    case FLOOD_TRIGGERED:
      client.publish((char*)String(systemID).concat("/FloodSystem"), "Triggered");
      break;
    case FLOOD_HANDLED:
      client.publish((char*)String(systemID).concat("/FloodSystem"), "Handled");
      break;
    case MOTION_TRIGGERED:
      client.publish((char*)String(systemID).concat("/MotionSystem"), "Triggered");
      break;
    case MOTION_HANDLED:
      client.publish((char*)String(systemID).concat("/MotionSystem"), "Handled");
      break;
    case DOOR_OPENED:
      client.publish((char*)String(systemID).concat("/DoorSystem"), "Opened");
      break;
    case DOOR_CLOSED:
      client.publish((char*)String(systemID).concat("/DoorSystem"), "Closed");
      break;
    default:
      break;
  }
}

void AppToAvr(char* topic, char* payload) {
  uint8_t sData = 0x00;
  if (topic == (char*) String(systemID).concat("/MotionEnable")) {
    if (payload == "On") {
      sData = MOTION_ON;
    } else if (payload == "Off") {
      sData = MOTION_OFF;
    }
  } else if (topic == (char*) String(systemID).concat("/PanicMode")) {
    if (payload == "On") {
      sData = PANIC_ON;
    } else if (payload == "Off") {
      sData = PANIC_OFF;
    }
  } else if (topic == (char*) String(systemID).concat("/DisarmMode")) {
    if (payload == "On") {
      sData = DISARM_ON;
    } else if (payload == "Off") {
      sData = DISARM_OFF;
    }
  } else if (topic == (char*) String(systemID).concat("/DoorLock")) {
    if (payload == "On") {
      sData = DOOR_OPEN;
    } else if (payload == "Off") {
      sData = DOOR_CLOSE;
    }
  }
  avrSerial.write(sData);
  Serial.println(sData, HEX);
}
