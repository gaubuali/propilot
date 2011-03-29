/*------------------------------------------------------------------------/
/  Universal string handler for user console interface
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
#include <string.h>
#include <stdarg.h>
#include "monitor.h"
#include "diskio.h"
#include "ff.h"
#include "pic33f.h"

#if _USE_XFUNC_IN
unsigned char (*xfunc_in)(void);	/* Pointer to the input stream */
#endif
#if _USE_XFUNC_OUT
void (*xfunc_out)(unsigned char);	/* Pointer to the output stream */
#endif

#if _USE_XFUNC_OUT
/*----------------------------------------------*/
/* Put a character                              */
/*----------------------------------------------*/

void xputc (char c)
{
	if (_CR_CRLF && c == '\n') xfunc_out('\r');		/* LF -> CRLF */
	xfunc_out((unsigned char)c);
}


/*----------------------------------------------*/
/* Put a null-terminated string                 */
/*----------------------------------------------*/

void xputs (const char* str)
{
	if ( str == NULL ) return;
	while (*str)
		xputc(*str++);
}


/*----------------------------------------------*/
/* Formatted string output                      */
/*----------------------------------------------*/
/*  xprintf("%6d", -200);			"  -200"
    xprintf("%02u", 5);				"05"
    xprintf("%ld", 12345678L);		"12345678C"
    xprintf("%08LX", 0x123ABCUL);	"00123ABC"
    xprintf("%016b", 0x550F);		"0101010100001111"
    xprintf("%s", "String");		"String"
    xprintf("%c", 'a');				"a"
*/

void xprintf (
	const char*	str,	/* Pointer to the format string */
	...					/* Optional arguments */
)
{
	va_list arp;
	unsigned int r, i, w, f;
	unsigned long val;
	char s[16], c, d;


	va_start(arp, str);

	while ((c = *str++) != 0) {
		if (c != '%') {
			xputc(c); continue;
		}
		c = *str++;
		f = 0;
		if (c == '0') {				/* Flag: '0' padded */
			f = 1; c = *str++;
		}
		w = 0;
		while (c >= '0' && c <= '9') {	/* Minimum width */
			w = w * 10 + c - '0';
			c = *str++;
		}
		if (c == 'l' || c == 'L') {	/* Prefix: Size is long int */
			f |= 2; c = *str++;
		}
		if (!c) break;
		d = c;
		if (d >= 'a') d -= 0x20;
		switch (d) {				/* Type is... */
		case 'S' :					/* String */
			xputs(va_arg(arp, char*)); continue;
		case 'C' :					/* Character */
			xputc((char)va_arg(arp, int)); continue;
		case 'B' :					/* Binary */
			r = 2; break;
		case 'O' :					/* Octal */
			r = 8; break;
		case 'D' :					/* Signed decimal */
		case 'U' :					/* Unsigned decimal */
			r = 10; break;
		case 'X' :					/* Hexdecimal */
			r = 16; break;
		default:					/* Unknown */
			xputc(c); continue;
		}

		/* Get an argument and put it in numeral */
		val = (f & 2) ? va_arg(arp, long) : ((d == 'D') ? (long)va_arg(arp, int) : va_arg(arp, unsigned int));
		if (d == 'D' && (val & 0x80000000)) {
			val = 0 - val;
			f |= 4;
		}
		i = 0;
		do {
			d = (char)(val % r); val /= r;
			if (d > 9) {
				d += 7;
				if (c == 'x') d += 0x20;
			}
			s[i++] = d + '0';
		} while (val && i < sizeof(s));
		if (f & 4) s[i++] = '-';
		while (i < w--) xputc((f & 1) ? '0' : ' ');
		do xputc(s[--i]); while(i);
	}

	va_end(arp);
}


/*----------------------------------------------*/
/* Dump a block of byte array                   */
/*----------------------------------------------*/

void put_dump (
	const void* buff,		/* Pointer to the byte array to be dumped */
	unsigned long addr,		/* Heading address value */
	int cnt					/* Number of bytes to be dumped */
)
{
	int i;
	const unsigned char *p = buff;


	xprintf("%08lX ", addr);		/* address */

	for (i = 0; i < cnt; i++)		/* data (hexdecimal) */
		xprintf(" %02X", p[i]);

	xputc(' ');
	for (i = 0; i < cnt; i++)		/* data (ascii) */
		xputc((p[i] >= ' ' && p[i] <= '~') ? p[i] : '.');

	xputc('\n');
}

#endif /* _USE_XFUNC_OUT */



#if _USE_XFUNC_IN
/*----------------------------------------------*/
/* Get a value of the string                    */
/*----------------------------------------------*/
/*	"123 -5   0x3ff 0b1111 0377  w "
	    ^                           1st call returns 123 and next ptr
	       ^                        2nd call returns -5 and next ptr
                   ^                3rd call returns 1023 and next ptr
                          ^         4th call returns 15 and next ptr
                               ^    5th call returns 255 and next ptr
                                  ^ 6th call fails and returns 0
*/

int xatoi (			/* 0:Failed, 1:Successful */
	char **str,		/* Pointer to pointer to the string */
	long *res		/* Pointer to the valiable to store the value */
)
{
	unsigned long val;
	unsigned char c, r, s = 0;


	*res = 0;

	while ((c = **str) == ' ') (*str)++;	/* Skip leading spaces */

	if (c == '-') {		/* negative? */
		s = 1;
		c = *(++(*str));
	}

	if (c == '0') {
		c = *(++(*str));
		switch (c) {
		case 'x':		/* hexdecimal */
			r = 16; c = *(++(*str));
			break;
		case 'b':		/* binary */
			r = 2; c = *(++(*str));
			break;
		default:
			if (c <= ' ') return 1;	/* single zero */
			if (c < '0' || c > '9') return 0;	/* invalid char */
			r = 8;		/* octal */
		}
	} else {
		if (c < '0' || c > '9') return 0;	/* EOL or invalid char */
		r = 10;			/* decimal */
	}

	val = 0;
	while (c > ' ') {
		if (c >= 'a') c -= 0x20;
		if ( c == 'M' ) val *= (1024L*1024L); else
		if ( c == 'K' ) val *= 1024L; else 
		{	c -= '0';
			if (c >= 17) {
				c -= 7;
				if (c <= 9) return 0;	/* invalid char */
			}
			if (c >= r) return 0;		/* invalid char for current radix */
			val = val * r + c;
		}
		c = *(++(*str));
	}
	if (s) val = 0 - val;			/* apply sign if needed */

	*res = val;
	return 1;
}


/*----------------------------------------------*/
/* Get a line from the input                    */
/*----------------------------------------------*/

int get_line (		/* 0:End of stream, 1:A line arrived */
	char* buff,		/* Pointer to the buffer */
	int len			/* Buffer length */
)
{
	int rv, c, i;

	rv = i = 0;
	for (;;) {
		c = xfunc_in();				/* Get a char from the incoming stream */
		if (!c) return 0;			/* End of stream? */
		if (c == '\r') break;		/* End of line? */
		if (c == '\b' && i) {		/* Back space? */
			i--;
//			xputc(c);
			xputs("\b \b");			// kill it on ansi terminal
			continue;
		}
		if (c >= ' ' && i < len - 1) {	/* Visible chars */
			buff[i++] = c;
			xputc(c);
		}
	}
	buff[i] = 0;	/* Terminate with zero */
	xputc('\n');
	return 1;
}

#endif /* _USE_XFUNC_IN */

#define STATS
#if !defined(STATS)
#define calcStats( a, b, c )
#else
void calcStats( int cmd, long bytes, long stats[16] )
{
	stats[7] = (DWORD)TMR2, stats[7] += (DWORD)TMR3HLD<<16;
	switch ( cmd ) {
	case 0:	// normal
		stats[11]++;
		stats[0] = stats[7] - stats[1], stats[1] = stats[7];
		if ( stats[0] > 256 )	// if no detected time has past then skip everything
		{
			stats[2] = bytes - stats[3], stats[3] = bytes;
			if ( stats[2] > 0)	// make sure some count change
			{
				stats[4] = (stats[2]*(FCY/256000)) / stats[0];	// calc rate per ms
				if ( stats[4] > stats[5] ) 
					stats[5] = stats[4], stats[12] = stats[11];	// update
				if ( stats[4] < stats[6] ) 
					stats[6] = stats[4], stats[13] = stats[11];	// update
			}
		}
	break;
	case 1:	// suspend time
		stats[8] += stats[7] - stats[1], stats[1] = stats[7];
	break;
	case 2:	// clear
		stats[8] = 0, stats[1] = 0, stats[7] = 0;
		stats[5] = 0, stats[6] = 0x7fffffff;
		stats[3] = 0, stats[11] = 0, TMR3HLD = 0;
		TMR2 = 0;
	break;
	case 3: // display no line control
	case 4: // display prepend \r
	case 5: // display append \n
		stats[9] = (stats[1] - stats[8])/(FCY/256000);			// actual time
		if ( stats[9] )
			stats[10] = stats[3] / stats[9];					// avg
		else stats[10] = 0;
		if ( cmd != 3 )
			xputc( '\r' );
		xprintf( "%11lu in %6lu mSec, avg %5lu kb/sec, max %5lu, min %5lu ",
				stats[3], stats[9],   stats[10],	   stats[5], stats[6] );
		if ( cmd == 5 )
		{	xprintf( "\n%6lu active, %6lu suspend, %6lu total mSec",
					stats[9], stats[8]/(FCY/256000), stats[1]/(FCY/256000) );
			xprintf( "\nmax %5lu @ call %5lu, min %5lu @ call %5lu, %5lu calls",
						stats[5], stats[12], stats[6], stats[13], stats[11] );
		};
	break;
	}
}
#endif

#define dops (3072/sizeof(diskOP))
//#define dops (4096/8)

void monitor (void)
{
	char *ptr, *ptr2, Line[128];
	long p1, p2, p3, p4, p5, p6;
	BYTE res, b;
	const BYTE ft[] = {0,12,16,32};
	WORD w1;
	UINT s1 = 1;
	UINT s2 = 0;
	UINT cnt = 0;
	DWORD ofs = 0, sect = 0;
	FATFS *fs;				/* Pointer to file system object */
	long Rstats[16];
	long Wstats[16];
	diskOP diskOPsave[dops];
	pdiskOP diskOPp;
	UINT diskOPcounter = 0, lastOP = 0;
	volatile BYTE mode = 1;

	xprintf("\nFatFs module test monitor for PIC33FJ %s\n", __DATE__ );
	xputs(_USE_LFN ? "LFN Enabled" : "LFN Disabled");
	xprintf(", Code page: %u\n", _CODE_PAGE );
	xprintf("getSDcard()=%d, Stat=0x%02x\n", getSDcard(), Stat);

	do {
		xputc('>');
		get_line(Line, sizeof(Line));

		ptr = Line;
		switch (*ptr++) {
		case 'm' :
			switch (*ptr++) {
			case 'c' :	/* mc - exit to logger */
				mode = 0;
				break;
			case 'g' :	/* mg - try to get card */
				xprintf("getSDcard()=%d, Stat=0x%02x\n", getSDcard(), Stat);
				break;
			case 'r' :	/* mr - try to release card */
				xprintf("giveSDcard()=%d, Stat=0x%02x\n", giveSDcard(), Stat);
				break;
			}
			break;

		case 'd' :
			switch (*ptr++) {
			case 'd' :	/* dd [<sector>] - Dump sector */
				if (!xatoi(&ptr, &p2)) p2 = sect;
				res = disk_read(0, Buff, p2, 1);
				if (res) { xprintf("rc=%d\n", res); break; }
				sect = p2 + 1;
				xprintf("Sector:%lu\n", p2);
				for (ptr=(char*)Buff, ofs = 0; ofs < 0x200; ptr+=16, ofs+=16)
					put_dump((BYTE*)ptr, ofs, 16);
				break;

			case 'i' :	/* di - Initialize physical drive */
				xprintf("rc=%d, Type=0x%04x, Stat=0x%02x\n", disk_initialize(0), CardType, Stat);
				break;

			case 's' :	/* ds - Show disk status */
				if (disk_ioctl(0, GET_SECTOR_COUNT, &p2) == RES_OK)
					{ xprintf("Drive size: %lu sectors\n", p2); }
				if (disk_ioctl(0, GET_SECTOR_SIZE, &w1) == RES_OK)
					{ xprintf("Sector size: %u\n", w1); }
				if (disk_ioctl(0, GET_BLOCK_SIZE, &p2) == RES_OK)
					{ xprintf("Erase block size: %lu sectors\n", p2); }
				if (disk_ioctl(0, MMC_GET_TYPE, &b) == RES_OK)
					{ xprintf("MMC/SDC type: %u\n", b); }
				if (disk_ioctl(0, MMC_GET_CSD, Buff) == RES_OK)
					{ xputs("CSD:\n"); put_dump(Buff, 0, 16); }
				if (disk_ioctl(0, MMC_GET_CID, Buff) == RES_OK)
					{ xputs("CID:\n"); put_dump(Buff, 0, 16); }
				if (disk_ioctl(0, MMC_GET_OCR, Buff) == RES_OK)
					{ xputs("OCR:\n"); put_dump(Buff, 0, 4); }
				if (disk_ioctl(0, MMC_GET_SDSTAT, Buff) == RES_OK) {
					xputs("SD Status:\n");
					for (s1 = 0; s1 < 64; s1 += 16) put_dump(Buff+s1, s1, 16);
				}
				break;

#if defined(__DEBUG) && defined(TRACK_diskOP)
			case 'o' :	/* do - Show disk opperations */
				b = (dopStat)&0xf;
				for ( res = 0; res < 16; res++ )
				{
					xprintf("%2d: %c %2d @ 0x%08lx start %5u for %5u\n", 
						b, diskOPtrack[lastOP].op ? 'r' : 'w', diskOPtrack[b].count+1, diskOPtrack[b].lba,
						diskOPtrack[b].started, diskOPtrack[b].dur*32 );
					b = (b+1)&0xf;
				}
				break;

			case 'l' :	/* dl - Show disk long list opperations */
				for ( w1 = 0; w1 < diskOPcounter; w1++ )
				{
					xprintf("%4d: %c %2d @ 0x%08lx start %6u for %5u\n", 
						w1, diskOPtrack[lastOP].op ? 'r' : 'w', diskOPsave[w1].count+1, diskOPsave[w1].lba,
						diskOPsave[w1].started, diskOPsave[w1].dur*32 );
				}
				break;
#endif
			}
			break;

		case 'b' :
			switch (*ptr++) {
			case 'd' :	/* bd <addr> - Dump R/W buffer */
				if (!xatoi(&ptr, &p1)) break;
				for (ptr=(char*)&Buff[p1], ofs = p1, cnt = 32; cnt; cnt--, ptr+=16, ofs+=16)
					put_dump((BYTE*)ptr, ofs, 16);
				break;

			case 'e' :	/* be <addr> [<data>] ... - Edit R/W buffer */
				if (!xatoi(&ptr, &p1)) break;
				if (xatoi(&ptr, &p2)) {
					do {
						Buff[p1++] = (BYTE)p2;
					} while (xatoi(&ptr, &p2));
					break;
				}
				for (;;) {
					xprintf("%04X %02X-", (WORD)p1, Buff[p1]);
					get_line(Line, sizeof(Line));
					ptr = Line;
					if (*ptr == '.') break;
					if (*ptr < ' ') { p1++; continue; }
					if (xatoi(&ptr, &p2))
						Buff[p1++] = (BYTE)p2;
					else
						xputs("???\n");
				}
				break;

			case 'r' :	/* br <sector> [<n>] - Read disk into R/W buffer */
				if (!xatoi(&ptr, &p3)) break;
				if (!xatoi(&ptr, &p2)) p2 = 1;
				if ( (p2*512) > sizeof(Buff) )
					p2 = sizeof(Buff) / 512;
				Timer = 0;
				xprintf("rc=%u\n", disk_read(0, Buff, p3, p2));
				xprintf("%lu bytes read in %lumSec, %lu kB/sec.\n", p2*512, Timer, Timer ? ((p2*512) / Timer) : 0L);
				break;

			case 'w' :	/* bw <sector> [<n>] [<ticks>] - Write R/W buffer into disk !CAUTION! */
				if (!xatoi(&ptr, &p3)) break;
				if (!xatoi(&ptr, &p2)) p2 = 1;
				if ( (p2*512) > sizeof(Buff) )
					cnt = sizeof(Buff) / 512;
				else cnt = p2;
//				Timer = 0;
//				xprintf("rc=%u\n", disk_write(0, Buff, p3, p2));
//				xprintf("%lu bytes written in %lumSec, %lu kB/sec.\n", p2*512, Timer, Timer ? ((p2*512) / Timer) : 0L);
				p4 = 0, p1 = 0, b = 0;
				Timer = 0;
				diskOPp = &diskOPsave[0];
				lastOP = (dopStat)&0xf;
				diskOPcounter = 0;
				calcStats( 2, 0L, Wstats );

				if (!xatoi(&ptr, &p5)) {
					p5 = 0;
				} else {
					p4 = (DWORD)TMR2, p4 += (DWORD)TMR3HLD<<16;
					p4 += p5;
				}

				while (p2 > 0) {
					p2 -= cnt;
					calcStats( 1, p1*512, Wstats );
					res = disk_write(0, Buff, p3, cnt);
					if (res != RES_OK) { put_rc(1); break; }
					p3 += cnt, p1 += cnt;
					calcStats( 0, p1*512, Wstats );
					if ( p5 != 0 )
					{
						while ( lastOP != dopStat && diskOPcounter < dops )
						{
//							*diskOPp++ = diskOPtrack[lastOP], diskOPcounter++;
							xprintf("%5ld(%2d): %c %2d @ 0x%08lx start %5u for %5u\n", 
								Wstats[11], lastOP, diskOPtrack[lastOP].op ? 'r' : 'w', 
								diskOPtrack[lastOP].count+1, 
								diskOPtrack[lastOP].lba, diskOPtrack[lastOP].started, 
								diskOPtrack[lastOP].dur );
							lastOP = (lastOP+1)&0xf;
						}
						do {
							p6 = (DWORD)TMR2, p6 += (DWORD)TMR3HLD<<16;
						} while ( p6 < p4 );
						p4 += p5;
					} else calcStats( 4, p1*512, Wstats );
				}
				calcStats( 5, p1*512, Wstats );
				xprintf("\n%lu bytes writen in %lumSec, %lu kB/sec.\n", p1*512, Timer, Timer ? ((p1*512) / Timer) : 0L);
				break;

			case 'f' :	/* bf <n> - Fill working buffer */
				if (!xatoi(&ptr, &p1)) break;
				memset(Buff, (int)p1, sizeof(Buff));
				break;

			}
			break;

		case 'f' :	// has "abcde g ijklmnop rstuvwx  "
			switch (*ptr++) {

			case 'i' :	/* fi - Force initialized the logical drive */
				put_rc(f_mount(0, &Fatfs));
				break;

			case 's' :	/* fs [<path>] - Show logical drive status */
				while (*ptr == ' ') ptr++;
				res = f_getfree(ptr, (DWORD*)&p2, &fs);
				if (res) { put_rc(res); break; }
				xprintf("FAT type = FAT%u\nBytes/Cluster = %lu\nNumber of FATs = %u\n"
						"Root DIR entries = %u\nSectors/FAT = %lu\nNumber of clusters = %lu\n"
						"FAT start (lba) = %lu\nDIR start (lba,clustor) = %lu\nData start (lba) = %lu\n\n...",
						ft[fs->fs_type & 3], fs->csize * 512UL, fs->n_fats,
						fs->n_rootdir, fs->fsize, fs->n_fatent - 2,
						fs->fatbase, fs->dirbase, fs->database
				);
				acc_size = acc_files = acc_dirs = 0;
				res = scan_files(ptr);
				if (res) { put_rc(res); break; }
				xprintf("\r%u files, %lu bytes.\n%u folders.\n"
						"%lu KB total disk space.\n%lu KB available.\n",
						acc_files, acc_size, acc_dirs,
						(fs->n_fatent - 2) * (fs->csize / 2), p2 * (fs->csize / 2)
				);
				break;

			case 'l' :	/* fl [<path>] - Directory listing */
				while (*ptr == ' ') ptr++;
				res = f_opendir(&dir, ptr);
				if (res) { put_rc(res); break; }
				p1 = s1 = s2 = 0;
				for(;;) {
					res = f_readdir(&dir, &Finfo);
					if ((res != FR_OK) || !Finfo.fname[0]) break;
					if (Finfo.fattrib & AM_DIR) {
						s2++;
					} else {
						s1++; p1 += Finfo.fsize;
					}
					xprintf("%c%c%c%c%c %u/%02u/%02u %02u:%02u %9lu  %s",
							(Finfo.fattrib & AM_DIR) ? 'D' : '-',
							(Finfo.fattrib & AM_RDO) ? 'R' : '-',
							(Finfo.fattrib & AM_HID) ? 'H' : '-',
							(Finfo.fattrib & AM_SYS) ? 'S' : '-',
							(Finfo.fattrib & AM_ARC) ? 'A' : '-',
							(Finfo.fdate >> 9) + 1980, (Finfo.fdate >> 5) & 15, Finfo.fdate & 31,
							(Finfo.ftime >> 11), (Finfo.ftime >> 5) & 63, Finfo.fsize, Finfo.fname);
#if _USE_LFN
					for (p2 = strlen(Finfo.fname); p2 < 14; p2++)
						xputc(' ');
					xprintf("%s\n", Lfname);
#else
					xputc('\n');
#endif
				}
				xprintf("%4u File(s),%10lu bytes total\n%4u Dir(s)", s1, p1, s2);
				if (f_getfree(ptr, (DWORD*)&p1, &fs) == FR_OK)
					xprintf(", %10lu bytes free\n", p1 * fs->csize * 512);
				break;

			case 'o' :	/* fo <mode> <file> - Open a file */
				if (!xatoi(&ptr, &p1)) break;
				while (*ptr == ' ') ptr++;
				put_rc(f_open(&file1, ptr, (BYTE)p1));
				res = f_lseek(&file1, 0L);
				break;

			case 'b' :	/* fb - information on open file */
				xprintf("FATFS* = %04x, id = %04x, flag = %02x\n", (UINT)file1.fs, 
						file1.id, (UINT)file1.flag );
				xprintf("fptr = %10lu, fsize = %10lu\n", file1.fptr, file1.fsize );
				xprintf("orgc = %10lu, currc = %10lu\n", file1.org_clust, file1.curr_clust );
				xprintf("dsec = %10lu, dir_s = %10lu\n", file1.dsect, file1.dir_sect );
				break;

			case 'c' :	/* fc - Close a file */
				put_rc(f_close(&file1));
				break;

			case 'e' :	/* fe - Seek file pointer */
				if (!xatoi(&ptr, &p1)) p1 = file1.fptr;
				res = f_lseek(&file1, p1);
				put_rc(res);
				if (res == FR_OK)
					xprintf("fptr = %lu(0x%lX)\n", file1.fptr, file1.fptr);
				break;

			case 'r' :	/* fr [<len>] - read file */
				if (!xatoi(&ptr, &p1)) p1 = file1.fsize;
				p2 = 0, b = 0;
				Timer = 0;
				calcStats( 2, 0L, Rstats );
				while (p1) {
					if ((DWORD)p1 >= sizeof(Buff)) {
						cnt = sizeof(Buff); p1 -= sizeof(Buff);
					} else {
						cnt = p1; p1 = 0;
					}
					calcStats( 1, p2, Rstats );
					res = f_read(&file1, Buff, cnt, &s2);
					if (res != FR_OK) { put_rc(res); break; }
					p2 += s2;
					calcStats( 0, p2, Rstats );
					if (cnt != s2) break;
					calcStats( 4, p2, Rstats );
				}
				calcStats( 5, p2, Rstats );
				xprintf("\n%lu bytes read in %lumSec, %lu kB/sec.\n", p2, Timer, Timer ? (p2 / Timer) : 0L);
				break;

			case 'd' :	/* fd <len> - read and dump file from current fp */
				if (!xatoi(&ptr, &p1)) break;
				ofs = file1.fptr;
				while (p1) {
					if ((UINT)p1 >= 16) { cnt = 16; p1 -= 16; }
					else 				{ cnt = p1; p1 = 0; }
					res = f_read(&file1, Buff, cnt, &cnt);
					if (res != FR_OK) { put_rc(res); break; }
					if (!cnt) break;
					put_dump(Buff, ofs, cnt);
					ofs += 16;
				}
				break;

			case 'p' :	/* fp <len> - read and dump <len> LINES from current fp */
				if (!xatoi(&ptr, &p1)) p1 = 1;
				if ( f_error(&file1) ) break; 
				ofs = file1.fptr;
				while (p1) {
					if ( f_eof(&file1) ) { xprintf("EOF\n"); break; };
					p1--;
					xprintf("%s", f_gets((TCHAR *)Buff, 256, &file1 ) );
				}
				break;

			case 'w' :	/* fw <len> <val> <ticks> - write file */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;
				memset(Buff, (int)p2, sizeof(Buff));
				p4 = 0, p2 = 0, b = 0;
				Timer = 0;
				diskOPp = &diskOPsave[0];
				lastOP = (dopStat)&0xf;
				diskOPcounter = 0;
				calcStats( 2, 0L, Wstats );

				if (!xatoi(&ptr, &p3)) {
					p3 = 0;
				} else {
					p4 = (DWORD)TMR2, p4 += (DWORD)TMR3HLD<<16;
					p4 += p3;
				}

				while (p1) {
					if ((DWORD)p1 >= sizeof(Buff)) {
						cnt = sizeof(Buff); p1 -= sizeof(Buff);
					} else {
						cnt = p1; p1 = 0;
					}
					calcStats( 1, p2, Wstats );
					res = f_write(&file1, Buff, cnt, &s2);
					if (res != FR_OK) { put_rc(res); break; }
					p2 += s2;
					calcStats( 0, p2, Wstats );
					if (cnt != s2) break;
					if ( p3 != 0 )
					{
						while ( lastOP != dopStat && diskOPcounter < dops )
						{
//							*diskOPp++ = diskOPtrack[lastOP], diskOPcounter++;
							xprintf("%5ld(%2d): %c %2d @ 0x%08lx start %5u for %5u\n", 
								Wstats[11], lastOP, diskOPtrack[lastOP].op ? 'r' : 'w', 
								diskOPtrack[lastOP].count+1, 
								diskOPtrack[lastOP].lba, diskOPtrack[lastOP].started, 
								diskOPtrack[lastOP].dur );
							lastOP = (lastOP+1)&0xf;
						}
						do {
							p5 = (DWORD)TMR2, p5 += (DWORD)TMR3HLD<<16;
						} while ( p5 < p4 );
						p4 += p3;
					} else calcStats( 4, p2, Wstats );
				}
				calcStats( 5, p2, Wstats );
				xprintf("\n%lu bytes writen in %lumSec, %lu kB/sec.\n", p2, Timer, Timer ? (p2 / Timer) : 0L);
				break;

			case 'n' :	/* fn <old_name> <new_name> - Change file/dir name */
				while (*ptr == ' ') ptr++;
				ptr2 = strchr(ptr, ' ');
				if (!ptr2) break;
				*ptr2++ = 0;
				while (*ptr2 == ' ') ptr2++;
				put_rc(f_rename(ptr, ptr2));
				break;

			case 'u' :	/* fu <name> - Unlink a file or dir */
				while (*ptr == ' ') ptr++;
				put_rc(f_unlink(ptr));
				break;

			case 'v' :	/* fv - Truncate file */
				put_rc(f_truncate(&file1));
				break;

			case 'k' :	/* fk <name> - Create a directory */
				while (*ptr == ' ') ptr++;
				put_rc(f_mkdir(ptr));
				break;

			case 'a' :	/* fa <atrr> <mask> <name> - Change file/dir attribute */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2)) break;
				while (*ptr == ' ') ptr++;
				put_rc(f_chmod(ptr, p1, p2));
				break;

			case 't' :	/* ft <year> <month> <day> <hour> <min> <sec> <name> - Change timestamp */
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2) || !xatoi(&ptr, &p3)) break;
				Finfo.fdate = (WORD)(((p1 - 1980) << 9) | ((p2 & 15) << 5) | (p3 & 31));
				if (!xatoi(&ptr, &p1) || !xatoi(&ptr, &p2) || !xatoi(&ptr, &p3)) break;
				Finfo.ftime = (WORD)(((p1 & 31) << 11) | ((p1 & 63) << 5) | ((p1 >> 1) & 31));
				put_rc(f_utime(ptr, &Finfo));
				break;

			case 'x' : /* fx <src_name> <dst_name> - Copy file */
				while (*ptr == ' ') ptr++;
				ptr2 = strchr(ptr, ' ');
				if (!ptr2) break;
				*ptr2++ = 0;
				while (*ptr2 == ' ') ptr2++;
				xprintf("Opening \"%s\"", ptr);
				Timer = 0;
				calcStats( 2, 0L, Rstats );
				calcStats( 2, 0L, Wstats );
				res = f_open(&file1, ptr, FA_OPEN_EXISTING | FA_READ);
				xputc('\n');
				if (res) {
					put_rc(res);
					break;
				}
				xprintf("Creating \"%s\"", ptr2);
				res = f_open(&file2, ptr2, FA_CREATE_ALWAYS | FA_WRITE);
				xputc('\n');
				if (res) {
					put_rc(res);
					f_close(&file1);
					break;
				}
				xprintf("Copying...");
				p1 = 0, b = 0;
				for (;;) {
					calcStats( 1, p1, Rstats );
					res = f_read(&file1, Buff, sizeof(Buff), &s1);
					if (res || s1 == 0) break;   /* error or eof */
					calcStats( 0, p1+s1, Rstats );
					calcStats( 1, p1, Wstats );
					res = f_write(&file2, Buff, s1, &s2);
					p1 += s2;
					if (res || s2 < s1) break;   /* error or disk full */
					calcStats( 0, p1, Wstats );
					calcStats( 4, p1, Wstats );
				}
//				xprintf("\n%lu bytes copied.\n", p1);
				calcStats( 5, p1, Rstats );
				xputc('\n');
				calcStats( 5, p1, Wstats );
				xprintf("\nClosing files...");
				f_close(&file1);
				f_close(&file2);
				xprintf("\n%lu bytes read / write in %lumSec, %lu kB/sec write speed.\n", p1, Timer, Timer ? (p1 / Timer) : 0L);
				break;
#if _FS_RPATH
			case 'g' :	/* fg <path> - Change current directory */
				while (*ptr == ' ') ptr++;
				put_rc(f_chdir(ptr));
				break;

			case 'j' :	/* fj <drive#> - Change current drive */
				if (xatoi(&ptr, &p1)) {
					put_rc(f_chdrive((BYTE)p1));
				}
				break;
#endif
#if _USE_MKFS
			case 'm' :	/* fm <partition rule> <sect/clust> - Create file system */
				if (!xatoi(&ptr, &p2) || !xatoi(&ptr, &p3)) break;
				xprintf("The memory card will be formatted. Are you sure? (Y/n)=", p1);
				get_line(ptr, sizeof(Line));
				if (*ptr == 'Y')
					put_rc(f_mkfs(0, (BYTE)p2, (WORD)p3));
				break;
#endif
			}
			break;

		case 't' :		/* t [<year> <mon> <mday> <hour> <min> <sec>] */
			if (xatoi(&ptr, &p1)) {
				rtcYear = p1-1900;
				xatoi(&ptr, &p1); rtcMon = p1-1;
				xatoi(&ptr, &p1); rtcMday = p1;
				xatoi(&ptr, &p1); rtcHour = p1;
				xatoi(&ptr, &p1); rtcMin = p1;
				if(!xatoi(&ptr, &p1)) break;
				rtcSec = p1;
			}
			xprintf("%u/%u/%u %02u:%02u:%02u\n", rtcYear+1900, rtcMon+1, rtcMday, rtcHour, rtcMin, rtcSec);
			break;
		}
	} while ( mode );

}
