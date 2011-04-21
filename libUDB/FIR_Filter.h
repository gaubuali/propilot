
#ifndef FIRFILT_H
#define FIRFILT_H

/* .......................................................................... */

typedef struct
{
  int  numTaps;
  int *pTapsBase;
  int *pTapsEnd;
  int  tapsPage;
  int *pDelayBase;
  int *pDelayEnd;
  int *pDelayPtr;
} MDSFIRStruct;


extern void MDSFIR( int, int *, int *, MDSFIRStruct * );
extern void MDSFIRDelayInit( MDSFIRStruct * );
extern void MDSFIRFilterInit( MDSFIRStruct * );

/* .......................................................................... */

#endif /* FIRFILT_H*/
