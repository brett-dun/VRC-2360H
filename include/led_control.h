#ifndef LEDCONTROL_H_
#define LEDCONTROL_H_


#include "API.h"


//Pins
#define pinR 2
#define pinG 3
#define pinB 4

//Refresh Rate
#define hz 50
#define maximum (255.0 / hz) //255 / hz

//Color Value / Hz (Time on)
extern float r;
extern float g;
extern float b;

//Time off
extern float timeR;
extern float timeG;
extern float timeB;


TaskHandle ledTask;


enum Color {
  Red, Orange, Yellow, YellowGreen, Green, SpringGreen, Cyan, Azure, Blue, Violet, Magenta, Rose, White
};
typedef enum Color Color;


void setRGB(float red, float green, float blue);
void setColor(Color color);

void rgbWrite(void * parameter);
void enableLEDs();

#endif
