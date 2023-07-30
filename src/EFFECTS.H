#ifndef EFFECTS_H
#define EFFECTS_H

#include "psg.h"
#include "types.h"
#include "vbl.h"
#include "isr.h"

/*asynchronously activated effects*/
void play_hit_effect();
void play_kick_effect();
void play_explosion_effect();

/*synchronous controller*/
bool update_sndfx();

/*helper methods*/
void stop_effects();

#endif