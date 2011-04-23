/*------------------------------------------------------------------------/
/  MMCv3/SDv1/SDv2 (in SPI mode) control module
/-------------------------------------------------------------------------/
/
/  Copyright (C) 2010, ChaN, all right reserved.
/
/ * This software is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial products UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/-------------------------------------------------------------------------*/


#include <p33Fxxxx.h>
#include "diskio.h"
#include "ff.h"
#include "pic33f.h"


/* Definitions for MMC/SDC command */
#define CMD0   (0)			/* GO_IDLE_STATE */
#define CMD1   (1)			/* SEND_OP_COND */
#define ACMD41 (41|0x80)	/* SEND_OP_COND (SDC) */
#define CMD8   (8)			/* SEND_IF_COND */
#define CMD9   (9)			/* SEND_CSD */
#define CMD10  (10)			/* SEND_CID */
#define CMD12  (12)			/* STOP_TRANSMISSION */
#define ACMD13 (13|0x80)	/* SD_STATUS (SDC) */
#define CMD16  (16)			/* SET_BLOCKLEN */
#define CMD17  (17)			/* READ_SINGLE_BLOCK */
#define CMD18  (18)			/* READ_MULTIPLE_BLOCK */
#define CMD23  (23)			/* SET_BLOCK_COUNT */
#define ACMD23 (23|0x80)	/* SET_WR_BLK_ERASE_COUNT (SDC) */
#define CMD24  (24)			/* WRITE_BLOCK */
#define CMD25  (25)			/* WRITE_MULTIPLE_BLOCK */
#define CMD41  (41)			/* SEND_OP_COND (ACMD) */
#define CMD55  (55)			/* APP_CMD */
#define CMD58  (58)			/* READ_OCR */


/* Port Controls  (Platform dependent) */
#define CS_LOW()  SD_CS_LAT = 0	/* MMC CS = L */
#define CS_HIGH() SD_CS_LAT = 1	/* MMC CS = H */

#define SOCKPORT	PORTB		/* Socket contact port */
//#define SOCKWP	(1<<10)		/* Write protect switch (RB10) */
#define SOCKWP	(0)				/* NO Write protect switch */
//#define SOCKINS	(1<<11)		/* Card detect switch (RB11) */
#define SOCKINS	(0)				/* NO Card detect switch */

/* Set slow clock (100k-400k) - @40Mips this gives 104.166 kHz*/
#define	FCLK_SLOW() _SPIEN = 0; SPI1CON1bits.SPRE = 2; SPI1CON1bits.PPRE = 0; _SPIEN = 1;
/* Set fast clock (depends on the CSD)  - @40Mips this gives 10 MHz*/
#define	FCLK_FAST() _SPIEN = 0; SPI1CON1bits.SPRE = 4; SPI1CON1bits.PPRE = 3; _SPIEN = 1;



/*--------------------------------------------------------------------------

   Module Private Functions

---------------------------------------------------------------------------*/

//static 
volatile DSTATUS Stat = (STA_NOINIT | STA_NODISK);	/* Disk status */

//static 
volatile UINT Timer1, Timer2;		/* 1000Hz decrement timer */

// static
UINT CardType;

#if defined(TRACK_spi) && defined(TRACK_diskOP)
#error define EITHER TRACK_spi OR TRACK_diskOP, not both
#endif

//#if defined(__DEBUG)
#if defined(TRACK_spi)
UINT __attribute__ ((near)) spiStat;
UINT __attribute__ ((near)) spiStats[0x40];
#elif defined(TRACK_diskOP)
volatile diskOP diskOPtrack[16];
volatile UINT __attribute__ ((near)) dopStat;
#endif
//#endif

/*-----------------------------------------------------------------------*/
/* Exchange a byte between PIC and MMC via SPI  (Platform dependent)     */
/*-----------------------------------------------------------------------*/

#define xmit_spi(dat) 	xchg_spi(dat)
#define rcvr_spi()		xchg_spi(0xFF)
#define rcvr_spi_m(p)	SPI1BUF = 0xFF; while (!_SPIRBF); *(p) = (BYTE)SPI1BUF;

// attempt to get continious operation and deal with chip errata
//#define rcvr_spi_s()	SPI1BUF = 0xFF; while (!_SPITBF);  while (_SPITBF);
//#define rcvr_spi_e(p)	while (!_SPIRBF); *(p) = (BYTE)SPI1BUF;

static
BYTE xchg_spi (BYTE dat)
{
//	SPI1STATbits.SPIROV = 0;
	SPI1BUF = dat;
	if ( !_SPIEN )
		return (BYTE) 0x24;	// return an R1 error response
	else while (!_SPIRBF);
	return (BYTE)SPI1BUF;
}


/*-----------------------------------------------------------------------*/
/* Wait for card ready                                                   */
/*-----------------------------------------------------------------------*/

static
BYTE wait_ready (void)
{
	BYTE res;
//	BYTE volatile t = 0;

	Timer2 = 500;	/* Wait for ready in timeout of 500ms */
	rcvr_spi();
	do {
		res = rcvr_spi();
//		if ( res != 0xff )
//			t = 1;
	} while ((res != 0xFF) && Timer2);

	Nop();
	return res;
}



/*-----------------------------------------------------------------------*/
/* Deselect the card and release SPI bus                                 */
/*-----------------------------------------------------------------------*/

static
void deselect (void)
{
	CS_HIGH();
	rcvr_spi();
}



/*-----------------------------------------------------------------------*/
/* Select the card and wait ready                                        */
/*-----------------------------------------------------------------------*/

static
int select (void)	/* 1:Successful, 0:Timeout */
{
	CS_LOW();
	if (wait_ready() != 0xFF) {
		deselect();
		return 0;
	}
	return 1;
}



/*-----------------------------------------------------------------------*/
/* Power Control  (Platform dependent)                                   */
/*-----------------------------------------------------------------------*/
/* When the target system does not support socket power control, there   */
/* is nothing to do in these functions and chk_power always returns 1.   */

//static 
void power_on (void)
{
	if ( (oSDPOWER + iSDPOWER + tSDPOWER) || (SDcard == 0) )
	{
		Stat |= (STA_NOINIT | STA_NODISK);		/* Set STA_NOINIT */
		return;					// all those bits should be 0
	} else ;
	SPIOUTLAT = SPIOUTPORT;
	SPIOUT = 0;					// TRIS SDO out
	SPICLOCKLAT = SPICLOCKPORT;
	SPICLOCK = 0;				// TRIS SCK out
	SD_CS_LAT = SD_CS;
	SD_CS_TRIS = 0;				// TRIS CS out
	CS_HIGH();					// make sure its not selected (high)

	/* Enable SPI1 */
	SPI1STAT = 0;
	SPI1CON1 = 0x0128;			// slow speed for card init
	SPI1CON2 = 0x0000;
	_SPIEN = 1;
}

// static
void power_off (void)
{
	if ( getSDcard() && _SPIEN )
	{
		select();			/* Wait for card ready */
		deselect();
	} else {
//		giveSDcard();
	}

	_SPIEN = 0;			/* Disable SPI1 */
	SPIOUT = 1;			// cpu SDO out change to input
	SPICLOCK = 1;		// cpu SCK out change to input
	SD_CS_TRIS = 1;		// cpu CS out change to input
	SPIIN = 1;
	SPIOUTLAT = SPIOUTPORT;
	SPICLOCKLAT = SPICLOCKPORT;
	SD_CS_LAT = SD_CS;

	Stat |= (STA_NOINIT | STA_NODISK);	/* Set STA_NOINIT */
}



/*-----------------------------------------------------------------------*/
/* Receive a data packet from MMC                                        */
/*-----------------------------------------------------------------------*/
#define USE_INT

static
int rcvr_datablock (	/* 1:OK, 0:Failed */
	BYTE *buff,			/* Data buffer to store received data */
	UINT btr			/* Byte count (must be multiple of 4) */
)
{
	BYTE token;

	spiTime();

	Timer1 = 10;
	do {							/* Wait for data packet in timeout of 10ms */
		token = rcvr_spi();
	} while ((token == 0xFF) && Timer1);

	if(token != 0xFE) return 0;		/* If not valid data token, return with error */

	spiTime();

	do {							/* Receive the data block into buffer */
		rcvr_spi_m(buff++);
		rcvr_spi_m(buff++);
		rcvr_spi_m(buff++);
		rcvr_spi_m(buff++);
	} while (btr -= 4);
	rcvr_spi();						/* Discard CRC */
	rcvr_spi();
	return 1;						/* Return with success */
}

#if defined(USE_FAST)

// runs interrupts disabled during transfer
static
int rcvr_datablockFAST (	/* 1:OK, 0:Failed */
	BYTE *buff,			/* Data buffer to store received data */
	UINT btr			/* Byte count (must be multiple of 4) */
)
{
	BYTE token;

	spiTime();

	Timer1 = 10;
	do {							/* Wait for data packet in timeout of 10ms */
		token = rcvr_spi();
	} while ((token == 0xFF) && Timer1);

	if(token != 0xFE) return 0;		/* If not valid data token, return with error */

	spiTime();

#define rcvr_spi_f()	SPI1BUF = 0xFF; while (!_SPITBF);  while (_SPITBF);
//#define rcvr_spi_e()	while (!_SPIRBF); *(p) = (BYTE)SPI1BUF;
#define rcvr_spi_m1(p)	SPI1BUF = 0xFF; while (!_SPIRBF); *(p) = (BYTE)SPI1BUF;
	_DI150();
	rcvr_spi_f();					// start it
	do {							/* Receive the data block into buffer */
		rcvr_spi_m(buff++);
		rcvr_spi_m(buff++);
		_DI150();
		rcvr_spi_m(buff++);
		rcvr_spi_m(buff++);
	} while (btr -= 4);
	while (!_SPIRBF);
	token = (BYTE)SPI1BUF;
	spiTime();
	rcvr_spi();						/* Discard CRC */
//	rcvr_spi();
	return 1;						/* Return with success */
}
#endif

volatile BYTE *intSENDadr __attribute__((near));
volatile BYTE *intRECadr __attribute__((near));
volatile int intCOUNT __attribute__((near));
BYTE intSENDff = 0;

#if defined(USE_INT)
BYTE intBUF[516] __attribute__ ((far,section("Buffers")));

// spi interrupt driven - sucks as it burns ~60% of cpu cycles but at least can run
// interrupts enabled with a few severe restrictions. #1 it uses shadow push and pop
// #2 it has to run priority #7 and NOTHING else can.
static
int rcvr_datablockINT (	/* 1:OK, 0:Failed */
	BYTE *buff,			/* Data buffer to store received data */
	UINT btr			/* Byte count (must be multiple of 4) */
)
{
	BYTE token, sb1, sb2;
	WORD fillCount;

	spiTime();
	if ( intSENDff == 0 )	// prepare send data for a read
	{
		for ( fillCount = 0; fillCount < 512; )
			intBUF[fillCount++] = 0xff;
		intSENDff = 1;
	}

	intSENDadr = &intBUF[0];
	intRECadr = buff;
	intCOUNT = btr;
	IPC2bits.SPI1IP = 7;	// not maskable - it has to run if enabled
	sb1 = *intSENDadr++, intCOUNT--;
	sb2 = *intSENDadr++, intCOUNT--;

	Timer1 = 10;
	do {							/* Wait for data packet in timeout of 10ms */
		token = rcvr_spi();
	} while ((token != 0xFF) && Timer1);
	do {							/* Wait for data packet in timeout of 10ms */
		token = rcvr_spi();
	} while ((token == 0xFF) && Timer1);

	if(token != 0xFE) return 0;		/* If not valid data token, return with error */

	spiTime();
	TMR4 = 0;
	_DI24();
	SPI1BUF = sb1; while (!_SPITBF);  while (_SPITBF); SPI1BUF = sb2; 
	Nop(); Nop();
	IFS0bits.SPI1IF = 0;
	IEC0bits.SPI1IE = 1;
	_EI();

//	while ( (buff + btr) > intRECadr ) ;	// compiler failure
	while ( intCOUNT != -2 ) ;

	IEC0bits.SPI1IE = 0;
	IFS0bits.SPI1IF = 0;
	if ( SPI1STATbits.SPIROV )
	{
		token = (BYTE)SPI1BUF;
		SPI1STATbits.SPIROV = 0;	// must have gotten 2 to get OV
	} else {
		token = (BYTE)SPI1BUF;		// make sure its clear
		SPI1STATbits.SPIROV = 0;
		rcvr_spi();						/* Discard CRC */
		rcvr_spi();
	}
	_EI();
	spiTime();


	return 1;						/* Return with success */
}
#endif

#if defined(USE_DMA)
BYTE dmaSEND[512] __attribute__((space(dma)));
BYTE dmaREC[512] __attribute__((space(dma)));

// DMA bad - can't do back to back - uses 9 SPI clocks / byte at best
static
int rcvr_datablockDMA (	/* 1:OK, 0:Failed */
	BYTE *buff,			/* Data buffer to store received data */
	UINT btr			/* Byte count (must be multiple of 4) */
)
{
	BYTE token;
	WORD dmaDone, dmaLast, dmaSent, fillCount;

	spiTime();

	DMA1CON = 0x4001; // Null Write, one shot, no Ping-Pong,
	// Post-Increment, Periph-to-RAM
	DMA1CNT = btr - 1; // Transfer sector bytes at a time
	DMA1REQ = 0x000A; // Select SPI1 as DMA request source
	DMA1STA = __builtin_dmaoffset(dmaREC);
	DMA1STB = __builtin_dmaoffset(dmaREC);
	DMA1PAD = (volatile unsigned int) &SPI1BUF;
	IFS0bits.DMA1IF = 0;

	DMA0CON = 0x6001; // One shot, no Ping-Pong,
	// Post-Increment, RAM-to-Periph
	DMA0CNT = btr - 1; // Transfer sector bytes at a time (2 are pre-started)
	DMA0REQ = 0x000A; // Select SPI1 as DMA request source
	DMA0STA = __builtin_dmaoffset(dmaSEND);
	DMA0STB = __builtin_dmaoffset(dmaSEND);
	DMA0PAD = (volatile unsigned int) &SPI1BUF;
	IFS0bits.DMA0IF = 0;

	if ( intSENDff == 0 )	// prepare send data for a read
	{
		for ( fillCount = 0; fillCount < 512; )
			dmaSEND[fillCount++] = 0xff;
		intSENDff = 1;
	}

//	IEC0bits.DMA1IE = 1; // Enable DMA interrupt
//	DMA1CONbits.CHEN = 1; // Enable DMA Channel
//	DMA1REQbits.FORCE = 1; // Force First word after Enabling SPI
	Timer1 = 10;
	do {							/* Wait for data packet in timeout of 10ms */
		token = rcvr_spi();
	} while ((token == 0xFF) && Timer1);

	if(token != 0xFE) return 0;		/* If not valid data token, return with error */

	spiTime();

#define rcvr_spi_d()	SPI1BUF = 0xFF; while (!_SPITBF);  while (_SPITBF);
//#define rcvr_spi_e()	while (!_SPIRBF); *(p) = (BYTE)SPI1BUF;
//#define rcvr_spi_m1(p)	SPI1BUF = 0xFF; while (!_SPIRBF); *(p) = (BYTE)SPI1BUF;
#define rcvr_spi_dma(p)	*(p) = (BYTE)dmaREC[dmaDone++];

//	DMA1REQbits.FORCE = 1; // Force First word after Enabling SPI
	dmaDone = 0, dmaSent = 2;
	_DI24();
	rcvr_spi_d();					// start it
	SPI1BUF = 0xFF;
	while (!_SPITBF);
	Nop(); Nop();
	IFS0bits.SPI1IF = 0;
	DMA1CONbits.CHEN = 1; // Enable DMA Channel
	DMA0CONbits.CHEN = 1; // Enable DMA Channel
	for (token = 0; token < 250; token++);
	while ( !IFS0bits.DMA1IF )
	{
//		if ( !_SPITBF )
//			SPI1BUF = 0xFF, dmaSent++;
		dmaLast = DSADR;
		dmaLast--;
		if ( (dmaLast > (WORD)__builtin_dmaoffset(dmaREC)) && (dmaLast < (WORD)__builtin_dmaoffset(dmaREC)+btr) )	// check what buffer
			while ( (dmaLast - (WORD)__builtin_dmaoffset(dmaREC)) > dmaDone )					// check count
				rcvr_spi_dma(buff++);
	};
	while ( dmaDone < btr )					// check count
		rcvr_spi_dma(buff++);

	spiTime();

	while (!_SPIRBF);
	token = (BYTE)SPI1BUF, dmaDone++;

//	if ( dmaDone == dmaSent )
		rcvr_spi(), dmaDone++;				/* Discard CRC */
//	else {
//		while (!_SPIRBF); 
//		token = (BYTE)SPI1BUF, dmaDone++;
//	}
	if ( dmaDone < 514 )
		rcvr_spi();						/* Discard CRC */
	
//	rcvr_spi();
	return 1;						/* Return with success */
}
#endif

/*-----------------------------------------------------------------------*/
/* Send a data packet to MMC                                             */
/*-----------------------------------------------------------------------*/

#if _READONLY == 0
static
int xmit_datablock (	/* 1:OK, 0:Failed */
	const BYTE *buff,	/* 512 byte data block to be transmitted */
	BYTE token			/* Data token */
)
{
	BYTE resp;
	UINT bc = 512;


	if (wait_ready() != 0xFF) return 0;

	xmit_spi(token);		/* Xmit a token */
	if (token != 0xFD) {	/* Not StopTran token */
		do {						/* Xmit the 512 byte data block to the MMC */
			xmit_spi(*buff++);
			xmit_spi(*buff++);
		} while (bc -= 2);
		xmit_spi(0xFF);				/* CRC (Dummy) */
		xmit_spi(0xFF);
		resp = rcvr_spi();			/* Receive a data response */
		if ((resp & 0x1F) != 0x05)	/* If not accepted, return with error */
			return 0;
	}

	return 1;
}
static
#if defined(USE_INT)
int xmit_datablockINT (	/* 1:OK, 0:Failed */
	const BYTE *buff,	/* 512 byte data block to be transmitted */
	BYTE token			/* Data token */
)
{
	BYTE resp, sb1, sb2;
	UINT bc = 512;

	intSENDadr = buff;
	intRECadr = &intBUF[0];
	intCOUNT = bc;
	IPC2bits.SPI1IP = 7;	// not maskable - it has to run if enabled
	sb1 = *intSENDadr++, intCOUNT--;
	sb2 = *intSENDadr++, intCOUNT--;
	intSENDff = 0;	// mark buffer invalid

	if (wait_ready() != 0xFF) return 0;

	xmit_spi(token);		/* Xmit a token */
	if (token != 0xFD) {	/* Not StopTran token */
		_DI24();
		SPI1BUF = sb1; while (!_SPITBF);  while (_SPITBF); SPI1BUF = sb2; 
		Nop(); Nop();
		IFS0bits.SPI1IF = 0;
		IEC0bits.SPI1IE = 1;
		_EI();

		while ( intCOUNT != -2 ) ;	// wait on complete

		IEC0bits.SPI1IE = 0;
		IFS0bits.SPI1IF = 0;
		xmit_spi(0xFF);				/* CRC (Dummy) */
		xmit_spi(0xFF);
		resp = rcvr_spi();			/* Receive a data response */
		if ((resp & 0x1F) != 0x05)	/* If not accepted, return with error */
			return 0;
	}

	return 1;
}
#endif // #if defined(USE_INT)
#endif	/* _READONLY */



/*-----------------------------------------------------------------------*/
/* Send a command packet to MMC                                          */
/*-----------------------------------------------------------------------*/

static
BYTE send_cmd (
	BYTE cmd,		/* Command byte */
	DWORD arg		/* Argument */
)
{
	BYTE n, res;


	if (cmd & 0x80) {	/* ACMD<n> is the command sequense of CMD55-CMD<n> */
		cmd &= 0x7F;
		res = send_cmd(CMD55, 0);
		if (res > 1) return res;
	}

	/* Select the card and wait for ready */
	deselect();
	if (!select()) return 0xFF;

	/* Send command packet */
	xmit_spi(0x40 | cmd);			/* Start + Command index */
	xmit_spi((BYTE)(arg >> 24));	/* Argument[31..24] */
	xmit_spi((BYTE)(arg >> 16));	/* Argument[23..16] */
	xmit_spi((BYTE)(arg >> 8));		/* Argument[15..8] */
	xmit_spi((BYTE)arg);			/* Argument[7..0] */
	n = 0x01;						/* Dummy CRC + Stop */
	if (cmd == CMD0) n = 0x95;		/* Valid CRC for CMD0(0) */
	if (cmd == CMD8) n = 0x87;		/* Valid CRC for CMD8(0x1AA) */
	xmit_spi(n);

	/* Receive command response */
	if (cmd == CMD12) rcvr_spi();	/* Skip a stuff byte when stop reading */
	n = 100;						/* Wait for a valid response in timeout of 10 attempts */
	do
		res = rcvr_spi();
	while ((res & 0x80) && --n);

	return res;			/* Return with the response value */
}



/*--------------------------------------------------------------------------

   Public Functions

---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE drv		/* Physical drive nmuber (0) */
)
{
	BYTE n, cmd, ty, ocr[4];


	if (drv) return STA_NOINIT;			/* Supports only single drive */
	if (Stat & STA_NODISK) return Stat;	/* No card in the socket */
	if (!getSDcard()) return Stat;		/* don't have ownership of card */

	power_on();							/* Force socket power on */
	FCLK_SLOW();
	Timer2 = 2; while ( Timer2 ) ;		/* forced wait */
	for (n = 10; n; n--) rcvr_spi();	/* 80 dummy clocks */
//	Timer2 = 2; while ( Timer2 ) ;		/* forced wait */

	ty = 0;
	if (send_cmd(CMD0, 0) == 1) {			/* Enter Idle state */
		Timer1 = 1000;						/* Initialization timeout of 1000 msec */
		if (send_cmd(CMD8, 0x1AA) == 1) {	/* SDv2? */
			for (n = 0; n < 4; n++) ocr[n] = rcvr_spi();			/* Get trailing return value of R7 resp */
			if (ocr[2] == 0x01 && ocr[3] == 0xAA) {				/* The card can work at vdd range of 2.7-3.6V */
				while (Timer1 && send_cmd(ACMD41, 0x40000000));	/* Wait for leaving idle state (ACMD41 with HCS bit) */
				if (Timer1 && send_cmd(CMD58, 0) == 0) {			/* Check CCS bit in the OCR */
					for (n = 0; n < 4; n++) ocr[n] = rcvr_spi();
					ty = (ocr[0] & 0x40) ? CT_SD2|CT_BLOCK : CT_SD2;	/* SDv2 */
				}
			}
		} else {							/* SDv1 or MMCv3 */
			if (send_cmd(ACMD41, 0) <= 1) 	{
				ty = CT_SD1; cmd = ACMD41;	/* SDv1 */
			} else {
				ty = CT_MMC; cmd = CMD1;	/* MMCv3 */
			}
			while (Timer1 && send_cmd(cmd, 0));		/* Wait for leaving idle state */
			if (!Timer1 || send_cmd(CMD16, 512) != 0)	/* Set read/write block length to 512 */
				ty = 0;
		}
	}
	CardType = ty;
	deselect();

	if (ty) {			/* Initialization succeded */
		Stat &= ~STA_NOINIT;	/* Clear STA_NOINIT */
		FCLK_FAST();
	} else {			/* Initialization failed */
		power_off();
	}

	return Stat;
}



/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0) */
)
{
	if (drv) return STA_NOINIT;		/* Supports only single drive */
	return Stat;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE drv,		/* Physical drive nmuber (0) */
	BYTE *buff,		/* Pointer to the data buffer to store read data */
	DWORD sector,	/* Start sector number (LBA) */
	BYTE count		/* Sector count (1..255) */
)
{
//	int fillCount;

	if (drv || !count) return RES_PARERR;
	if (Stat & STA_NOINIT) return RES_NOTRDY;

	dopTimeS(1);
	if (!(CardType & CT_BLOCK)) sector *= 512;	/* Convert to byte address if needed */

//	TMR5 = 0; spiStat = 0;
	if (count == 1) {		/* Single block read */
		if ((send_cmd(CMD17, sector) == 0)	/* READ_SINGLE_BLOCK */
#if defined(USE_DMA)
			&& rcvr_datablockDMA(buff, 512))
#elif defined(USE_INT)
			&& rcvr_datablockINT(buff, 512))
#elif defined(USE_FAST)
			&& rcvr_datablockFAST(buff, 512))
#else
			&& rcvr_datablock(buff, 512))
#endif
			count = 0;
	}
	else {				/* Multiple block read */
		if (send_cmd(CMD18, sector) == 0) {	/* READ_MULTIPLE_BLOCK */
			do {
#if defined(USE_DMA)
				if (!rcvr_datablockDMA(buff, 512)) break;
#elif defined(USE_INT)
				if (!rcvr_datablockINT(buff, 512)) break;
#elif defined(USE_FAST)
				if (!rcvr_datablockFAST(buff, 512)) break;
#else
				if (!rcvr_datablock(buff, 512)) break;
#endif
				buff += 512;
			} while (--count);
			send_cmd(CMD12, 0);				/* STOP_TRANSMISSION */
			spiTime();
		}
	}
	deselect();
	dopTimeE(1);

	return count ? RES_ERROR : RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _READONLY == 0
DRESULT disk_write (
	BYTE drv,				/* Physical drive nmuber (0) */
	const BYTE *buff,		/* Pointer to the data to be written */
	DWORD sector,			/* Start sector number (LBA) */
	BYTE count				/* Sector count (1..255) */
)
{
	if (drv || !count) return RES_PARERR;
	if (Stat & STA_NOINIT) return RES_NOTRDY;
	if (Stat & STA_PROTECT) return RES_WRPRT;

	dopTimeS(0);
	if (!(CardType & CT_BLOCK)) sector *= 512;	/* Convert to byte address if needed */

//	TMR5 = 0; spiStat = 0;
	if (count == 1) {		/* Single block write */
		if ((send_cmd(CMD24, sector) == 0)	/* WRITE_BLOCK */
			&& xmit_datablock(buff, 0xFE))
			count = 0;
	}
	else {				/* Multiple block write */
		if (CardType & CT_SDC) send_cmd(ACMD23, count);
		if (send_cmd(CMD25, sector) == 0) {	/* WRITE_MULTIPLE_BLOCK */
			do {
				spiTime();
#if defined(USE_INT)
				if (!xmit_datablockINT(buff, 0xFC)) break;
#else
				if (!xmit_datablock(buff, 0xFC)) break;
#endif
				buff += 512;
				spiTime();
			} while (--count);
			if (!xmit_datablock(0, 0xFD))	/* STOP_TRAN token */
				count = 1;
		}
	}
	spiTime();
	deselect();

	spiTime();
	dopTimeE(0);

	return count ? RES_ERROR : RES_OK;
}
#endif /* _READONLY */



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive data block */
)
{
	DRESULT res;
	BYTE n, csd[16], *ptr = buff;
	DWORD csize;


	if (drv) return RES_PARERR;
	if (Stat & STA_NOINIT) return RES_NOTRDY;

	res = RES_ERROR;
	switch (ctrl) {
		case CTRL_SYNC :	/* Flush dirty buffer if present */
			if (select()) {
				deselect();
				res = RES_OK;
			}
			break;

		case GET_SECTOR_COUNT :	/* Get number of sectors on the disk (WORD) */
			if ((send_cmd(CMD9, 0) == 0) && rcvr_datablock(csd, 16)) {
				if ((csd[0] >> 6) == 1) {	/* SDv2? */
					csize = csd[9] + ((WORD)csd[8] << 8) + 1;
					*(DWORD*)buff = (DWORD)csize << 10;
				} else {					/* SDv1 or MMCv2 */
					n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
					csize = (csd[8] >> 6) + ((WORD)csd[7] << 2) + ((WORD)(csd[6] & 3) << 10) + 1;
					*(DWORD*)buff = (DWORD)csize << (n - 9);
				}
				res = RES_OK;
			}
			break;

		case GET_SECTOR_SIZE :	/* Get sectors on the disk (WORD) */
			*(WORD*)buff = 512;
			res = RES_OK;
			break;

		case GET_BLOCK_SIZE :	/* Get erase block size in unit of sectors (DWORD) */
			if (CardType & CT_SD2) {	/* SDv2? */
				if (send_cmd(ACMD13, 0) == 0) {		/* Read SD status */
					rcvr_spi();
					if (rcvr_datablock(csd, 16)) {				/* Read partial block */
						for (n = 64 - 16; n; n--) rcvr_spi();	/* Purge trailing data */
						*(DWORD*)buff = 16UL << (csd[10] >> 4);
						res = RES_OK;
					}
				}
			} else {					/* SDv1 or MMCv3 */
				if ((send_cmd(CMD9, 0) == 0) && rcvr_datablock(csd, 16)) {	/* Read CSD */
					if (CardType & CT_SD1) {	/* SDv1 */
						*(DWORD*)buff = (((csd[10] & 63) << 1) + ((WORD)(csd[11] & 128) >> 7) + 1) << ((csd[13] >> 6) - 1);
					} else {					/* MMCv3 */
						*(DWORD*)buff = ((WORD)((csd[10] & 124) >> 2) + 1) * (((csd[11] & 3) << 3) + ((csd[11] & 224) >> 5) + 1);
					}
					res = RES_OK;
				}
			}
			break;

		case MMC_GET_TYPE :		/* Get card type flags (1 byte) */
			*ptr = CardType;
			res = RES_OK;
			break;

		case MMC_GET_CSD :	/* Receive CSD as a data block (16 bytes) */
			if ((send_cmd(CMD9, 0) == 0)	/* READ_CSD */
				&& rcvr_datablock(buff, 16))
				res = RES_OK;
			break;

		case MMC_GET_CID :	/* Receive CID as a data block (16 bytes) */
			if ((send_cmd(CMD10, 0) == 0)	/* READ_CID */
				&& rcvr_datablock(buff, 16))
				res = RES_OK;
			break;

		case MMC_GET_OCR :	/* Receive OCR as an R3 resp (4 bytes) */
			if (send_cmd(CMD58, 0) == 0) {	/* READ_OCR */
				for (n = 0; n < 4; n++)
					*((BYTE*)buff+n) = rcvr_spi();
				res = RES_OK;
			}
			break;

		case MMC_GET_SDSTAT :	/* Receive SD statsu as a data block (64 bytes) */
			if (send_cmd(ACMD13, 0) == 0) {	/* SD_STATUS */
				rcvr_spi();
				if (rcvr_datablock(buff, 64))
					res = RES_OK;
			}
			break;

		default:
			res = RES_PARERR;
	}

	deselect();

	return res;
}



/*-----------------------------------------------------------------------*/
/* Device Timer Interrupt Procedure  (Platform dependent)                */
/*-----------------------------------------------------------------------*/
/* This function must be called in period of 1ms                         */

void disk_timerproc (void)
{
	static WORD pv;
	WORD p;
//	BYTE s;
	UINT n;


	n = Timer1;						/* 1000Hz decrement timers */
	if (n) Timer1 = --n;
	n = Timer2;
	if (n) Timer2 = --n;
	n = SDcardDelay;
	if (n) SDcardDelay = --n;

#if (SOCKWP + SOCKINS) != 0
	p = pv;
	pv = SOCKPORT & (SOCKWP | SOCKINS);	/* Sample socket switch */

	if (p == pv) {						/* Have contacts stabled? */
		s = Stat;

		if (p & SOCKWP)					/* WP is H (write protected) */
			s |= STA_PROTECT;
		else							/* WP is L (write enabled) */
			s &= ~STA_PROTECT;

		if (p & SOCKINS)				/* INS = H (Socket empty) */
			s |= (STA_NODISK | STA_NOINIT);
		else							/* INS = L (Card inserted) */
			s &= ~STA_NODISK;

		Stat = s;
	}
#else
	p = pv;
	pv = iSDSELECT;						/* Sample socket switch */

	if (p == pv)						/* Have contacts stabled? */
	{
		if ( !iSDSELECT )	// 18 is requesting card
			Stat = Stat | STA_RELEASE;
		else Stat = Stat & (!STA_RELEASE);
	}
	if ( tSDPOWER || oSDPOWER )
		Stat |= (STA_NODISK | STA_NOINIT);

#endif
}

