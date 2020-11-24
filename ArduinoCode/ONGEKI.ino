#include <Keyboard.h>
#if ARDUINO > 10605
#include <Mouse.h>
#endif  //ARDUINO > 10605
#include <MouseTo.h>
typedef struct {
  int pin;
  char keycode;
} LIST;

LIST keylist[] =
{
  {2, 'a'}, {4, 's'},
  {5, 'd'}, {6, 'j'},
  {7, 'k'}, {8, 'l'}, {9, 'q'}, {10, 'e'},
};
int Keys = sizeof(keylist) / sizeof(keylist[0]);
int o_ec1=500;
const int Pin_Lever = A0;
void setup() {
  for (int i = 0; i < Keys; i++) {
    pinMode(keylist[i].pin, INPUT_PULLUP);
  }
  Keyboard.begin();
  Mouse.begin();
  MouseTo.setCorrectionFactor(1);
  Serial.begin(115200);
}

void loop() {
  //MouseTo.setTarget(500, 0); 
  for (int i = 0; i < Keys; i++) {
    if (digitalRead(keylist[i].pin) == LOW) {
      Keyboard.press(keylist[i].keycode);
    } else {
      Keyboard.release(keylist[i].keycode);
    }
    int lever = analogRead(Pin_Lever);
    Serial.println(lever);
    MouseTo.setTarget(lever-500, 0 ,false);
    while (MouseTo.move() == false) {}
    /*if (lever >= o_ec1+40||lever <= o_ec1-40) {
      Serial.println(lever);
      Mouse.move(lever > o_ec1 ? -1 : 1, 0);
    }*/
  }
}
