/* 
 * File:   ccs811.h
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

#ifndef CCS811_H
#define	CCS811_H

#ifdef	__cplusplus
extern "C" {
#endif

#define CSS811_STATUS          0x00
#define CSS811_MEAS_MODE       0x01
#define CSS811_ALG_RESULT_DATA 0x02
#define CSS811_RAW_DATA        0x03
#define CSS811_ENV_DATA        0x05
#define CSS811_THRESHOLDS      0x10
#define CSS811_BASELINE        0x11
#define CSS811_HW_ID           0x20
#define CSS811_HW_Version      0x21
#define CSS811_FW_Boot_Version 0x23
#define CSS811_FW_App_Version  0x24
#define CSS811_Internal_State  0xA0
#define CSS811_ERROR_ID        0xE0
#define CSS811_APP_ERASE       0xF1
#define CSS811_APP_DATA        0xF2
#define CSS811_APP_VERIFY      0xF3
#define CSS811_APP_START       0xF4
#define CSS811_SW_RESET        0xFF


void css811init(void);
void css811write(uint8_t regaddr, uint8_t *data, uint8_t count);
void css811read(uint8_t regaddr, uint8_t *data, uint8_t count);


#ifdef	__cplusplus
}
#endif

#endif	/* CCS811_H */

