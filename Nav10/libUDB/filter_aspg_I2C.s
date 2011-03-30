; ..............................................................................
;    File   filter_aspg_I2C.s
; ..............................................................................

		.equ filter_aspg_I2CNumTaps, 32

; ..............................................................................
; Allocate and initialize filter taps

		.section .filter_aspg_I2Cconst, code
		.align 64

filter_aspg_I2CTaps:
.hword 	0xFFEC,	0xFFE9,	0x000C,	0x0061,	0x00C8,	0x00EA,	0x0064,	0xFF0E,	0xFD47
.hword 	0xFC13,	0xFCC4,	0x005D,	0x06E8,	0x0F21,	0x16C1,	0x1B5A,	0x1B5A,	0x16C1
.hword 	0x0F21,	0x06E8,	0x005D,	0xFCC4,	0xFC13,	0xFD47,	0xFF0E,	0x0064,	0x00EA
.hword 	0x00C8,	0x0061,	0x000C,	0xFFE9,	0xFFEC

; ..............................................................................
; Allocate delay line in (uninitialized) Y data space

;;		.section .ybss, bss, ymemory
		.section filter_aspg_I2C, ymemory, address(0x7700)
;;		.section .ydata, address(0x7700)

		.align 64
		.global _filter_aspg_I2CX_Delay
filter_aspg_I2CX_Delay:
		.space filter_aspg_I2CNumTaps*2

		.align 64
		.global _filter_aspg_I2CY_Delay
filter_aspg_I2CY_Delay:
		.space filter_aspg_I2CNumTaps*2

		.align 64
		.global _filter_aspg_I2CZ_Delay
filter_aspg_I2CZ_Delay:
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
.hword filter_aspg_I2CX_Delay
.hword filter_aspg_I2CX_Delay+filter_aspg_I2CNumTaps*2-1
.hword filter_aspg_I2CX_Delay

		.global _filter_aspg_I2CY_Filter

_filter_aspg_I2CY_Filter:
.hword filter_aspg_I2CNumTaps
.hword psvoffset(filter_aspg_I2CTaps)
.hword psvoffset(filter_aspg_I2CTaps)+filter_aspg_I2CNumTaps*2-1
.hword psvpage(filter_aspg_I2CTaps)
.hword filter_aspg_I2CY_Delay
.hword filter_aspg_I2CY_Delay+filter_aspg_I2CNumTaps*2-1
.hword filter_aspg_I2CY_Delay

		.global _filter_aspg_I2CZ_Filter

_filter_aspg_I2CZ_Filter:
.hword filter_aspg_I2CNumTaps
.hword psvoffset(filter_aspg_I2CTaps)
.hword psvoffset(filter_aspg_I2CTaps)+filter_aspg_I2CNumTaps*2-1
.hword psvpage(filter_aspg_I2CTaps)
.hword filter_aspg_I2CZ_Delay
.hword filter_aspg_I2CZ_Delay+filter_aspg_I2CNumTaps*2-1
.hword filter_aspg_I2CZ_Delay

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
