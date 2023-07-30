/********************************************************************
*   File:       VBL.H
*
*   Author(s):  Tobias W
*               Jayden M
*
*   Date:       2022-03-29   
*   Purpose:    Contains all functions related to the vertical blank
*               interrupt/timer
********************************************************************/
#ifndef VBL_H
#define VBL_H

#include "ISR.H"
#include "types.h"
#include "effects.h"
#include "music.h"

/*--------- { Timers } ----------*/
/*human player*/
extern int TIMER_PUNCH; /*cooldown timers (might be checked in async)*/
extern int TIMER_KICK;

/*non-human player*/
extern int TIMER_AI_ACTION;

/*sound*/
extern int TIMER_MUSIC_A;
extern int TIMER_MUSIC_B;
extern int TIMER_MUSIC_C;
extern int TIMER_SNDFX;


void myVsync();
void do_vbl_isr();
UINT32 getTime();
void setgTicks();
void setgSeconds();
void setVblFlag();


#endif