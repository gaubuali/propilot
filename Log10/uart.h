#ifndef _COMMFUNC
#define _COMMFUNC

#include "integer.h"

void uart_init (void);
int uart_test (void);
void uart_put (BYTE);
BYTE uart_get (void);

void uart2_init (void);
int uart2_test (void);
void uart2_put (BYTE);
BYTE uart2_get (void);
#endif

