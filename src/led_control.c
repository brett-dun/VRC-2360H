#include "led_control.h"

void setRGB(float red, float green, float blue) {

  red = red > 255 ? 255 : (red < 0 ? 0 : red);
  green = green > 255 ? 255 : (green < 0 ? 0 : green);
  blue = blue > 255 ? 255 : (blue < 0 ? 0 : blue);

  r = red / hz;
  g = green / hz;
  b = blue / hz;

}

void setColor(Color color) {

  switch(color) {
    case Red: setRGB(255, 0, 0); return;
    case Orange: setRGB(255, 127, 0); return;
    case Yellow: setRGB(255, 255, 0); return;
    case YellowGreen: setRGB(127, 255, 0); return;
    case Green: setRGB(0, 255, 0); return;
    case SpringGreen: setRGB(0, 255, 127); return;
    case Cyan: setRGB(0, 255, 255); return;
    case Azure: setRGB(0, 127, 255); return;
    case Blue: setRGB(0, 0, 255); return;
    case Violet: setRGB(127, 0, 255); return;
    case Magenta: setRGB(255, 0, 255); return;
    case Rose: setRGB(255, 0, 127); return;
    default: setRGB(255, 255, 255); return;
  }

}

void rgbControl(void * parameter) {

  timeR = maximum - r;
  timeG = maximum - g;
  timeB = maximum - b;

  digitalWrite(pinR, 1);
  delay(r);
  digitalWrite(pinR, 0);
  delay(timeR);
  digitalWrite(pinG, 1);
  delay(g);
  digitalWrite(pinG, 0);
  delay(timeG);
  digitalWrite(pinB, 1);
  delay(b);
  digitalWrite(pinB, 0);
  delay(timeB);

}

void lol() {
  TaskHandle firstTaskHandle = taskCreate(rgbControl, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  taskDelete(firstTaskHandle);
}
