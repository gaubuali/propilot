.ifdef __dsPIC33F
.include "p33fxxxx.inc"
.endif

.ifdef __PIC24H
.include "p24hxxxx.inc"
.endif

	.data
	.extern	_intSENDadr
	.extern	_intRECadr
	.extern	_intCOUNT

	.text
	.global __SPI1Interrupt

; handle spi interrupt
__SPI1Interrupt:
		PUSH.S
		MOV		_intRECadr,W1
		MOV		#SPI1BUF,W2
		MOV.B	[W2],[W1++]
		MOV		W1,_intRECadr
		BCLR	IFS0,#SPI1IF	; all driven on receive
;		CP0		_intCOUNT		; check done sending
;		BRA		Z, iDONE
		DEC		_intCOUNT
		BRA		LT, iDONE
		MOV		_intSENDadr,W0
		MOV.B	[W0++],[W2]
		MOV		W0,_intSENDadr
;		DEC		_intCOUNT
;		BTSC	SR,#Z			; MAJOR silicon problem
;		BRA 	NZ,	iDONE
;		DISI	#200
;		BCLR	IEC0,#SPI1IE
iDONE:	
		POP.S
    	retfie
