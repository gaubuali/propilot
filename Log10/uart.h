#ifndef _COMMFUNC
#define _COMMFUNC

#include "integer.h"
#define UART_BUFFER_SIZE 128
typedef struct {
	int		ri, wi, ct;
	BYTE	buff[UART_BUFFER_SIZE];
} UFIFO, *LPUFIFO;
typedef struct {
unsigned int mode:2;			// 0 = not logging, 1 = logging
//unsigned int log1Buff:1;		// use log buffer rather than private buffer
//unsigned int log2Buff:1;		// use log buffer rather than private buffer
//unsigned int log3Buff:1;		// use log buffer rather than private buffer
unsigned int logBuff1xfer:2;	// 0 = private buffers, 1 = log rx, 2 = rx1 -> tx2, 3 = log & xfer
unsigned int logBuff2xfer:2;	// 0 = private buffers, 1 = log rx, 2 = rx1 -> tx2, 3 = log & xfer
unsigned int logBuff3xfer:2;	// TODO: CAN
unsigned int logBuff1Active:4;	// comm1 using this buffer - see log.c
unsigned int logBuff2Active:4;	// comm2 using this buffer - see log.c
		BYTE *log1Next;
		BYTE *log1Last;
		BYTE *log2Next;
		BYTE *log2Last;
} ULOGC, *PULOGC;
typedef struct {
unsigned int status:2;	// = 0 unused and free, 1 = current used, 2 need file system write
unsigned int over:2;	// buffer over run
unsigned int curr:4;	// buffer in use
unsigned int next:4;	// buffer to use next, 15 = invalid
unsigned int last:4;	// buffer to use last, 15 = invalid
	UINT	used;	// used characters
	BYTE	*head;	// pointer to next unused
	BYTE	*end;	// used to copy one buff to another & show end
} BUFC, *PBUFC;

extern BYTE TxRun, Tx2Run;
extern UFIFO volatile __attribute__ ((space(dma))) RxFifo;
extern UFIFO volatile __attribute__ ((space(dma))) TxFifo;
extern UFIFO volatile __attribute__ ((space(dma))) Tx2Fifo;
extern UFIFO volatile __attribute__ ((space(dma))) Rx2Fifo;
extern ULOGC volatile logCtrl;	// default to private buffers
extern BUFC volatile BuffCtrl[8];	// keep track of the 8 buffers (start with 3, split later)


void uart_init (void);
int uart_test (void);
void uart_put (BYTE);
BYTE uart_get (void);
void uart_baud( long );

void uart2_init (void);
int uart2_test (void);
void uart2_put (BYTE);
BYTE uart2_get (void);
void uart2_baud( long );

#define BPS 115200UL

#endif

