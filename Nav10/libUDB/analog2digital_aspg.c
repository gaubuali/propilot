// This file is part of MatrixPilot.
//
//    http://code.google.com/p/gentlenav/
//
// Copyright 2009, 2010 MatrixPilot Team
// See the AUTHORS.TXT file for a list of authors of MatrixPilot.
//
// MatrixPilot is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MatrixPilot is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MatrixPilot.  If not, see <http://www.gnu.org/licenses/>.


#include "libUDB_internal.h"

#if (BOARD_TYPE == ASPG_BOARD)

//	Variables.

struct ADchannel udb_xaccel, udb_yaccel , udb_zaccel ; // x, y, and z accelerometer channels
struct ADchannel udb_xrate , udb_yrate, udb_zrate ;  // x, y, and z gyro channels
struct ADchannel udb_vref ; // reference voltage

int	AD1_Raw[NUM_AD1_LIST+1] __attribute__ ((section(".myDataSection"),address(0x1220)));	// save raw values to look at

int sampcount = 1 ;

// #define USE_AD1_DMA

#if defined(USE_AD1_DMA)

//	Analog to digital processing.
//	Sampling and conversion is done automatically, so that all that needs to be done during 
//	interrupt processing is to read the data out of the buffer.
//	Raw samples are taken approximately 500 per second per channel.
//	A first order digital lowpass filter with a time constant of about 32 milliseconds 
//  is applied to improve signal to noise.
//  CHANGED - see below

#define AD1_SUPER_SAM 16
int  AD1BufferA[AD1_SUPER_SAM][NUM_AD1_LIST+1] __attribute__((space(dma),aligned(256)));
int  AD1BufferB[AD1_SUPER_SAM][NUM_AD1_LIST+1] __attribute__((space(dma),aligned(256)));

void udb_init_gyros( void )
{
	// turn off auto zeroing 
	tAZ_Y = tAZ_XZ = 0 ;
	oAZ_Y = oAZ_XZ = 0 ;
	
	return ;
}


void udb_init_accelerometer(void)
{
// TODO: write I2C accel code
	
//	_TRISA6 = 0 ;  // GSELECT is an output
//	_LATA6 = 1 ;   // 6 G setting
//
//	//	set as inputs:
//	_TRISB9 = 1 ;
//	_TRISB10 = 1 ;
//	_TRISB11 = 1 ;
	
	return ;
}


void udb_init_ADC( void )
{
	udb_init_gyros() ;
	udb_init_accelerometer() ;	// technically init the I2C bus
	
	udb_flags._.firstsamp = 1 ;
	
	AD1CSSL = AD1CSSH = AD2CSSL = 0 ; 	// start with no channels selected
	AD2PCFGL = AD1PCFGL = !LOW_ANALOGS;	// have to set both AD cfg registers
	AD1PCFGH = !HIGH_ANALOGS;			// ad2 only does first 16
	
// configure the high rate AD of the gyro's
	AD1CON1bits.AD12B = 1 ;		// 12 bit A to D
	AD1CON1bits.FORM = 1 ;		// signed int - first level dps is to add 16 values together
	AD1CON1bits.SSRC = 7 ;		// auto convert
	AD1CON1bits.ASAM = 1 ;		// auto samp
	AD1CON1bits.SIMSAM = 0 ;	// multiple channels in sequence
	
	AD1CON2bits.VCFG = 0 ;		// use supply as reference voltage
	AD1CON2bits.CSCNA = 1 ;		// scanA ch0
	
	AD1CON2bits.ALTS = 0 ;		// always A
	AD1CON2bits.BUFM = 1 ;		// ping-pong buffers

// timing calculated based on 80MHz Fosc, we want max super samples per channel for dsp
// super sample = 16 12bit samples to get us 16 bit nominal samples that go into the
// low pass fir filter.
//
// total samples per second = 10 (num channels) x 16 (super) x 50 (frame rate) x 50 (fir)
// = 10 x 16 x 50 x 50 = 400000 < 500000 max from pic so its ok
// from ChipSetup page in ASPG board cfg.xls
// ADCS = 5, must be over 117.6 nS, Tcy = 25nS x 5 = 125nSec = Tad
// SAMC = 6, must be larger than 3
	
	AD1CON3bits.SAMC = 6 ;		// auto sample time = 6 TAD, 0.750 microseconds
	AD1CON3bits.ADCS = 5 - 1 ;	// TAD = 125 nanoseconds
	
	AD1CON1bits.ADDMABM = 1 ;	// DMA buffer written in conversion order
//	AD1CON2bits.SMPI = 10-1 ;	// 10 samples
	AD1CON2bits.SMPI = 1 - 1 ;	// xfer each sample
	AD1CON4bits.DMABL = 4 ;		// double buffering

// setup DMA

	DMA0CONbits.AMODE = 0;			// Configure DMA for Register Indirect with Post-Increment mode
	DMA0CONbits.MODE  = 2;			// Configure DMA for Continuous Ping-Pong mode
	DMA0CONbits.SIZE  = 0;			// WORD mode
	DMA0CONbits.DIR  = 0;			// Read from Peripheral address, write to DPSRAM address
	DMA0CONbits.HALF  = 0;			// add data, using two buffers

	DMA0REQ = 13;					// Select ADC1 as DMA Request source

	DMA0STA = __builtin_dmaoffset(AD1BufferA);
	DMA0STB = __builtin_dmaoffset(AD1BufferB);
	DMA0PAD=(int)&ADC1BUF0;
	DMA0CNT = (AD1_SUPER_SAM*NUM_AD1_LIST) - 1;

	IFS0bits.DMA0IF = 0;			//Clear the DMA interrupt flag bit
    IEC0bits.DMA0IE = 1;			//Set the DMA interrupt enable bit

	DMA0CONbits.CHEN=1;				// Enable DMA
	
	AD1CSSH = AD1_LIST;				// ad1 scan list
	_AD1IF = 0 ;					// clear the AD interrupt
	_AD1IP = 5 ;					// priority 5
//	_AD1IE = 1 ;					// enable the interrupt
	_AD1IE = 0 ;					// dma gets the interrupt, don't enable cpu as well
	AD1CON1bits.ADON = 1 ;			// turn on the A to D
	
	return ;
}

/*=============================================================================
	_DMA0Interrupt(): ISR name is chosen from the device linker script.

	TODO: add each individual super sample and store in FIR input buffer
	 	 should be in assembler as the layout would allow a loop.
	 	 need to decide what to do with the vref and temp signals - they don't
	 	 require fir but should affect the final super sample values.
=============================================================================*/

unsigned int DmaBuffer = 0;

void __attribute__((interrupt, no_auto_psv)) _DMA0Interrupt(void)
{
	if(DmaBuffer == 0)
	{
	} 	else 	{
	}

	DmaBuffer ^= 1;

	IFS0bits.DMA0IF = 0;		// Clear the DMA0 Interrupt Flag
}

#define ADC2SAMPLE ((int)(ADC2BUF0))

void __attribute__((__interrupt__,__no_auto_psv__)) _ADC2Interrupt(void)
{	
	interrupt_save_extended_state ;
	
	indicate_loading_inter ;
	
	_AD2IF = 0 ; 	// clear the AD interrupt
	
	switch ( sampcount ) {
		case yrateBUFF :
			udb_yrate.input = ADC2SAMPLE ;
			if ( udb_flags._.firstsamp )
			{
				udb_yrate.value = udb_yrate.input ;
			}
			else
			{
				udb_yrate.value = udb_yrate.value + ((( (udb_yrate.input>>1) - (udb_yrate.value>>1) ))>>FILTERSHIFT ) ;
			}
			break;
			
		case zrateBUFF :
			udb_zrate.input = ADC2SAMPLE ;
			if ( udb_flags._.firstsamp )
			{
				udb_zrate.value = udb_zrate.input ;
			}
			else
			{
				udb_zrate.value = udb_zrate.value + ((( (udb_zrate.input>>1) - (udb_zrate.value>>1) ))>>FILTERSHIFT ) ;
			}
			break;
			
		case xrateBUFF :
			udb_xrate.input = ADC2SAMPLE ;
			if ( udb_flags._.firstsamp )
			{
				udb_xrate.value = udb_xrate.input ;
			}
			else
			{
				udb_xrate.value = udb_xrate.value + ((( (udb_xrate.input>>1) - (udb_xrate.value>>1) ))>>FILTERSHIFT ) ;
			}
			break;
			
		case zaccelBUFF :
			udb_zaccel.input = ADC2SAMPLE ;
			if ( udb_flags._.firstsamp )
			{
				udb_zaccel.value = udb_zaccel.input ;
			}
			else
			{
				udb_zaccel.value = udb_zaccel.value + ((( (udb_zaccel.input>>1) - (udb_zaccel.value>>1) ))>>FILTERSHIFT ) ;
			}
			break;
			
		case xaccelBUFF :
			udb_xaccel.input = -ADC2SAMPLE ;
			if ( udb_flags._.firstsamp )
			{
				udb_xaccel.value = udb_xaccel.input ;
			}
			else
			{
				udb_xaccel.value = udb_xaccel.value + (((( udb_xaccel.input>>1 )- (udb_xaccel.value>>1) ))>>FILTERSHIFT ) ;
			}
			break;
			
		case yaccelBUFF :
			udb_yaccel.input = -ADC2SAMPLE ;
			if ( udb_flags._.firstsamp )
			{
				udb_yaccel.value = udb_yaccel.input ;
				udb_flags._.firstsamp = 0 ;
			}
			else
			{
				udb_yaccel.value = udb_yaccel.value + ((( (udb_yaccel.input>>1) - (udb_yaccel.value>>1) ))>>FILTERSHIFT ) ;
			}
			break;
			
		default :
			break;
	}
	
	sampcount++ ;
	if ( sampcount > 6 )
	{
		sampcount = 1 ;
	}
	
	interrupt_restore_extended_state ;
	return ;
}

#else // USE_AD1_DMA

void udb_init_gyros( void )
{
	// turn off auto zeroing
	tAZ_Y = tAZ_XZ = 0 ;
	oAZ_Y = oAZ_XZ = 0 ;

	return ;
}


void udb_init_accelerometer(void)
{
// TODO: write I2C accel code

//	_TRISA6 = 0 ;  // GSELECT is an output
//	_LATA6 = 1 ;   // 6 G setting
//
//	//	set as inputs:
//	_TRISB9 = 1 ;
//	_TRISB10 = 1 ;
//	_TRISB11 = 1 ;

	return ;
}

void udb_init_ADC( void )
{
	udb_init_gyros() ;
	udb_init_accelerometer() ;

	udb_flags._.firstsamp = 1 ;

	AD1CSSL = AD1CSSH = AD2CSSL = 0 ; 	// start with no channels selected
	AD2PCFGL = AD1PCFGL = !LOW_ANALOGS;	// have to set both AD cfg registers
	AD1PCFGH = !HIGH_ANALOGS;			// ad2 only does first 16

	AD1CSSH = AD1_LIST;				// ad1 scan list

	AD1CON1bits.AD12B = 1 ;		// 12 bit A to D
	AD1CON1bits.FORM = 3 ;		// signed fractional
	AD1CON1bits.SSRC = 7 ;		// auto convert
	AD1CON1bits.ASAM = 1 ;		// auto samp
	AD1CON1bits.SIMSAM = 0 ;	// multiple channels in sequence

	AD1CON2bits.VCFG = 0 ;		// use supply as reference voltage
	AD1CON2bits.CSCNA = 1 ;		// scanA ch0

	AD1CON2bits.ALTS = 0 ;		// always A
//	AD2CON2bits.BUFM = 1 ;		// ping-pong buffers

// modified this for Fosc (80 vs 32MHz) and scanning more channels (10 vs 6)
// (1/(32e6/2))*128*(31+14)*6 = 2160uSec = (1/(80e6/2))*192*31*10 = 2160uSec once for all channels
// kinda wondering why this isn't an exact multiple of frame rate
//	AD1CON3bits.SAMC = 31 ;		// auto sample time = 31 TAD, approximately 246.0625 microseconds
//	AD1CON3bits.ADCS = 127 ;	// TAD = 7.9375 microseconds
	AD1CON3bits.SAMC = 31 ;		// auto sample time = 30 TAD, approximately 148.80 microseconds
	AD1CON3bits.ADCS = 192 - 1; // TAD = 4.8 microseconds

//	AD2CON1bits.ADDMABM = 1 ;	// DMA buffer written in conversion order
//	AD1CON2bits.SMPI = 5 ;		// 6 samples
//	AD2CON4bits.DMABL = 1 ;		// double buffering

	_AD1IF = 0 ;		// clear the AD interrupt
	_AD1IP = 5 ;		// priority 5
	_AD1IE = 1 ;		// enable the interrupt
	AD1CON1bits.ADON = 1 ;		// turn on the A to D

	return ;
}


#define ADCSAMPLE ((int)(ADC1BUF0))

void __attribute__((__interrupt__,__no_auto_psv__)) _ADC1Interrupt(void)
{
	interrupt_save_extended_state ;

	indicate_loading_inter ;

	_AD1IF = 0 ; 	// clear the AD interrupt
	AD1_Raw[sampcount] = ADCSAMPLE;

	switch ( sampcount ) {
		case yrateBUFF :
			udb_yrate.input = ADCSAMPLE ;
			if ( udb_flags._.firstsamp )
			{
				udb_yrate.value = udb_yrate.input ;
			}
			else
			{
				udb_yrate.value = udb_yrate.value + ((( (udb_yrate.input>>1) - (udb_yrate.value>>1) ))>>FILTERSHIFT ) ;
			}
			break;

		case zrateBUFF :
			udb_zrate.input = ADCSAMPLE ;
			if ( udb_flags._.firstsamp )
			{
				udb_zrate.value = udb_zrate.input ;
			}
			else
			{
				udb_zrate.value = udb_zrate.value + ((( (udb_zrate.input>>1) - (udb_zrate.value>>1) ))>>FILTERSHIFT ) ;
			}
			break;

		case xrateBUFF :
			udb_xrate.input = ADCSAMPLE ;
			if ( udb_flags._.firstsamp )
			{
				udb_xrate.value = udb_xrate.input ;
			}
			else
			{
				udb_xrate.value = udb_xrate.value + ((( (udb_xrate.input>>1) - (udb_xrate.value>>1) ))>>FILTERSHIFT ) ;
			}
			break;

		case zaccelBUFF :
			udb_zaccel.input = ADCSAMPLE ;
			if ( udb_flags._.firstsamp )
			{
				udb_zaccel.value = udb_zaccel.input ;
			}
			else
			{
				udb_zaccel.value = udb_zaccel.value + ((( (udb_zaccel.input>>1) - (udb_zaccel.value>>1) ))>>FILTERSHIFT ) ;
			}
			break;

		case xaccelBUFF :
			udb_xaccel.input = -ADCSAMPLE ;
			if ( udb_flags._.firstsamp )
			{
				udb_xaccel.value = udb_xaccel.input ;
			}
			else
			{
				udb_xaccel.value = udb_xaccel.value + (((( udb_xaccel.input>>1 )- (udb_xaccel.value>>1) ))>>FILTERSHIFT ) ;
			}
			break;

		case yaccelBUFF :
			udb_yaccel.input = -ADCSAMPLE ;
			if ( udb_flags._.firstsamp )
			{
				udb_yaccel.value = udb_yaccel.input ;
				udb_flags._.firstsamp = 0 ;
			}
			else
			{
				udb_yaccel.value = udb_yaccel.value + ((( (udb_yaccel.input>>1) - (udb_yaccel.value>>1) ))>>FILTERSHIFT ) ;
			}
			break;

		default :
			break;
	}

	sampcount++ ;
	if ( sampcount > NUM_AD1_LIST )
	{
		sampcount = 1 ;
	}

	interrupt_restore_extended_state ;
	return ;
}
#endif // USE_AD1_DMA

#endif