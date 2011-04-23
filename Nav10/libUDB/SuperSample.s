;******************************************************************************
;   How to use this file:                                                     *
;   ======================                                                    *
;                                                                             *
;   This file provides the fast function to add samples in the sequential     *
;   A/D DMA buffer and store the result in ASM30 assembler language.          *
;                                                                             *
;   The function SuperSample must be called with two arguments, first is the  *
;   address of the DMA buffer and second is the destination buffer. The       *
;   function is hard coded to expect 16 samples x 10 channels.                *
;                                                                             *
;   Declare the function in c as follows:                                     *
;   extern void SuperSample( (void *)Source, (void *)Dest );                  *
;   were Source is the name of the source DMA buffer and Dest is the name     *
;   of the destination buffer. The function adds all of                       *
;   Source[0..15][x] and places the result in Dest[x]. This function will     *
;   only be usefull for A/D results converted with FORM<1:0> = 00 or 01. It   *
;   can be used with either 10 or 12 bit data but expected use is 12 bit as   *
;   adding 16 12 bit samples together gives a 16 bit result.                  *
;                                                                             *
;   The assembly expects Source to be passed in W0 and Dest in W1 - the       *
;   standard calling convention for C30. There is no return value or error    *
;   checking. This function does save and restore W8..W13 but NOT DO counter  *
;   and accociated registers - this is expected to be done external to this   *
;   function if required (strongly sugested).                                 *
;                                                                             *
;******************************************************************************
;                                                                             *
;    Author              :  Paul G.                                           *
;    Company             :  ASPG                                              *
;    Filename            :  SuperSample.s                                     *
;    Date                :  01/05/2011                                        *
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
        .global  _superSample

         .text
_superSample:
		push	W8			; save c runtime regs
		push	W9			; save c runtime regs
;;		push	W10			; save c runtime regs
;;		push	W11			; save c runtime regs
;;		push	W12			; save c runtime regs
		push	W13			; save c runtime regs
		mov		W0, W13		; move source address
		push	W1			; save destination

		mov		#0, W0		; clear all accumulators
		mov		#0, W1		; clear all accumulators
		mov		#0, W2		; clear all accumulators
		mov		#0, W3		; clear all accumulators
		mov		#0, W4		; clear all accumulators
		mov		#0, W5		; clear all accumulators
		mov		#0, W6		; clear all accumulators
		mov		#0, W7		; clear all accumulators
		mov		#0, W8		; clear all accumulators
		mov		#0, W9		; clear all accumulators
;;		mov		#0, W11		; clear all accumulators
;;		mov		#0, W10		; clear all accumulators
;;		mov		#0, W12		; clear all accumulators

ACC_S:	DO		#15, ACC_E	; add em all up
		ADD		W0, [W13++], W0
		ADD		W1, [W13++], W1
		ADD		W2, [W13++], W2
		ADD		W3, [W13++], W3
		ADD		W4, [W13++], W4
		ADD		W5, [W13++], W5
		ADD		W6, [W13++], W6
		ADD		W7, [W13++], W7
		ADD		W8, [W13++], W8
ACC_E:	ADD		W9, [W13++], W9		;; accululate each value steping pointer
;;		ADD		W10, [W13++], W10
;;		ADD		W11, [W13++], W11
;;		ADD		W13, [W13++], W12

		POP		W13					;; restore destination
		MOV		W0, [W13++]			;; store each value steping pointer
		MOV		W1, [W13++]
		MOV		W2, [W13++]
		MOV		W3, [W13++]
		MOV		W4, [W13++]
		MOV		W5, [W13++]
		MOV		W6, [W13++]
		MOV		W7, [W13++]
		MOV		W8, [W13++]
		MOV		W9, [W13++]
;;		LSR		W0, [W13++]
;;		LSR		W1, [W13++]
;;		LSR		W2, [W13++]
;;		LSR		W3, [W13++]
;;		LSR		W4, [W13++]
;;		LSR		W5, [W13++]
;;		LSR		W6, [W13++]
;;		LSR		W7, [W13++]
;;		LSR		W8, [W13++]
;;		LSR		W9, [W13++]			;; store each value steping pointer
;;		LSR		W10, [W13++]
;;		LSR		W11, [W13++]
;;		LSR		W13, [W13++]

		pop		W13			; save c runtime regs
;;		pop		W12			; save c runtime regs
;;		pop		W11			; save c runtime regs
;;		pop		W10			; save c runtime regs
		pop		W9			; save c runtime regs
		pop		W8			; save c runtime regs

		return

        .global  _superSample6

         .text
_superSample6:
;;		push	W8			; save c runtime regs
;;		push	W9			; save c runtime regs
;;		push	W10			; save c runtime regs
;;		push	W11			; save c runtime regs
;;		push	W12			; save c runtime regs
		push	W13			; save c runtime regs
		mov		W0, W13		; move source address
		push	W1			; save destination

		mov		#0, W0		; clear all accumulators
		mov		#0, W1		; clear all accumulators
		mov		#0, W2		; clear all accumulators
		mov		#0, W3		; clear all accumulators
		mov		#0, W4		; clear all accumulators
		mov		#0, W5		; clear all accumulators
;;		mov		#0, W6		; clear all accumulators
;;		mov		#0, W7		; clear all accumulators
;;		mov		#0, W8		; clear all accumulators
;;		mov		#0, W9		; clear all accumulators
;;		mov		#0, W11		; clear all accumulators
;;		mov		#0, W10		; clear all accumulators
;;		mov		#0, W12		; clear all accumulators

ACC_S6:	DO		#15, ACC_E6	; add em all up
		ADD		W0, [W13++], W0
		ADD		W1, [W13++], W1
		ADD		W2, [W13++], W2
		ADD		W3, [W13++], W3
		ADD		W4, [W13++], W4
ACC_E6:	ADD		W5, [W13++], W5
;;		ADD		W6, [W13++], W6
;;		ADD		W7, [W13++], W7
;;		ADD		W8, [W13++], W8
;;		ADD		W9, [W13++], W9		;; accululate each value steping pointer
;;		ADD		W10, [W13++], W10
;;		ADD		W11, [W13++], W11
;;		ADD		W13, [W13++], W12

		POP		W13					;; restore destination
		MOV		W0, [W13++]			;; store each value steping pointer
		MOV		W1, [W13++]
		MOV		W2, [W13++]
		MOV		W3, [W13++]
		MOV		W4, [W13++]
		MOV		W5, [W13++]
;;		MOV		W6, [W13++]
;;		MOV		W7, [W13++]
;;		MOV		W8, [W13++]
;;		MOV		W9, [W13++]
;;		LSR		W0, [W13++]
;;		LSR		W1, [W13++]
;;		LSR		W2, [W13++]
;;		LSR		W3, [W13++]
;;		LSR		W4, [W13++]
;;		LSR		W5, [W13++]
;;		LSR		W6, [W13++]
;;		LSR		W7, [W13++]
;;		LSR		W8, [W13++]
;;		LSR		W9, [W13++]			;; store each value steping pointer
;;		LSR		W10, [W13++]
;;		LSR		W11, [W13++]
;;		LSR		W13, [W13++]

		pop		W13			; save c runtime regs
;;		pop		W12			; save c runtime regs
;;		pop		W11			; save c runtime regs
;;		pop		W10			; save c runtime regs
;;		pop		W9			; save c runtime regs
;;		pop		W8			; save c runtime regs

		return
;--------End of All Code Sections ---------------------------------------------
        .end                               ;End of program code in this file

