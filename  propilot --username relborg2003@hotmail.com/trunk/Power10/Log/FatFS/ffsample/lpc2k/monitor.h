/*------------------------------------------------------------------------*/
/* Universal string handler for user console interface  (C)ChaN, 2010     */
/*------------------------------------------------------------------------*/

#ifndef _STRFUNC
#define _STRFUNC

#define _USE_XFUNC_IN	1
#define _USE_XFUNC_OUT	1
#define	_CR_CRLF		1


#if _USE_XFUNC_OUT
extern void (*xfunc_out)(unsigned char);
void xputc (char);
void xputs (const char*);
void xprintf (const char*, ...);
void put_dump (const void*, unsigned long, int);
#endif

#if _USE_XFUNC_IN
extern unsigned char (*xfunc_in)(void);
int get_line (char*, int);
int xatoi (char**, long*);
#endif

#endif
