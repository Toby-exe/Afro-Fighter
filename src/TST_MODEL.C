#include <osbind.h>
#include <stdio.h>
#include "raster.h"
#include "fonts.h"
#include "splash.h"
#include "model.h"

int main () {
    
    UINT8 *base = (UINT8 *) Physbase();
	UINT16 *base_16 = (UINT16 *) Physbase();
	UINT32 *base_32 = (UINT32 *) Physbase();
	UINT16 input;

    /*test game loop*/
    while(1 && input != q_KEY) {
        /*plot bitmap */
        input = Cconin();
    }

    return 0;
};