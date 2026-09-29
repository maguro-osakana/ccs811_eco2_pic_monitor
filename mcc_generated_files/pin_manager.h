/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC16F1827
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.00
        MPLAB 	          :  MPLAB X 5.10	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set LCD_DAT4 aliases
#define LCD_DAT4_TRIS                 TRISAbits.TRISA0
#define LCD_DAT4_LAT                  LATAbits.LATA0
#define LCD_DAT4_PORT                 PORTAbits.RA0
#define LCD_DAT4_ANS                  ANSELAbits.ANSA0
#define LCD_DAT4_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define LCD_DAT4_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define LCD_DAT4_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define LCD_DAT4_GetValue()           PORTAbits.RA0
#define LCD_DAT4_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define LCD_DAT4_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define LCD_DAT4_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define LCD_DAT4_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set LCD_RS aliases
#define LCD_RS_TRIS                 TRISAbits.TRISA1
#define LCD_RS_LAT                  LATAbits.LATA1
#define LCD_RS_PORT                 PORTAbits.RA1
#define LCD_RS_ANS                  ANSELAbits.ANSA1
#define LCD_RS_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define LCD_RS_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define LCD_RS_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define LCD_RS_GetValue()           PORTAbits.RA1
#define LCD_RS_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define LCD_RS_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define LCD_RS_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define LCD_RS_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set LCD_E aliases
#define LCD_E_TRIS                 TRISAbits.TRISA2
#define LCD_E_LAT                  LATAbits.LATA2
#define LCD_E_PORT                 PORTAbits.RA2
#define LCD_E_ANS                  ANSELAbits.ANSA2
#define LCD_E_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define LCD_E_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define LCD_E_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define LCD_E_GetValue()           PORTAbits.RA2
#define LCD_E_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define LCD_E_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define LCD_E_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define LCD_E_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set LCD_DAT5 aliases
#define LCD_DAT5_TRIS                 TRISAbits.TRISA3
#define LCD_DAT5_LAT                  LATAbits.LATA3
#define LCD_DAT5_PORT                 PORTAbits.RA3
#define LCD_DAT5_ANS                  ANSELAbits.ANSA3
#define LCD_DAT5_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define LCD_DAT5_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define LCD_DAT5_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define LCD_DAT5_GetValue()           PORTAbits.RA3
#define LCD_DAT5_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define LCD_DAT5_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define LCD_DAT5_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define LCD_DAT5_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set LCD_DAT7 aliases
#define LCD_DAT7_TRIS                 TRISAbits.TRISA4
#define LCD_DAT7_LAT                  LATAbits.LATA4
#define LCD_DAT7_PORT                 PORTAbits.RA4
#define LCD_DAT7_ANS                  ANSELAbits.ANSA4
#define LCD_DAT7_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define LCD_DAT7_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define LCD_DAT7_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define LCD_DAT7_GetValue()           PORTAbits.RA4
#define LCD_DAT7_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define LCD_DAT7_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define LCD_DAT7_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define LCD_DAT7_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set USER_SW aliases
#define USER_SW_TRIS                 TRISAbits.TRISA6
#define USER_SW_LAT                  LATAbits.LATA6
#define USER_SW_PORT                 PORTAbits.RA6
#define USER_SW_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define USER_SW_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define USER_SW_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define USER_SW_GetValue()           PORTAbits.RA6
#define USER_SW_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define USER_SW_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)

// get/set LCD_DAT6 aliases
#define LCD_DAT6_TRIS                 TRISAbits.TRISA7
#define LCD_DAT6_LAT                  LATAbits.LATA7
#define LCD_DAT6_PORT                 PORTAbits.RA7
#define LCD_DAT6_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define LCD_DAT6_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define LCD_DAT6_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define LCD_DAT6_GetValue()           PORTAbits.RA7
#define LCD_DAT6_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define LCD_DAT6_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)

// get/set CO2nWAKE aliases
#define CO2nWAKE_TRIS                 TRISBbits.TRISB0
#define CO2nWAKE_LAT                  LATBbits.LATB0
#define CO2nWAKE_PORT                 PORTBbits.RB0
#define CO2nWAKE_WPU                  WPUBbits.WPUB0
#define CO2nWAKE_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define CO2nWAKE_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define CO2nWAKE_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define CO2nWAKE_GetValue()           PORTBbits.RB0
#define CO2nWAKE_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define CO2nWAKE_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define CO2nWAKE_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define CO2nWAKE_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)

// get/set SDA1 aliases
#define SDA1_TRIS                 TRISBbits.TRISB1
#define SDA1_LAT                  LATBbits.LATB1
#define SDA1_PORT                 PORTBbits.RB1
#define SDA1_WPU                  WPUBbits.WPUB1
#define SDA1_ANS                  ANSELBbits.ANSB1
#define SDA1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define SDA1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define SDA1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define SDA1_GetValue()           PORTBbits.RB1
#define SDA1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define SDA1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define SDA1_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define SDA1_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define SDA1_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define SDA1_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set RB2 procedures
#define RB2_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define RB2_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define RB2_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define RB2_GetValue()              PORTBbits.RB2
#define RB2_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define RB2_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define RB2_SetPullup()             do { WPUBbits.WPUB2 = 1; } while(0)
#define RB2_ResetPullup()           do { WPUBbits.WPUB2 = 0; } while(0)
#define RB2_SetAnalogMode()         do { ANSELBbits.ANSB2 = 1; } while(0)
#define RB2_SetDigitalMode()        do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set CO2nRST aliases
#define CO2nRST_TRIS                 TRISBbits.TRISB3
#define CO2nRST_LAT                  LATBbits.LATB3
#define CO2nRST_PORT                 PORTBbits.RB3
#define CO2nRST_WPU                  WPUBbits.WPUB3
#define CO2nRST_ANS                  ANSELBbits.ANSB3
#define CO2nRST_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define CO2nRST_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define CO2nRST_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define CO2nRST_GetValue()           PORTBbits.RB3
#define CO2nRST_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define CO2nRST_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define CO2nRST_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define CO2nRST_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define CO2nRST_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define CO2nRST_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set SCL1 aliases
#define SCL1_TRIS                 TRISBbits.TRISB4
#define SCL1_LAT                  LATBbits.LATB4
#define SCL1_PORT                 PORTBbits.RB4
#define SCL1_WPU                  WPUBbits.WPUB4
#define SCL1_ANS                  ANSELBbits.ANSB4
#define SCL1_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define SCL1_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define SCL1_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define SCL1_GetValue()           PORTBbits.RB4
#define SCL1_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define SCL1_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define SCL1_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define SCL1_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define SCL1_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define SCL1_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set RB5 procedures
#define RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RB5_GetValue()              PORTBbits.RB5
#define RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define RB5_SetPullup()             do { WPUBbits.WPUB5 = 1; } while(0)
#define RB5_ResetPullup()           do { WPUBbits.WPUB5 = 0; } while(0)
#define RB5_SetAnalogMode()         do { ANSELBbits.ANSB5 = 1; } while(0)
#define RB5_SetDigitalMode()        do { ANSELBbits.ANSB5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/