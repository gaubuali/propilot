


; MATH_ERROR 1
; STACK_ERROR 2
; ADDRESS_ERROR 4
; OSC_FAIL 8
; unhandled interrupt 16

.extern	_trap_flags
.extern _trap_source

.global __MathError
.global __StackError
.global __AddressError
.global __OscillatorFail

.ifdecl __dsPIC30F
__MathError:	mov.w #1,w0
				mov.w w0,_trap_flags
				pop	w0
				pop w0
				mov.w w0,_trap_source
				reset

__StackError:	mov.w #2,w0
				mov.w w0,_trap_flags
				pop	w0
				pop w0
				mov.w w0,_trap_source
				reset

__AddressError:	mov.w #4,w0
				mov.w w0,_trap_flags
				pop	w0
				pop w0
				mov.w w0,_trap_source
				reset


__OscillatorFail: mov.w #8,w0
				mov.w w0,_trap_flags
				pop	w0
				pop w0
				mov.w w0,_trap_source
				reset
.else
.global	__DefaultInterrupt

__MathError:	mov.w	#1,w0
				bra		save_states

__StackError:	mov.w	#2,w0
				bra		save_states

__AddressError:	mov.w	#4,w0
				bra		save_states


__OscillatorFail: mov.w #8,w0
				bra		save_states

__DefaultInterrupt:
				mov.w #16,w0

save_states:
				mov.w	w0,_trap_flags
				pop.d	w0
				and		#0x7f,w1
				mov.w	w0,_trap_source
				mov.w	w1,_trap_source+2
				reset
.endif

