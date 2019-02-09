#include "main.h"
#include "API.h"
#include <lcd.h>

void initializeIO() {
    pinMode(INPUT_SPIN_ENCODER_TOP, INPUT);
    pinMode(INPUT_SPIN_ENCODER_BOTTOM, INPUT);
    pinMode(INPUT_POWER_EXPANDER, INPUT);

    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);

    setLEDStatus(false);
}

void initialize() {
    lcd_init();
    speakerInit();

    //lcdSetText(uart1, 1, &"1.1"[0]);
    //lcdSetText(uart1, 2, &"1.2"[0]);
    //lcdSetText(uart2, 1, &"2.1"[0]);
    //lcdSetText(uart2, 2, &"2.2"[0]);

    // spin_encoder = encoderInit(INPUT_SPIN_ENCODER_TOP, INPUT_SPIN_ENCODER_BOTTOM, true);
}
