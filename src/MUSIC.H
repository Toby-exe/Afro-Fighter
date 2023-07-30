#ifndef MUSIC_H
#define MUSIC_H

#include "psg.h"
#include "vbl.h"
#include "keys.h"

/*note: 1 beat = 32Hz = 0.45s*/
#define WHOLE_NOTE 128      /*4 beats (1 full bar)*/
#define HALF_NOTE 64        /*2 beats*/
#define QUARTER_NOTE 32     /*1 beats*/
#define EIGHTH_NOTE 16      /*1/2 beats*/
#define SIXTEENTH_NOTE 8    /*1/4 beats*/

void start_music();
void update_music(bool sndfx_on);


#endif
