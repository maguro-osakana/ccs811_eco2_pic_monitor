/* 
 * File:   userif.c
 * Author: maguro-osakana
 *
 * Created on 2019/03/14, 20:52
  *
 * MIT License
 *
 * Copyright (c) 2019-2026 maguro-osakana
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#include <string.h>
#include "mcc_generated_files/mcc.h"
#include "lcd1602.h"
#include "ccs811.h"
#include "rtc.h"
#include "misc.h"

static uint8_t state;
static uint8_t hour, min, sec;

#define STATE_DEFAULT                   0
#define STATE_RAW_AND_BASELINE          1
#define STATE_BASELINE_SAVE_MENU        2
#define STATE_BASELINE_RESTORE_MENU     3
#define STATE_CLOCK_HOUR_ADJUST_MENU    4
#define STATE_CLOCK_MIN_ADJUST_MENU     5
#define STATE_BASELINE_SAVE_WRITE       6
#define STATE_BASELINE_RESTORE_READ     7
#define STATE_CLOCK_HOUR_ADJUST_ADJUST  8
#define STATE_CLOCK_MIN_ADJUST_ADJUST   9

/*
  state machine

  +-------+
  |Default|
  +-------+
      | Short
  +-------+
  |Raw, BL|
  +-------+
      | Short
  +-------+           +-----------+
  |Save   | -(Long)-> | EEP Write | -(Auto Exit)-> Default
  +-------+           +-----------|
      | Short
  +-------+           +-----------+
  |Restore| -(Long)-> | EEP Read  | -(Auto Exit)-> Default
  +-------+           +-----------+
      | Short
  +-------+           +-------------+
  |Hour   | -(Long)-> | Hour Adjust | -(Long)-> Default
  +-------+           +-------------+
      | Short
  +-------+           +-------------+
  |Min    | -(Long)-> | Min  Adjust | -(Long)-> Default
  +-------+           +-------------+
      | Short
   Default


*/


void userif(void)
{
    uint8_t data[2];
    char lcdmsg[17];
    uint8_t user_sw;
    uint16_t ohm;

    //              0000000000111111
    //              0123456789012345
    strcpy(lcdmsg, "CO2=00000[ppm]");
    css811read(CSS811_ALG_RESULT_DATA, data, 2);
    itoa16(&lcdmsg[4], (data[0] << 8) | data[1]);
    lcdprint(0, lcdmsg);

    user_sw = rtcusersw();

    switch (state) {
        case STATE_DEFAULT:
        //              0000000000111111
        //              0123456789012345
        strcpy(lcdmsg, "BL=xxxx hh:mm:ss");
        css811read(CSS811_BASELINE, data, 2);
        htoa8(&lcdmsg[3], data[0]);
        htoa8(&lcdmsg[5], data[1]);
        rtcget(&hour, &min, &sec);
        itoa8(&lcdmsg[8],  hour);
        itoa8(&lcdmsg[11], min);
        itoa8(&lcdmsg[14], sec);
        lcdprint(1, lcdmsg);
        if (user_sw == USERSW_SHORT_MAKE) {
            state = STATE_RAW_AND_BASELINE;
        } 
        break;

        case STATE_RAW_AND_BASELINE:
        //              0000000000111111
        //              0123456789012345
        //              RAW=xxxx BL=xxxx
        strcpy(lcdmsg, "RAW=xxxx BL=xxxx");
        css811read(CSS811_RAW_DATA, data, 2);
        htoa8(&lcdmsg[4], data[0]);
        htoa8(&lcdmsg[6], data[1]);
        css811read(CSS811_BASELINE, data, 2);
        htoa8(&lcdmsg[12], data[0]);
        htoa8(&lcdmsg[14], data[1]);
        lcdprint(1, lcdmsg);
        if (user_sw == USERSW_SHORT_MAKE) {
            state = STATE_BASELINE_SAVE_MENU;
        } 
        break;

        case STATE_BASELINE_SAVE_MENU:
        lcdprint(1, "BL SAVE?");
        if (user_sw == USERSW_SHORT_MAKE) {
            state = STATE_BASELINE_RESTORE_MENU;
        } else if (user_sw == USERSW_LONG_MAKE) {
            state = STATE_BASELINE_SAVE_WRITE;
        }
        break;

        case STATE_BASELINE_RESTORE_MENU:
        lcdprint(1, "BL RESTORE?");
        if (user_sw == USERSW_SHORT_MAKE) {
            state = STATE_CLOCK_HOUR_ADJUST_MENU;
        } else if (user_sw == USERSW_LONG_MAKE) {
            state = STATE_BASELINE_RESTORE_READ;
        }
        break;

        case STATE_CLOCK_HOUR_ADJUST_MENU:
        lcdprint(1, "HOUR ADJ?");
        if (user_sw == USERSW_SHORT_MAKE) {
            state = STATE_CLOCK_MIN_ADJUST_MENU;
        } else if (user_sw == USERSW_LONG_MAKE) {
            state = STATE_CLOCK_HOUR_ADJUST_ADJUST;
        }
        break;

        case STATE_CLOCK_MIN_ADJUST_MENU:
        lcdprint(1, "MIN ADJ?");
        if (user_sw == USERSW_SHORT_MAKE) {
            state = STATE_DEFAULT;
        } else if (user_sw == USERSW_LONG_MAKE) {
            state = STATE_CLOCK_MIN_ADJUST_ADJUST;
        }
        break;

        case STATE_BASELINE_SAVE_WRITE:
        lcdprint(1, "BL SAVE START");
        __delay_ms(1000);
        css811read(CSS811_BASELINE, data, 2);
        DATAEE_WriteByte(0x00, data[0]);
        DATAEE_WriteByte(0x01, data[1]);
        lcdprint(1, "DONE");
        __delay_ms(1000);
        state = STATE_DEFAULT;
        break;

        case STATE_BASELINE_RESTORE_READ:
        lcdprint(1, "BL RESTORE START");
        __delay_ms(1000);
        data[0] = DATAEE_ReadByte(0x00);
        data[1] = DATAEE_ReadByte(0x01);
        css811write(CSS811_BASELINE, data, 2);
        lcdprint(1, "DONE");
        __delay_ms(1000);
        state = STATE_DEFAULT;
        break;

        case STATE_CLOCK_HOUR_ADJUST_ADJUST:
        strcpy(lcdmsg, "HOUR=xx");
        itoa8(&lcdmsg[5], hour);
        lcdprint(1, lcdmsg);
        if (user_sw == USERSW_SHORT_MAKE) {
            hour++;
            if (hour == 24) {
                hour = 0;
            }
        } else if (user_sw == USERSW_LONG_MAKE) {
            rtcset(hour, min, 0);
            state = STATE_DEFAULT;
        }
        break;

        case STATE_CLOCK_MIN_ADJUST_ADJUST:
        strcpy(lcdmsg, "MIN=xx");
        itoa8(&lcdmsg[4], min);
        lcdprint(1, lcdmsg);
        if (user_sw == USERSW_SHORT_MAKE) {
            min++;
            if (min == 60) {
                min = 0;
            }
        } else if (user_sw == USERSW_LONG_MAKE) {
            rtcset(hour, min, 0);
            state = STATE_DEFAULT;
        }
        break;
    }
}
