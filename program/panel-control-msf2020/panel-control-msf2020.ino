// Custom MFS2020 panel
// Arduino micro pro
// Gabriel Wallace

#include <HID-Project.h> //https://github.com/NicoHood/HID
#include <HID-Settings.h>

int CH1 = 7;
int CH2 = 6;
int CH3 = 5;
int CH4 = 4;
int CH5 = 3;
int CH6 = 2;

byte rows[] = {15, 14, 16};
byte cols[] = {10, 9, 8};

const int rowCount = sizeof(rows)/sizeof(rows[0]);
const int colCount = sizeof(cols)/sizeof(cols[0]);

byte keys[colCount][rowCount];

void setup() {
  Serial.begin(115200);
  
  for(int x=0; x<rowCount; x++)
    pinMode(rows[x], INPUT);
    
  for(int x=0; x<rowCount; x++)
    pinMode(cols[x], INPUT_PULLUP);

  pinMode(CH1, INPUT_PULLUP);
  pinMode(CH2, INPUT_PULLUP);
  pinMode(CH3, INPUT_PULLUP);
  pinMode(CH4, INPUT_PULLUP); 
  pinMode(CH5, INPUT_PULLUP);
  pinMode(CH6, INPUT_PULLUP);
  
  Gamepad.begin();
}

void readMatrix() {
    // iterate the columns
    for (int colIndex=0; colIndex < colCount; colIndex++) {
        // col: set to output to low
        byte curCol = cols[colIndex];
        pinMode(curCol, OUTPUT);
        digitalWrite(curCol, LOW);
 
        // row: interate through the rows
        for (int rowIndex=0; rowIndex < rowCount; rowIndex++) {
            byte rowCol = rows[rowIndex];
            pinMode(rowCol, INPUT_PULLUP);
            keys[colIndex][rowIndex] = digitalRead(rowCol);
            pinMode(rowCol, INPUT);
        }
        // disable the column
        pinMode(curCol, INPUT);
    }
}

void printMatrix() {
    for (int rowIndex=0; rowIndex < rowCount; rowIndex++) {
        if (rowIndex < 10)
            Serial.print(F("0"));
        Serial.print(rowIndex); Serial.print(F(": "));
 
        for (int colIndex=0; colIndex < colCount; colIndex++) {  
            Serial.print(keys[colIndex][rowIndex]);
            if (colIndex < colCount)
                Serial.print(F(", "));
        }   
        Serial.println("");
    }
    Serial.println("");
}

void loop() {
  //readMatrix();
      //delay(200);
        //printMatrix();

 if(digitalRead(CH6) == LOW) 
  Gamepad.press(1);
 else
  Gamepad.release(1);

 Gamepad.write();
 
}
