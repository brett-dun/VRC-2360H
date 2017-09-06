#ifndef LEDCONTROL_H_
#define LEDCONTROL_H_


#include "API.h"


//Pins
const unsigned short pinR = 2;
const unsigned short pinG = 3;
const unsigned short pinB = 4;

//Refresh Rate
#define hz 50
const float maximum = 255.0 / hz;

//Color Value / Hz (Time on)
float r = 0;
float g = 0;
float b = 0;

//Time off
float timeR = 0;
float timeG = 0;
float timeB = 0;


enum Color {
  Red, Orange, Yellow, YellowGreen, Green, SpringGreen, Cyan, Azure, Blue, Violet, Magenta, Rose, White
};
typedef enum Color Color;


void setRGB(float red, float green, float blue);
void setColor(Color color);

void rgbWrite(void * parameter);

#endif
