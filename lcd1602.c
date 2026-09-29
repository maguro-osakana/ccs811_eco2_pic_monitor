/* 
 * File:   lcd1602.c
 * Author: maguro-osakana
 *
 * Created on 2019/02/24, 18:04
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
#include "lcd1602.h"

static void lcdiowrite(uint8_t rs, uint8_t data4)
{    
    LCD_E_LAT = 0;
    __delay_us(1);
    LCD_RS_LAT  = rs;
    __delay_us(1);
    LCD_E_LAT = 1;
    __delay_us(1);
    LCD_DAT4_LAT = (data4 >> 0) & 1;
    LCD_DAT5_LAT = (data4 >> 1) & 1;
    LCD_DAT6_LAT = (data4 >> 2) & 1;
    LCD_DAT7_LAT = (data4 >> 3) & 1;
    __delay_us(1);
    LCD_E_LAT = 0;
    __delay_us(1);
}

void lcdwrite8(uint8_t rs, uint8_t data8)
{
    lcdiowrite(rs, (data8 >> 4) & 0xF);
    lcdiowrite(rs, (data8 >> 0) & 0xF);
    __delay_us(41); 
}

void lcdprint(uint8_t line, const char *msg)
{
    int i;
    
    if (line == 0) {
        lcdwrite8(0, 0x80 + 0x00); // DDRAM Addess == 0x00
    } else {
        lcdwrite8(0, 0x80 + 0x40); // DDRAM Addess == 0x40        
    }
    
    for (i = 0; i < 16; i++) {
        if (*msg) {
            lcdwrite8(1, *msg);
            msg++;
        } else {
            lcdwrite8(1, ' ');
        }
    }
}


void lcdinit(void)
{
    // LCD init
    __delay_us(40000);
    lcdiowrite(0, 0b0011); // 8bit mode write 0011xxxx 
    __delay_us(4100);
    lcdiowrite(0, 0b0011); // 8bit mode write 0011xxxx
    __delay_us(100);
    lcdiowrite(0, 0b0011); // 8bit mode write 0011xxxx 
    __delay_us(41);    
    lcdiowrite(0, 0b0010); // 8bit mode write 0010xxxx (Switch to 4bit mode)
    __delay_us(41);        
    lcdiowrite(0, 0b0010); // 4bit mode upper bits write 0_0_1_0 
    lcdiowrite(0, 0b1000); // 4bit mode lower bits write N_F_*_* (Number=1, Fontsize=0) 
    __delay_us(41);    
    lcdiowrite(0, 0b0000); // 4bit mode upper bits write 0_0_0_0 
    lcdiowrite(0, 0b1111); // 4bit mode lower bits write 1_D_C_B (Display=1, Cursor=1, Blink=1) 
    __delay_us(41);    
    lcdiowrite(0, 0b0000); // 4bit mode upper bits write 0_0_0_0 All clear
    lcdiowrite(0, 0b0001); // 4bit mode lower bits write 0_0_0_1 
    __delay_us(1520);    
    lcdiowrite(0, 0b0000); // 4bit mode upper bits write 0_0_0_0 
    lcdiowrite(0, 0b0110); // 4bit mode lower bits write 0_1_I/D_S (Inc/Dec=1(Inc) Scroll=0)
    __delay_us(37);    
}


