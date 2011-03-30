#include <string.h>
// #include <p24FJ64GA002.h>
#include <p33Fxxxx.h>
#include "diskio.h"
#include "ff.h"
#include "uart.h"
#include "pic33f.h"
#include "miniINI\minIni.h"

#define BUFF2_SIZE 8192

//UINT BuffCtrl[3][4] = { 0 };	// buffer controls
// [x][0] used BYTES, [x][1] head, [x][2] tail, [x][3] status
// status = 0 unused and free, 1 = current used, 2 in file system write
// [0][x] file system buffer, ie Buff
// [1][x] 1st half stack buffer in log(), ie BuffS[0]->BuffS[4095]
// [2][x] 2nd half stack buffer in log(), ie BuffS[4096]->BuffS[8192]
// 

BUFC volatile BuffCtrl[8];	// keep track of the 8 buffers (start with 3, split later)

UINT write_buffer1( UINT idx, UINT *written )
{
	UINT count, countw;
	BYTE *wBuff = &Buff[0];

	switch ( idx ) {
	case 0:
		wBuff = BuffCtrl[0].head;				// start of buffer
		if ( logCtrl.logBuff1Active != 0 )		// if its not active its fully used
			count = (UINT)(BuffCtrl[0].end - BuffCtrl[0].head)+1;
		else count = (UINT)(logCtrl.log1Next - BuffCtrl[0].head);
	break;
	case 1:
		wBuff = BuffCtrl[1].head;				// start of buffer
		if ( logCtrl.logBuff1Active != 1 )		// if its not active its fully used
			count = (UINT)(BuffCtrl[1].end - BuffCtrl[1].head)+1;
		else count = (UINT)(logCtrl.log1Next - BuffCtrl[1].head);
	break;
	case 2:
		wBuff = BuffCtrl[2].head;				// start of buffer
		if ( logCtrl.logBuff1Active != 2 )		// if its not active its fully used
			count = (UINT)(BuffCtrl[2].end - BuffCtrl[2].head)+1;
		else count = (UINT)(logCtrl.log1Next - BuffCtrl[2].head);
	break;
	default:
		count = 0;
	break;			};
	if ( count > 0 ) f_write(&file1, wBuff, (WORD)count, &countw), *written += count / 512;
	switch ( idx ) {
	case 0:
		BuffCtrl[2].next = 0, BuffCtrl[0].next = 15;
		BuffCtrl[0].status = 0, idx++;
	break;
	case 1:
		BuffCtrl[0].next = 1, BuffCtrl[1].next = 15;
		BuffCtrl[1].status = 0, idx++;
	break;
	case 2:
		BuffCtrl[1].next = 2, BuffCtrl[2].next = 15;
		BuffCtrl[2].status = 0, idx = 0;
	break;
	default:
		idx = 0;
	break;			};
	return idx;
}

void logger1( void )
{
	BYTE BuffS[BUFF2_SIZE];
	UINT idx, count, written;
	volatile BYTE mode = 1;

	BuffCtrl[0].used = 0, BuffCtrl[0].status = 1;
	BuffCtrl[0].head = &Buff[0], BuffCtrl[0].end = &Buff[(sizeof(Buff)-1)];
	BuffCtrl[0].next = 1, BuffCtrl[0].curr = 0;

	BuffCtrl[1].used = 0, BuffCtrl[1].status = 0;
	BuffCtrl[1].head = &BuffS[0], BuffCtrl[1].end = &BuffS[0]+((BUFF2_SIZE/2)-1);
	BuffCtrl[1].next = 2, BuffCtrl[1].curr = 1;
	
	BuffCtrl[2].used = 0, BuffCtrl[2].status = 0;
	BuffCtrl[2].head = &BuffS[0]+(BUFF2_SIZE/2), BuffCtrl[2].end = &BuffS[0]+(BUFF2_SIZE-1);
	BuffCtrl[2].next = 15, BuffCtrl[2].curr = 2;

	for ( count = 3; count < 8; count++ ) // init unused buffers in case of error
	{
		BuffCtrl[count].used = 3, BuffCtrl[count].status = 0;
		BuffCtrl[count].head = BuffCtrl[count].end = (BYTE *) &BuffCtrl[count].used;
		BuffCtrl[count].next = 15, BuffCtrl[count].curr = count;
	}

	logCtrl.logBuff1Active = 0;	// start logging on port 1
	logCtrl.log1Next = BuffCtrl[logCtrl.logBuff1Active].head;
	logCtrl.log1Last = BuffCtrl[logCtrl.logBuff1Active].end;

	logCtrl.logBuff1xfer = 3;	// start logging on port 1
	logCtrl.logBuff2xfer = 2;	// just pass through
	idx = count = written = 0;	// start monitor on first buffer

	do {
		if ( BuffCtrl[idx].status == 2 )		// buffer filled, write it
		{	idx = write_buffer1( idx, &written );
			if ( BuffCtrl[idx].status != 2 && (written >= Fatfs.csize) )
				f_sync( &file1 ), written &= (Fatfs.csize - 1);
		} else ;
		if ( (Stat & STA_RELEASE) || (canRXdelay > 100) )	// 18f requesting card
		{
			if ( logCtrl.logBuff1xfer & 1 )	// in log mode
			{
				count = 0xffff;					// max delay
				logCtrl.logBuff1xfer &= 2;		// turn off log
				idx = write_buffer1( idx, &written );
				if ( BuffCtrl[idx].status != 0 )
					idx = write_buffer1( idx, &written );
				if ( BuffCtrl[idx].status != 0 )
					idx = write_buffer1( idx, &written );
				mode = 0;
			};
		} else
		if ( !(Stat & STA_RELEASE) && !count && iSDPOWER )	// request card
			getSDcard();
		else 
		if ( count ) count--;			// forced delay

	} while ( mode );
}

UINT write_buffer2( UINT idx, UINT *written  )
{
	UINT count, countw;
	BYTE *wBuff = &Buff[0];

	switch ( idx ) {
	case 4:
		wBuff = BuffCtrl[4].head;				// start of buffer
		if ( logCtrl.logBuff2Active != 4 )		// if its not active its fully used
			count = (UINT)(BuffCtrl[4].end - BuffCtrl[4].head)+1;
		else count = (UINT)(logCtrl.log2Next - BuffCtrl[4].head);
	break;
	case 5:
		wBuff = BuffCtrl[5].head;				// start of buffer
		if ( logCtrl.logBuff2Active != 5 )		// if its not active its fully used
			count = (UINT)(BuffCtrl[5].end - BuffCtrl[5].head)+1;
		else count = (UINT)(logCtrl.log2Next - BuffCtrl[5].head);
	break;
	case 6:
		wBuff = BuffCtrl[6].head;				// start of buffer
		if ( logCtrl.logBuff1Active != 6 )		// if its not active its fully used
			count = (UINT)(BuffCtrl[6].end - BuffCtrl[6].head)+1;
		else count = (UINT)(logCtrl.log2Next - BuffCtrl[6].head);
	break;
	default:
		count = 0;
	break;			};
	if ( count > 0 ) f_write(&file2, wBuff, (WORD)count, &countw), *written += count / 512;
	switch ( idx ) {
	case 4:
		BuffCtrl[6].next = 4, BuffCtrl[4].next = 15;
		BuffCtrl[4].status = 0, idx++;
	break;
	case 5:
		BuffCtrl[4].next = 5, BuffCtrl[5].next = 15;
		BuffCtrl[5].status = 0, idx++;
	break;
	case 6:
		BuffCtrl[5].next = 6, BuffCtrl[6].next = 15;
		BuffCtrl[6].status = 0, idx = 4;
	break;
	default:
		idx = 4;
	break;			};
	return idx;
}

void logger2( void )
{
	BYTE BuffS[BUFF2_SIZE];
	UINT idx, count, written;
	volatile BYTE mode = 1;

	BuffCtrl[4].used = 0, BuffCtrl[4].status = 1;
	BuffCtrl[4].head = &Buff[4], BuffCtrl[4].end = &Buff[(sizeof(Buff)-1)];
	BuffCtrl[4].next = 5, BuffCtrl[4].curr = 4;

	BuffCtrl[5].used = 0, BuffCtrl[5].status = 0;
	BuffCtrl[5].head = &BuffS[0], BuffCtrl[5].end = &BuffS[0]+((BUFF2_SIZE/2)-1);
	BuffCtrl[5].next = 6, BuffCtrl[5].curr = 5;
	
	BuffCtrl[6].used = 0, BuffCtrl[6].status = 0;
	BuffCtrl[6].head = &BuffS[0]+(BUFF2_SIZE/2), BuffCtrl[6].end = &BuffS[0]+(BUFF2_SIZE-1);
	BuffCtrl[6].next = 15, BuffCtrl[6].curr = 6;

	for ( count = 0; count < 4; count++ ) // init unused buffers in case of error
	{
		BuffCtrl[count].used = 3, BuffCtrl[count].status = 0;
		BuffCtrl[count].head = BuffCtrl[count].end = (BYTE *) &BuffCtrl[count].used;
		BuffCtrl[count].next = 15, BuffCtrl[count].curr = count;
	}

	logCtrl.logBuff2Active = 4;	// start logging on port 2
	logCtrl.log2Next = BuffCtrl[logCtrl.logBuff2Active].head;
	logCtrl.log2Last = BuffCtrl[logCtrl.logBuff2Active].end;

	logCtrl.logBuff2xfer = 3;	// start logging on port 2
	logCtrl.logBuff1xfer = 2;	// just pass through
	idx = 4, count = written = 0;	// start monitor on first buffer

	do {
		if ( BuffCtrl[idx].status == 2 )		// buffer filled, write it
		{	idx = write_buffer2( idx, &written );
			if ( BuffCtrl[idx].status != 2 && (written >= Fatfs.csize) )
				f_sync( &file2 ), written &= (Fatfs.csize - 1);
		} else ;
		if ( (Stat & STA_RELEASE) || (canRXdelay > 100) )	// 18f requesting card
		{
			if ( logCtrl.logBuff2xfer & 1 )	// in log mode
			{
				count = 0xffff;					// max delay
				logCtrl.logBuff2xfer &= 2;		// turn off log
				idx = write_buffer2( idx, &written );
				if ( BuffCtrl[idx].status != 0 )
					idx = write_buffer2( idx, &written );
				if ( BuffCtrl[idx].status != 0 )
					idx = write_buffer2( idx, &written );
				mode = 0;
			};
		} else
		if ( !(Stat & STA_RELEASE) && !count && iSDPOWER )	// request card
			getSDcard();
		else 
		if ( count ) count--;			// forced delay

	} while ( mode );
}


//	DMA2CON = 0x4002; // Continuous, Ping-Pong, Post-Inc., Periph-RAM
//	DMA2CNT = ((UART_BUFFER_SIZE/2)-1); // split buffer for DMA requests
//	DMA2REQ = 0x001E; // Select UART2 Receiver
//	DMA2PAD = (volatile unsigned int) &U2RXREG;
//	DMA2STA = __builtin_dmaoffset(Rx2Fifo.buff);
//	DMA2STB = __builtin_dmaoffset(Rx2Fifo.buff+(UART_BUFFER_SIZE/2));
//	IFS1bits.DMA2IF = 0; // Clear DMA interrupt
//	IEC1bits.DMA2IE = 1; // Enable DMA interrupt
//	DMA2CONbits.CHEN = 1; // Enable DMA Channel

