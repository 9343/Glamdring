#pragma once
#include <main.h>

Button button(u8 button_group, u8 button);

int dewhine(int value);

void doSingleButtonV(int motorPort, Button button, int value);
void doSingleButton(int motorPort, Button button);
void doButtonsV(int motorPort, Button button1, Button button2, int value);
void doButtons(int motorPort, Button button1, Button button2);
void setLEDStatus(bool initialized);
