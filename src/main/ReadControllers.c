#include "wof.h"

void ReadControllers(void) {
    OSContPad *pad;
    u16 i;
    s32 j;
    u16 buttons;
    u16 sp1E;

    sp1E = 1;
    osContGetReadData(contPads);
    i = 0;
    while (i < 4) {
        if ((contPattern >> i) % 2 != 0) {
            pad = &contPads[i];
            switch (pad->errno) {
            case 0:
                if (rumbles[i].present != 0) {
                    if (rumbles[i].frames > 0) {
                        rumbles[i].frames--;
                        rumbles[i].level += rumbles[i].strength;
                        if ((f64)rumbles[i].level < 1.0) {
                            StopMotor(i);
                        } else {
                            rumbles[i].level = (f32)((f64)rumbles[i].level - 1.0);
                            StartMotor(i);
                        }
                    } else if (motorOn[i] != 0) {
                        StopMotor(i);
                    }
                }
                buttons = pad->button;
                j = 0;
                while (j < 16) {
                    if ((buttons & 1) != 0) {
                        if (buttonUpFrames[i][j] < 5) {
                            buttonUpFrames[i][j] = 0;
                        } else {
                            contPressed[i] |= 1 << j;
                            buttonUpFrames[i][j] = 0;
                        }
                    } else if (buttonUpFrames[i][j] < 6) {
                        buttonUpFrames[i][j]++;
                    }
                    buttons >>= 1;
                    j++;
                }
            }
        }
        i++;
    }
    if (newFrame != 0) {
        if (D_800BCD54 == 3 || D_800BCD54 == 1 || D_800BCD54 == 7 || D_800BCD54 == 8) {
            playerPad.stick_x = 0;
            playerPad.stick_y = 0;
            buttonsPressed = 0;
            i = 0;
            while (i < 4) {
                buttonsPressed |= contPressed[i];
                if ((contPattern >> i) % 2 != 0) {
                    if (contPads[i].stick_x >= 41 || contPads[i].stick_x < -40) {
                        playerPad.stick_x = contPads[i].stick_x;
                    }
                    if (contPads[i].stick_y >= 41 || contPads[i].stick_y < -40) {
                        playerPad.stick_y = contPads[i].stick_y;
                    }
                }
                i++;
            }
        } else if (D_800BCD54 == 6 || D_800B9990[D_800FB808].unk_014 == 4) {
            buttonsPressed = 0;
            i = 0;
            while (i < 4) {
                buttonsPressed = (contPressed[i] & 0x1000) | buttonsPressed;
                i++;
            }
        } else {
            buttonsPressed = contPressed[D_800B9990[D_800FB808].unk_014];
            playerPad = contPads[D_800B9990[D_800FB808].unk_014];
        }
        i = 0;
        while (i < 4) {
            contPressed[i] = 0;
            i++;
        }
        newFrame = 0;
    }
}
