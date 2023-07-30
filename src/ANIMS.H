/********************************************************************
*   File:       ANIMS.H
*
*   Author(s):  Tobias W
*               Jayden M
*
*   Date:       2022-03-29 
*   Purpose:    Simply initializes the animations for the avatar
*               and stores them in the globaly accessible Animations
********************************************************************/

#ifndef ANIMS_H
#define ANIMS_H

#include "types.h"
#include "sprites.h"

/*rs animations*/
extern Animation avatarIdleRS, avatarRunRS, avatarLightAttackRS, avatarHeavyAttackRS, avatarSuperRS, avatarBlockRS;
/*ls animations*/
extern Animation avatarIdleLS, avatarRunLS, avatarLightAttackLS, avatarHeavyAttackLS, avatarSuperLS, avatarBlockLS;

extern Frame RUN_F1_LS, RUN_F2_LS, RUN_F3_LS, RUN_F4_LS;
extern Frame RUN_F1_RS, RUN_F2_RS, RUN_F3_RS, RUN_F4_RS;

extern Frame IDLE_F1_LS, IDLE_F2_LS;
extern Frame IDLE_F1_RS, IDLE_F2_RS;

extern Frame BLOCK_F1_LS;
extern Frame BLOCK_F1_RS;

extern Frame LIGHT_ATTACK_F1_LS;
extern Frame LIGHT_ATTACK_F1_RS;

extern Frame HEAVY_ATTACK_F1_RS;
extern Frame HEAVY_ATTACK_F1_LS;

extern Frame SUPER_F1_LS, SUPER_F2_LS, SUPER_F3_LS, SUPER_F4_LS, SUPER_F5_LS, SUPER_F6_LS, SUPER_F7_LS;
extern Frame SUPER_F1_RS, SUPER_F2_RS, SUPER_F3_RS, SUPER_F4_RS, SUPER_F5_RS, SUPER_F6_RS, SUPER_F7_RS;

extern Frame idleAnimationLS[2];
extern Frame idleAnimationRS[2];

extern Frame blockAnimationLS[1];
extern Frame blockAnimationRS[1];

extern Frame runAnimationLS[5];
extern Frame runAnimationRS[5];

extern Frame lightAttackAnimationLS[1];
extern Frame lightAttackAnimationRS[1];

extern Frame heavyAttackAnimationLS[1];
extern Frame heavyAttackAnimationRS[1];

extern Frame superAnimationLS[7];

void initAnimations();
void initFrames();

void initIdleFrames();
void initBlockFrames();
void initRunFrames();
void initLightAttackFrames();
void initSuperFrames();
void initHeavyAttackFrames();

void initIdleAnimationLS();
void initIdleAnimationRS();

void initBlockAnimationLS();
void initBlockAnimationRS();

void initRunAnimationLS();
void initRunAnimationRS();

void initLightAttackAnimationLS();
void initLightAttackAnimationRS();

void initHeavyAttackAnimationLS();
void initHeavyAttackAnimationRS();

void initSuperAnimationLS();



#endif