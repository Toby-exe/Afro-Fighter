#include <osbind.h>
#include <stdio.h>
#include "raster.h"
#include "fonts.h"
#include "splash.h"

int main()
{
	
    UINT8 *base = (UINT8 *) Physbase();
	UINT16 *base_16 = (UINT16 *) Physbase();
	UINT32 *base_32 = (UINT32 *) Physbase();
	UINT16 input;
	int y, x, i;
	
	const UINT8 letterEbitmap [] = {
		0x00,0x7E,0x40,0x7C,0x40,0x40,0x7E,0x00
	};

	/*plot a rect at 416 x and 0 y that goes to 640 x and 400 y */
	fill_screen(base);
	
	Cconin();

	clear_screen((UINT32*)base);
	/*arena base/floor*/
	/*plotRectFill(base, 640, 48, 0, 354);*/

	/*plot bit map with font array*/
	plotBitmap16(base_16, 1, 1, avatarProfilePic, 48, 48);
	plotBitmap16(base_16, 2, 49, avatarProfilePic, 48, 48);
	plotBitmap16(base_16, 3, 97, avatarProfilePic, 48, 48);
	
	/*plot letter E*/
	printString(base, 62, 36, 8, "TO");
	printString(base, 553, 36, 8, "TO");

	/*plot afro fighter (fix issue with greys)*/

	Cconin();
	/*plot the avatarPP*/

    return 0;	
}
  