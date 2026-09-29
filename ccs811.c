/*
 * File:   ccs811.c
 * Author: maguro-osakana
 *
 * Created on 2019/02/27, 13:24
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
#include "ccs811.h"

#define ADDR 0x5A
#define WRITE ((ADDR << 1) | 0)
#define READ  ((ADDR << 1) | 1)

#define WAIT_MAX 2000 // 100us x 2000 = 200ms

void css811init(void)
{
    uint8_t wdata;

    __delay_ms(20); // Time between power on and the device being ready for new I2C command

    CO2nWAKE_LAT = 0;
    __delay_us(20); // Minimum time nWAKE should be high after rising nWAKE
    __delay_us(50); // Time after falling nWAKE and the device being ready for new I2C commands

    CO2nRST_LAT = 0;
    __delay_us(15); // Minimum time nRESET should be low after falling nRESET
    CO2nRST_LAT = 1;
    __delay_us(20); // Minimum time nRESET should be high after rising nRESET
    __delay_ms(2);  // Time after rising nRESET pin or giving the SW_RESET command and the device being ready for new I2C commands

    i2c1_driver_open();

    css811write(CSS811_APP_START, NULL, 0);
    __delay_ms(1); // Time between giving the APP_START command in boot mode and the device being ready for new I2C commands 

    wdata = 0x10; // Mode 1 – Constant power mode, IAQ measurement every second & Int Disable
    css811write(CSS811_MEAS_MODE, &wdata, 1); 
}

static inline void clrIF(void)
{
    mssp1_clearIRQ();
}

static void waitIF(void)
{
    uint16_t i;

    for (i = 0; i < WAIT_MAX; i++) {
        if (mssp1_IRQisSet()) {
            clrIF();
            return;
        }
        __delay_us(100);
    }
}

void css811write(uint8_t regaddr, uint8_t *data, uint8_t count)
{
    uint8_t remain = count;

    clrIF();

    i2c1_driver_start();
    waitIF();
    i2c1_driver_TXData(WRITE);
    waitIF();
    i2c1_driver_TXData(regaddr);
    waitIF();
    while (remain) {
        i2c1_driver_TXData(*data);
        waitIF();    
        data++;
        remain--;
    }
    i2c1_driver_stop();
    waitIF();
}

void css811read(uint8_t regaddr, uint8_t *data, uint8_t count)
{
    uint8_t remain = count;

    clrIF();

    // Select register address
    i2c1_driver_start();
    waitIF();
    i2c1_driver_TXData(WRITE);
    waitIF();
    i2c1_driver_TXData(regaddr);
    waitIF();
    i2c1_driver_stop();
    waitIF();

    // Read Register value
    if (remain) {
        i2c1_driver_start();
        waitIF();
        i2c1_driver_TXData(READ);
        waitIF();
    }
    while (remain) {
        i2c1_driver_startRX();
        waitIF();;
        *data = i2c1_driver_getRXData();
        data++;
        remain--;
        if (remain) {
            i2c1_driver_sendACK();
            waitIF();
        } else {
            i2c1_driver_sendNACK();
            waitIF();
            i2c1_driver_stop();
            waitIF();
        }
    }
}

/*
EEP READ ASM
  BANKSEL EEADRL ;
  MOVLW DATA_EE_ADDR ;
  MOVWF EEADRL ;Data Memory
  ;Address to read
  BCF EECON1, CFGS ;Deselect Config space
  BCF EECON1, EEPGD;Point to DATA memory
  BSF EECON1, RD ;EE Read
  MOVF EEDATL, W ;W = EEDATL

EEP WRITE ASM
  BANKSEL EEADRL ;
  MOVLW DATA_EE_ADDR ;
  MOVWF EEADRL ;Data Memory Address to write
  MOVLW DATA_EE_DATA ;
  MOVWF EEDATL ;Data Memory Value to write
  BCF EECON1, CFGS ;Deselect Configuration space
  BCF EECON1, EEPGD ;Point to DATA memory
  BSF EECON1, WREN ;Enable writes
  BCF INTCON, GIE ;Disable INTs.
  MOVLW 55h ;
  MOVWF EECON2 ;Write 55h
  MOVLW 0AAh ;
  MOVWF EECON2 ;Write AAh
  BSF EECON1, WR ;Set WR bit to begin write
  BSF INTCON, GIE ;Enable Interrupts
  BCF EECON1, WREN ;Disable writes
  BTFSC EECON1, WR ;Wait for write
*/