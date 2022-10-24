#if !defined(_MOVUINOESP32_RESISTIVESOLE_)
#define _MOVUINOESP32_RESISTIVESOLE_

// Touch surface
#define  SOLEROWS  4
#define  SOLECOLS  6
// Pins 
int row[SOLEROWS] = {27, 26, 25, 33};
int col[SOLECOLS] = {32, 39, 35, 38, 37, 34};

class MovuinoResistiveSole
{
private:
	int _rows = SOLEROWS; //Number of rows
	int _cols = SOLECOLS; //Number of columns
	
	int _sensorValue = 0; 
	
	int** _lastUpdate;
	
public:
	MovuinoResistiveSole();
	~MovuinoResistiveSole();
	
	void begin();
	void update();
	void printData();
	int getValue(int i, int j);
};

MovuinoResistiveSole::MovuinoResistiveSole()
{
	this->_lastUpdate = new int*[this->_rows];
	for (int i = 0; i < this->_rows; i++){
		_lastUpdate[i] = new int[this->_cols];
	}	
}
	
MovuinoResistiveSole::~MovuinoResistiveSole(){
	for (int i = 0; i < this->_rows; i++){
		delete(_lastUpdate[i]);
	}
	delete(_lastUpdate);
}

void MovuinoResistiveSole::begin()
{
	for(int i = 0; i < SOLEROWS; i++){
		pinMode(row[i], OUTPUT);
		digitalWrite(row[i], LOW);
	}
	analogReadResolution(8); //Sets the size of the values returned by the ADC to 8 bits
}

void MovuinoResistiveSole::update()
{
   for (int i = 0; i < this->_rows; i++) {
 
	//ACTIVATE ROW
    digitalWrite(row[i], 1);

    // READ LINE VALUES
    for (int j = 0; j < this->_cols; j++) {
      _lastUpdate[i][j] = analogRead(col[j]);
    }
	
    //DEACTIVATE ROW
    digitalWrite(row[i], 0);
  }
}

void MovuinoResistiveSole::printData()
{
  this->update();
  for (int i=0; i< this->_rows; i++){
	Serial.print("z");
	Serial.print(i);
	for (int j=0; j< this->_cols; j++){
		Serial.print("x");
		Serial.print(this->_lastUpdate[i][j]);
	}
	Serial.println();
  }
}

int MovuinoResistiveSole::getValue(int i, int j)
{
	this->update();
	return _lastUpdate[i][j];
}

#endif