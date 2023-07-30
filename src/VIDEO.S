;-----------------------------------------------------------------------------
;   File:       VIDEO.S
;   Author(s):  Tobias W
;               Jayden M
;   Date:       2022-03-29  
;   Purpose:    Video buffer manipulation
;-----------------------------------------------------------------------------
                xdef _get_buffer
                xdef _set_buffer

VDL_VBH         equ     $FFFF8201   ;video base high
VDL_VBM         equ     $FFFF8203   ;video base middle
OFFSET 	        equ 	8
;---------------------------------------------------------------------------
; UINT16 *get_video_base()
; {
; 	/*see memory table for naming*/
; 	UINT8 *VDL_VBH = (UINT8 *) 0xFFFF8201; 
; 	UINT8 *VDL_VBM = (UINT8 *) 0xFFFF8203;
; 	UINT8 baseHi, baseMi;
; 	UINT32 base;
; 	long oldSsp;

; 	oldSsp = Super(0);
; 	baseHi = *VDL_VBH;
; 	baseMi = *VDL_VBM;
; 	Super(oldSsp);

; 	base = ((UINT32) baseHi << 16);
; 	base |= ((UINT32) baseMi << 8);
	
; 	return (UINT16*) base;
; }
;
;   Attempt at translating get the the buffer portion of the code to asm
;---------------------------------------------------------------------------
;   Name:           get_buffer
;   Purpose:        Get the video buffer
;   Details:        returns the current video buffer address
;   Outputs:        UINT16 *buffer - the current buffer address
;---------------------------------------------------------------------------
_get_buffer:    move.l  d1,-(sp)        ;save d1

                clr.l   d0              ;equavilent to baseHi;
                clr.l   d1              ;equavilent to baseMi;

                move.b  (VDL_VBH),d0    ;baseHi = *VDL_VBH;
                move.b  (VDL_VBM),d1    ;baseMi = *VDL_VBM;

                lsl.l   #8,d0           ;base = ((UINT32) baseHi << 16);
                lsl.l   #8,d0

                lsl.l   #8,d1           ;base |= ((UINT32) baseMi << 8);

                or.l    d1,d0           ;base = baseHi << 16 | baseMi << 8;

                move.l  (sp)+,d1        ;restore d1
                rts


;---------------------------------------------------------------------------
;   Name:           set_buffer
;   Purpose:        Set the video buffer
;   Details:        updates/sets the video base register to the 
;                   new buffer (input address)
;   Inputs:         UINT16 *buffer - the new buffer address
;---------------------------------------------------------------------------
_set_buffer:    
                link	a6,#0
                movem.l	d0/a0,-(sp)

                move.l 	OFFSET(a6),d0
                lsr.l 	#8,d0
                lea 	VDL_VBH,a0
                movep.w d0,0(a0)

                movem.l (sp)+,d0/a0
                unlk	a6
                rts  
