#include <main.h>

Button button(u8 button_group, u8 button) {
    Button b;
    b.button_group = button_group;
    b.button = button;
    return b;
}

int dewhine(int value) {
    return (value > -20 && value < 20) ? 0 : value;
}

void doSingleButtonV(int motorPort, Button button, int value) {
	if (joystickGetDigital(1, button.button_group, button.button)) {
		motorSet(motorPort, value);
	} else {
		motorSet(motorPort, 0);
	}
}

void doSingleButton(int motorPort, Button button) {
	doSingleButtonV(motorPort, button, 127);
}

void doButtonsV(int motorPort, Button button1, Button button2, int value) {
	if (joystickGetDigital(1, button1.button_group, button1.button)) {
		motorSet(motorPort, value);
	} else {
		doSingleButtonV(motorPort, button2, -value);
	}
}

void doButtons(int motorPort, Button button1, Button button2) {
	doButtonsV(motorPort, button1, button2, 127);
}

void setLEDStatus(bool initialized) {
    digitalWrite(8, !initialized);
    digitalWrite(9, !initialized);
    digitalWrite(10, initialized);
    digitalWrite(11, initialized);
}
