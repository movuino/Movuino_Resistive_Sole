#include "_MOVUINO_ESP32/_WifiOSC.h"
#include "_MOVUINO_SHIELDS/_ResistiveSole.h"

// Wifi configuration
char ssid[] = "CRI-MAKERLAB";
char pass[] = "--criMAKER--";
int port = 5555;
int ip[4] = {192, 168, 1, 18};

//Force Sensitive Resistive Sole dimensions
#define ROWS 4
#define COLS 6

MovuinoWifiOSC osc = MovuinoWifiOSC(ssid, pass, ip, port);
MovuinoResistiveSole sole = MovuinoResistiveSole();

long timerRecord0;

void setup()
{
  Serial.begin(115200);
  Serial.println("Start Setup");
  osc.begin();
  sole.begin();
  timerRecord0 = millis();
  Serial.println("Setup Done!");
}

bool isRecording = false;

void loop()
{
  sole.update();
  sendRawData();
  OSCMessage received = osc.receiveMessage();
  if (received.getInt(0)==1){
    isRecording = !isRecording;
    timerRecord0 = millis();
  }
}

void sendRawData(){
  if(isRecording){
    OSCMessage msg("/data");
    msg.add(int(millis()- timerRecord0)/1000);
    for(int i = 0; i < ROWS; i++){
      for(int j = 0; j < COLS; j++){
        msg.add((int)sole.getValue(i,j));
        Serial.print(sole.getValue(i,j));
        if (j < COLS -1)Serial.print("x");
     }
    Serial.println();
    }
    Serial.println("Problem before");
    osc.sendMessage(msg);
    Serial.println("Problem after");
  } 
}
