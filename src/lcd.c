#include <API.h>
#include <ports.h>
#include <lcd.h>
#include <string.h>

TaskHandle lcdTaskHandle;

int lastButtons = 0;
int readButtons = 0;
int currentAuto = 0;
int lcd_rotation = 0;

int nAutos = 5;
char autoNames[5][17] = {
    "    Disabled    ",
    "ShootLow Red    ",
    "ShootLow Blue   ",
    "Platform Red    ",
    "Platform Blue   "
};

char battery1[17];
char battery2[17];

int getAutonomousSelection() {
    return currentAuto;
}

void lcd_thread(void* arg) {
    lcdInit(uart1);
    lcdClear(uart1);
    lcdSetBacklight(uart1, true);
    lcdInit(uart2);
    lcdClear(uart1);
    lcdSetBacklight(uart2, true);

    while(true) {
        // Limit LCD update rate
        //lcd_rotation++;
        //lcdClear(uart1);
        //if(lcd_rotation < 25) {
        //    lcdPrint(uart1, 1, "%d", lcd_rotation);
        //    continue;
        //}
        //lcd_rotation = 0;

        // Debug lines
        //lcdSetText(uart1, 1, &"1.1"[0]);
        //lcdSetText(uart1, 2, &"1.2"[0]);
        //lcdSetText(uart2, 1, &"2.1"[0]);
        //lcdSetText(uart2, 2, &"2.2"[0]);

        // Display battery on LCD

        memset(battery1, 0, 17);
        sprintf(battery1, "1st: %4.1f%%      ", (float) powerLevelMain() / (1000 * 7.2));
        memset(battery2, 0, 17);
        sprintf(battery2, "2nd: %4.1f%%      ", (float) digitalRead(INPUT_POWER_EXPANDER) / (45.6 * 7.2));

	    lcdSetText(uart1, 1, battery1);
	    lcdSetText(uart1, 2, battery2);

        // Read and react to buttons on second LCD
        readButtons = lcdReadButtons(uart2);

        if(readButtons > lastButtons) {
            // Button has been pressed!
            if((readButtons & 1) == 1) {
                 // Left button
                currentAuto--;
                if(currentAuto < 0) currentAuto = nAutos - 1;
            }

              if((readButtons & 2) == 2) {
                  // Center button
              }

              if((readButtons & 4) == 4) {
                  // Right button
                  currentAuto++;
                  if(currentAuto == nAutos) currentAuto = 0;
              }
          }

          lastButtons = readButtons;

          lcdSetText(uart2, 1, autoNames[currentAuto]);
          lcdPrint(uart2, 2, "LAST   %02d   NEXT", currentAuto + 1);

          delay(100);
    }
}

void lcd_init() {
    lcdTaskHandle = taskCreate(&lcd_thread, TASK_DEFAULT_STACK_SIZE * 4, NULL, TASK_PRIORITY_DEFAULT);
}
