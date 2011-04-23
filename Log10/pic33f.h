#if !defined(PIC33F_H)
#define PIC33F_H

#include "integer.h"

#define USE_EC_CLOCK

#if defined(USE_EC_CLOCK)
#define FCY		40000000UL
#else
#error
#define FCY		25000000UL
#endif

#define _DI()		__asm__ volatile("disi #0x3FFF")
#define _EI()		__asm__ volatile("disi #0")
#define _DI150()	__asm__ volatile("disi #150")
#define _DI24()		__asm__ volatile("disi #24")
#define _DI64()		__asm__ volatile("disi #64")

#define INPUT 1
#define OUTPUT 0

#define SD_CS			PORTBbits.RB15
#define SD_CS_LAT		LATBbits.LATB15
#define SD_CS_TRIS		TRISBbits.TRISB15
    
/* TRIS pins for the SCK/SDI/SDO lines */
#define SPICLOCK		TRISBbits.TRISB13
#define SPIIN			TRISBbits.TRISB12
#define SPIOUT			TRISBbits.TRISB14

/* Latch pins for SCK/SDI/SDO lines */
#define SPICLOCKLAT		LATBbits.LATB13
#define SPIINLAT		LATBbits.LATB12
#define SPIOUTLAT		LATBbits.LATB14

/* Port pins for SCK/SDI/SDO lines */
#define SPICLOCKPORT	PORTBbits.RB13
#define SPIINPORT		PORTBbits.RB12
#define SPIOUTPORT		PORTBbits.RB14

/* two pins define who has access to the SD card, these are both pulled up
// externally so they are only pulled down by the code in each CPU
// normally the 33 has access so it pulls PSCL1 low and monitors PSDA1
// once it sees PSDA1 go low it closes files, flushes buffers and releases
// PSCL1 indicating the 18f is free to use the card - at this point it will
// also start passing its serial input to uart1.
// CHANGED: now uses just SDSELECT and SDPOWER */
#define tPSCL1	TRISBbits.TRISB6    /* Input */
#define iPSCL1	PORTBbits.RB6
#define tPSDA1	TRISBbits.TRISB5    /* Input / Output */
#define iPSDA1	PORTBbits.RB5
#define oPSDA1	LATBbits.LATB5
/* actual power control on the SD card */
#define tSDPOWER	TRISAbits.TRISA1    /* Input / Output */
#define iSDPOWER	PORTAbits.RA1
#define oSDPOWER	LATAbits.LATA1
#define tSDSELECT	TRISAbits.TRISA4    /* Input / Output */
#define iSDSELECT	PORTAbits.RA4
#define oSDSELECT	LATAbits.LATA4

#define tCanTX	TRISBbits.TRISB7    /* Input / Output */
#define iCanTX	PORTBbits.RB7
#define oCanTX	LATBbits.LATB7
#define pCanTX	CNPU2bits.CN23PUE
#define tCanRX	TRISBbits.TRISB4    /* Input / Output */
#define iCanRX	PORTBbits.RB4
#define oCanRX	LATBbits.LATB4
#define pCanRX	CNPU1bits.CN1PUE

#define BuffSIZE 4096

extern DWORD acc_size;				/* Work register for fs command */
extern WORD acc_files, acc_dirs;
extern FILINFO Finfo;
#if _USE_LFN
extern char __attribute__ ((near,section("Important"))) Lfname[(_MAX_LFN+1)*2];
#endif

extern FATFS __attribute__ ((near,section("Important"))) Fatfs;		/* File system object for each logical drive */
extern BYTE __attribute__ ((far,section("Buffers"))) Buff[BuffSIZE];	/* Working buffer */

extern volatile ULONG Timer;	/* 1kHz increment timer */

extern volatile BYTE rtcYear, rtcMon, rtcMday, rtcHour, rtcMin, rtcSec;

extern volatile BYTE SDcardDelay;
extern volatile BYTE SDcard;
extern volatile BYTE canTXdelay;
extern volatile BYTE canRXdelay;

//char __attribute__ ((near,section("Important"))) Line[128];			/* Console input buffer */
extern FIL __attribute__ ((near,section("Important"))) file1;		/* File objects */
extern FIL __attribute__ ((near,section("Important"))) file2;
extern DIR __attribute__ ((near,section("Important"))) dir;		/* Directory object */

extern void put_rc (FRESULT );
extern FRESULT scan_files(	char* );		/* Pointer to the path name working buffer */

extern const char ini_file[];

#endif
