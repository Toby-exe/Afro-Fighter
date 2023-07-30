/********************************************************************
*   File:       VBL.C
*
*   Author(s):  Tobias W
*               Jayden M
*
*   Date:       2022-03-29   
********************************************************************/
#include "VBL.H"

/*init timers*/
int TIMER_AI_ACTION = 0;
int TIMER_MUSIC_A = 0;
int TIMER_MUSIC_B = 0;
int TIMER_MUSIC_C = 0;
int TIMER_SNDFX = 0;

int gSeconds;
UINT32 gTicks;
bool vblFlag;

/********************************************************************
 *  Name:   do_vbl_isr
 * 
 *  Details:  This function is called every time the VBL interrupt is
 *            triggered. It increments the timers and updates the
 *            music and sound effects.
 ********************************************************************/

void do_vbl_isr()
{
    bool sndfx_on;

    gTicks += 1;

    /*increment timers*/
    TIMER_AI_ACTION++;
    TIMER_MUSIC_A++;
    TIMER_MUSIC_B++;
    TIMER_MUSIC_C++;
    TIMER_SNDFX++;

    sndfx_on = update_sndfx();
    update_music(sndfx_on);

    /*increment seconds every 70 invocations of this function*/
    if (gTicks % 70 == 0)
    {
        gSeconds++;
    }
    vblFlag = 1;
    
}

void myVsync()
{
    while (!vblFlag)
        ; 
    vblFlag = false;
    return;
}

UINT32 getTime()
{
    return gTicks;
}

void setVblFlag() {
    vblFlag = false;
}

void setgTicks() {
    gTicks = 0;
}

void setgSeconds() {
    gSeconds = 0;
}