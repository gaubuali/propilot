; ..............................................................................
;    File   filter_aspg_I2C.s
; ..............................................................................

;;		.equ filter_aspg_I2CNumTaps, 32
		.equ filter_aspg_I2CNumTaps, 64

; ..............................................................................
; Allocate and initialize filter taps

		.section .filter_aspg_I2Cconst, psv
		.global _filter_aspg_I2CTaps

		.align (filter_aspg_I2CNumTaps * 2)
_filter_aspg_I2CTaps:
filter_aspg_I2CTaps:
.hword 	0x0014,	0x0018,	0x0018,	0x0015,	0x000C,	0xFFFE,	0xFFE8,	0xFFCB,	0xFFA9
.hword 	0xFF82,	0xFF5A,	0xFF34,	0xFF14,	0xFEFF,	0xFEFB,	0xFF0C,	0xFF38,	0xFF82
.hword 	0xFFEC,	0x0077,	0x0123,	0x01ED,	0x02CF,	0x03C3,	0x04C1,	0x05BF,	0x06B2
.hword 	0x0790,	0x0850,	0x08E8,	0x0952,	0x0988,	0x0988,	0x0952,	0x08E8,	0x0850
.hword 	0x0790,	0x06B2,	0x05BF,	0x04C1,	0x03C3,	0x02CF,	0x01ED,	0x0123,	0x0077
.hword 	0xFFEC,	0xFF82,	0xFF38,	0xFF0C,	0xFEFB,	0xFEFF,	0xFF14,	0xFF34,	0xFF5A
.hword 	0xFF82,	0xFFA9,	0xFFCB,	0xFFE8,	0xFFFE,	0x000C,	0x0015,	0x0018,	0x0018
.hword 	0x0014
;;.hword 	0xFFEC,	0xFFE9,	0x000C,	0x0061,	0x00C8,	0x00EA,	0x0064,	0xFF0E,	0xFD47
;;.hword 	0xFC13,	0xFCC4,	0x005D,	0x06E8,	0x0F21,	0x16C1,	0x1B5A,	0x1B5A,	0x16C1
;;.hword 	0x0F21,	0x06E8,	0x005D,	0xFCC4,	0xFC13,	0xFD47,	0xFF0E,	0x0064,	0x00EA
;;.hword 	0x00C8,	0x0061,	0x000C,	0xFFE9,	0xFFEC

; ..............................................................................
; Allocate delay line in (uninitialized) Y data space

;;		.section .ybss, bss, ymemory
;;		.section filter_aspg_I2C, ymemory, address(0x7700)
		.section .filter_aspg_I2C, ymemory
;;		.section .ydata, address(0x7700)

		.align (filter_aspg_I2CNumTaps * 2)
		.global _filter_aspg_I2CX_Delay
_filter_aspg_I2CX_Delay:
		.space filter_aspg_I2CNumTaps*2

		.align (filter_aspg_I2CNumTaps * 2)
		.global _filter_aspg_I2CY_Delay
_filter_aspg_I2CY_Delay:
		.space filter_aspg_I2CNumTaps*2

		.align (filter_aspg_I2CNumTaps * 2)
		.global _filter_aspg_I2CZ_Delay
_filter_aspg_I2CZ_Delay:
		.space filter_aspg_I2CNumTaps*2
; fix microchip's or the linkers stupidity of putting this at the highest 
; possible address and then having a pointer reach the address max
;		.space 2
; ..............................................................................
; Allocate and intialize filter structure

		.section .data
		.global _filter_aspg_I2CX_Filter

_filter_aspg_I2CX_Filter:
.hword filter_aspg_I2CNumTaps
.hword psvoffset(filter_aspg_I2CTaps)
.hword psvoffset(filter_aspg_I2CTaps)+filter_aspg_I2CNumTaps*2-1
.hword psvpage(filter_aspg_I2CTaps)
.hword _filter_aspg_I2CX_Delay
.hword _filter_aspg_I2CX_Delay+filter_aspg_I2CNumTaps*2-1
.hword _filter_aspg_I2CX_Delay

		.global _filter_aspg_I2CY_Filter

_filter_aspg_I2CY_Filter:
.hword filter_aspg_I2CNumTaps
.hword psvoffset(filter_aspg_I2CTaps)
.hword psvoffset(filter_aspg_I2CTaps)+filter_aspg_I2CNumTaps*2-1
.hword psvpage(filter_aspg_I2CTaps)
.hword _filter_aspg_I2CY_Delay
.hword _filter_aspg_I2CY_Delay+filter_aspg_I2CNumTaps*2-1
.hword _filter_aspg_I2CY_Delay

		.global _filter_aspg_I2CZ_Filter

_filter_aspg_I2CZ_Filter:
.hword filter_aspg_I2CNumTaps
.hword psvoffset(filter_aspg_I2CTaps)
.hword psvoffset(filter_aspg_I2CTaps)+filter_aspg_I2CNumTaps*2-1
.hword psvpage(filter_aspg_I2CTaps)
.hword _filter_aspg_I2CZ_Delay
.hword _filter_aspg_I2CZ_Delay+filter_aspg_I2CNumTaps*2-1
.hword _filter_aspg_I2CZ_Delay

; ..............................................................................
; ..............................................................................
; Sample assembly language calling program
;  The following declarations can be cut and pasted as needed into a program
;		.extern	_FIRFilterInit
;		.extern	_FIR
;		.extern	_filter_aspg_I2CFilter
;
;		.section	.bss
;
;	 The input and output buffers can be made any desired size
;	   the value 40 is just an example - however, one must ensure
;	   that the output buffer is at least as long as the number of samples
;	   to be filtered (parameter 1)
;input:		.space	40
;output:	.space	40
;		.text
;
;
;  This code can be copied and pasted as needed into a program
;
;
; Set up pointers to access input samples, filter taps, delay line and
; output samples.
;		mov	#_filter_aspg_I2CFilter, W0	; Initalize W0 to filter structure
;		call	_FIRDelayInit	; call this function once
;
; The next 4 instructions are required prior to each subroutine call
; to _FIR
;		mov	#_filter_aspg_I2CFilter, W3	; Initalize W3 to filter structure
;		mov	#input, W2	; Initalize W2 to input buffer 
;		mov	#output, W1	; Initalize W1 to output buffer
;		mov	#20, W0	; Initialize W0 with number of required output samples
;		call	_FIR	; call as many times as needed
