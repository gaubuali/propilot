#include "LPC2300.h"
#include "interrupt.h"
#include "uart.h"


#define BUFFER_SIZE 128

#define PCLK		18000000
#define BPS 		230400
#define	DIVADDVAL	5
#define	MULVAL		8
#define	DLVAL		((int)((double)PCLK / BPS / 16 / (1 + (double)DIVADDVAL / MULVAL)))


static volatile int TxRun;
static volatile struct {
	int		ri, wi, ct;
	BYTE	buff[BUFFER_SIZE];
} TxFifo, RxFifo;




void Isr_UART0 (void)
{
	int d, i, cnt, iir;


	for (;;) {
		iir = U0IIR;			/* Get Interrupt ID*/
		if (iir & 1) break;		/* Exit if there is no interrupt */
		switch (iir & 6) {
		case 4:			/* Receive FIFO is half filled or timeout occured */
			i = RxFifo.wi;
			cnt = RxFifo.ct;
			while (U0LSR & 0x01) {			/* Receive all data in the FIFO */
				d = U0RBR;
				if (cnt < BUFFER_SIZE) {	/* Store data if buffer is not full */
					RxFifo.buff[i++] = d;
					i %= BUFFER_SIZE;
					cnt++;
				}
			}
			RxFifo.wi = i;
			RxFifo.ct = cnt;
			break;

		case 2:			/* Transmisson FIFO empty */
			cnt = TxFifo.ct;
			if (cnt) {
				i = TxFifo.ri;
				for (d = 12; d && cnt; d--, cnt--) {	/* Store data into FIFO (max 12 chrs) */
					U0THR = TxFifo.buff[i++];
					i %= BUFFER_SIZE;
				}
				TxFifo.ri = i;
				TxFifo.ct = cnt;
			} else {
				TxRun = 0;				/* When no data in the buffer, clear running flag */
			}
			break;

		default:		/* Data error or break detected */
			d = U0LSR;
			d = U0RBR;
			break;
		}
	}
}




int uart0_test (void)
{
	return RxFifo.ct;
}




BYTE uart0_get (void)
{
	BYTE d;
	int i;

	/* Wait while Rx buffer is empty */
	while (!RxFifo.ct) ;

	U0IER = 0;				/* Disable interrupts */
	i = RxFifo.ri;
	d = RxFifo.buff[i++];	/* Get a byte from Rx buffer */
	RxFifo.ri = i % BUFFER_SIZE;
	RxFifo.ct--;
	U0IER = 0x07;			/* Enable interrupt */

	return d;
}




void uart0_put (BYTE d)
{
	int i;

	/* Wait for buffer ready */
	while (TxFifo.ct >= BUFFER_SIZE) ;

	U0IER = 0x05;		/* Disable Tx Interrupt */
	if (!TxRun) {		/* When not in runnig, trigger transmission */
		U0THR = d;
		TxRun = 1;
	} else {			/* When transmission is runnig, store the data into the Tx buffer */
		i = TxFifo.wi;
		TxFifo.buff[i++] = d;
		TxFifo.wi = i % BUFFER_SIZE;
		TxFifo.ct++;
	}
	U0IER = 0x07;		/* Enable Tx Interrupt */
}




void uart0_init (void)
{
	U0IER = 0x00;
	RegisterIrq(UART0_INT, Isr_UART0, PRI_LOWEST);

	/* Attach UART0 unit to I/O pad */
	PINSEL0 = (PINSEL0 & 0xFFFFFF0F) | 0x50;

	/* Initialize UART0 */
	U0LCR = 0x83;			/* Select divisor latch */
	U0DLM = DLVAL / 256;	/* Initialize BRG */
	U0DLL = DLVAL % 256;
	U0FDR = (MULVAL << 4) | DIVADDVAL;
	U0LCR = 0x03;			/* Set serial format N81 and deselect divisor latch */
	U0FCR = 0x87;			/* Enable FIFO */
	U0TER = 0x80;			/* Enable Tansmission */

	/* Clear Tx/Rx FIFOs */
	TxFifo.ri = 0; TxFifo.wi = 0; TxFifo.ct = 0;
	RxFifo.ri = 0; RxFifo.wi = 0; RxFifo.ct = 0;

	/* Enable Tx/Rx/Error interrupts */
	U0IER = 0x07;
}


