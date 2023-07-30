#include "game.h"

int main()
{
    UINT8 *base = (UINT8 *)get_video_base();
    Vector origVBL = installVector(VBL_ISR, vbl_isr);
    Vector origIKBD = installVector(IKBD_ISR, ikbd_isr);
   

    clear_screen((UINT32 *)base);

    gameLoop();

    installVector(IKBD_ISR, origIKBD);
    installVector(VBL_ISR, origVBL);

    return 0;
}