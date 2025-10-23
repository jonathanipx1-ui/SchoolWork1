
.include "xc.inc"

.text                       ;BP (put the following data in ROM(program memory))

; This is a library, thus it can *not* contain a _main function: the C file will
; define main().  However, we will need a .global statement to make available ASM
; functions to C code.
; All functions utilized outside of this file will need to have a leading 
; underscore (_) and be included in a comment delimited list below.
.global _example_public_function, _second_public_function, _write_0, _write_1, _delay_100us, _delay_1ms



_delay_1ms:	    ; 8000 cycles
		    ; func call 2 cycles
    repeat #7993   ; 1 cycle
    nop		    ; 7993 + 1 cycles
    return	    ; 3 cycles