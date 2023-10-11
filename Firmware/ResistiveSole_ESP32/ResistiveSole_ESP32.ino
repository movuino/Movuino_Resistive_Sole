// #include "_MOVUINO_SHIELDS/_ResistiveSole.h"
#include "_MOVUINO_SHIELDS/_ResistiveMatrix.h"

//Force Sensitive Resistive Sole dimensions
#define COLS 7 // 7
#define ROWS 15 // 15

MovuinoResistiveMatrix sole = MovuinoResistiveMatrix(COLS, ROWS);

void setup() {
  Serial.begin(115200);
  sole.begin();
  // Serial.println("Setup Done!");
}

void loop() {
  sole.update();
  // sendRawData();
  sole.printData();

  delay(3);

  // to test signle data
  // Serial.println(sole.getValue(0,0));
}

void sendRawData() {
  for (int i = 0; i < ROWS; i++) {
    Serial.print("z");
    Serial.print(i);
    Serial.print("x");
    for (int j = 0; j < COLS; j++) {
      Serial.print(sole.getValue(i, j));
      if (j < COLS - 1) Serial.print("x");
    }
    Serial.println();
  }
}
