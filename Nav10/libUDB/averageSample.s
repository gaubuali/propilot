;******************************************************************************
;   How to use this file:                                                     *
;   ======================                                                    *
;                                                                             *
;   This file provides the fast function to add a variable number of samples  *
;   in a sequential buffer and return the average result in ASM30 assembler   *
;   language.                                                                 *
;                                                                             *
;   The function averageSample must be called with two arguments, first is    *
;   the address of the buffer and second is the number of samples. The result *
;   is returned in W0.                                                        *
;                                                                             *
;   Declare the function in c as follows:                                     *
;   extern int averageSample( (void *)Source, int Count );	                  *
;   were Source is the name of the source buffer and Count is the number of   *
;   samples in the buffer.                                                    *
;                                                                             *
;   The assembly expects Source to be passed in W0 and Dest in W1 - the       *
;   standard calling convention for C30. There is no error checking. This     *
;   function does save and restore W8..W13 but NOT DSP counter and accociated *
;   registers - this is expected to be done external to this function if      *
;   required (strongly sugested). Return value is in W0 per C30 convention.   *
;                                                                             *
;******************************************************************************
;                                                                             *
;    Author              :  Paul G.                                           *
;    Company             :  ASPG                                              *
;    Filename            :  averageSample.s                                   *
;    Date                :  01/19/2011                                        *
;    File Version        :  1.00                                              *
;                                                                             *
;    Devices Supported by this file:                                          *
;                        All PIC24F,PIC24H,dsPIC30F,dsPIC33F devices          *
;                                                                             *
;******************************************************************************
.nolist
.ifdef __dsPIC30F
        .include "p30fxxxx.inc"
.endif
.ifdef __dsPIC33F
        .include "p33Fxxxx.inc"
.endif
.ifdef __PIC24F
        .include "p24Fxxxx.inc"
.endif
.ifdef __PIC24H
        .include "p24Hxxxx.inc"
.endif
.list
        .global  _averageSample

         .text
_averageSample:
		mov		W0, W4		; move source address
		mov		W1, W5		; save count
		sub		W1, #1, W6	; set REPEAT count

;;		mov		#0, W0		; clear all accumulators
;;		mov		#0, W1		; clear all accumulators
;;		mov		#0, W2		; clear all accumulators
;;		mov		#0, W3		; clear all accumulators

		CLR		A			; 0 40 bit Acc
;;		DSI		W5
ACC_S:	REPEAT	W6			; add em all up
		ADD		[W4++], #7, A ; signed 16 add to ACCA
		SFTAC	A, #9		; get to exact 32bit result
		MOV		ACCAH, W1	; move for DIV instruction
		MOV		ACCAL, W0
		REPEAT	#17			; Execute DIV.SD 18 times
		DIV.SD	W0, W5		; Divide W1:W0 by W5
							; Store quotient to W0, remainder to W1
		NOP
		return
;--------End of All Code Sections ---------------------------------------------
        .end                               ;End of program code in this file

