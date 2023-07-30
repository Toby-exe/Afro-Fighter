#include "TYPES.H"
#include "model.h"
#include "render.h"
#include "game.h"
#include "VBL.H"
#include <osbind.h>



int main () {

    Model model;
    UINT32 timeThen, timeNow, timeDelta;
    UINT8 *base = (UINT8 *) Physbase();
    bool rendering = true;
    unsigned int input;

    
    initPlayer(&model.player, 200, 300);

    clear_screen((UINT32*)base);
    while (rendering == true) {
        timeNow = getTime();
        timeDelta = timeNow - timeThen;

        if(Cconis()) {
            input = Cnecin();
        
            if (input == q_KEY) {
                rendering = false;
            }
        }
        if(timeDelta > 0) {
            renderAvatarIdle(&model.player); 
            Vsync();
            clear_screen((UINT32*)base);
            timeThen = timeNow;
        }   
    }

    return 0;
}

