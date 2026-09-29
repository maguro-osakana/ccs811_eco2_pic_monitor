/* 
 * File:   misc.c
 * Author: maguro-osakana
 *
 * Created on 2019/03/13, 21:13
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

#include <inttypes.h>

static uint8_t atoh4(char c)
{
    if (('0' <= c) && (c <= '9')) {
        return c - '0';
    } else if (('A' <= c) && (c <= 'F')) {
        return c - 'A' + 0x0A;
    } else if (('a' <= c) && (c <= 'f')) {
        return c - 'a' + 0x0A;
    }
    return 0;
}

uint8_t atoh8(const char *s)
{
    if ((s[1] == ' ') || (s[1] == '\0')) {
        return atoh4(s[0]);
    } else {
        return (atoh4(s[0]) * 0x10) + atoh4(s[1]);
    }
}

static char htoa4(uint8_t h)
{
    if (h < 10) {
        return '0' + h;
    } else {
        return 'A' + (h - 10);
    }

}

void htoa8(char *s, uint8_t h)
{
    s[0] = htoa4(h >> 4);
    s[1] = htoa4(h & 0x0F);
}



uint8_t atoi8(const char *s)
{
    if ((s[1] == ' ') || (s[1] == '\0')) {
        return atoh4(s[0]);
    } else {
        return (atoh4(s[0]) * 10) + atoh4(s[1]);
    }
}

static inline char itoa_sub(uint8_t i)
{
    return '0' + i;
}

void itoa16(char *s, uint16_t i)
{
    s[0] = itoa_sub((i)         / 10000);
    s[1] = itoa_sub((i % 10000) /  1000);
    s[2] = itoa_sub((i %  1000) /   100);
    s[3] = itoa_sub((i %   100) /    10);
    s[4] = itoa_sub((i %    10)        );
}

void itoa8(char *s, uint8_t i)
{
    s[0] = itoa_sub((i %   100) /    10);
    s[1] = itoa_sub((i %    10)        );
}