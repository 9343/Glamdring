#include "main.h"
#include "lcd.h"
#include "ports.h"

void go4(int leftFront, int leftBack, int rightFront, int rightBack) {
    motorSet(MOTOR_WHEELS_LEFT_FRONT, leftFront);
    motorSet(MOTOR_WHEELS_LEFT_BACK, leftBack);
    motorSet(MOTOR_WHEELS_RIGHT_FRONT, -rightFront);
    motorSet(MOTOR_WHEELS_RIGHT_BACK, -rightBack);
}

void go2(int left, int right) {
    go4(left, left, right, right);
}

void go(int x){
    go2(x, x);
}

void autonomous() {
    int n = getAutonomousSelection();
    if(n == 0) return;

    if(n >= 1 && n <= 2) {
        int multiplier = (n == 1 ? 1 : -1);

        motorSet(MOTOR_BALL_LAUNCHER_1, 127);
        motorSet(MOTOR_BALL_LAUNCHER_2, 127);
        delay(1500);
        motorSet(MOTOR_BALL_LAUNCHER_1, 0);
        motorSet(MOTOR_BALL_LAUNCHER_2, 0);
        delay(500);
        if(n == 2) {
            go2(-25 * multiplier, 25 * multiplier);
            delay(600);
            go(0);
            delay(400);
        }
        go(-127);
        delay(1800);
        if(n == 1) {
            go2(-10 * multiplier, 10 * multiplier);
            delay(600);
            go(0);
            delay(400);
        }
        go(127);
        delay(3300);
        go2(127 * multiplier, -127 * multiplier);
        delay(n == 3 ? 800 : 600);
        go(0);
        delay(400);
        go(-127);
        delay(2200);
        go(0);
    }

    if(n >= 3 && n <= 4) {
        int multiplier = (n == 3 ? 1 : -1);

        go(127);
	    delay(1300);
        go(-127);
        delay(400);
        go(0);
        delay(400);
        go2(127 * multiplier, -127 * multiplier);
        delay(700);
        go(-50);
        delay(1500);
        go(-127);
        delay(500);
        go(-70);
        delay(900);
        go(0);
    }
}
