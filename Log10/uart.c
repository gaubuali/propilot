#include <p33Fxxxx.h>
#include "monitor.h"
#include "diskio.h"
#include "ff.h"
#include "uart.h"
#include "pic33f.h"

#if !defined(BPS)
#define BPS 		115200UL
#endif
#define SIG_LEVEL 0

// static volatile int TxRun;
BYTE TxRun, Tx2Run;
UFIFO volatile __attribute__ ((space(dma))) RxFifo;
UFIFO volatile __attribute__ ((space(dma))) TxFifo;
UFIFO volatile __attribute__ ((space(dma))) Tx2Fifo;
UFIFO volatile __attribute__ ((space(dma))) Rx2Fifo;
ULOGC volatile logCtrl;	// default to private buffers

//UFIFO volatile __attribute__ ((far,section("Buffers"))) RxFifo;
//UFIFO volatile __attribute__ ((far,section("Buffers"))) TxFifo;
//UFIFO volatile __attribute__ ((far,section("Buffers"))) Tx2Fifo;
//UFIFO volatile __attribute__ ((far,section("Buffers"))) Rx2Fifo;
//UFIFO volatile __attribute__ ((near,section("Important"))) RxFifo;
//UFIFO volatile __attribute__ ((near,section("Important"))) TxFifo;
//UFIFO volatile __attribute__ ((near,section("Important"))) Tx2Fifo;
//UFIFO volatile __attribute__ ((near,section("Important"))) Rx2Fifo;

/* UART Rx interrupt ISR */
void __attribute__((interrupt, auto_psv)) _U1RXInterrupt (void)
{
	BYTE d;

	while ( U1STAbits.URXDA ) {
		d = (BYTE)U1RXREG;
		_U1RXIF = 0;
		if (U1STAbits.OERR) U1STAbits.OERR = 0;
	
		switch ( logCtrl.logBuff1xfer ) {
		case 0:	// private buffer
			RxFifo.buff[RxFifo.wi] = d;
			RxFifo.wi++;
	//		if ( RxFifo.wi >= UART_BUFFER_SIZE )
	//			RxFifo.wi = 0;
			RxFifo.wi &= (UART_BUFFER_SIZE-1);		// only works for power of 2 sizes
		break;
		case 3:	// xfer to other port, does NOT buffer, and log
			U2TXREG = d;
		case 1: // log rx characters
			*logCtrl.log1Next++ = d;
			if ( logCtrl.log1Next > logCtrl.log1Last )			// buffer full so need to mark it and use next one
			{
				BuffCtrl[logCtrl.logBuff1Active].status = 2;	// mark as needing write
				if ( BuffCtrl[logCtrl.logBuff1Active].next == 15 )
				{	// no buffers left, just spin on last character of buffer + mark overflow
					BuffCtrl[logCtrl.logBuff1Active].over = 1;
					logCtrl.log1Next--;
				} else {
					logCtrl.logBuff1Active = BuffCtrl[logCtrl.logBuff1Active].next;
					logCtrl.log1Next = BuffCtrl[logCtrl.logBuff1Active].head;
					logCtrl.log1Last = BuffCtrl[logCtrl.logBuff1Active].end;
					BuffCtrl[logCtrl.logBuff1Active].status = 1;	// mark as in use
				}
			}
		break;
		case 2:	// xfer to other port, does NOT buffer
			U2TXREG = d;
		break;
		}
	}
}

/* UART2 Rx interrupt ISR */
void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt (void)
{
	BYTE d;
	int i;

	while ( U2STAbits.URXDA ) {
		d = (BYTE)U2RXREG;
		_U2RXIF = 0;
		if (U2STAbits.OERR) U2STAbits.OERR = 0;
	
		switch ( logCtrl.logBuff2xfer ) {
		case 0:	// private buffer
			i = Rx2Fifo.ct;
			if (i < UART_BUFFER_SIZE) {
				i++;
				Rx2Fifo.ct = i;
				i = Rx2Fifo.wi;
				Rx2Fifo.buff[i++] = d;
				Rx2Fifo.wi = i % UART_BUFFER_SIZE;
			}
		break;
		case 3:	// xfer to other port, does NOT buffer, and log
			U1TXREG = d;
		case 1: // log rx characters
			*logCtrl.log2Next++ = d;
			if ( logCtrl.log2Next > logCtrl.log2Last )			// buffer full so need to mark it and use next one
			{	// buffer full so need to mark it and use next one
				BuffCtrl[logCtrl.logBuff2Active].status = 2;	// mark as needing write
				if ( BuffCtrl[logCtrl.logBuff2Active].next == 15 )
				{	// no buffers left, just spin on last character of buffer + mark overflow
					BuffCtrl[logCtrl.logBuff2Active].over = 1;
					logCtrl.log2Next--;
				} else {
					logCtrl.logBuff2Active = BuffCtrl[logCtrl.logBuff2Active].next;
					logCtrl.log2Next = BuffCtrl[logCtrl.logBuff2Active].head;
					logCtrl.log2Last = BuffCtrl[logCtrl.logBuff2Active].end;
					BuffCtrl[logCtrl.logBuff2Active].status = 1;	// mark as in use
				}
			}
		break;
		case 2:	// xfer to other port, does NOT buffer
			U1TXREG = d;
		break;
		}
	}
}



/* UART Tx interrupt ISR */
void __attribute__((interrupt, auto_psv)) _U1TXInterrupt (void)
{

	while ( (TxFifo.ri != TxFifo.wi) && !U1STAbits.UTXBF )
	{
		U1TXREG = (unsigned char)TxFifo.buff[TxFifo.ri];
		TxFifo.ri++;
		if ( TxFifo.ri >= UART_BUFFER_SIZE )
			TxFifo.ri = 0;
	}
	if ( TxFifo.ri == TxFifo.wi )
		TxRun = 0;

	_U1TXIF = 0;		/* Clear interrupt flag */

}

/* UART2 Tx interrupt ISR */
void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt (void)
{
	int i;

	i = Tx2Fifo.ct;	/* Number of data in the FIFO */
	if (i) {			/* If any data is available, pop a byte and send it. */
		i--;
		Tx2Fifo.ct = i;
		i = Tx2Fifo.ri;
		U2TXREG = Tx2Fifo.buff[i++];
		Tx2Fifo.ri = i % UART_BUFFER_SIZE;
	} else {			/* No data in the FIFO. Stop transmission. */
		Tx2Run = 0;
	}

	_U2TXIF = 0;		/* Clear interrupt flag */
	
}



/* Check number of bytes in the Rx FIFO */
int uart_test (void)
{
	if ( RxFifo.wi != RxFifo.ri )
		return 1;
	else return 0;
}

/* Check number of bytes in the Rx2 FIFO */
int uart2_test (void)
{
	return Rx2Fifo.ct;
}


/* Get a byte from Rx FIFO */
BYTE uart_get (void)
{
	BYTE d;

// FIX: CAN'T BLOCK HERE
	while (RxFifo.ri == RxFifo.wi) ;		/* Wait while Rx FIFO empty */

	d = RxFifo.buff[RxFifo.ri];
	RxFifo.ri++;
	if ( RxFifo.ri >= UART_BUFFER_SIZE )
		RxFifo.ri = 0;

	return d;
}

/* Get a byte from Rx2 FIFO */
BYTE uart2_get (void)
{
	BYTE d;
	int i;

// FIX: CAN'T BLOCK HERE
	while (!Rx2Fifo.ct) ;		/* Wait while Rx FIFO empty */

	i = Rx2Fifo.ri;			/* Pop a byte from Rx FIFO */
	d = Rx2Fifo.buff[i++];
	Rx2Fifo.ri = i % UART_BUFFER_SIZE;
	_DI();
	Rx2Fifo.ct--;
	_EI();

	return d;
}


/* Put a byte into Tx FIFO */
void uart_put (BYTE d)
{

//	while (TxFifo.ct >= UART_BUFFER_SIZE) ;	/* Wait while Tx FIFO full */

	TxFifo.buff[TxFifo.wi] = d;
	TxFifo.wi++;
	if ( TxFifo.wi >= UART_BUFFER_SIZE )
		TxFifo.wi = 0;

	if (!TxRun) {	/* If Tx is not running, generate 1st Tx interrupt */
		TxRun = 1;
		_U1TXIF = 1;
	}
}

/* Put a byte into Tx2 FIFO */
void uart2_put (BYTE d)
{
	int i;

	while (Tx2Fifo.ct >= UART_BUFFER_SIZE) ;	/* Wait while Tx FIFO full */

	i = Tx2Fifo.wi;		/* Push data into Tx FIFO */
	Tx2Fifo.buff[i++] = d;
	Tx2Fifo.wi = i % UART_BUFFER_SIZE;
	_DI();
	Tx2Fifo.ct++;
	if (!Tx2Run) {	/* If Tx is not running, generate 1st Tx interrupt */
		Tx2Run = 1;
		_U2TXIF = 1;
	}
	_EI();
}

/* Initialize UART module */
void uart_init (void)
{
//	TRISBbits.TRISB9 = 0;		// PTX out, rest inputs
//	LATBbits.LATB9 = !SIG_LEVEL; 

	__builtin_write_OSCCONL(0x0);	// enable writes to RP regs
//	_IOLOCK = 0;
//	_RP9R = 3;		// map RP9 = RB9 = U1TX
//	_U1RXR = 8;		// map RP8 = RB8 = U1RX
//	RPOR1 = 0x0003;		/* U1TX -- RP2 */
//	RPINR18 = 0x1F03;	/* U1RX -- RP3 */
	_U1RXR = 8;			/* U1RX  -- RB8  -- RP8  -- CN22 */
	_RP9R = 3;			/* U1TX  -- RB9  -- RP9  -- CN21 */
	_RP10R = 4;			/* U1RTS -- RB10 -- RP10 -- CN16 */
	_U1CTSR = 11;		/* U1CTS -- RB11 -- RP11 -- CN15 */
	_CN15PUE = 1;		// pull-up on for CTS

	__builtin_write_OSCCONL(0x40);	// set _IOLOCK
//	_IOLOCK = 1;

	/* Disable UART1 Tx/Rx interrupts */
	// configure U2MODE
	U1MODEbits.UARTEN = 0;	// Bit15 TX, RX DISABLED, ENABLE at end of func
	//						// Bit14
	U1MODEbits.USIDL = 0;	// Bit13 Continue in Idle
	U1MODEbits.IREN = 0;	// Bit12 No IR translation
	U1MODEbits.RTSMD = 0;	// Bit11 Simplex Mode
	//						// Bit10
	U1MODEbits.UEN = 0;		// Bits8,9 TX,RX enabled, CTS,RTS not
	U1MODEbits.WAKE = 0;	// Bit7 No Wake up (since we don't sleep here)
	U1MODEbits.LPBACK = 0;	// Bit6 No Loop Back
	U1MODEbits.ABAUD = 0;	// Bit5 No Autobaud (would require sending '55')
	U1MODEbits.URXINV = SIG_LEVEL;	// Bit4 IdleState = 1  (for dsPIC)
	U1MODEbits.BRGH = 1;	// Bit3 4 clocks per bit period
	U1MODEbits.PDSEL = 0;	// Bits1,2 8bit, No Parity
	U1MODEbits.STSEL = 0;	// Bit0 One Stop Bit

	// Load all values in for U1STA SFR
	U1STAbits.UTXISEL1 = 0;	//Bit15 Int when Char is transferred (1/2 config!)
	U1STAbits.UTXINV = SIG_LEVEL;	//Bit14 tx active polarity
	U1STAbits.UTXISEL0 = 1;	//Bit13 Other half of Bit15
	//						//Bit12
	U1STAbits.UTXBRK = 0;	//Bit11 Disabled
	//U1STAbits.UTXEN = 1;	//Bit10 TX pins controlled by periph (handled below)
	//U1STAbits.UTXBF = 0;	//Bit9 *Read Only Bit*
	//U1STAbits.TRMT = 0;	//Bit8 *Read Only bit*
	U1STAbits.URXISEL = 0;	//Bits6,7 Int. on character recieved
	U1STAbits.ADDEN = 0;	//Bit5 Address Detect Disabled
	//U1STAbits.RIDLE = 0;	//Bit4 *Read Only Bit*
	//U1STAbits.PERR = 0;	//Bit3 *Read Only Bit*
	//U1STAbits.FERR = 0;	//Bit2 *Read Only Bit*
	U1STAbits.OERR = 0;		//Bit1 *Read Only Bit*
	//U1STAbits.URXDA = 0;	//Bit0 *Read Only Bit*

	_U1RXIP = 1;	// Low Range Interrupt Priority level, no urgent reason
	_U1TXIP = 1;	// Low Range Interrupt Priority level, no urgent reason

	/* Initialize UART1 */
	U1BRG = (FCY / 4 / BPS) - 1;

	_U1TXIF = 0;	// Clear the Transmit Interrupt Flag
	_U1TXIE = 0;	// Disable Transmit Interrupts
	_U1RXIF = 0;	// Clear the Recieve Interrupt Flag
	_U1RXIE = 0;	// Enable Receive Interrupts

	/* Clear Tx/Rx FIFOs */
	TxFifo.ri = 0; TxFifo.wi = 0; TxFifo.ct = 0;
	RxFifo.ri = 0; RxFifo.wi = 0; RxFifo.ct = 0;
	TxRun = 0;

	U1MODEbits.UARTEN = 1;	// And turn the peripheral on
	U1STAbits.UTXEN = 1;

	/* Enable UART Tx/Rx interruptrs */
	_U1RXIE = 1;
	_U1TXIE = 1;
}

void uart_baud ( long rate )
{
	U1BRG = (FCY / 4 / rate) - 1;
}

/* Initialize UART2 module */
void uart2_init (void)
{
//	TRISBbits.TRISB9 = 0;		// PTX out, rest inputs
//	LATBbits.LATB9 = !SIG_LEVEL; 

	__builtin_write_OSCCONL(0x0);	// enable writes to RP regs
//	_IOLOCK = 0;
//	_U2RXR = 8;			/* U1RX  -- RB8  -- RP8  -- CN22 */
//	_RP9R = 5;			/* U1TX  -- RB9  -- RP9  -- CN21 */
//	_RP10R = 6;			/* U1RTS -- RB10 -- RP10 -- CN16 */
//	_U2CTSR = 11;		/* U1CTS -- RB11 -- RP11 -- CN15 */
//	_CN15PUE = 1;		// pull-up on for CTS
//
	_U2RXR = 3;			/* U2RX  -- RB3  -- RP3  -- CN7 */
	_RP2R = 5;			/* U2TX  -- RB2  -- RP2  -- CN6 */
//	_RP10R = 6;			/* U1RTS -- RB10 -- RP10 -- CN16 */
//	_U2CTSR = 11;		/* U1CTS -- RB11 -- RP11 -- CN15 */
//	_CN15PUE = 1;		// pull-up on for CTS
//
	__builtin_write_OSCCONL(0x40);	// set _IOLOCK
//	_IOLOCK = 1;

	/* Disable UART1 Tx/Rx interrupts */
	// configure U2MODE
	U2MODEbits.UARTEN = 0;	// Bit15 TX, RX DISABLED, ENABLE at end of func
	//						// Bit14
	U2MODEbits.USIDL = 0;	// Bit13 Continue in Idle
	U2MODEbits.IREN = 0;	// Bit12 No IR translation
	U2MODEbits.RTSMD = 0;	// Bit11 Simplex Mode
	//						// Bit10
	U2MODEbits.UEN = 0;		// Bits8,9 TX,RX enabled, CTS,RTS not
	U2MODEbits.WAKE = 0;	// Bit7 No Wake up (since we don't sleep here)
	U2MODEbits.LPBACK = 0;	// Bit6 No Loop Back
	U2MODEbits.ABAUD = 0;	// Bit5 No Autobaud (would require sending '55')
	U2MODEbits.URXINV = SIG_LEVEL;	// Bit4 IdleState = 1  (for dsPIC)
	U2MODEbits.BRGH = 1;	// Bit3 4 clocks per bit period
	U2MODEbits.PDSEL = 0;	// Bits1,2 8bit, No Parity
	U2MODEbits.STSEL = 0;	// Bit0 One Stop Bit

	// Load all values in for U1STA SFR
	U2STAbits.UTXISEL1 = 0;	//Bit15 Int when Char is transferred (1/2 config!)
	U2STAbits.UTXINV = SIG_LEVEL;	//Bit14 N/A, IRDA config
	U2STAbits.UTXISEL0 = 1;	//Bit13 Other half of Bit15
	//						//Bit12
	U2STAbits.UTXBRK = 0;	//Bit11 Disabled
	//U1STAbits.UTXEN = 1;	//Bit10 TX pins controlled by periph (handled below)
	//U1STAbits.UTXBF = 0;	//Bit9 *Read Only Bit*
	//U1STAbits.TRMT = 0;	//Bit8 *Read Only bit*
	U2STAbits.URXISEL = 0;	//Bits6,7 Int. on character recieved
	U2STAbits.ADDEN = 0;	//Bit5 Address Detect Disabled
	//U1STAbits.RIDLE = 0;	//Bit4 *Read Only Bit*
	//U1STAbits.PERR = 0;	//Bit3 *Read Only Bit*
	//U1STAbits.FERR = 0;	//Bit2 *Read Only Bit*
	U2STAbits.OERR = 0;		//Bit1 *Read Only Bit*
	//U1STAbits.URXDA = 0;	//Bit0 *Read Only Bit*

	_U2RXIP = 1;	// Low Range Interrupt Priority level, no urgent reason
	_U2TXIP = 1;	// Low Range Interrupt Priority level, no urgent reason

	/* Initialize UART1 */
	U2BRG = (FCY / 4 / BPS) - 1;

	_U2TXIF = 0;	// Clear the Transmit Interrupt Flag
	_U2TXIE = 0;	// Disable Transmit Interrupts
	_U2RXIF = 0;	// Clear the Recieve Interrupt Flag
	_U2RXIE = 0;	// Enable Receive Interrupts

	/* Clear Tx/Rx FIFOs */
	Tx2Fifo.ri = 0; Tx2Fifo.wi = 0; Tx2Fifo.ct = 0;
	Rx2Fifo.ri = 0; Rx2Fifo.wi = 0; Rx2Fifo.ct = 0;
	Tx2Run = 0;

	U2MODEbits.UARTEN = 1;	// And turn the peripheral on
	U2STAbits.UTXEN = 1;

	/* Enable UART Tx/Rx interruptrs */
	_U2RXIE = 1;
	_U2TXIE = 1;
}

void uart2_baud ( long rate )
{
	U2BRG = (FCY / 4 / rate) - 1;
}

