; ..............................................................................
;    File   filter_aspg.s
; ..............................................................................

		.equ filter_aspgNumTaps, 32

; ..............................................................................
; Allocate and initialize filter taps

		.section .filter_aspgconst, code
		.align 64

filter_aspgTaps:
.hword 	0x000B,	0x0004,	0xFFE6,	0xFFA4,	0xFF45,	0xFEDE,	0xFE9E,	0xFEC1,	0xFF88
.hword 	0x0121,	0x0399,	0x06C5,	0x0A48,	0x0DA2,	0x1044,	0x11B7,	0x11B7,	0x1044
.hword 	0x0DA2,	0x0A48,	0x06C5,	0x0399,	0x0121,	0xFF88,	0xFEC1,	0xFE9E,	0xFEDE
.hword 	0xFF45,	0xFFA4,	0xFFE6,	0x0004,	0x000B

; ..............................................................................
; Allocate delay line in (uninitialized) Y data space

;;		.section .filt_ybss, bss, ymemory, address(7600), align(64)
		.section filter_aspg, ymemory, address(0x7600)
;;		.section .ydata, address(0x7600)

		.align 64
		.global _filter_aspgDelayX
filter_aspgDelayX:
		.space filter_aspgNumTaps*2

		.align 64
		.global _filter_aspgDelayY
filter_aspgDelayY:
		.space filter_aspgNumTaps*2

		.align 64
		.global _filter_aspgDelayZ
filter_aspgDelayZ:
		.space filter_aspgNumTaps*2

; fix microchip's or the linkers stupidity of putting this at the highest 
; possible address and then having a pointer reach the address max
;		.space 2
; ..............................................................................
; Allocate and intialize filter structure

		.section .data
		.global _filter_aspgFilterX

_filter_aspgFilterX:
.hword filter_aspgNumTaps
.hword psvoffset(filter_aspgTaps)
.hword psvoffset(filter_aspgTaps)+filter_aspgNumTaps*2-1
.hword psvpage(filter_aspgTaps)
.hword filter_aspgDelayX
.hword filter_aspgDelayX+filter_aspgNumTaps*2-1
.hword filter_aspgDelayX

		.global _filter_aspgFilterY

_filter_aspgFilterY:
.hword filter_aspgNumTaps
.hword psvoffset(filter_aspgTaps)
.hword psvoffset(filter_aspgTaps)+filter_aspgNumTaps*2-1
.hword psvpage(filter_aspgTaps)
.hword filter_aspgDelayY
.hword filter_aspgDelayY+filter_aspgNumTaps*2-1
.hword filter_aspgDelayY

		.global _filter_aspgFilterZ

_filter_aspgFilterZ:
.hword filter_aspgNumTaps
.hword psvoffset(filter_aspgTaps)
.hword psvoffset(filter_aspgTaps)+filter_aspgNumTaps*2-1
.hword psvpage(filter_aspgTaps)
.hword filter_aspgDelayZ
.hword filter_aspgDelayZ+filter_aspgNumTaps*2-1
.hword filter_aspgDelayZ

; ..............................................................................
; ..............................................................................
; Sample assembly language calling program
;  The following declarations can be cut and pasted as needed into a program
;		.extern	_FIRFilterInit
;		.extern	_FIR
;		.extern	_filter_aspgFilter
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
;		mov	#_filter_aspgFilter, W0	; Initalize W0 to filter structure
;		call	_FIRDelayInit	; call this function once
;
; The next 4 instructions are required prior to each subroutine call
; to _FIR
;		mov	#_filter_aspgFilter, W3	; Initalize W3 to filter structure
;		mov	#input, W2	; Initalize W2 to input buffer 
;		mov	#output, W1	; Initalize W1 to output buffer
;		mov	#20, W0	; Initialize W0 with number of required output samples
;		call	_FIR	; call as many times as needed
