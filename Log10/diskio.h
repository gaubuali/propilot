/*-----------------------------------------------------------------------
/  Low level disk interface modlue include file  R0.05   (C)ChaN, 2007
/-----------------------------------------------------------------------*/

#ifndef _DISKIO
/* #warning doing it */
#define _READONLY	0	/* 1: Read-only mode */
#define _USE_IOCTL	1

#include "integer.h"


/* Status of Disk Functions */
typedef BYTE	DSTATUS;

/* Results of Disk Functions */
typedef enum {
	RES_OK = 0,		/* 0: Successful */
	RES_ERROR,		/* 1: R/W Error */
	RES_WRPRT,		/* 2: Write Protected */
	RES_NOTRDY,		/* 3: Not Ready */
	RES_PARERR		/* 4: Invalid Parameter */
} DRESULT;


/*---------------------------------------*/
/* Prototypes for disk control functions */

DSTATUS disk_initialize (BYTE);
DSTATUS disk_status (BYTE);
DRESULT disk_read (BYTE, BYTE*, DWORD, BYTE);
#if	_READONLY == 0
DRESULT disk_write (BYTE, const BYTE*, DWORD, BYTE);
#endif
DRESULT disk_ioctl (BYTE, BYTE, void*);
void	disk_timerproc (void);
//static 
void	power_off (void);
//static 
void	power_on (void);

extern BYTE getSDcard( void );
extern BYTE giveSDcard( void );

extern volatile DSTATUS Stat;	/* Disk status */
extern volatile UINT Timer1, Timer2;		/* 1000Hz decrement timer */
extern UINT CardType;

/* Disk Status Bits (DSTATUS) */

#define STA_NOINIT		0x01	/* Drive not initialized */
#define STA_NODISK		0x02	/* No medium in the drive */
#define STA_PROTECT		0x04	/* Write protected */
#define STA_RELEASE		0x08	/* release card */


/* Command code for disk_ioctrl() */

/* Generic command */
#define CTRL_SYNC			0	/* Mandatory for write functions */
#define GET_SECTOR_COUNT	1	/* Mandatory for only f_mkfs() */
#define GET_SECTOR_SIZE		2
#define GET_BLOCK_SIZE		3	/* Mandatory for only f_mkfs() */
#define CTRL_POWER			4
#define CTRL_LOCK			5
#define CTRL_EJECT			6
/* MMC/SDC command */
#define MMC_GET_TYPE		10
#define MMC_GET_CSD			11
#define MMC_GET_CID			12
#define MMC_GET_OCR			13
#define MMC_GET_SDSTAT		14
/* ATA/CF command */
#define ATA_GET_REV			20
#define ATA_GET_MODEL		21
#define ATA_GET_SN			22


/* Card type definitions (CardType) */

#define CT_MMC				0x01
#define CT_SD1				0x02
#define CT_SD2				0x04
#define CT_SDC				(CT_SD1|CT_SD2)
#define CT_BLOCK			0x08

//#define TRACK_spi
#define TRACK_diskOP
#if defined(TRACK_spi) && defined(TRACK_diskOP)
#error define EITHER TRACK_spi OR TRACK_diskOP, not both
#endif

//#if defined(__DEBUG)
#if defined(TRACK_spi)
#define spiTime() spiStats[spiStat++] = TMR5, spiStat &= 0x3f
#define dopTimeS(o)
#define dopTimeE(o)
#elif defined(TRACK_diskOP)
#define spiTime()
typedef struct {
	DWORD lba;			// LBA for request
	WORD  started;		// TMR2 time
unsigned int dur:11;	// duration (TMR2 end - started)>>5
unsigned int op:1;		// opperation, 1 = read, 0 = write
unsigned int count:4;	// count of LBA's
} diskOP, *pdiskOP;
extern volatile diskOP diskOPtrack[16];
extern volatile UINT __attribute__ ((near)) dopStat;
#define dopTimeS(o) diskOPtrack[dopStat].count = ((count-1)&0xf);	\
					diskOPtrack[dopStat].lba = TMR2 + ((DWORD)TMR3HLD<<16);\
					diskOPtrack[dopStat].started = (diskOPtrack[dopStat].lba)>>5;\
					diskOPtrack[dopStat].op = o
#define dopTimeE(o) diskOPtrack[dopStat].lba = TMR2 + ((DWORD)TMR3HLD<<16);\
					diskOPtrack[dopStat].lba = diskOPtrack[dopStat].lba>>5;\
					diskOPtrack[dopStat].dur = (diskOPtrack[dopStat].lba - diskOPtrack[dopStat].started); \
					diskOPtrack[dopStat].lba = sector;				\
					dopStat++; dopStat &= 0xf
#endif
//#else
//#define spiTime()
//#define dopTimeS(o)
//#define dopTimeE(o)
//#endif

#define _DISKIO
#endif
