/* 
 * File:   rtc.c
 * Author: maguro-osakana
 *
 * Created on March 14, 2019, 6:16 PM
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

#include <time.h>
#include "mcc_generated_files/mcc.h"
#include "rtc.h"

static uint8_t cnt20ms;
static uint8_t hour;
static uint8_t min;
static uint8_t sec;
static uint8_t ready;

static uint8_t usersw_counter;
static uint8_t usersw_stat;

static void rtc20msint(void)
{
    // 20ms interrupt
    cnt20ms++;
    if (cnt20ms == 50) { // 20ms * 50 = 1sec
        cnt20ms = 0;
        ready = 1;
        sec++;
        if (sec == 60) {
            sec = 0;
            min++;
            if (min == 60) {
                min = 0;
                hour++;
                if (hour == 24) {
                    hour = 0;
                }
            }
        }
    }

    if (USER_SW_GetValue() == 0) {
        // 0 = GND: Make
        if (usersw_counter != 255) {
            usersw_counter++;
        }
    } else {
        // 1 = Pull-up : Break
        if ((1 <= usersw_counter) && (usersw_counter < 50)) { // 20ms * 50 = 1sec
            // less than 1sec
            usersw_stat = USERSW_SHORT_MAKE;
        } else if (50 <= usersw_counter) {
            // and more than 1sec
            usersw_stat = USERSW_LONG_MAKE;
        }
        usersw_counter = 0;
    }
}

void rtcinit(void)
{
    TMR2_StopTimer();
    cnt20ms = 0;
    hour = 0;
    min = 0;
    sec = 0;
    ready = 0;
    TMR2_SetInterruptHandler(rtc20msint);
    TMR2_StartTimer();

    usersw_counter = 0;
}

void rtcget(uint8_t *h, uint8_t *m, uint8_t *s)
{
    uint8_t check_cnt20ms;

    ready = 0;

    do {
        check_cnt20ms = cnt20ms;
        *h = hour;
        *m = min;
        *s = sec;
    } while (check_cnt20ms != cnt20ms);
}

void rtcset(uint8_t  h, uint8_t  m, uint8_t  s)
{
    cnt20ms = 0;
    hour = h;
    min  = m;
    sec  = s;

    ready = 1;
}

uint8_t rtcready(void)
{
    return ready;
}

uint8_t rtcusersw(void)
{
    uint8_t ret;
    ret = usersw_stat;
    usersw_stat = USERSW_BREAK;
    return ret;
}

