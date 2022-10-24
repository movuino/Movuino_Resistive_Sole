#include "_MOVUINO_SHIELDS/_ResistiveSole.h"

//Force Sensitive Resistive Sole dimensions
#define ROWS 4
#define COLS 6

MovuinoResistiveSole sole = MovuinoResistiveSole();

void setup()
{
  Serial.begin(115200);
  sole.begin();
  Serial.println("Setup Done!");
}

void loop()
{
  sole.update();
  sendRawData();
}

void sendRawData(){
    for(int i = 0; i < ROWS; i++){
      Serial.print("z");
      Serial.print(i);
      Serial.print("x");
      for(int j = 0; j < COLS; j++){
        Serial.print(sole.getValue(i,j));
        if (j < COLS -1)Serial.print("x");
     }
    Serial.println();
    }
}
