#include <main.h>
#include <lcd.h>

int controlScheme = 1;
bool swapPressed = false;

void operatorControl() {
	setLEDStatus(true);

	while (1) {
		if(joystickGetDigital(1, 7, JOY_UP) && joystickGetDigital(1, 8, JOY_UP)) {
			if(!swapPressed) {
				swapPressed = true;
				controlScheme *= -1;
				speakerPlayRtttl("SwapTone: d=4,o=2,b=120: 4a#2");
			}
		} else {
			swapPressed = false;
		}

		// Movement
		if(controlScheme == 1) {
			// Arcade controls
			motorSet(MOTOR_WHEELS_LEFT_FRONT, dewhine(joystickGetAnalog(1, 2) + joystickGetAnalog(1, 4)));
			motorSet(MOTOR_WHEELS_LEFT_BACK, dewhine(joystickGetAnalog(1, 2) + joystickGetAnalog(1, 4)));
			motorSet(MOTOR_WHEELS_RIGHT_FRONT, dewhine(-joystickGetAnalog(1, 2) + joystickGetAnalog(1, 4)));
			motorSet(MOTOR_WHEELS_RIGHT_BACK, dewhine(-joystickGetAnalog(1, 2) + joystickGetAnalog(1, 4)));
		} else {
			// Tank controls
			motorSet(MOTOR_WHEELS_LEFT_FRONT, dewhine(joystickGetAnalog(1, 3)));
			motorSet(MOTOR_WHEELS_LEFT_BACK, dewhine(joystickGetAnalog(1, 3)));
			motorSet(MOTOR_WHEELS_RIGHT_FRONT, dewhine(-joystickGetAnalog(1, 2)));
			motorSet(MOTOR_WHEELS_RIGHT_BACK, dewhine(-joystickGetAnalog(1, 2)));
		}

		// Lift
		doButtons(MOTOR_LIFT_1, button(6, JOY_DOWN), button(6, JOY_UP));
		doButtons(MOTOR_LIFT_2, button(6, JOY_UP), button(6, JOY_DOWN));

		// Claw spin
		doButtonsV(MOTOR_CLAW_SPIN, button(8, JOY_LEFT), button(8, JOY_RIGHT), 25);

		// Ball launcher
		doSingleButton(MOTOR_BALL_LAUNCHER_1, button(5, JOY_DOWN));
		doSingleButton(MOTOR_BALL_LAUNCHER_2, button(5, JOY_DOWN));

		delay(10);
	}
}
