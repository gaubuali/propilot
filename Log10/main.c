/*---------------------------------------------------------------*/
/* FAT file system module test program            (C)ChaN, 2008  */
/*---------------------------------------------------------------*/

#include <string.h>
// #include <p24FJ64GA002.h>
#include <p33Fxxxx.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "uart.h"
#include "monitor.h"
#include "diskio.h"
#include "ff.h"
#include "miniINI\minIni.h"
#include "pic33f.h"
#include "deviceConfig.h"

DWORD acc_size;				/* Work register for fs command */
WORD acc_files, acc_dirs;
FILINFO Finfo;
#if _USE_LFN
char __attribute__ ((near,section("Important"))) Lfname[(_MAX_LFN+1)*2];
#endif

FATFS __attribute__ ((near,section("Important"))) Fatfs;		/* File system object for each logical drive */
BYTE __attribute__ ((far,section("Buffers"))) Buff[BuffSIZE];	/* Working buffer */

volatile ULONG Timer;	/* 1kHz increment timer */

volatile BYTE rtcYear = (2011-1900), rtcMon = 2, rtcMday = 25, rtcHour, rtcMin, rtcSec;

volatile BYTE SDcardDelay;
volatile BYTE SDcard;
volatile BYTE canTXdelay;
volatile BYTE canRXdelay;

static void IoInit( void );
FRESULT scan_files(	char* );		/* Pointer to the path name working buffer */
void put_rc (FRESULT);
extern void logger1( void );
extern void logger2( void );

/*--------------------------------------------------------------------------*/
/* Monitor                                                                  */

FIL __attribute__ ((near,section("Important"))) file1;		/* File objects */
FIL __attribute__ ((near,section("Important"))) file2;
DIR __attribute__ ((near,section("Important"))) dir;		/* Directory object */

void makeFilename( void )
{
	long num;
	int	dot, len, idx, digit;

	strncpy( (TCHAR *)&Buff[256], (TCHAR *)Buff, 250 );
	num = ini_getl("Settings", "LogNumber", (long) 1, ini_file);
	if ( (num > 500) || (num < 1) ) num = 1;
	ini_putl("Settings", "LogNumber", (long) num+1, ini_file);
	len = strlen( (TCHAR *)Buff ), dot = 0;
	for ( idx = len - 1; (idx > 1) && (dot == 0); idx-- )
	{
		switch ( Buff[idx] )
		{	case '.':	// normal trigger char
				dot = idx;
			break;
			case '\\':	// no . in name before directory sep
			case '/':	// no . in name before directory sep
				dot = len;
			break;
		}
	}
	idx = dot;
	if ( idx <= 2 ) idx = len;
	if ( num >= 100 ) 
		digit = num / 100, num = num - (digit * 100);
	else digit = 0;
	Buff[idx+256] = (BYTE)(digit + '0'), idx++;
	if ( num >= 10 ) 
		digit = num / 10, num = num - (digit * 10);
	else digit = 0;
	Buff[idx+256] = (BYTE)(digit + '0'), idx++;
	digit = num;
	Buff[idx+256] = (BYTE)(digit + '0'), idx++;
	for ( ; dot < len ; idx++, dot++ )
		Buff[idx+256] = Buff[dot];
	Buff[idx+256] = 0;
	strncpy( (TCHAR *)Buff, (TCHAR *)&Buff[256], 250 );
}

/*-----------------------------------------------------------------------*/
/* Main                                                                  */

const char ini_file[] = { "log.ini" };

int main (void)
{
	FRESULT fr = 1;
	BYTE	mode = 'b';			// bypass - just pass through

	IoInit();					// also calls uart_init and uart2_init
	xfunc_in = uart2_get;		/* Default join UART2 and console */
	xfunc_out = uart2_put;
	logCtrl.logBuff1xfer = 2;	// just pass through
	logCtrl.logBuff2xfer = 2;	// just pass through
#if _USE_LFN
	Finfo.lfname = Lfname;
	Finfo.lfsize = sizeof(Lfname);
#endif

	Timer = 0; while ( Timer < 2 );	// let the 18f get the card first in case of usb powered
	getSDcard(), getSDcard(), getSDcard();

	do {
	if ( !getSDcard() )		// try re-power card then issue error
	{
		power_off();
		while ( giveSDcard() ) ;
		Timer = 0; while ( Timer < 2 );
		while ( Timer < 10 ) getSDcard();
		if ( !getSDcard() )
		{
			xputs("\nUnable to access card.\n");
			while ( giveSDcard() ) ;
			Timer = 0; while ( Timer < 2 );
			while ( giveSDcard() ) ;
		};
	} else {
		power_on();
		disk_initialize(0);
		if ( CardType == 0 )
			xputs("\nNo card or not recognized.\n");
		else 
		{
			if ( (fr = f_mount(0, &Fatfs)) )
				put_rc(fr), mode = 'b';
			else 
			{
				Nop();
				while ( Timer < 100 );	// delay a bit for signals to stabilize

				if ( ini_getl("Settings", "Version", (long) 0, ini_file ) < 1 )
				{	// empty / wrong file
					ini_putl("Settings", "Version", (long) 1, ini_file );
					ini_putl("Settings", "CmdPort", (long) 2, ini_file);
					ini_putl("Settings", "LogPort", (long) 1, ini_file);
					ini_puts("Settings", "LogFile", "log.txt", ini_file);
					ini_putl("Settings", "LogNumber", (long) 1, ini_file);
					ini_puts("Settings", "LogType", "overwrite", ini_file);
					ini_puts("Settings", "Mode", "log", ini_file);
					ini_putl("Comm", "UART1", (long) BPS, ini_file );
					ini_putl("Comm", "UART2", (long) BPS, ini_file );
					ini_putl("Comm", "CAN", (long) 1e6, ini_file );
				};
				uart_baud( ini_getl("Comm", "UART1", (long) BPS, ini_file ));
				uart2_baud( ini_getl("Comm", "UART2", (long) BPS, ini_file ));
				// can_baud( ini_getl("Comm", "CAN", (long) CAN_BPS, ini_file ));
				if ( ini_getl("Settings", "CmdPort", (long) 2, ini_file) == 2 )
				{
					xfunc_in = uart2_get;	/* Join UART2 and console */
					xfunc_out = uart2_put;
				} else {
					xfunc_in = uart_get;	/* Join UART1 and console */
					xfunc_out = uart_put;
				}
				if ( mode == 'b' )
				{
					ini_gets("Settings", "Mode", "log", (TCHAR *)Buff, 256, ini_file);
					mode = Buff[0];
				}
				if ( (mode == 'l') && (canRXdelay < 100) )
				{
					ini_gets("Settings", "LogFile", "log.txt", (TCHAR *)Buff, 250, ini_file);
					if ( Buff[0] == 0 ) strncpy( (TCHAR *)Buff, "log.txt", 10 );
					ini_gets("Settings", "LogType", "overwrite", (TCHAR *)&Buff[512], 250, ini_file);
					if ( Buff[512] == 's' )	// sequential overwrite
						makeFilename(), Buff[512] = 'o';
					else ;
					fr = 0;
					if ( ini_getl("Settings", "LogPort", (long) 1, ini_file) == 2 )
						fr = f_open(&file2, (TCHAR *)Buff, (BYTE)(FA_READ | FA_WRITE | FA_CREATE_ALWAYS | FA_OPEN_ALWAYS)); 
					else fr = f_open(&file1, (TCHAR *)Buff, (BYTE)(FA_READ | FA_WRITE | FA_CREATE_ALWAYS | FA_OPEN_ALWAYS)); 
					if ( fr )
						mode = 'c' ;
					else {
						if ( Buff[512] == 'o' )	// overwrite
							f_lseek(&file1, 0L), f_truncate( &file1 );
						else
						if ( Buff[512] == 'a' )	// append
							f_lseek(&file1, file1.fsize);	// append
						else ;
						
						f_sync( &file1 );
					}
				} else // if ( mode == 'l' )
				if ( (canRXdelay > 100) || (canTXdelay > 100) )
				{
					logCtrl.logBuff1xfer = 2;	// just pass through
					logCtrl.logBuff2xfer = 2;	// just pass through
				} else
				if ( (canRXdelay > 100) && (canTXdelay > 100) )
				{
					logCtrl.logBuff1xfer = 0;	// nothing, cmd mode
					logCtrl.logBuff2xfer = 0;	// nothing, cmd mode
				};
			}
		}
	}

	if ( (mode == 'l') && (canRXdelay < 100) && (fr == 0) )	// if these ever return try to flip to other mode
	{
		if ( ini_getl("Settings", "LogPort", (long) 1, ini_file) == 2 )
			logger2(), f_close( &file2 );
		else logger1(), f_close( &file1 );
		power_off();
		while ( giveSDcard() );				// stay here till done
		Timer = 0; while ( Timer < 1000 );	// then wait one full second
		CardType = 0, fr = 1, Stat |= (STA_NODISK | STA_NOINIT);
		// mode = 'c';
	};
	do {
		if ( (mode == 'c') || ((canRXdelay > 100) && (canTXdelay > 100)) )	// if these ever return try to flip to other mode
		{
			logCtrl.logBuff1xfer = 0;	// nothing, cmd mode
			logCtrl.logBuff2xfer = 0;	// nothing, cmd mode
			monitor();
			mode = 'l', canRXdelay = 0, canTXdelay = 0;
		};
		if ( Stat & STA_RELEASE )
		{
			power_off();
			while ( giveSDcard() );				// stay here till done
			Timer = 0; while ( Timer < 1000 );	// then wait one full second
			CardType = 0, fr = 1, Stat |= (STA_NODISK | STA_NOINIT);
		}
	} while ( (canRXdelay > 100) || (canTXdelay > 100) || (!iSDPOWER && oSDPOWER) );
	Timer = 0;
	} while ( 1 );

}
//	for (;;) {
//		if (  !Tx2Run && U2STAbits.TRMT && !(div1k&0xf) )
//		{
//			cnt = (int)((float)U2BRG * 0.001);
//			if ( cnt < 1 )
//				cnt = 1;
//			cnt *= s1;
//			if ( U2BRG > 10 )
//				U2BRG = U2BRG - cnt;
//			else U2BRG = 0x2000;
//			xputs("\0xff\0x55\n0123456789\n");
//			xputs("\n0123456789\n");
//			cnt = rtcSec;
//		}
//		if ( uart2_test() )
//			uart2_put( uart2_get() );
//	}
//

/*---------------------------------------------------------*/
/* 1000Hz timer interrupt generated by Timer1              */
/*---------------------------------------------------------*/

	static UINT div1k;

void __attribute__((interrupt, auto_psv)) _T1Interrupt (void)
{
	static const BYTE samurai[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	BYTE n;


	_T1IF = 0;			/* Clear irq flag */
	Timer++;			/* Performance counter for this module */
	disk_timerproc();	/* Drive timer procedure of low level disk I/O module */
	if ( !iCanTX )
		if ( canTXdelay < 250 ) canTXdelay++; else ;
	else canTXdelay = 0;
	if ( !iCanRX )
		if ( canRXdelay < 250 ) canRXdelay++; else ;
	else canRXdelay = 0;

	/* Real Time Clock */
	if (++div1k >= 1000) {
		div1k = 0;
		if (++rtcSec >= 60) {
			rtcSec = 0;
			if (++rtcMin >= 60) {
				rtcMin = 0;
				if (++rtcHour >= 24) {
					rtcHour = 0;
					n = samurai[rtcMon - 1];
					if ((n == 28) && !(rtcYear & 3)) n++;
					if (++rtcMday > n) {
						rtcMday = 1;
						if (++rtcMon > 12) {
							rtcMon = 1;
							rtcYear++;
						}
					}
				}
			}
		}
	}
}

/*---------------------------------------------------------*/
/* User Provided RTC Function for FatFs module             */
/*---------------------------------------------------------*/
/* This is a real time clock service to be called from     */
/* FatFs module. Any valid time must be returned even if   */
/* the system does not support an RTC.                     */
/* This function is not required in read-only cfg.         */

DWORD get_fattime (void)
{
	DWORD tmr;


	_DI();
	/* Pack date and time into a DWORD variable */
	tmr =	  (((DWORD)rtcYear - 80) << 25)
			| ((DWORD)rtcMon << 21)
			| ((DWORD)rtcMday << 16)
			| (WORD)(rtcHour << 11)
			| (WORD)(rtcMin << 5)
			| (WORD)(rtcSec >> 1);
	_EI();

	return tmr;
}

void __attribute__((interrupt, no_auto_psv)) _DefaultInterrupt (void)
{
	while(1);
}

void put_rc (FRESULT rc)
{
	const char *str =
		"OK\0" "DISK_ERR\0" "INT_ERR\0" "NOT_READY\0" "NO_FILE\0" "NO_PATH\0"
		"INVALID_NAME\0" "DENIED\0" "EXIST\0" "INVALID_OBJECT\0" "WRITE_PROTECTED\0"
		"INVALID_DRIVE\0" "NOT_ENABLED\0" "NO_FILE_SYSTEM\0" "MKFS_ABORTED\0" "TIMEOUT\0"
		"LOCKED\0" "NOT_ENOUGH_CORE\0" "TOO_MANY_OPEN_FILES\0" "UNKNOWN_ERROR\0";
	FRESULT i;

	if ( rc > FR_TOO_MANY_OPEN_FILES )
		rc = FR_TOO_MANY_OPEN_FILES + 1;
	for (i = 0; i != rc && *str; i++) {
		while (*str++) ;
	}
	xprintf("rc=%u FR_%s\n", (UINT)rc, str);
}

FRESULT scan_files (
	char* path		/* Pointer to the path name working buffer */
)
{
	DIR dirs;
	FRESULT res;
	BYTE i;
	char *fn;


	if ((res = f_opendir(&dirs, path)) == FR_OK) {
		i = strlen(path);
		while (((res = f_readdir(&dirs, &Finfo)) == FR_OK) && Finfo.fname[0]) {
			if (_FS_RPATH && Finfo.fname[0] == '.') continue;
#if _USE_LFN
			fn = *Finfo.lfname ? Finfo.lfname : Finfo.fname;
#else
			fn = Finfo.fname;
#endif
			if (Finfo.fattrib & AM_DIR) {
				acc_dirs++;
				*(path+i) = '/'; strcpy(path+i+1, fn);
				res = scan_files(path);
				*(path+i) = '\0';
				if (res != FR_OK) break;
			} else {
/*				xprintf("%s/%s\n", path, fn);	*/
				acc_files++;
				acc_size += Finfo.fsize;
			}
		}
	}

	return res;
}

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
 * Side Effects:    make all card power io outputs
 *
 * Overview:        Prepare and turn on SD card power so the 33F can
 *                  use the SD card.
 *
 * Note:            None
 *******************************************************************/
BYTE getSDcard(void)
{
	switch ( SDcard ) {
	case 0:
		if ( iSDPOWER && iSDSELECT )// check 18F is not using card
		{
			tSDSELECT = OUTPUT;		// request SD card
			oSDSELECT = 0;			// by grounding SDSELECT
			SDcard++;
		} else Stat |= STA_NODISK;
	break;
	case 1:
		if ( iSDPOWER )				// wait till 18F has released card
		{	// do a double check all the IO = 1 pull-down and 3 pull up state
			if ( !SPICLOCKPORT && SPIINPORT && SPIOUTPORT && SD_CS)	// should be like this
			{
				tSDPOWER = OUTPUT;		// re-power card
				oSDPOWER = 0;			// turn the P mosfet on
				SDcard = 2;
				tSDSELECT = INPUT;		// release request line
				oSDSELECT = 1;
				Stat = Stat & (!STA_NODISK);
//			    MDD_SDSPI_InitIO();
//				if ( !iPrintBufFull )
//				{	
//					iPrintBufFull = sprintf( &cPrintBuf[0], "\r\nAquire SD card %d, B %02x = %02x, C %02x = %02x.\r\n", 
//						SDcardDelay, TRISB, PORTB, TRISC, PORTC );
//				};
			};
		};
	break;
	case 2: // 33F has sd card
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
 * Side Effects:    after a delay releases the SD card to the 18f
 *					and makes all its SPI & card power io inputs
 *
 * Overview:        Turn off SD card power so the 18F can
 *                  use the SD card.
 *
 * Note:            None
 *******************************************************************/
BYTE giveSDcard(void)
{
	switch ( SDcard ) {
	case 0:
		Stat |= (STA_NODISK || STA_NOINIT);
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
//#if defined(__DEBUG)
//			if ( !iPrintBufFull )
//			{	
//				iPrintBufFull = sprintf( &cPrintBuf[0], "\r\nReleased SD card %d, B %02x = %02x, C %02x = %02x.\r\n", 
//					SDcardDelay, TRISB, PORTB, TRISC, PORTC );
//			};
//#endif
		};
	break;
	case 2: // 33F has sd card
		if ( !oSDPOWER )			// 33F has card
		{
			SDcardDelay = 250;		// set a 250ms delay before actually doing it - for write
			SDcard = 1;
//#if defined(__DEBUG)
//			if ( !iPrintBufFull )
//			{	
//				iPrintBufFull = sprintf( &cPrintBuf[0], "\r\nRelease SD card %d, B %02x = %02x, C %02x = %02x.\r\n", 
//					SDcardDelay, TRISB, PORTB, TRISC, PORTC );
//			};
//#endif
		} else {					// no delay as 33F not powering card
			goto CARD_FREE;			// technically should not happen
		};
	break;
	}
	if ( SDcard != 0 )
		return 1;					// card used
	else return 0;					// card not used
}


static
void IoInit ()
{
	// change over to 40MHz
	RCONbits.SWDTEN = 0;		// make sure its disabled
	ClrWdt();

#if defined(USE_EC_CLOCK)
	CLKDIVbits.PLLPRE = 1 ;		// pre devide = 3 (12MHz / 3 = 4MHz)
	PLLFBDbits.PLLDIV = 40-2 ; 	// Fvco = 160 MHz (4MHz x 40 = 160Mhz)
	CLKDIVbits.PLLPOST = 0;		// FOSC = Fvco / 2 = 80MHz

// Clock switch to incorporate PLL
	__builtin_write_OSCCONH(0x03);				// Initiate Clock Switch to
												// EC with PLL (NOSC=0b011)
	__builtin_write_OSCCONL(0x01);				// Start clock switching
	while(OSCCONbits.LOCK!=1) {};				// Wait for PLL to lock
	while (OSCCONbits.COSC != 0x03);			// Wait for Clock switch to occur
#else
	OSCTUNbits.TUN = 23;		// boost speed up to 8.00566MHz, FRC = 7.37MHz * 23*0.375%

// Clock switch to incorporate PLL
	__builtin_write_OSCCONH(0x01);				// Initiate Clock Switch to
												// FRC with PLL (NOSC=0b001)
	__builtin_write_OSCCONL(0x01);				// Start clock switching
	while(OSCCONbits.LOCK!=1) {};				// Wait for PLL to lock
	while (OSCCONbits.COSC != 0x01);			// Wait for Clock switch to occur
#endif
	// now running 40mips, 80MHz clock

	/* Initialize GPIO ports */
//	AD1PCFG = 0x1FFF;
	AD1PCFGL = 0xFFFF;	// all digital
//	LATB =  0xD00C;
//	TRISB = 0x1C08;
	LATB =  0xFFFF;
	TRISB = 0xFFFF;		// all inputs
//	LATA =  0x0001;
//	TRISA = 0x0000;
	LATA =  0xFFFF;
	TRISA = 0xFFFF;		// all inputs
//	_CN15PUE = 1;
//	_CN16PUE = 1;

	/* Attach UART1 module to I/O pads done in uart.c */
	__builtin_write_OSCCONL(0x00);			// do the port remaps

	/* Attach SPI1 module to I/O pads */
//	RPINR20 = 0x1F0C;	/* SDI1 -- RP12 */
//	RPOR6 = 0x0800;		/* SCK1OUT -- RP13 */
//	RPOR7 = 0x0007;		/* SDO1 -- RP14 */
	_SDI1R = 12;		/* SDI1  -- RB12 -- RP12 -- CN14 */
	_RP14R = 7;			/* SDO1  -- RB14 -- RP14 -- CN12 */
	_RP13R = 8;			/* SCK1  -- RB13 -- RP13 -- CN13 */

	tCanTX = 1, pCanTX = 1;	/* make input and enable pullup */
	tCanRX = 1, pCanRX = 1;	/* make input and enable pullup */

	/* Start Timer1 in interval time of 1ms */
	PR1 = FCY / 8 / 1000;
	_TCKPS0 = 1;	/* Select prescaler Fcy/8 */
	_TON = 1;		/* Start Timer1 */
	_T1IE = 1;		/* Enable Timer1 interrupt */

	_EI();
	T5CON = 0xc010; T4CON = 0xc000;
	T3CON = 0, T2CON = 0x30, TMR3 = 0, TMR2 = 0;
	PR2 = 0xffff, PR3 = 0xffff;
	T2CONbits.T32 = 1;	// Start in 32-bit Timer2/3 operation
	T2CONbits.TON = 1;	// free running at Tcy - no interrupts
	RCON = 0;

	uart_init();	/* Initialize UART driver */
	uart2_init();	/* Initialize UART driver */

//	_LATA0 = 0;		/* LED ON */
}


