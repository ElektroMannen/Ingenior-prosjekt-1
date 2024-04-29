//Avoid using delay as this will mess with the timing of the mesh network

#include "painlessMesh.h"

#define   MESH_PREFIX     "Gruppe1-MESH"
#define   MESH_PASSWORD   "PassordGruppeEN"
#define   MESH_PORT       5555

bool Charging = true;
bool Discharging = false;
bool ChargingComplete = false;

Scheduler userScheduler;
painlessMesh mesh;

void sendMessage() {
  String msg = "The weather is nice today!";
  mesh.sendBroadcast( msg );
}

Task taskSendMessage( TASK_SECOND * 5 , TASK_FOREVER, &sendMessage );

// Needed for painless library, be careful changing these parameters!
void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("Information: Received from %u msg = %s\n Charging = %d\n", from, msg.c_str(), Charging);
}

void newConnectionCallback(uint32_t nodeId) {
    Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
    Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}

void setup() {
  Serial.begin(115200);
  mesh.setDebugMsgTypes( ERROR | STARTUP );
  
  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();
}

void loop() {
  mesh.update();
}