#ifndef FILTER_ASPG_H
#define FILTER_ASPG_H

void abort(void);
extern MDSFIRStruct filter_aspgFilterX;
extern MDSFIRStruct filter_aspgFilterY;
extern MDSFIRStruct filter_aspgFilterZ;

extern MDSFIRStruct filter_aspg_I2CX_Filter;
extern MDSFIRStruct filter_aspg_I2CY_Filter;
extern MDSFIRStruct filter_aspg_I2CZ_Filter;

#endif /* FILTER_ASPG_H */

/* The following C-code fragment demonstrates how to call the filter routine
#include "FIR_Filter.h"
#include "filter_aspg.h"

// NUM_SAMPLES defines the number of samples in one block of input data.
// This value should be changed as needed for the application
#define NUM_SAMPLES 100

{
   // Declare input and output sample arrays.
   int  inSamples[NUM_SAMPLES], outSamples[NUM_SAMPLES];


   // Call the FIRDelayInit routine to zero out the delay line
   FIRFilterInit( &filter_aspgFilter );

   // Call FIR for each block of input samples
   // This routine would normally be called inside a FOR or a DO-WHILE loop
   // Only one instance has been shown
   FIR( NUM_SAMPLES, &outSamples, &inSamples,  &filter_aspgFilter,);
}
*/
