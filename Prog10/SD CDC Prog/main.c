/********************************************************************
 FileName:		main.c
 Dependencies:	See INCLUDES section
 Processor:		PIC18, PIC24, and PIC32 USB Microcontrollers
 Hardware:		This demo is natively intended to be used on Microchip USB demo
 				boards supported by the MCHPFSUSB stack.  See release notes for
 				support matrix.  This demo can be modified for use on other hardware
 				platforms.
 Complier:  	Microchip C18 (for PIC18), C30 (for PIC24), C32 (for PIC32)
 Company:		Microchip Technology, Inc.

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
  Rev   Description
  ----  -----------------------------------------
  1.0   Initial release
  2.1   Updated for simplicity and to use common
                     coding style
  2.8  Improvements to USBCBSendResume(), to make it easier to use.
	Added runtime check to avoid buffer overflow possibility if
	the USB IN data rate is somehow slower than the UART RX rate.
********************************************************************/

/** INCLUDES *******************************************************/

#include "./USB/USB.h"
#include "HardwareProfile.h"
#include "FSconfig.h"
#if defined(USE_INTERNAL_FLASH)
#include "MDD File System/internal flash.h"
#elif defined(USE_SD_INTERFACE_WITH_SPI)
#include "MDD File System/SD-SPI.h"
#endif

#include "./USB/usb_function_msd.h"
#include "./USB/usb_function_cdc.h"

// two pins define who has access to the SD card, these are both pulled up
// externally so they are only pulled down by the code in each CPU
// normally the 33 has access so it pulls PSCL1 low and monitors PSDA1
// once it sees PSDA1 go low it closes files, flushes buffers and releases
// PSCL1 indicating the 18f is free to use the card - at this point it will
// also start passing its serial input to uart1.
// CHANGED: now uses just SDSELECT and SDPOWER
#define tPSCL1	TRISBbits.TRISB4    // Input
#define iPSCL1	PORTBbits.RB4
#define tPSDA1	TRISBbits.TRISB5    // Input / Output
#define iPSDA1	PORTBbits.RB5
#define oPSDA1	LATBbits.LATB5
// actual power control on the SD card
#define tSDPOWER	TRISCbits.TRISC0    // Input / Output
#define iSDPOWER	PORTCbits.RC0
#define oSDPOWER	LATCbits.LATC0
#define tSDSELECT	TRISCbits.TRISC2    // Input / Output
#define iSDSELECT	PORTCbits.RC2
#define oSDSELECT	LATCbits.LATC2

#include "HardwareConfig.h"
//#define T0_Adjust (0xffff - ((GetSystemClock()/4)/1000))
#define T4_PRE_DIV (((GetSystemClock()/16)/1000)/250)
#define T4_PRE (((GetSystemClock()/16)/1000)/T4_PRE_DIV)
#if T4_PRE > 255
#error T4_PRE to large, reduce last factor in T4_PRE_DIV
#endif
BYTE SDcard = 0;		// = 2 for 18f has ownership of card interface
BYTE SDcardDelay = 0;	// delay for 18f losing ownership of card interface

/** VARIABLES ******************************************************/
#pragma udata
// char USB_Out_Buffer[CDC_DATA_OUT_EP_SIZE+1];	// bad Microchip code
unsigned char RS232_Out_Data[CDC_DATA_IN_EP_SIZE+1];		// bad Microchip code

#define RS232_IntRec_Buf (250)
#if defined(__18CXX)
	#pragma udata myCDC=CDC_BUFFER_ADDRESS
#endif
unsigned char RS232_In_Buffer[RS232_IntRec_Buf+1];
unsigned char volatile RS232_In_Head = 0;
unsigned char volatile RS232_In_Tail = 0;	// interrupt driven circular buffer
unsigned char ucInt;

#if defined(__18CXX)
#pragma udata
#endif

char cPrintBuf[CDC_DATA_OUT_EP_SIZE+1];

int iPrintBufFull;

unsigned char  NextUSBOut;
//unsigned char  NextUSBOut; // the ways they fail is amasing

unsigned char volatile LastRS232Out;  // Number of characters in the buffer
unsigned char volatile RS232cp;       // current position within the buffer
unsigned char volatile RS232_Out_Data_Rdy = 0;
USB_HANDLE  lastTransmission;

USB_HANDLE USBOutHandle = 0;
USB_HANDLE USBInHandle = 0;
BOOL blinkStatusValid = TRUE;

char USB_In_Buffer[64+1];
char USB_Out_Buffer[64+1];
BOOL stringPrinted;
volatile BOOL buttonPressed;
volatile BYTE buttonCount;


#if defined(__C30__) || defined(__C32__)
//The LUN variable definition is critical to the MSD function driver.  This
//  array is a structure of function pointers that are the functions that 
//  will take care of each of the physical media.  For each additional LUN
//  that is added to the system, an entry into this array needs to be added
//  so that the stack can know where to find the physical layer functions.
//  In this example the media initialization function is named 
//  "MediaInitialize", the read capacity function is named "ReadCapacity",
//  etc.  
LUN_FUNCTIONS LUN[MAX_LUN + 1] = 
{
    {
        &MDD_IntFlash_MediaInitialize,
        &MDD_IntFlash_ReadCapacity,
        &MDD_IntFlash_ReadSectorSize,
        &MDD_IntFlash_MediaDetect,
        &MDD_IntFlash_SectorRead,
        &MDD_IntFlash_WriteProtectState,
        &MDD_IntFlash_SectorWrite
    }
};
#endif

/* Standard Response to INQUIRY command stored in ROM 	*/
const ROM InquiryResponse inq_resp = {
	0x00,		// peripheral device is connected, direct access block device
	0x80,           // removable
	0x04,	 	// version = 00=> does not conform to any standard, 4=> SPC-2
	0x02,		// response is in format specified by SPC-2
	0x20,		// n-4 = 36-4=32= 0x20
	0x00,		// sccs etc.
	0x00,		// bque=1 and cmdque=0,indicates simple queueing 00 is obsolete,
			// but as in case of other device, we are just using 00
	0x00,		// 00 obsolete, 0x80 for basic task queueing
	{'M','i','c','r','o','c','h','p'
    },
	// this is the T10 assigned Vendor ID
	{'M','a','s','s',' ','S','t','o','r','a','g','e',' ',' ',' ',' '
    },
	{'0','0','0','1'
    }
};

/** PRIVATE PROTOTYPES *********************************************/
static void InitializeSystem(void);
void USBDeviceTasks(void);
void ProcessIO(void);
void YourHighPriorityISRCode(void);
void YourLowPriorityISRCode(void);
void USBCBSendResume(void);
void BlinkUSBStatus(void);
void UserInit(void);
void InitializeUSART(void);
void putcUSART(char c);
unsigned char getcUSART ();
// added functions to control what cpu has the SD card
BYTE getSDcard();
BYTE giveSDcard();

#if defined(__18CXX)
    #define mDataRdyUSART() PIR1bits.RCIF
//    #define mTxRdyUSART()   TXSTAbits.TRMT
    #define mTxRdyUSART()   PIR1bits.TXIF
#elif defined(__C30__) || defined(__C32__)
    #define mDataRdyUSART() UART2IsPressed()
    #define mTxRdyUSART()   U2STAbits.TRMT
#endif

/** VECTOR REMAPPING ***********************************************/
#if defined(__18CXX)
	//On PIC18 devices, addresses 0x00, 0x08, and 0x18 are used for
	//the reset, high priority interrupt, and low priority interrupt
	//vectors.  However, the current Microchip USB bootloader 
	//examples are intended to occupy addresses 0x00-0x7FF or
	//0x00-0xFFF depending on which bootloader is used.  Therefore,
	//the bootloader code remaps these vectors to new locations
	//as indicated below.  This remapping is only necessary if you
	//wish to program the hex file generated from this project with
	//the USB bootloader.  If no bootloader is used, edit the
	//usb_config.h file and comment out the following defines:
	//#define PROGRAMMABLE_WITH_USB_HID_BOOTLOADER
	//#define PROGRAMMABLE_WITH_USB_LEGACY_CUSTOM_CLASS_BOOTLOADER
	
	#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)
		#define REMAPPED_RESET_VECTOR_ADDRESS			0x1000
		#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x1008
		#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x1018
	#elif defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)	
		#define REMAPPED_RESET_VECTOR_ADDRESS			0x800
		#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x808
		#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x818
	#else	
		#define REMAPPED_RESET_VECTOR_ADDRESS			0x00
		#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x08
		#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x18
	#endif
	
	#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)||defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)
	extern void _startup (void);        // See c018i.c in your C18 compiler dir
	#pragma code REMAPPED_RESET_VECTOR = REMAPPED_RESET_VECTOR_ADDRESS
	void _reset (void)
	{
	    _asm goto _startup _endasm
	}
	#endif
	#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS
	void Remapped_High_ISR (void)
	{
	     _asm goto YourHighPriorityISRCode _endasm
	}
	#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS
	void Remapped_Low_ISR (void)
	{
	     _asm goto YourLowPriorityISRCode _endasm
	}
	
	#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)||defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)
	//Note: If this project is built while one of the bootloaders has
	//been defined, but then the output hex file is not programmed with
	//the bootloader, addresses 0x08 and 0x18 would end up programmed with 0xFFFF.
	//As a result, if an actual interrupt was enabled and occured, the PC would jump
	//to 0x08 (or 0x18) and would begin executing "0xFFFF" (unprogrammed space).  This
	//executes as nop instructions, but the PC would eventually reach the REMAPPED_RESET_VECTOR_ADDRESS
	//(0x1000 or 0x800, depending upon bootloader), and would execute the "goto _startup".  This
	//would effective reset the application.
	
	//To fix this situation, we should always deliberately place a 
	//"goto REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS" at address 0x08, and a
	//"goto REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS" at address 0x18.  When the output
	//hex file of this project is programmed with the bootloader, these sections do not
	//get bootloaded (as they overlap the bootloader space).  If the output hex file is not
	//programmed using the bootloader, then the below goto instructions do get programmed,
	//and the hex file still works like normal.  The below section is only required to fix this
	//scenario.
	#pragma code HIGH_INTERRUPT_VECTOR = 0x08
	void High_ISR (void)
	{
	     _asm goto REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS _endasm
	}
	#pragma code LOW_INTERRUPT_VECTOR = 0x18
	void Low_ISR (void)
	{
	     _asm goto REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS _endasm
	}
	#endif	//end of "#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)||defined(PROGRAMMABLE_WITH_USB_LEGACY_CUSTOM_CLASS_BOOTLOADER)"

	#pragma code
	
	
	//These are your actual interrupt handling routines.
	#pragma interrupt YourHighPriorityISRCode
	void YourHighPriorityISRCode()
	{
		//Check which interrupt flag caused the interrupt.
		//Service the interrupt
		//Clear the interrupt flag
		//Etc.
        #if defined(USB_INTERRUPT)
	        USBDeviceTasks();
        #endif
	
	}	//This return will be a "retfie fast", since this is in a #pragma interrupt section 
	#pragma interruptlow YourLowPriorityISRCode
	void YourLowPriorityISRCode()
	{
		//Check which interrupt flag caused the interrupt.
		//Service the interrupt
		//Clear the interrupt flag
		//Etc.

		//Check if we received a character over the physical UART, and we need
		//to buffer it up for eventual transmission to the USB host.
    #if defined(__18CXX)
		if(mDataRdyUSART())	// check receive character
		{
			if (RCSTAbits.OERR)  // in case of overrun error
			{                    // we should never see an overrun error, but if we do, 
				RCSTAbits.CREN = 0;  // reset the port
				ucInt = RCREG;
				RCSTAbits.CREN = 1;  // and keep going.
			}
			else
				ucInt = RCREG;
		// not necessary.  EUSART auto clears the flag when RCREG is cleared
		//	PIR1bits.RCIF = 0;    // clear Flag
			RS232_In_Buffer[RS232_In_Head] = ucInt;
			RS232_In_Head++;
			if ( RS232_In_Head > RS232_IntRec_Buf )
				RS232_In_Head = 0;
		}
		if( PIE1bits.TX1IE ) // check tx buffer
		{	
			if ( RS232_Out_Data_Rdy && mTxRdyUSART() )
			{	TXREG = RS232_Out_Data[RS232cp];
				RS232cp++;
			};
			if (RS232cp >= LastRS232Out)
			{	RS232_Out_Data_Rdy = 0;	// buffer empty so
				PIE1bits.TX1IE = 0;    	// turn off interrupt 
			};
		}
		if ( PIR3bits.TMR4IF )
		{
			if ( SDcardDelay )
				SDcardDelay--;
			PIR3bits.TMR4IF = 0;
		}
	#endif
	
	}	//This return will be a "retfie", since this is in a #pragma interruptlow section 

#elif defined(__C30__)
    #if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)
        /*
         *	ISR JUMP TABLE
         *
         *	It is necessary to define jump table as a function because C30 will
         *	not store 24-bit wide values in program memory as variables.
         *
         *	This function should be stored at an address where the goto instructions 
         *	line up with the remapped vectors from the bootloader's linker script.
         *  
         *  For more information about how to remap the interrupt vectors,
         *  please refer to AN1157.  An example is provided below for the T2
         *  interrupt with a bootloader ending at address 0x1400
         */
//        void __attribute__ ((address(0x1404))) ISRTable(){
//        
//        	asm("reset"); //reset instruction to prevent runaway code
//        	asm("goto %0"::"i"(&_T2Interrupt));  //T2Interrupt's address
//        }
    #endif
#endif




/** DECLARATIONS ***************************************************/
#pragma code

/********************************************************************
 * Function:        void main(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Main program entry point.
 *
 * Note:            None
 *****************************************************************************/

 #if defined(__18CXX)
void main(void)
#else 
int main(void)
#endif
{
	MEDIA_INFORMATION * ucMediaResp = 0;

    InitializeSystem();
//	ucMediaResp = MDD_SDSPI_MediaInitialize();

    #if defined(USB_INTERRUPT)
        USBDeviceAttach();
    #endif

    while(1)
    {
        #if defined(USB_POLLING)
		// Check bus status and service USB interrupts.
        USBDeviceTasks(); // Interrupt or polling method.  If using polling, must call
        				  // this function periodically.  This function will take care
        				  // of processing and responding to SETUP transactions 
        				  // (such as during the enumeration process when you first
        				  // plug in).  USB hosts require that USB devices should accept
        				  // and process SETUP packets in a timely fashion.  Therefore,
        				  // when using polling, this function should be called 
        				  // regularly (such as once every 1.8ms or faster** [see 
        				  // inline code comments in usb_device.c for explanation when
        				  // "or faster" applies])  In most cases, the USBDeviceTasks() 
        				  // function does not take very long to execute (ex: <100 
        				  // instruction cycles) before it returns.
        #endif
    				  

		// Application-specific tasks.
		// Application related code may be added here, or in the ProcessIO() function.
        ProcessIO();        
//		if ( ucMediaResp->errorCode )
//			ucMediaResp = MDD_SDSPI_MediaInitialize();
    }//end while
}//end main

/********************************************************************
 * Function:        void ProcessIO(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is a place holder for other user
 *                  routines. It is a mixture of both USB and
 *                  non-USB tasks.
 *
 * Note:            None
 *******************************************************************/
void ProcessIO(void)
{   
    BYTE numBytesRead;
	int iIdx;
    //Blink the LEDs according to the USB device status
    BlinkUSBStatus();
    // User Application USB tasks
    if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) 
	{
		if((USBDeviceState == DEFAULT_STATE)||(USBSuspendControl==1)) 
			giveSDcard();
		else ;
		return;
	}

#if !defined(CUSTOM_PIM)
    if(buttonPressed)
    {
        if(stringPrinted == FALSE)
        {
            if(mUSBUSARTIsTxTrfReady())
            {
                putrsUSBUSART("Button Pressed -- \r\n");
                stringPrinted = TRUE;
            }
        }
    }
    else
    {
        stringPrinted = FALSE;
    }
#endif

	if (RS232_Out_Data_Rdy == 0)  // only check for new USB buffer if the old RS232 buffer is
	{						  // empty.  This will cause additional USB packets to be NAK'd
		LastRS232Out = getsUSBUSART( &RS232_Out_Data[0], 64); //until the buffer is free.
		if(LastRS232Out > 0)
		{	
			RS232_Out_Data_Rdy = 1;  // signal buffer full
			RS232cp = 0;  // Reset the current position
		}
	}

    //Check if one or more bytes are waiting in the physical UART transmit
    //queue.  If so, send it out the UART TX pin.
	if(RS232_Out_Data_Rdy && mTxRdyUSART() && !PIE1bits.TX1IE)
	{
		PIE1bits.TX1IE = 1;    // set Flag to generate interrupt
//		putcUSART(RS232_Out_Data[RS232cp]);
//		++RS232cp;
//		if (RS232cp == LastRS232Out)
//			RS232_Out_Data_Rdy = 0;
	}

//    //Check if we received a character over the physical UART, and we need
//    //to buffer it up for eventual transmission to the USB host.
//	if(mDataRdyUSART() && (NextUSBOut < (CDC_DATA_OUT_EP_SIZE - 1)))
//	{
//		USB_Out_Buffer[NextUSBOut] = getcUSART();
//		++NextUSBOut;
//		USB_Out_Buffer[NextUSBOut] = 0;
//	}
	while ((RS232_In_Head != RS232_In_Tail) && (NextUSBOut < CDC_DATA_OUT_EP_SIZE))
	{
		USB_Out_Buffer[NextUSBOut] = RS232_In_Buffer[RS232_In_Tail];
		++NextUSBOut, RS232_In_Tail++;	// interrupt driven circular buffer
		if ( RS232_In_Tail > RS232_IntRec_Buf )
			RS232_In_Tail = 0;
//		USB_Out_Buffer[NextUSBOut] = 0;
	};

    //Check if the print buffer needs to be sent - one time only so may lose
    //some buffer. Only used in debug mode.
	if(iPrintBufFull)
	{	iIdx = 0;
		while ((NextUSBOut < (CDC_DATA_OUT_EP_SIZE - 1)) && iPrintBufFull)
		{
			USB_Out_Buffer[NextUSBOut] = cPrintBuf[iIdx];
			++NextUSBOut, iIdx++, iPrintBufFull--;
			USB_Out_Buffer[NextUSBOut] = 0;
		};
		iPrintBufFull = 0;
	}

    //Check if any bytes are waiting in the queue to send to the USB host.
    //If any bytes are waiting, and the endpoint is available, prepare to
    //send the USB packet to the host.
	if((USBUSARTIsTxTrfReady()) && (NextUSBOut > 0))
	{
		putUSBUSART(&USB_Out_Buffer[0], NextUSBOut);
		NextUSBOut = 0;
	}

    CDCTxService();
    MSDTasks();    
}//end ProcessIO

/********************************************************************
 * Function:        static BYTE getSDcard(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          return 0 until this cpu has access to SD card
 *					and then returns 1
 *
 * Side Effects:    tells the 33F to close files / flush buffers
 *					and make all its SPI & card power io inputs
 *
 * Overview:        Prepare and turn on SD card power so the 18F can
 *                  use the SD card.
 *
 * Note:            None
 *******************************************************************/
BYTE getSDcard(void)
{
	switch ( SDcard ) {
	case 0:
		if ( !iSDPOWER )			// 33F using card
		{
			tSDSELECT = OUTPUT;		// request SD card
			oSDSELECT = 0;			// by grounding SDSELECT
		}
		SDcard++;
	break;
	case 1:
		if ( iSDPOWER )				// wait till 33F has released card
		{	// do a double check all the IO = 1 pull-down and 3 pull up state
			if ( !SPICLOCKPORT && SPIINPORT && SPIOUTPORT && SD_CS)	// should be like this
			{
				tSDPOWER = OUTPUT;		// re-power card
				oSDPOWER = 0;			// turn the P mosfet on
				SDcard = 2;
				tSDSELECT = INPUT;		// release request line
				oSDSELECT = 1;
			    MDD_SDSPI_InitIO();
				if ( !iPrintBufFull )
				{	
					iPrintBufFull = sprintf( &cPrintBuf[0], "\r\nAquire SD card %d, B %02x = %02x, C %02x = %02x.\r\n", 
						SDcardDelay, TRISB, PORTB, TRISC, PORTC );
				};
			};
		};
	break;
	case 2: // 18F has sd card
	break;
	}
	if ( SDcard == 2 )
		return 1;					// card available
	else return 0;					// card not available
}

/********************************************************************
 * Function:        static BYTE giveSDcard(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          return 1 if this cpu has access to SD card
 *					otherwise returns 0
 *
 * Side Effects:    after a delay releases the SD card to the 33f
 *					and makes all its SPI & card power io inputs
 *
 * Overview:        Turn off SD card power so the 33F can
 *                  use the SD card.
 *
 * Note:            None
 *******************************************************************/
BYTE giveSDcard(void)
{
	switch ( SDcard ) {
	case 0:
	break;
	case 1:
		if ( SDcardDelay == 0 )		// 18F has released card
		{
CARD_FREE:	SDcard = 0;				// technically should not happen so
			SDcardDelay = 0;		// set a 0 delay and
			tSDPOWER = INPUT;		// reset all the IO - un-power card
			oSDPOWER = 1;			// turn the N mosfet on
			tSDSELECT = INPUT;		// release request line
			oSDSELECT = 1;
			SD_CS_TRIS = INPUT;		//Card Select - input
		    SD_CS = 1;				//Initialize Chip Select line
			SPIOUTLAT = 1;
			SPICLOCKLAT = 1;
			SPICLOCK = INPUT;
			SPIOUT = INPUT;			// all inputs
#if defined(__DEBUG)
			if ( !iPrintBufFull )
			{	
				iPrintBufFull = sprintf( &cPrintBuf[0], "\r\nReleased SD card %d, B %02x = %02x, C %02x = %02x.\r\n", 
					SDcardDelay, TRISB, PORTB, TRISC, PORTC );
			};
#endif
		};
	break;
	case 2: // 18F has sd card
		if ( !oSDPOWER )			// 18F has card
		{
			SDcardDelay = 25;		// set a 25ms delay before actually doing it
			SDcard = 1;
#if defined(__DEBUG)
			if ( !iPrintBufFull )
			{	
				iPrintBufFull = sprintf( &cPrintBuf[0], "\r\nRelease SD card %d, B %02x = %02x, C %02x = %02x.\r\n", 
					SDcardDelay, TRISB, PORTB, TRISC, PORTC );
			};
#endif
		} else {					// no delay as 18F not powering card
			goto CARD_FREE;			// technically should not happen
		};
	break;
	}
	if ( SDcard != 0 )
		return 1;					// card used
	else return 0;					// card not used
}

/********************************************************************
 * Function:        static void InitializeSystem(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        InitializeSystem is a centralize initialization
 *                  routine. All required USB initialization routines
 *                  are called from here.
 *
 *                  User application initialization routine should
 *                  also be called from here.                  
 *
 * Note:            None
 *******************************************************************/
static void InitializeSystem(void)
{
    #if (defined(__18CXX) & !defined(PIC18F87J50_PIM))
        ADCON1 |= 0x0F;                 // Default all pins to digital
    #elif defined(__C30__)
        #if defined(PIC24FJ256GB110_PIM) || defined(PIC24F_STARTER_KIT) || defined(PIC24FJ64GB004_PIM)
            AD1PCFGL = 0xFFFF;
        #endif
    #elif defined(__C32__)
        AD1PCFG = 0xFFFF;
    #endif

    #if defined(PIC18F87J50_PIM) || defined(PIC18F46J50_PIM) || defined(PIC18F_STARTER_KIT_1) || defined(PIC18F47J53_PIM) || defined(CUSTOM_PIM)
	//On the PIC18F87J50 Family of USB microcontrollers, the PLL will not power up and be enabled
	//by default, even if a PLL enabled oscillator configuration is selected (such as HS+PLL).
	//This allows the device to power up at a lower initial operating frequency, which can be
	//advantageous when powered from a source which is not gauranteed to be adequate for 48MHz
	//operation.  On these devices, user firmware needs to manually set the OSCTUNE<PLLEN> bit to
	//power up the PLL.
    {
        unsigned int pll_startup_counter = 600;
        OSCTUNEbits.PLLEN = 1;  //Enable the PLL and wait 2+ms until the PLL locks before enabling USB module
        while(pll_startup_counter--);
    }
    //Device switches over automatically to PLL output after PLL is locked and ready.
    #endif

    #if defined(PIC18F87J50_PIM)
	//Configure all I/O pins to use digital input buffers.  The PIC18F87J50 Family devices
	//use the ANCONx registers to control this, which is different from other devices which
	//use the ADCON1 register for this purpose.
    WDTCONbits.ADSHR = 1;			// Select alternate SFR location to access ANCONx registers
    ANCON0 = 0xFF;                  // Default all pins to digital
    ANCON1 = 0xFF;                  // Default all pins to digital
    WDTCONbits.ADSHR = 0;			// Select normal SFR locations
    #endif

    #if defined(PIC18F46J50_PIM) || defined(PIC18F_STARTER_KIT_1) || defined(PIC18F47J53_PIM)
	//Configure all I/O pins to use digital input buffers.  The PIC18F87J50 Family devices
	//use the ANCONx registers to control this, which is different from other devices which
	//use the ADCON1 register for this purpose.
    ANCON0 = 0xFC;                  // Default all pins to digital, low 2 are analog on power board
    ANCON1 = 0x7F;                  // Default all pins to digital
    #endif

    #if defined(CUSTOM_PIM)
	//Configure all I/O pins to use digital input buffers.  The PIC18F87J50 Family devices
	//use the ANCONx registers to control this, which is different from other devices which
	//use the ADCON1 register for this purpose.
    ANCON0 = 0xFC;                  // Default all pins to digital, low 2 are analog on power board
    ANCON1 = 0x1F;                  // Default all pins to digital
    #endif
    
   #if defined(PIC24FJ64GB004_PIM) || defined(PIC24FJ256DA210_DEV_BOARD)
	//On the PIC24FJ64GB004 Family of USB microcontrollers, the PLL will not power up and be enabled
	//by default, even if a PLL enabled oscillator configuration is selected (such as HS+PLL).
	//This allows the device to power up at a lower initial operating frequency, which can be
	//advantageous when powered from a source which is not gauranteed to be adequate for 32MHz
	//operation.  On these devices, user firmware needs to manually set the CLKDIV<PLLEN> bit to
	//power up the PLL.
    {
        unsigned int pll_startup_counter = 600;
        CLKDIVbits.PLLEN = 1;
        while(pll_startup_counter--);
    }

    //Device switches over automatically to PLL output after PLL is locked and ready.
    #endif

   #if defined(DSPIC33EP512MU810_PIM)

    // Configure the device PLL to obtain 60 MIPS operation. The crystal
    // frequency is 8MHz. Divide 8MHz by 2, multiply by 60 and divide by
    // 2. This results in Fosc of 120MHz. The CPU clock frequency is
    // Fcy = Fosc/2 = 60MHz. Wait for the Primary PLL to lock and then
    // configure the auxilliary PLL to provide 48MHz needed for USB 
    // Operation.

	PLLFBD = 58;				/* M  = 60	*/
	CLKDIVbits.PLLPOST = 0;		/* N1 = 2	*/
	CLKDIVbits.PLLPRE = 0;		/* N2 = 2	*/
	OSCTUN = 0;			

    /*	Initiate Clock Switch to Primary
     *	Oscillator with PLL (NOSC= 0x3)*/
	
    __builtin_write_OSCCONH(0x03);		
	__builtin_write_OSCCONL(0x01);
	while (OSCCONbits.COSC != 0x3);       

    // Configuring the auxiliary PLL, since the primary
    // oscillator provides the source clock to the auxiliary
    // PLL, the auxiliary oscillator is disabled. Note that
    // the AUX PLL is enabled. The input 8MHz clock is divided
    // by 2, multiplied by 24 and then divided by 2. Wait till 
    // the AUX PLL locks.

    ACLKCON3 = 0x24C1;   
    ACLKDIV3 = 0x7;
    ACLKCON3bits.ENAPLL = 1;
    while(ACLKCON3bits.APLLCK != 1); 

    #endif


//	The USB specifications require that USB peripheral devices must never source
//	current onto the Vbus pin.  Additionally, USB peripherals should not source
//	current on D+ or D- when the host/hub is not actively powering the Vbus line.
//	When designing a self powered (as opposed to bus powered) USB peripheral
//	device, the firmware should make sure not to turn on the USB module and D+
//	or D- pull up resistor unless Vbus is actively powered.  Therefore, the
//	firmware needs some means to detect when Vbus is being powered by the host.
//	A 5V tolerant I/O pin can be connected to Vbus (through a resistor), and
// 	can be used to detect when Vbus is high (host actively powering), or low
//	(host is shut down or otherwise not supplying power).  The USB firmware
// 	can then periodically poll this I/O pin to know when it is okay to turn on
//	the USB module/D+/D- pull up resistor.  When designing a purely bus powered
//	peripheral device, it is not possible to source current on D+ or D- when the
//	host is not actively providing power on Vbus. Therefore, implementing this
//	bus sense feature is optional.  This firmware can be made to use this bus
//	sense feature by making sure "USE_USB_BUS_SENSE_IO" has been defined in the
//	HardwareProfile.h file.    
    #if defined(USE_USB_BUS_SENSE_IO)
    tris_usb_bus_sense = INPUT_PIN; // See HardwareProfile.h
    #endif
    
//	If the host PC sends a GetStatus (device) request, the firmware must respond
//	and let the host know if the USB peripheral device is currently bus powered
//	or self powered.  See chapter 9 in the official USB specifications for details
//	regarding this request.  If the peripheral device is capable of being both
//	self and bus powered, it should not return a hard coded value for this request.
//	Instead, firmware should check if it is currently self or bus powered, and
//	respond accordingly.  If the hardware has been configured like demonstrated
//	on the PICDEM FS USB Demo Board, an I/O pin can be polled to determine the
//	currently selected power source.  On the PICDEM FS USB Demo Board, "RA2" 
//	is used for	this purpose.  If using this feature, make sure "USE_SELF_POWER_SENSE_IO"
//	has been defined in HardwareProfile.h, and that an appropriate I/O pin has been mapped
//	to it in HardwareProfile.h.
    #if defined(USE_SELF_POWER_SENSE_IO)
    tris_self_power = INPUT_PIN;	// See HardwareProfile.h
    #endif
    
    UserInit();

    //********* Initialize Peripheral Pin Select (PPS) *************************
    //  This section only pertains to devices that have the PPS capabilities.
    //    When migrating code into an application, please verify that the PPS
    //    setting is correct for the port pins that are used in the application.
    #if defined(PIC24FJ256GB110_PIM)
    //Initialize the SPI
    RPINR20bits.SDI1R = 23;
    RPOR7bits.RP15R = 7;
    RPOR0bits.RP0R = 8;    

    //enable a pull-up for the card detect, just in case the SD-Card isn't attached
    //  then lets have a pull-up to make sure we don't think it is there.
    CNPU5bits.CN68PUE = 1; 

    #elif defined(PIC24FJ64GB004_PIM)
    //Initialize the SPI
    RPINR20bits.SDI1R = 17;     //MSDI
    RPOR8bits.RP16R = 7;        //MSDO
    RPOR7bits.RP15R = 8;        //SCK

    //enable a pull-up for the card detect, just in case the SD-Card isn't attached
    //  then lets have a pull-up to make sure we don't think it is there.
    CNPU1bits.CN6PUE = 1; 

    #elif defined(PIC18F46J50_PIM)
    //Initialize the SPI
    //RPINR21bits.SDI2R = 1;
    //RPOR4bits.RP4R = 10;    //RP4 = SCK
    //RPOR2bits.RP2R = 9;     //RP2 = SDO   
    RPINR21 = 6;   //SDI = RP1
    RPOR4 = 10;    //RP4 = SCK
    RPOR2 = 9;     //RP2 = SDO
    RPINR22 = 5;   //SCK = RP4

    //enable a pull-up for the card detect, just in case the SD-Card isn't attached
    //  then lets have a pull-up to make sure we don't think it is there.
    INTCON2bits.RBPU = 0; 

    #elif defined(CUSTOM_PIM)
    //Initialize the SPI
    //RPINR21bits.SDI2R = 1;
    //RPOR4bits.RP4R = 10;    //RP4 = SCK
    //RPOR2bits.RP2R = 9;     //RP2 = SDO   
    RPINR21 = 6;   //PICSDI = RP6 = SD CARD DO
    RPOR5 = 10;    //RP5 = SCK
    RPINR22 = 5;   //RP5 = SCK
    RPOR4 = 9;     //PICSDO = RP4 = SD CARD DI
    RPINR22 = 5;   //SCK = RP10
	T4CONbits.T4OUTPS = T4_PRE_DIV;	// set post devide
	T4CONbits.T4CKPS = 3;			// set pre devide = 16
	PR4 = T4_PRE;					// terminal count
	T4CONbits.TMR4ON = 1;			// turn on timer
	IPR3bits.TMR4IP = 0;			// low priority
	PIE3bits.TMR4IE = 1;			// turn on interrupt
	T3CON = 0x32;					// set pre devide = 8, clk = Fosc/4, 16bit mode
	T3CONbits.TMR3ON = 1;			// turn on timer

    //enable a pull-up for the card detect, just in case the SD-Card isn't attached
    //  then lets have a pull-up to make sure we don't think it is there.
//    INTCON2bits.RBPU = 0; // all signals have hardware pullups

    #endif

#if defined(USE_SD_INTERFACE_WITH_SPI)
//    MDD_SDSPI_InitIO();
#endif

    USBDeviceInit();	//usb_device.c.  Initializes USB module SFRs and firmware
    					//variables to known states.
}//end InitializeSystem



/******************************************************************************
 * Function:        void UserInit(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine should take care of all of the demo code
 *                  initialization that is required.
 *
 * Note:            
 *
 *****************************************************************************/
void UserInit(void)
{
	unsigned char i;
    InitializeUSART();

// 	 Initialize the arrays
	for (i=0; i<sizeof(USB_Out_Buffer); i++)
    {
		USB_Out_Buffer[i] = 0;
    }
	NextUSBOut = 0;
	LastRS232Out = 0;
	lastTransmission = 0;

    //Initialize all of the debouncing variables
    buttonCount = 0;
    buttonPressed = FALSE;
	stringPrinted = FALSE;

#if !defined(CUSTOM_PIM)
	mInitAllLEDs();
    mInitAllSwitches();
#endif
}//end UserInit

/******************************************************************************
 * Function:        void InitializeUSART(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine initializes the UART to 19200
 *
 * Note:            
 *
 *****************************************************************************/
void InitializeUSART(void)
{
    #if defined(__18CXX)
	    unsigned char c;
        #if defined(__18F14K50)
    	    //ANSELHbits.ANS11 = 0;	// Make RB5 digital so USART can use pin for Rx
            ANSELH = 0;
            #ifndef BAUDCON
                #define BAUDCON BAUDCTL
            #endif
        #endif
        UART_TRISRx=1;			// RX
        UART_TRISTx=0;			// TX
        TXSTA = 0x24;       	// TX enable BRGH=1
        RCSTA = 0x90;       	// Single Character RX
        SPBRG = 0x71;
        SPBRGH = 0x02;      	// 0x0271 for 48MHz -> 19200 baud
   		PIE1bits.RC1IE = 1, IPR1bits.RC1IP = 0;	// RX enable low priority
//   		PIE1bits.TX1IE = 1, 
							IPR1bits.TX1IP = 0;	// TX enable low priority
		INTCONbits.PEIE = 1;	// enable interrupt
// ABDOVF RCIDL RXDTP TXCKP BRG16 � WUE ABDEN
        BAUDCON = 0x08;     	// BRG16 = 1
//        BAUDCON = 0x38;     	// BRG16 = 1, TX and RX idle low
        c = RCREG;				// read 
    #endif

    #if defined(__C30__)
        #if defined( __PIC24FJ256GB110__ ) || defined( PIC24FJ256GB210_PIM )
            // PPS - Configure U2RX - put on pin 49 (RP10)
            RPINR19bits.U2RXR = 10;

            // PPS - Configure U2TX - put on pin 50 (RP17)
            RPOR8bits.RP17R = 5;
        #elif defined(__PIC24FJ64GB004__)
            // PPS - Configure U2RX - put on RC3/pin 36 (RP19)
            RPINR19bits.U2RXR = 19;

            // PPS - Configure U2TX - put on RC9/pin 5 (RP25)
            RPOR12bits.RP25R = 5;
        #elif defined(__PIC24FJ256DA210__)
            // PPS - Configure U2RX - put on RC14/pin 74 (RPI37)
            RPINR19bits.U2RXR = 37;
    
            // PPS - Configure U2TX - put on RF3/pin 51 (RP16)
            RPOR8bits.RP16R = 5;

            TRISFbits.TRISF3 = 0;
        #elif defined(__dsPIC33EP512MU810__)
            // The dsPIC33EP512MU810 features Peripheral Pin
            // select. The following statements map UART2 to 
            // device pins which would connect to the the 
            // RX232 transciever on the Explorer 16 board.

             RPINR19 = 0;
             RPINR19 = 0x64;
             RPOR9bits.RP101R = 0x3;

        #else
            #error Verify that any required PPS is done here.
        #endif

        UART2Init();
    #endif

    #if defined(__C32__)
        UART2Init();
    #endif

}//end InitializeUSART

/******************************************************************************
 * Function:        void putcUSART(char c)
 *
 * PreCondition:    None
 *
 * Input:           char c - character to print to the UART
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Print the input character to the UART
 *
 * Note:            
 *
 *****************************************************************************/
void putcUSART(char c)  
{
    #if defined(__18CXX)
	    TXREG = c;
    #else
        UART2PutChar(c);
    #endif
}


/******************************************************************************
 * Function:        void mySetLineCodingHandler(void)
 *
 * PreCondition:    USB_CDC_SET_LINE_CODING_HANDLER is defined
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function gets called when a SetLineCoding command
 *                  is sent on the bus.  This function will evaluate the request
 *                  and determine if the application should update the baudrate
 *                  or not.
 *
 * Note:            
 *
 *****************************************************************************/
#if defined(USB_CDC_SET_LINE_CODING_HANDLER)
void mySetLineCodingHandler(void)
{
    //If the request is not in a valid range
    if(cdc_notice.GetLineCoding.dwDTERate.Val > 2000000)
    {
        //NOTE: There are two ways that an unsupported baud rate could be
        //handled.  The first is just to ignore the request and don't change
        //the values.  That is what is currently implemented in this function.
        //The second possible method is to stall the STATUS stage of the request.
        //STALLing the STATUS stage will cause an exception to be thrown in the 
        //requesting application.  Some programs, like HyperTerminal, handle the
        //exception properly and give a pop-up box indicating that the request
        //settings are not valid.  Any application that does not handle the
        //exception correctly will likely crash when this requiest fails.  For
        //the sake of example the code required to STALL the status stage of the
        //request is provided below.  It has been left out so that this demo
        //does not cause applications without the required exception handling
        //to crash.
        //---------------------------------------
        //USBStallEndpoint(0,1);
    }
    else
    {
        DWORD_VAL dwBaud, dwBaud1, dwError, dwError1, dwRate, dwRate1;
		char cPercent[10];

        //Update the baudrate info in the CDC driver
        CDCSetBaudRate(cdc_notice.GetLineCoding.dwDTERate.Val);
        
        //Update the baudrate of the UART
        #if defined(__18CXX)
            dwBaud.Val = (DWORD)(GetSystemClock()/4)/line_coding.dwDTERate.Val-1;
			dwRate.Val = ((DWORD)(GetSystemClock()/4)/(dwBaud.Val+1));
			dwError.Val = dwRate.Val - line_coding.dwDTERate.Val;
			dwBaud1.Val = ((DWORD)(GetSystemClock()/4)/line_coding.dwDTERate.Val);	// pick next larger to slow more
			dwRate1.Val = ((DWORD)(GetSystemClock()/4)/(dwBaud1.Val+1));
			dwError1.Val = line_coding.dwDTERate.Val - dwRate1.Val;		// make both positive
			if ( dwError.Val > dwError1.Val )	// if error > error1 then use rate1
			{
	            dwBaud.Val = dwBaud1.Val;
				dwRate.Val = dwRate1.Val;
				dwError.Val = dwError1.Val;
				cPercent[9] = '-';
			} else cPercent[0] = ' ';
            SPBRG = dwBaud.v[0];
            SPBRGH = dwBaud.v[1];
#if defined(__DEBUG)
			if ( !iPrintBufFull )
			{	
				dwError.Val *= 10000; // for %
				dwError.Val /= line_coding.dwDTERate.Val; // for %
				sprintf( &cPercent[0], "%04ld", dwError.Val );
				cPercent[4] = cPercent[3], cPercent[3] = cPercent[2], cPercent[2] = '.', cPercent[5] = 0;
				if ( cPercent[0] == '0' )
				{	cPercent[0] = cPercent[1], cPercent[1] = cPercent[2];
					cPercent[2] = cPercent[3], cPercent[3] = cPercent[4], cPercent[4] = 0;
				};
				if ( cPercent[9] == '-' )
				{	cPercent[5] = cPercent[4], cPercent[4] = cPercent[3], cPercent[3] = cPercent[2];
					cPercent[2] = cPercent[1], cPercent[1] = cPercent[0];
					cPercent[0] = '-', cPercent[6] = 0;
				};
				iPrintBufFull = sprintf( &cPrintBuf[0], "\r\nRequest %ld, divisor %ld = %ld baud, %s%% error.\r\n", 
					line_coding.dwDTERate.Val, dwBaud.Val, dwRate.Val, &cPercent[0] );
			};
#endif
        #elif defined(__C30__)
            #if defined(__dsPIC33EP512MU810__)
            dwBaud.Val = ((GetPeripheralClock()+(BRG_DIV2/2*line_coding.dwDTERate.Val))/BRG_DIV2/line_coding.dwDTERate.Val-1);
            #else
            dwBaud.Val = (((GetPeripheralClock()/2)+(BRG_DIV2/2*line_coding.dwDTERate.Val))/BRG_DIV2/line_coding.dwDTERate.Val-1);
            #endif
            U2BRG = dwBaud.Val;
        #elif defined(__C32__)
            U2BRG = ((GetPeripheralClock()+(BRG_DIV2/2*line_coding.dwDTERate.Val))/BRG_DIV2/line_coding.dwDTERate.Val-1);
            //U2MODE = 0;
            U2MODEbits.BRGH = BRGH2;
            //U2STA = 0;
        #endif
    }
}
#endif

/******************************************************************************
 * Function:        unsigned char getcUSART ()
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          unsigned char c - character received on the UART
 *
 * Side Effects:    None
 *
 * Overview:        get a character from the UART
 *
 * Note:            
 *
 *****************************************************************************/
unsigned char getcUSART ()
{
	char  c;

    #if defined(__18CXX)

	if (RCSTAbits.OERR)  // in case of overrun error
	{                    // we should never see an overrun error, but if we do, 
		RCSTAbits.CREN = 0;  // reset the port
		c = RCREG;
		RCSTAbits.CREN = 1;  // and keep going.
	}
	else
		c = RCREG;
// not necessary.  EUSART auto clears the flag when RCREG is cleared
//	PIR1bits.RCIF = 0;    // clear Flag

    #endif

    #if defined(__C30__) || defined(__C32__)
        c = UART2GetChar();
    #endif

	return c;
}

/********************************************************************
 * Function:        void BlinkUSBStatus(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        BlinkUSBStatus turns on and off LEDs 
 *                  corresponding to the USB device state.
 *
 * Note:            mLED macros can be found in HardwareProfile.h
 *                  USBDeviceState is declared and updated in
 *                  usb_device.c.
 *******************************************************************/
void BlinkUSBStatus(void)
{
#if !defined(HARDWARE_PROFILE_CUSTOM_PIM_H)
    static WORD led_count=0;
    
    if(led_count == 0)led_count = 10000U;
    led_count--;

    #define mLED_Both_Off()         {mLED_1_Off();mLED_2_Off();}
    #define mLED_Both_On()          {mLED_1_On();mLED_2_On();}
    #define mLED_Only_1_On()        {mLED_1_On();mLED_2_Off();}
    #define mLED_Only_2_On()        {mLED_1_Off();mLED_2_On();}

    if(USBSuspendControl == 1)
    {
        if(led_count==0)
        {
            mLED_1_Toggle();
            if(mGetLED_1())
            {
                mLED_2_On();
            }
            else
            {
                mLED_2_Off();
            }
        }//end if
    }
    else
    {
        if(USBDeviceState == DETACHED_STATE)
        {
            mLED_Both_Off();
        }
        else if(USBDeviceState == ATTACHED_STATE)
        {
            mLED_Both_On();
        }
        else if(USBDeviceState == POWERED_STATE)
        {
            mLED_Only_1_On();
        }
        else if(USBDeviceState == DEFAULT_STATE)
        {
            mLED_Only_2_On();
        }
        else if(USBDeviceState == ADDRESS_STATE)
        {
            if(led_count == 0)
            {
                mLED_1_Toggle();
                mLED_2_Off();
            }//end if
        }
        else if(USBDeviceState == CONFIGURED_STATE)
        {
            if(led_count==0)
            {
                mLED_1_Toggle();
                if(mGetLED_1())
                {
                    mLED_2_Off();
                }
                else
                {
                    mLED_2_On();
                }
            }//end if
        }//end if(...)
    }//end if(UCONbits.SUSPND...)
#endif //#if !defined(HARDWARE_PROFILE_CUSTOM_PIM_H)
}//end BlinkUSBStatus




// ******************************************************************************************************
// ************** USB Callback Functions ****************************************************************
// ******************************************************************************************************
// The USB firmware stack will call the callback functions USBCBxxx() in response to certain USB related
// events.  For example, if the host PC is powering down, it will stop sending out Start of Frame (SOF)
// packets to your device.  In response to this, all USB devices are supposed to decrease their power
// consumption from the USB Vbus to <2.5mA each.  The USB module detects this condition (which according
// to the USB specifications is 3+ms of no bus activity/SOF packets) and then calls the USBCBSuspend()
// function.  You should modify these callback functions to take appropriate actions for each of these
// conditions.  For example, in the USBCBSuspend(), you may wish to add code that will decrease power
// consumption from Vbus to <2.5mA (such as by clock switching, turning off LEDs, putting the
// microcontroller to sleep, etc.).  Then, in the USBCBWakeFromSuspend() function, you may then wish to
// add code that undoes the power saving things done in the USBCBSuspend() function.

// The USBCBSendResume() function is special, in that the USB stack will not automatically call this
// function.  This function is meant to be called from the application firmware instead.  See the
// additional comments near the function.

/******************************************************************************
 * Function:        void USBCBSuspend(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Call back that is invoked when a USB suspend is detected
 *
 * Note:            None
 *****************************************************************************/
void USBCBSuspend(void)
{
	//Example power saving code.  Insert appropriate code here for the desired
	//application behavior.  If the microcontroller will be put to sleep, a
	//process similar to that shown below may be used:
	
	//ConfigureIOPinsForLowPower();
	//SaveStateOfAllInterruptEnableBits();
	//DisableAllInterruptEnableBits();
	//EnableOnlyTheInterruptsWhichWillBeUsedToWakeTheMicro();	//should enable at least USBActivityIF as a wake source
	//Sleep();
	//RestoreStateOfAllPreviouslySavedInterruptEnableBits();	//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.
	//RestoreIOPinsToNormal();									//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.

	//IMPORTANT NOTE: Do not clear the USBActivityIF (ACTVIF) bit here.  This bit is 
	//cleared inside the usb_device.c file.  Clearing USBActivityIF here will cause 
	//things to not work as intended.	
	

    #if defined(__C30__)
    #if 0
        U1EIR = 0xFFFF;
        U1IR = 0xFFFF;
        U1OTGIR = 0xFFFF;
        IFS5bits.USB1IF = 0;
        IEC5bits.USB1IE = 1;
        U1OTGIEbits.ACTVIE = 1;
        U1OTGIRbits.ACTVIF = 1;
        Sleep();
    #endif
    #endif
}


/******************************************************************************
 * Function:        void _USB1Interrupt(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called when the USB interrupt bit is set
 *					In this example the interrupt is only used when the device
 *					goes to sleep when it receives a USB suspend command
 *
 * Note:            None
 *****************************************************************************/
#if 0
void __attribute__ ((interrupt)) _USB1Interrupt(void)
{
    #if !defined(self_powered)
        if(U1OTGIRbits.ACTVIF)
        {
            IEC5bits.USB1IE = 0;
            U1OTGIEbits.ACTVIE = 0;
            IFS5bits.USB1IF = 0;
        
            //USBClearInterruptFlag(USBActivityIFReg,USBActivityIFBitNum);
            USBClearInterruptFlag(USBIdleIFReg,USBIdleIFBitNum);
            //USBSuspendControl = 0;
        }
    #endif
}
#endif

/******************************************************************************
 * Function:        void USBCBWakeFromSuspend(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The host may put USB peripheral devices in low power
 *					suspend mode (by "sending" 3+ms of idle).  Once in suspend
 *					mode, the host may wake the device back up by sending non-
 *					idle state signalling.
 *					
 *					This call back is invoked when a wakeup from USB suspend 
 *					is detected.
 *
 * Note:            None
 *****************************************************************************/
void USBCBWakeFromSuspend(void)
{
	// If clock switching or other power savings measures were taken when
	// executing the USBCBSuspend() function, now would be a good time to
	// switch back to normal full power run mode conditions.  The host allows
	// a few milliseconds of wakeup time, after which the device must be 
	// fully back to normal, and capable of receiving and processing USB
	// packets.  In order to do this, the USB module must receive proper
	// clocking (IE: 48MHz clock must be available to SIE for full speed USB
	// operation).
}

/********************************************************************
 * Function:        void USBCB_SOF_Handler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USB host sends out a SOF packet to full-speed
 *                  devices every 1 ms. This interrupt may be useful
 *                  for isochronous pipes. End designers should
 *                  implement callback routine as necessary.
 *
 * Note:            None
 *******************************************************************/
void USBCB_SOF_Handler(void)
{
    // No need to clear UIRbits.SOFIF to 0 here.
    // Callback caller is already doing that.

    //This is reverse logic since the pushbutton is active low
#if !defined(CUSTOM_PIM)
    if(buttonPressed == sw2)
    {
        if(buttonCount != 0)
        {
            buttonCount--;
        }
        else
        {
            //This is reverse logic since the pushbutton is active low
            buttonPressed = !sw2;

            //Wait 100ms before the next press can be generated
            buttonCount = 100;
        }
    }
    else
    {
        if(buttonCount != 0)
        {
            buttonCount--;
        }
    }
#endif
}

/*******************************************************************
 * Function:        void USBCBErrorHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The purpose of this callback is mainly for
 *                  debugging during development. Check UEIR to see
 *                  which error causes the interrupt.
 *
 * Note:            None
 *******************************************************************/
void USBCBErrorHandler(void)
{
    // No need to clear UEIR to 0 here.
    // Callback caller is already doing that.

	// Typically, user firmware does not need to do anything special
	// if a USB error occurs.  For example, if the host sends an OUT
	// packet to your device, but the packet gets corrupted (ex:
	// because of a bad connection, or the user unplugs the
	// USB cable during the transmission) this will typically set
	// one or more USB error interrupt flags.  Nothing specific
	// needs to be done however, since the SIE will automatically
	// send a "NAK" packet to the host.  In response to this, the
	// host will normally retry to send the packet again, and no
	// data loss occurs.  The system will typically recover
	// automatically, without the need for application firmware
	// intervention.
	
	// Nevertheless, this callback function is provided, such as
	// for debugging purposes.
}


/*******************************************************************
 * Function:        void USBCBCheckOtherReq(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        When SETUP packets arrive from the host, some
 * 					firmware must process the request and respond
 *					appropriately to fulfill the request.  Some of
 *					the SETUP packets will be for standard
 *					USB "chapter 9" (as in, fulfilling chapter 9 of
 *					the official USB specifications) requests, while
 *					others may be specific to the USB device class
 *					that is being implemented.  For example, a HID
 *					class device needs to be able to respond to
 *					"GET REPORT" type of requests.  This
 *					is not a standard USB chapter 9 request, and 
 *					therefore not handled by usb_device.c.  Instead
 *					this request should be handled by class specific 
 *					firmware, such as that contained in usb_function_hid.c.
 *
 * Note:            None
 *******************************************************************/
void USBCBCheckOtherReq(void)
{
    USBCheckMSDRequest();
    USBCheckCDCRequest();
}//end


/*******************************************************************
 * Function:        void USBCBStdSetDscHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USBCBStdSetDscHandler() callback function is
 *					called when a SETUP, bRequest: SET_DESCRIPTOR request
 *					arrives.  Typically SET_DESCRIPTOR requests are
 *					not used in most applications, and it is
 *					optional to support this type of request.
 *
 * Note:            None
 *******************************************************************/
void USBCBStdSetDscHandler(void)
{
    // Must claim session ownership if supporting this request
}//end


/*******************************************************************
 * Function:        void USBCBInitEP(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called when the device becomes
 *                  initialized, which occurs after the host sends a
 * 					SET_CONFIGURATION (wValue not = 0) request.  This 
 *					callback function should initialize the endpoints 
 *					for the device's usage according to the current 
 *					configuration.
 *
 * Note:            None
 *******************************************************************/
void USBCBInitEP(void)
{
    #if (MSD_DATA_IN_EP == MSD_DATA_OUT_EP)
        USBEnableEndpoint(MSD_DATA_IN_EP,USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    #else
        USBEnableEndpoint(MSD_DATA_IN_EP,USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
        USBEnableEndpoint(MSD_DATA_OUT_EP,USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    #endif

    USBMSDInit();
    CDCInitEP();
}

/********************************************************************
 * Function:        void USBCBSendResume(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USB specifications allow some types of USB
 * 					peripheral devices to wake up a host PC (such
 *					as if it is in a low power suspend to RAM state).
 *					This can be a very useful feature in some
 *					USB applications, such as an Infrared remote
 *					control	receiver.  If a user presses the "power"
 *					button on a remote control, it is nice that the
 *					IR receiver can detect this signalling, and then
 *					send a USB "command" to the PC to wake up.
 *					
 *					The USBCBSendResume() "callback" function is used
 *					to send this special USB signalling which wakes 
 *					up the PC.  This function may be called by
 *					application firmware to wake up the PC.  This
 *					function will only be able to wake up the host if
 *                  all of the below are true:
 *					
 *					1.  The USB driver used on the host PC supports
 *						the remote wakeup capability.
 *					2.  The USB configuration descriptor indicates
 *						the device is remote wakeup capable in the
 *						bmAttributes field.
 *					3.  The USB host PC is currently sleeping,
 *						and has previously sent your device a SET 
 *						FEATURE setup packet which "armed" the
 *						remote wakeup capability.   
 *
 *                  If the host has not armed the device to perform remote wakeup,
 *                  then this function will return without actually performing a
 *                  remote wakeup sequence.  This is the required behavior, 
 *                  as a USB device that has not been armed to perform remote 
 *                  wakeup must not drive remote wakeup signalling onto the bus;
 *                  doing so will cause USB compliance testing failure.
 *                  
 *					This callback should send a RESUME signal that
 *                  has the period of 1-15ms.
 *
 * Note:            This function does nothing and returns quickly, if the USB
 *                  bus and host are not in a suspended condition, or are 
 *                  otherwise not in a remote wakeup ready state.  Therefore, it
 *                  is safe to optionally call this function regularly, ex: 
 *                  anytime application stimulus occurs, as the function will
 *                  have no effect, until the bus really is in a state ready
 *                  to accept remote wakeup. 
 *
 *                  When this function executes, it may perform clock switching,
 *                  depending upon the application specific code in 
 *                  USBCBWakeFromSuspend().  This is needed, since the USB
 *                  bus will no longer be suspended by the time this function
 *                  returns.  Therefore, the USB module will need to be ready
 *                  to receive traffic from the host.
 *
 *                  The modifiable section in this routine may be changed
 *                  to meet the application needs. Current implementation
 *                  temporary blocks other functions from executing for a
 *                  period of ~3-15 ms depending on the core frequency.
 *
 *                  According to USB 2.0 specification section 7.1.7.7,
 *                  "The remote wakeup device must hold the resume signaling
 *                  for at least 1 ms but for no more than 15 ms."
 *                  The idea here is to use a delay counter loop, using a
 *                  common value that would work over a wide range of core
 *                  frequencies.
 *                  That value selected is 1800. See table below:
 *                  ==========================================================
 *                  Core Freq(MHz)      MIP         RESUME Signal Period (ms)
 *                  ==========================================================
 *                      48              12          1.05
 *                       4              1           12.6
 *                  ==========================================================
 *                  * These timing could be incorrect when using code
 *                    optimization or extended instruction mode,
 *                    or when having other interrupts enabled.
 *                    Make sure to verify using the MPLAB SIM's Stopwatch
 *                    and verify the actual signal on an oscilloscope.
 *******************************************************************/
void USBCBSendResume(void)
{
    static WORD delay_count;
    
    //First verify that the host has armed us to perform remote wakeup.
    //It does this by sending a SET_FEATURE request to enable remote wakeup,
    //usually just before the host goes to standby mode (note: it will only
    //send this SET_FEATURE request if the configuration descriptor declares
    //the device as remote wakeup capable, AND, if the feature is enabled
    //on the host (ex: on Windows based hosts, in the device manager 
    //properties page for the USB device, power management tab, the 
    //"Allow this device to bring the computer out of standby." checkbox 
    //should be checked).
    if(USBGetRemoteWakeupStatus() == TRUE) 
    {
        //Verify that the USB bus is in fact suspended, before we send
        //remote wakeup signalling.
        if(USBIsBusSuspended() == TRUE)
        {
            USBMaskInterrupts();
            
            //Clock switch to settings consistent with normal USB operation.
            USBCBWakeFromSuspend();
            USBSuspendControl = 0; 
            USBBusIsSuspended = FALSE;  //So we don't execute this code again, 
                                        //until a new suspend condition is detected.

            //Section 7.1.7.7 of the USB 2.0 specifications indicates a USB
            //device must continuously see 5ms+ of idle on the bus, before it sends
            //remote wakeup signalling.  One way to be certain that this parameter
            //gets met, is to add a 2ms+ blocking delay here (2ms plus at 
            //least 3ms from bus idle to USBIsBusSuspended() == TRUE, yeilds
            //5ms+ total delay since start of idle).
            delay_count = 3600U;        
            do
            {
                delay_count--;
            }while(delay_count);
            
            //Now drive the resume K-state signalling onto the USB bus.
            USBResumeControl = 1;       // Start RESUME signaling
            delay_count = 1800U;        // Set RESUME line for 1-13 ms
            do
            {
                delay_count--;
            }while(delay_count);
            USBResumeControl = 0;       //Finished driving resume signalling

            USBUnmaskInterrupts();
        }
    }
}


/*******************************************************************
 * Function:        void USBCBEP0DataReceived(void)
 *
 * PreCondition:    ENABLE_EP0_DATA_RECEIVED_CALLBACK must be
 *                  defined already (in usb_config.h)
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called whenever a EP0 data
 *                  packet is received.  This gives the user (and
 *                  thus the various class examples a way to get
 *                  data that is received via the control endpoint.
 *                  This function needs to be used in conjunction
 *                  with the USBCBCheckOtherReq() function since 
 *                  the USBCBCheckOtherReq() function is the apps
 *                  method for getting the initial control transfer
 *                  before the data arrives.
 *
 * Note:            None
 *******************************************************************/
#if defined(ENABLE_EP0_DATA_RECEIVED_CALLBACK)
void USBCBEP0DataReceived(void)
{
}
#endif

/*******************************************************************
 * Function:        BOOL USER_USB_CALLBACK_EVENT_HANDLER(
 *                        USB_EVENT event, void *pdata, WORD size)
 *
 * PreCondition:    None
 *
 * Input:           USB_EVENT event - the type of event
 *                  void *pdata - pointer to the event data
 *                  WORD size - size of the event data
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called from the USB stack to
 *                  notify a user application that a USB event
 *                  occured.  This callback is in interrupt context
 *                  when the USB_INTERRUPT option is selected.
 *
 * Note:            None
 *******************************************************************/
BOOL USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, WORD size)
{
    switch(event)
    {
        case EVENT_TRANSFER:
            //Add application specific callback task or callback function here if desired.
            break;
        case EVENT_SOF:
            USBCB_SOF_Handler();
            break;
        case EVENT_SUSPEND:
            USBCBSuspend();
            break;
        case EVENT_RESUME:
            USBCBWakeFromSuspend();
            break;
        case EVENT_CONFIGURED: 
            USBCBInitEP();
            break;
        case EVENT_SET_DESCRIPTOR:
            USBCBStdSetDscHandler();
            break;
        case EVENT_EP0_REQUEST:
            USBCBCheckOtherReq();
            break;
        case EVENT_BUS_ERROR:
            USBCBErrorHandler();
            break;
        case EVENT_TRANSFER_TERMINATED:
            //Add application specific callback task or callback function here if desired.
            //The EVENT_TRANSFER_TERMINATED event occurs when the host performs a CLEAR
            //FEATURE (endpoint halt) request on an application endpoint which was 
            //previously armed (UOWN was = 1).  Here would be a good place to:
            //1.  Determine which endpoint the transaction that just got terminated was 
            //      on, by checking the handle value in the *pdata.
            //2.  Re-arm the endpoint if desired (typically would be the case for OUT 
            //      endpoints).
            break;
        default:
            break;
    }      
    return TRUE; 
}

           
/** EOF main.c ***************************************************************/

