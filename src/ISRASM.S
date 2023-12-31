;-----------------------------------------------------------------------------
;   File:       ISRASM.S
;   Author(s):  Tobias W
;               Jayden M
;   Date:       2022-03-29   
;   Purpose:    Interrupts and the IKBD
;-----------------------------------------------------------------------------
MFP_ISRB    equ     $FFFA11

            xdef    _ikbd_isr
            xdef    _set_ipl
            xdef    _vbl_isr
            xref    _do_ikbd_isr
            xref    _do_vbl_isr
;-----------------------------------------------------------------------------
;   Name:       ikbd_isr
;   Purpose:    Interrupt service routine for the IKBD
;   Details:    This routine is called when the IKBD generates an interrupt.
;-----------------------------------------------------------------------------

_ikbd_isr:  movem.l d0-d2/a0-a2,-(sp)   ;refer to lab 7 (scratch space)
            jsr     _do_ikbd_isr
            movem.l (sp)+,d0-d2/a0-a2
            bclr.b  #6,MFP_ISRB
            rte

;-----------------------------------------------------------------------------
;   Name:       vbl_isr
;   Purpose:    Interrupt service routine for the VBL
;   Details:    This routine is called when the VBL generates an interrupt.
;-----------------------------------------------------------------------------
_vbl_isr:   movem.l d0-d2/a0-a2,-(sp)   ;refer to lab 7 (scratch space)
            jsr     _do_vbl_isr
            movem.l (sp)+,d0-d2/a0-a2
            rte

;-----------------------------------------------------------------------------
;   Name:       set_ipl
;   Purpose:    Sets IPL = mask, returns old IPL (interrupt priority level)
;   Details:    Must be called from supervisor mode.
;-----------------------------------------------------------------------------
_set_ipl:   move.w  sr,d0
            move.w  d0,-(sp)    ; place orig. sr on stack

            lsr.w   #8,d0       ; will return orig. ipl
            and.w   #$0007,d0   ; ... in d0.w
            
            andi.w  #$F8FF,(sp)
            move.w  d1,-(sp)
            move.w  8(sp),d1    ; place new ipl in d1.w
            lsl.w   #8,d1
            and.w   #$0700,d1
            or.w    d1,2(sp)    ; insert it into sr on stack
            move.w  (sp)+,d1

            rte                 ; trick: when returning,
                                ; ... install modified sr
                                ; ... from stack!
