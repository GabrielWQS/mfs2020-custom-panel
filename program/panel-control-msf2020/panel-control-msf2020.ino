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

int led_red = 9;
int led_green = 10;

int btns[] = {2, 16, 14};
int btn_press[] = {1, 2, 3};

void setup() {
  Serial.begin(9600);

  for(int i = 0; i < (sizeof(switchs)/sizeof(int)); i++) {
    pinMode(switchs[i], INPUT_PULLUP);  
    sw_state[i] = digitalRead(switchs[i]);
  }

  for(int i = 0; i < (sizeof(btns)/sizeof(int)); i++)
    pinMode(btns[i], INPUT_PULLUP);  

  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);

  digitalWrite(led_red, LOW);
  digitalWrite(led_green, LOW);
  
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

int getPotValue(int pot) {
  int analog = analogRead(pot);
  int value = map(analog, 0, 1023, 0, 255);  
  return value;
}

void loop() {
  
  readSwitchs();
  readButtons();
  
  Gamepad.write();
  delay(300);
}
