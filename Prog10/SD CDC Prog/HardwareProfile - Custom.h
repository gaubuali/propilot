/********************************************************************
 FileName:     	HardwareProfile - PIC18F46J50 PIM.h
 Dependencies:	See INCLUDES section
 Processor:	PIC18 USB Microcontrollers
 Hardware:	PIC18F46J50 PIM
 Compiler:  	Microchip C18
 Company:	Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the �Company�) for its PIC� Microcontroller is intended and
 supplied to you, the Company�s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Date         Description
  1.0   11/19/2004   Initial release
  2.1   02/26/2007   Updated for simplicity and to use common
                     coding style
  2.3   09/15/2008   Broke out each hardware platform into its own
                     "HardwareProfile - xxx.h" file
********************************************************************/

#ifndef HARDWARE_PROFILE_PIC18F46J50_PIM_H
#define HARDWARE_PROFILE_PIC18F46J50_PIM_H
#define HARDWARE_PROFILE_CUSTOM_PIM_H
#include <p18f26j50.h>

    /*******************************************************************/
    /******** USB stack hardware selection options *********************/
    /*******************************************************************/
    //This section is the set of definitions required by the MCHPFSUSB
    //  framework.  These definitions tell the firmware what mode it is
    //  running in, and where it can find the results to some information
    //  that the stack needs.
    //These definitions are required by every application developed with
    //  this revision of the MCHPFSUSB framework.  Please review each
    //  option carefully and determine which options are desired/required
    //  for your application.

    //#define USE_SELF_POWER_SENSE_IO
    #define tris_self_power     TRISCbits.TRISC2    // Input
    #define self_power          1

    //#define USE_USB_BUS_SENSE_IO
    #define tris_usb_bus_sense  TRISCbits.TRISC2    // Input
    #define USB_BUS_SENSE       1 
 
    //Uncomment this to make the output HEX of this project 
    //   to be able to be bootloaded using the HID bootloader
	#define PROGRAMMABLE_WITH_USB_HID_BOOTLOADER		

    /*******************************************************************/
    /******** MDD File System selection options ************************/
    /*******************************************************************/
    #define USE_PIC18

    #define ERASE_BLOCK_SIZE 1024
    #define WRITE_BLOCK_SIZE 64

    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/
    /******** Application specific definitions *************************/
    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/

    /** Board definition ***********************************************/
    //These defintions will tell the main() function which board is
    //  currently selected.  This will allow the application to add
    //  the correct configuration bits as wells use the correct
    //  initialization functions for the board.  These defitions are only
    //  required in the stack provided demos.  They are not required in
    //  final application design.
//    #define DEMO_BOARD PIC18F46J50_PIM
//    #define PIC18F46J50_PIM
    #define CUSTOM_PIM
    #define CLOCK_FREQ 48000000
    #define GetSystemClock() CLOCK_FREQ   
    #define GetInstructionClock() GetSystemClock()

    /** LED ************************************************************/
//    #define mInitAllLEDs()      LATE &= 0xFC; TRISE &= 0xFC;
    #define mInitAllLEDs()      
    
//    #define mLED_1              LATEbits.LATE0
//    #define mLED_2              LATEbits.LATE1
    #define mLED_1              
    #define mLED_2              
    #define mLED_3              
    #define mLED_4              
    
//    #define mGetLED_1()         mLED_1
//    #define mGetLED_2()         mLED_2
    #define mGetLED_1()         1
    #define mGetLED_2()         1
    #define mGetLED_3()         1
    #define mGetLED_4()         1

//    #define mLED_1_On()         mLED_1 = 1;
//    #define mLED_2_On()         mLED_2 = 1;
    #define mLED_1_On()         
    #define mLED_2_On()         
    #define mLED_3_On()         
    #define mLED_4_On()        
    
//    #define mLED_1_Off()        mLED_1 = 0;
//    #define mLED_2_Off()        mLED_2 = 0;
    #define mLED_1_Off()        
    #define mLED_2_Off()        
    #define mLED_3_Off()        
    #define mLED_4_Off()        
    
//    #define mLED_1_Toggle()     mLED_1 = !mLED_1;
//    #define mLED_2_Toggle()     mLED_2 = !mLED_2;
    #define mLED_1_Toggle()     
    #define mLED_2_Toggle()     
    #define mLED_3_Toggle()     
    #define mLED_4_Toggle()     
    
    /** SWITCH *********************************************************/
//    #define mInitSwitch2()      TRISBbits.TRISB2=1;
//    #define mInitSwitch3()      mInitSwitch2();
//    #define mInitAllSwitches()  mInitSwitch2();
//    #define sw2                 PORTBbits.RB2
//    #define sw3                 PORTBbits.RB2
    #define mInitSwitch2()      ;
    #define mInitSwitch3()      mInitSwitch2();
    #define mInitAllSwitches()  mInitSwitch2();
    #define sw2                 1
    #define sw3                 1

	/** RS 232 lines ****************************************************/
//	#define UART_TRISTx   TRISCbits.TRISC6
//	#define UART_TRISRx   TRISCbits.TRISC7
//	#define UART_Tx       PORTCbits.RC6
//	#define UART_Rx       PORTCbits.RC7
//	#define UART_TRISRTS  TRISBbits.TRISB1
//	#define UART_RTS      PORTBbits.RB1
//	#define UART_TRISDTR  TRISBbits.TRISB2
//	#define UART_DTR      PORTBbits.RB2
//  #define UART_ENABLE RCSTAbits.SPEN

	#define UART_TRISTx   TRISCbits.TRISC6
	#define UART_TRISRx   TRISCbits.TRISC7
	#define UART_Tx       PORTCbits.RC6
	#define UART_Rx       PORTCbits.RC7
	#define UART_TRISRTS  TRISAbits.TRISA6
	#define UART_RTS      PORTAbits.RA6
	#define UART_TRISDTR  TRISCbits.TRISC1
	#define UART_DTR      PORTCbits.RC1
    #define UART_ENABLE RCSTAbits.SPEN

    /** I/O pin definitions ********************************************/
    #define INPUT_PIN 1
    #define OUTPUT_PIN 0

/*********************************************************************/
/******************* Pin and Register Definitions ********************/
/*********************************************************************/

/* SD Card definitions: Change these to fit your application when using
   an SD-card-based physical layer                                   */
    	#define USE_PIC18

#define MEDIA_SOFT_DETECT

//        #define TRIS_CARD_DETECT    TRISBbits.TRISB4    // Input
//        #define CARD_DETECT         PORTBbits.RB4
        
//        #define TRIS_WRITE_DETECT   TRISDbits.TRISD7    // Input
//        #define WRITE_DETECT        PORTDbits.RD7
     
        // Card detect signal
//        #define SD_CD               PORTBbits.RB4
//        #define SD_CD_TRIS          TRISBbits.TRISB4
            
        // Write protect signal
//        #define SD_WE               PORTDbits.RD7
//        #define SD_WE_TRIS          TRISDbits.TRISD7
    
        // Chip Select Signal
//        #define SD_CS               PORTBbits.RB3
//        #define SD_CS_TRIS          TRISBbits.TRISB3
        #define SD_CS               PORTBbits.RB0
        #define SD_CS_TRIS          TRISBbits.TRISB0
            
        // TRIS pins for the SCK/SDI/SDO lines
//        #define SPICLOCK            TRISBbits.TRISB1
//        #define SPIIN               TRISAbits.TRISA1
//        #define SPIOUT              TRISAbits.TRISA5
        #define SPICLOCK            TRISBbits.TRISB2
        #define SPIIN               TRISBbits.TRISB3
        #define SPIOUT              TRISBbits.TRISB1
    
        // Latch pins for SCK/SDI/SDO lines
//        #define SPICLOCKLAT         LATBbits.LATB1
//        #define SPIINLAT            LATAbits.LATA1
//        #define SPIOUTLAT           LATAbits.LATA5
        #define SPICLOCKLAT         LATBbits.LATB2
        #define SPIINLAT            LATBbits.LATB3
        #define SPIOUTLAT           LATBbits.LATB1
    
        // Port pins for SCK/SDI/SDO lines
//        #define SPICLOCKPORT        PORTBbits.RB1
//        #define SPIINPORT           PORTAbits.RA1
//        #define SPIOUTPORT          PORTAbits.RA5
        #define SPICLOCKPORT        PORTBbits.RB2
        #define SPIINPORT           PORTBbits.RB3
        #define SPIOUTPORT          PORTBbits.RB1
    
        // Registers for the SPI module you want to use
        #define SPICON1             SSP2CON1
        #define SPISTAT             SSP2STAT
        #define SPIBUF              SSP2BUF
        #define SPISTAT_RBF         SSP2STATbits.BF
        #define SPICON1bits         SSP2CON1bits
        #define SPISTATbits         SSP2STATbits
    
        #define SPI_INTERRUPT_FLAG  PIR3bits.SSP2IF 
        #define SPIENABLE           SSP2CON1bits.SSPEN
    
        // Will generate an error if the clock speed is too low to interface to the card
        #if (GetSystemClock() < 400000)
            #error System clock speed must exceed 400 kHz
        #endif
extern BYTE getSDcard( void );
extern BYTE giveSDcard( void );

#endif  //HARDWARE_PROFILE_PIC18F46J50_PIM_H
