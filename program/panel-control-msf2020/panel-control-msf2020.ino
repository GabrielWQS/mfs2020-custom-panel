// Custom MFS2020 panel
// Arduino micro pro
// Gabriel Wallace

#include <HID-Project.h> //https://github.com/NicoHood/HID
#include <HID-Settings.h>

//switchs
int switchs[] = {3, 4, 5, 6, 7, 8};
int sw_state[] = {0, 0, 0, 0, 0, 0};
int sw_up[] = {8, 6, 4, 14, 12, 10};
int sw_down[] = {9, 7, 5, 15, 13, 11};

//leds
int led_red = 9;
int led_green = 10;

//buttons
int btns[] = {2, 16, 14};
int btn_press[] = {1, 2, 3};

//potenciometer
int flaps = A0;
int motor1 = A1;
int motor2 = A2;

long flaps_value = 0;
long motor1_value = 0;
long motor2_value = 0;

void setup() {
  
  for(int i = 0; i < (sizeof(switchs)/sizeof(int)); i++) {
    pinMode(switchs[i], INPUT_PULLUP);  
    sw_state[i] = digitalRead(switchs[i]);
  }

  for(int i = 0; i < (sizeof(btns)/sizeof(int)); i++)
    pinMode(btns[i], INPUT_PULLUP);  

  pinMode(flaps, INPUT);
  pinMode(motor1, INPUT);
  pinMode(motor2, INPUT);

  flaps_value = getPotValue(flaps, false);
  motor1_value = getPotValue(motor1, true);
  motor2_value = getPotValue(motor2, true);

  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);

  digitalWrite(led_red, LOW);
  digitalWrite(led_green, LOW);

  turnOnLeds();
  
  Gamepad.begin();
}

void readSwitchs() {

  for(int i = 0; i < (sizeof(switchs)/sizeof(int)); i++) {
    
    bool aux = digitalRead(switchs[i]);
    
    if(sw_state[i] == aux) {
      Gamepad.release(sw_up[i]); 
      Gamepad.release(sw_down[i]); 
    } else {
      
      sw_state[i] = aux;
      
      if(sw_state[i] == LOW)
        Gamepad.press(sw_up[i]); 
      else
        Gamepad.press(sw_down[i]);
    }

    turnOnLeds();
  }
}

void readButtons() {

  for(int i = 0; i < (sizeof(btns)/sizeof(int)); i++) {

    if(digitalRead(btns[i]) == LOW)
      Gamepad.press(btn_press[i]);
    else
      Gamepad.release(btn_press[i]);
  }
}

long getPotValue(int pot, bool motor) {
  int analog = analogRead(pot);
  long value = 0;

  if(motor)
    value = map(analog, 0, 1023, 0, 32767); 
   else
    value = map(analog, 0, 255, -127, 127);  
  return value;
}

void turnOnLeds() {
  //TODO 
  //verde com o trem de pouso abaixado
  //10s de vermelho até mudar o estado
  if(sw_state[0] == 0) {
      digitalWrite(led_red, HIGH);
      digitalWrite(led_green, LOW);
  } else {
      digitalWrite(led_red, LOW);
      digitalWrite(led_green, HIGH);
  }
}

void readPots() {
  
    Gamepad.rzAxis(getPotValue(flaps, false));
    Gamepad.rxAxis(getPotValue(motor1, true));
    Gamepad.ryAxis(getPotValue(motor2, true));
}


void loop() {
  readSwitchs();
  readButtons();
  readPots();
  
  Gamepad.write();
  delay(200);
}
