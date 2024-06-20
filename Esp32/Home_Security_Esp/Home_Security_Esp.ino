#include <SoftwareSerial.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <FirebaseClient.h>
#include <string.h>

using namespace std;

#define FIRE_TRIGGERED 0x01
#define FIRE_HANDLED 0x02
#define GAS_TRIGGERED 0x03
#define GAS_HANDLED 0x04
#define FLOOD_TRIGGERED 0x05
#define FLOOD_HANDLED 0x06
#define MOTION_TRIGGERED 0x07
#define MOTION_HANDLED 0x08
#define DOOR_TRIGGERED 0x09
#define DOOR_HANDLED 0x0A

#define MOTION_ON 0x0B
#define MOTION_OFF 0x0C
#define PANIC_ON 0x0D
#define PANIC_OFF 0x0E
#define DISARM_ON 0x0F
#define DISARM_OFF 0x10
#define DOORLOCK_ON 0x11
#define DOORLOCK_OFF 0x12
#define FAN_ON 0x13
#define FAN_OFF 0x1


//Wi-Fi Manager Config:
#define WIFI_CONFIG_PIN 2
WiFiManager wifiManager;
uint8_t timeout = 120;  // seconds to run for
bool portalRunning = false;


// MQTT Credentails:
#define MQTT_SERVER "broker.emqx.io"
#define MQTT_PORT 1883

// Firebase Credentials:
#define FIREBASE_API_KEY "AIzaSyC5myNa5Pjkt6gWQZpBuc2lhmKgrHZMfA0"  // The API key can be obtained from Firebase console > Project Overview > Project settings.
#define FIREBASE_PROJECT_ID "hss-b4ea2"
#define FIREBASE_RTDB_URL "https://hss-b4ea2-default-rtdb.europe-west1.firebasedatabase.app"
DefaultNetwork network;  // initilize with boolean parameter to enable/disable network reconnection
NoAuth noAuth;
FirebaseApp app;
RealtimeDatabase database;

// ESP Client Configuration:
WiFiClient espClient;
const char* systemID = String("HSS@" + WiFi.macAddress()).c_str();
PubSubClient client(MQTT_SERVER, MQTT_PORT, espClient);
WiFiClientSecure ssl_client;
AsyncClientClass espAClient(ssl_client, getNetwork(network));
String systemPath = String(String("/Systems/") + systemID);

// Software UART Configuartion:
#define RX 13
#define TX 15
EspSoftwareSerial::UART avrSerial(RX, TX);

/***************************************************************************************************
  Function Prototypes
 ***************************************************************************************************/
void WIFIMANAGER_Init();
void WIFIMANAGER_Config();
void MQTT_Init();
void MQTT_Callback(char* topic, uint8_t* payload, unsigned int length);
void MQTT_Reconnect();
void FIREBASE_Init();
void FIREBASE_Callback(AsyncResult& aResult);
void AvrToApp(uint8_t rData);
void AppToAvr(char* topic, char* payload);


void setup() {
  Serial.begin(115200);  // Set Uart for Serial Monitor communication
  avrSerial.begin(115200, EspSoftwareSerial::SWSERIAL_5E1);
  if (!avrSerial) {  // If the object did not initialize, then its configuration is invalid
    Serial.println("Invalid EspSoftwareSerial pin configuration, check config");
    while (1) {  // Don't continue with invalid configuration
      delay(1000);
    }
  }
  WIFIMANAGER_Init();
  MQTT_Init();
  FIREBASE_Init();
  bool systemIsCreated = database.existed(espAClient, systemPath);
  if (!systemIsCreated) {
    Serial.println("System doesn't Exist in Firebase. \n Creating System Record... ");
    object_t systemData = "{\"Name\":\"Default\",\"Settings\":{\"DisarmMode\":false,\"MotionEnable\":true,\"PanicMode\":false,\"Fan\":false},\"Triggers\":{\"FireSystem\":false,\"GasSystem\":false,\"FloodSystem\":false,\"MotionSystem\":false,\"DoorSystem\":false}}";
    database.set<object_t>(espAClient, systemPath, systemData, FIREBASE_Callback);
  } else {
    Serial.println("System Exists in Firebase.");
  }
}

void loop() {
  WIFIMANAGER_Config();
  app.loop();
  database.loop();
  if (!client.loop()) {
    MQTT_Reconnect();
  }
  if (avrSerial.available()) {
    int rData = avrSerial.read();  // Read value received from AVR UART
    AvrToApp(rData);
  }
}

/***************************************************************************************************
  Function Definitions
 ***************************************************************************************************/
void WIFIMANAGER_Init() {
  Serial.println("\n Starting Connection");
  WiFi.mode(WIFI_STA);  // explicitly set mode, esp defaults to STA+AP
  pinMode(WIFI_CONFIG_PIN, INPUT_PULLUP);
  wifiManager.autoConnect();
}

void WIFIMANAGER_Config() {
  // is auto timeout portal running
  if (portalRunning) {
    wifiManager.process();
  }

  // is configuration portal requested?
  if (digitalRead(WIFI_CONFIG_PIN) == LOW) {
    delay(50);
    if (digitalRead(WIFI_CONFIG_PIN) == LOW) {
      if (!portalRunning) {
        Serial.println("Button Pressed, Starting Portal");
        wifiManager.startConfigPortal();
        portalRunning = true;
      } else {
        Serial.println("Button Pressed, Stopping Portal");
        wifiManager.stopConfigPortal();
        portalRunning = false;
      }
    }
  }
}

void MQTT_Init() {
  client.setCallback(MQTT_Callback);
  MQTT_Reconnect();
}

//print any message received for subscribed topic
void MQTT_Callback(char* topic, uint8_t* payload, unsigned int length) {
  String msg = "";
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    msg.concat((char)payload[i]);
  }
  Serial.println();
  AppToAvr(String(topic), msg);
}

void MQTT_Reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    WIFIMANAGER_Config();
    Serial.println("Attempting MQTT connection...");
    if (client.connect(systemID)) {
      Serial.println("MQTT connection established, Client ID: " + String(systemID));
      client.subscribe(String(systemID + String("/MotionEnable")).c_str());
      client.subscribe(String(systemID + String("/PanicMode")).c_str());
      client.subscribe(String(systemID + String("/DisarmMode")).c_str());
      client.subscribe(String(systemID + String("/DoorLock")).c_str());
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(", try again in 3 seconds");
      delay(3000);  // Wait 3 seconds before retrying
    }
  }
}

void FIREBASE_Init() {
  ssl_client.setInsecure();
  database.url(FIREBASE_RTDB_URL);
  app.setCallback(FIREBASE_Callback);
  initializeApp(espAClient, app, getAuth(noAuth));
  Firebase.printf("Firebase Client v%s\n", FIREBASE_CLIENT_VERSION);
  // Waits for app to be authenticated.
  uint16_t ms = millis();
  while (app.isInitialized() && !app.ready() && millis() - ms < 120 * 1000)
    ;
  app.getApp<RealtimeDatabase>(database);
}

void FIREBASE_Callback(AsyncResult& aResult) {
  if (aResult.appEvent().code() > 0) {
    Firebase.printf("Event task: %s, msg: %s, code: %d\n", aResult.uid().c_str(), aResult.appEvent().message().c_str(), aResult.appEvent().code());
  }
  if (aResult.isDebug()) {
    Firebase.printf("Debug task: %s, msg: %s\n", aResult.uid().c_str(), aResult.debug().c_str());
  }
  if (aResult.isError()) {
    Firebase.printf("Error task: %s, msg: %s, code: %d\n", aResult.uid().c_str(), aResult.error().message().c_str(), aResult.error().code());
  }
  if (aResult.available()) {
    Firebase.printf("task: %s, payload: %s\n", aResult.uid().c_str(), aResult.c_str());
  }
}

void AvrToApp(int rData) {
  Serial.println(rData, HEX);
  switch (rData) {
    case FIRE_TRIGGERED:
      client.publish(String(systemID + String("/FireSystem")).c_str(), "Triggered");
      database.set<object_t>(espAClient, String(systemPath + String("/Triggers/FireSystem")), object_t(true), FIREBASE_Callback);
      Serial.println("Fire System Triggered");
      break;
    case FIRE_HANDLED:
      client.publish(String(systemID + String("/FireSystem")).c_str(), "Handled");
      database.set<object_t>(espAClient, String(systemPath + String("/Triggers/FireSystem")), object_t(false), FIREBASE_Callback);
      Serial.println("Fire System Handled");
      break;
    case GAS_TRIGGERED:
      client.publish(String(systemID + String("/GasSystem")).c_str(), "Triggered");
      database.set<object_t>(espAClient, String(systemPath + String("/Triggers/Gasystem")), object_t(true), FIREBASE_Callback);
      Serial.println("Gas System Triggered");
      break;
    case GAS_HANDLED:
      client.publish(String(systemID + String("/GasSystem")).c_str(), "Handled");
      database.set<object_t>(espAClient, String(systemPath + String("/Triggers/GasSystem")), object_t(false), FIREBASE_Callback);
      Serial.println("Gas System Handled");
      break;
    case FLOOD_TRIGGERED:
      client.publish(String(systemID + String("/FloodSystem")).c_str(), "Triggered");
      database.set<object_t>(espAClient, String(systemPath + String("/Triggers/FloodSystem")), object_t(true), FIREBASE_Callback);
      Serial.println("Flood System Triggered");
      break;
    case FLOOD_HANDLED:
      client.publish(String(systemID + String("/FloodSystem")).c_str(), "Handled");
      database.set<object_t>(espAClient, String(systemPath + String("/Triggers/FloodSystem")), object_t(false), FIREBASE_Callback);
      Serial.println("Flood System Handled");
      break;
    case MOTION_TRIGGERED:
      client.publish(String(systemID + String("/MotionSystem")).c_str(), "Triggered");
      database.set<object_t>(espAClient, String(systemPath + String("/Triggers/MotionSystem")), object_t(true), FIREBASE_Callback);
      Serial.println("Motion System Triggered");
      break;
    case MOTION_HANDLED:
      client.publish(String(systemID + String("/MotionSystem")).c_str(), "Handled");
      database.set<object_t>(espAClient, String(systemPath + String("/Triggers/MotionSystem")), object_t(false), FIREBASE_Callback);
      Serial.println("Motion System Handled");
      break;
    case DOOR_TRIGGERED:
      client.publish(String(systemID + String("/DoorSystem")).c_str(), "Triggered");
      database.set<object_t>(espAClient, String(systemPath + String("/Triggers/DoorSystem")), object_t(true), FIREBASE_Callback);
      Serial.println("Door System Opened");
      break;
    case DOOR_HANDLED:
      client.publish(String(systemID + String("/DoorSystem")).c_str(), "Handled");
      database.set<object_t>(espAClient, String(systemPath + String("/Triggers/DoorSystem")), object_t(false), FIREBASE_Callback);
      Serial.println("Door System Closed");
      break;
    default:
      break;
  }
}

void AppToAvr(String topic, String msg) {
  uint8_t sData = 0x00;
  if (topic == systemID + String("/MotionEnable")) {
    if (msg == "On") {
      sData = MOTION_ON;
      database.set<boolean_t>(espAClient, String(systemPath + String("/Settings/MotionEnable")), boolean_t(true), FIREBASE_Callback);
    } else if (msg == "Off") {
      sData = MOTION_OFF;
      database.set<boolean_t>(espAClient, String(systemPath + String("/Settings/MotionEnable")), boolean_t(false), FIREBASE_Callback);
    }
  } else if (topic == systemID + String("/PanicMode")) {
    if (msg == "On") {
      sData = PANIC_ON;
      database.set<boolean_t>(espAClient, String(systemPath + String("/Settings/PanicMode")), boolean_t(true), FIREBASE_Callback);
    } else if (msg == "Off") {
      sData = PANIC_OFF;
      database.set<boolean_t>(espAClient, String(systemPath + String("/Settings/PanicMode")), boolean_t(false), FIREBASE_Callback);
    }
  } else if (topic == systemID + String("/DisarmMode")) {
    if (msg == "On") {
      sData = DISARM_ON;
      database.set<object_t>(espAClient, String(systemPath + String("/Settings/DisarmMode")), object_t(true), FIREBASE_Callback);
    } else if (msg == "Off") {
      sData = DISARM_OFF;
      database.set<object_t>(espAClient, String(systemPath + String("/Settings/DisarmMode")), object_t(false), FIREBASE_Callback);
    }
  } else if (topic == systemID + String("/Fan")) {
    if (msg == "On") {
      sData = FAN_ON;
      database.set<object_t>(espAClient, String(systemPath + String("/Settings/Fan")), object_t(true), FIREBASE_Callback);
    } else if (msg == "Off") {
      sData = FAN_OFF;
      database.set<object_t>(espAClient, String(systemPath + String("/Settings/Fan")), object_t(false), FIREBASE_Callback);
    }
  } else if (topic == systemID + String("/DoorLock")) {
    if (msg == "On") {
      sData = DOORLOCK_ON;
    } else if (msg == "Off") {
      sData = DOORLOCK_OFF;
    }
  }
  avrSerial.write(sData);
  Serial.println(sData, HEX);
}
