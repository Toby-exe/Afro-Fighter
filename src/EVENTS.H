#ifndef EVENTS_H
#define EVENTS_H

#include <osbind.h>
#include "TYPES.H"
#include "model.h"

typedef enum 
{
    jumpEv,
    crouchEv,
    moveEv,
    lightAttackEv,
    heavyAttackEv,
    superEv,
    blockEv,
    deathEv,
    noEv
}avatarEvents;



avatarStates on_move(Avatar *, UINT16);
avatarStates on_jump(Avatar *, UINT16);
avatarStates on_crouch(Avatar *, UINT16);
avatarStates on_lightAttack(Avatar *, UINT16);
avatarStates on_heavyAttack(Avatar *, UINT16);
avatarStates on_block(Avatar *, UINT16);
avatarStates on_super(Avatar *, UINT16);
avatarStates on_death(Avatar *);

void collisionCheck(Model *);

#endif