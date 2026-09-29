/* 
 * File:   shell.c
 * Author: maguro-osakana
 *
 * Created on February 27, 2019, 2:09 PM
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


#include "mcc_generated_files/mcc.h"
#include "shell.h"
#include "lcd1602.h"
#include "ccs811.h"
#include "misc.h"
#include "rtc.h"
#include <ctype.h>
#include <string.h>

#define LINE_MAX 40
#define ARGC_MAX 8

static void shellExec(char *s);

static int showHelp(int argc, char **argv);

static int printLcd(int argc, char **argv);
static int writeLcd(int argc, char **argv);

static int write811(int argc, char **argv);
static int read811(int argc, char **argv);

static int writeRtc(int argc, char **argv);
static int readRtc(int argc, char **argv);

static int writeEEPR(int argc, char **argv);
static int readEEPR(int argc, char **argv);

static int halt(int argc, char **argv);

static const struct {
    const char *name;
    int (*cmd)(int argc, char **argv);
    const char *usage;
} commands[] = {
    {"?",  showHelp,  "Help     :?"},
    {"l",  printLcd,  "LCD text :l  [line1] [line2]"},
    {"lw", writeLcd,  "LCD cmd w:lw [rs] [dt]" },
    {"w",  write811,  "CCS811 wt:w  [addr] [dt1] [dt2]..."},
    {"r",  read811,   "CCS811 rd:r  [addr] [cnt]"},
    {"rw", writeRtc,  "RTC wt   :rw [h] [m] [s]"},
    {"rr", readRtc,   "RTC rd   :rr"},
    {"ew", writeEEPR, "EEPR wt  :ew [addr] [dt]"},
    {"er", readEEPR,  "EEPR rd  :er"},
    {"z",  halt,      "Halt     :z"},
};

#define CMDCNT (sizeof(commands)/sizeof(commands[0]))

static const char *prompt = "help=?>";

void shell(void)
{
    volatile uint8_t rxData;
    static char buf[LINE_MAX];
    static uint8_t bufptr = 0;

    if (EUSART_is_rx_ready()) {
        // Read UART
        rxData = EUSART_Read();
        
        // Echoback
        if (EUSART_is_tx_ready()) {
            EUSART_Write(rxData);
        }

        // Store
        if (bufptr < LINE_MAX) {
            buf[bufptr++] = rxData;
        }

        // Backspace
        if (rxData == '\b') {
            if (bufptr >= 2) {
                bufptr = bufptr - 2;
            }
        }

        // Enter (CR or LF)
        if ((rxData == '\r') || (rxData == '\n')) {
            buf[bufptr - 1] = '\0';
            shellExec(buf);
            bufptr = 0;
            printf(prompt);
        }
    }   
}


static void shellExec(char *s)
{
    int i;
    int argc = 0;
    char *argv[ARGC_MAX];
    char prev = '\0';

    while (*s) {
        if (*s == ' ') {
            *s = '\0';
        }

        if ((*s != '\0') && (prev == '\0')) {
            argv[argc] = s;
            argc++;
        }

        prev = *s;
        s++;
    }

    for (i = 0; i < CMDCNT; i++) {
        if (strcmp(commands[i].name, argv[0]) == 0) {
            commands[i].cmd(argc, argv);
            break;
        }
    }
}

static int showHelp(int argc, char ** argv)
{
    int i;
    for (i = 0; i < CMDCNT; i++) {
        printf(commands[i].usage);
        printf("\n");
    }
    return 0;
}

static int printLcd(int argc, char **argv)
{
    if (argc >= 2) {
        lcdprint(0, argv[1]);
    }  
    if (argc >= 3) {
        lcdprint(1, argv[2]);
    }  
    return 0;
}

static int writeLcd(int argc, char **argv)
{
    uint8_t rs;
    uint8_t data;
    char s[3];
    s[2] = '\0';

    if (argc >= 3) {
        rs   = atoh8(argv[1]);
        data = atoh8(argv[2]);
        lcdwrite8(rs, data);
        printf("rs=");
        htoa8(s, rs);
        printf(s);
        printf(" data=");
        htoa8(s, data);
        printf(s);
        printf("\n");
    }
    return 0;
}


static int write811(int argc, char **argv)
{
    uint8_t i;
    uint8_t regaddr;
    uint8_t count;
    uint8_t data[8];
    char s[3];
    s[2] = '\0';

    if (argc >= 2) {
        regaddr = atoh8(argv[1]);
        for (i = 2; i < argc; i++) {
            data[i - 2] = atoh8(argv[i]);
        }
        count = argc - 2;

        css811write(regaddr, data, count);
    }
    return 0;
}

static int read811(int argc, char **argv)
{
    uint8_t i;
    uint8_t regaddr;
    uint8_t count;
    uint8_t data[8];
    char s[3];
    s[2] = '\0';

    if (argc >= 3) {
        regaddr = atoh8(argv[1]);
        count   = atoh8(argv[2]);
        if (count > 8) {
            count  = 8;
        }
        css811read(regaddr, data, count);
        for (i = 0; i < count; i++) {
            printf("reg=");
            htoa8(s, regaddr); printf(s);
            printf(" data=");
            htoa8(s, data[i]); printf(s);
            printf("\n");
        }
    }
    return 0;
}


static int writeRtc(int argc, char **argv)
{
    uint8_t hour, min, sec;

    if (argc >= 4) {
        hour = atoi8(argv[1]);
        min  = atoi8(argv[2]);
        sec  = atoi8(argv[3]);
        rtcset(hour, min, sec);
    }

    return 0;
}

static int readRtc(int argc, char **argv)
{
    uint8_t hour, min, sec;
    char s[3];

    s[2] = '\0';

    rtcget(&hour, &min, &sec);

    printf("RTC=");
    itoa8(s, hour);
    printf(s);
    printf(":");
    itoa8(s, min);
    printf(s);
    printf(":");
    itoa8(s, sec);
    printf(s);
    printf("\n");

    return 0;
}


static int writeEEPR(int argc, char **argv)
{
    uint8_t address, data;
    if (argc >= 3) {
        address = atoh8(argv[1]);
        data    = atoh8(argv[2]);
        DATAEE_WriteByte(address, data);
    }
    return 0;

}

static int readEEPR(int argc, char **argv)
{
    uint8_t i,j;
    char s[3];
    s[2] = '\0';

    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {
            printf(" ");
            htoa8(s, DATAEE_ReadByte((i << 4) | j));
            printf(s);
        }
        printf("\n");
    }


    return 0;
}



static int halt(int argc, char **argv)
{
    printf("halt\n\n");

    while (1) {
        ;
    }

    return 0;
}
