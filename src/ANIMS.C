/********************************************************************
*   File:       ANIMS.C
*
*   Author(s):  Tobias W
*               Jayden M
*
*   Date:       2022-03-29     
********************************************************************/

#include "anims.h"

Frame RUN_F1_LS, RUN_F2_LS, RUN_F3_LS, RUN_F4_LS;
Frame RUN_F1_RS, RUN_F2_RS, RUN_F3_RS, RUN_F4_RS;
Frame IDLE_F1_LS, IDLE_F2_LS;
Frame IDLE_F1_RS, IDLE_F2_RS;
Frame LIGHT_ATTACK_F1_LS;
Frame LIGHT_ATTACK_F1_RS;
Frame HEAVY_ATTACK_F1_RS;
Frame HEAVY_ATTACK_F1_LS;
Frame BLOCK_F1_LS;
Frame BLOCK_F1_RS;
Frame SUPER_F1_LS, SUPER_F2_LS, SUPER_F3_LS, SUPER_F4_LS, SUPER_F5_LS, SUPER_F6_LS, SUPER_F7_LS;

Frame idleAnimationLS[2];
Frame idleAnimationRS[2];
Frame runAnimationLS[5];
Frame runAnimationRS[5];
Frame lightAttackAnimationLS[1];
Frame lightAttackAnimationRS[1];
Frame heavyAttackAnimationLS[1];
Frame heavyAttackAnimationRS[1];
Frame blockAnimationLS[1];
Frame blockAnimationRS[1];
Frame superAnimationLS[7];

/*rs animations*/
Animation avatarIdleRS, avatarRunRS, avatarLightAttackRS, avatarHeavyAttackRS, avatarSuperRS, avatarBlockRS;
/*ls animations*/
Animation avatarIdleLS, avatarRunLS, avatarLightAttackLS, avatarHeavyAttackLS, avatarSuperLS, avatarBlockLS;

void initAnimations() {
    initFrames();
    initIdleAnimationLS();
    initIdleAnimationRS();
    initRunAnimationLS();
    initRunAnimationRS();
    initLightAttackAnimationLS();
    initLightAttackAnimationRS();
    initHeavyAttackAnimationRS();
    initHeavyAttackAnimationLS();
    initBlockAnimationLS();
    initBlockAnimationRS();
    initSuperAnimationLS();

}

void initFrames() {
    initIdleFrames();
    initRunFrames();
    initLightAttackFrames();
    initHeavyAttackFrames();
    initBlockFrames();
    initSuperFrames();
}

void initIdleAnimationLS()
{
    idleAnimationLS[0] = IDLE_F1_LS;
    idleAnimationLS[1] = IDLE_F2_LS;

    avatarIdleLS.frames = idleAnimationLS;
    avatarIdleLS.numFrames = 2;
    avatarIdleLS.offsetX = 0;
    avatarIdleLS.duration = 6;
};

void initIdleAnimationRS()
{
    idleAnimationRS[0] = IDLE_F1_RS;
    idleAnimationRS[1] = IDLE_F2_RS;

    avatarIdleRS.frames = idleAnimationRS;
    avatarIdleRS.numFrames = 2;
    avatarIdleRS.offsetX = 0;
    avatarIdleRS.duration = 6;
};

void initBlockAnimationLS()
{
    blockAnimationLS[0] = BLOCK_F1_LS;

    avatarBlockLS.frames = blockAnimationLS;
    avatarBlockLS.numFrames = 1;
    avatarBlockLS.offsetX = 0;
};

void initBlockAnimationRS()
{
    blockAnimationRS[0] = BLOCK_F1_RS;

    avatarBlockRS.frames = blockAnimationRS;
    avatarBlockRS.numFrames = 1;
    avatarBlockRS.offsetX = 0;
};

void initRunAnimationLS()
{
    runAnimationLS[0] = RUN_F1_LS;
    runAnimationLS[1] = RUN_F2_LS;
    runAnimationLS[2] = RUN_F3_LS;
    runAnimationLS[3] = RUN_F2_LS;
    runAnimationLS[4] = RUN_F1_LS;
    runAnimationLS[5] = RUN_F4_LS;
    


    avatarRunLS.frames = runAnimationLS;
    avatarRunLS.numFrames = 5;
    avatarIdleLS.offsetX = 0;
    avatarRunLS.duration = 2;
};

void initRunAnimationRS()
{
    runAnimationRS[0] = RUN_F1_RS;
    runAnimationRS[1] = RUN_F2_RS;
    runAnimationRS[2] = RUN_F3_RS;
    runAnimationRS[3] = RUN_F2_RS;
    runAnimationRS[4] = RUN_F1_RS;
    runAnimationRS[5] = RUN_F4_RS;

    avatarRunRS.frames = runAnimationRS;
    avatarRunRS.numFrames = 5;
    avatarRunRS.offsetX = 0;
    avatarRunRS.duration = 2;
};

void initLightAttackAnimationLS()
{
    lightAttackAnimationLS[0] = LIGHT_ATTACK_F1_LS;

    avatarLightAttackLS.frames = lightAttackAnimationLS;
    avatarLightAttackLS.numFrames = 0;
    avatarLightAttackLS.offsetX = -16;
    avatarLightAttackLS.duration = 1;
};

void initLightAttackAnimationRS()
{
    lightAttackAnimationRS[0] = LIGHT_ATTACK_F1_RS;

    avatarLightAttackRS.frames = lightAttackAnimationRS;
    avatarLightAttackRS.numFrames = 0;
    avatarLightAttackRS.offsetX = 0;
    avatarLightAttackLS.duration = 1;
};

void initHeavyAttackAnimationLS()
{
    heavyAttackAnimationLS[0] = HEAVY_ATTACK_F1_LS;

    avatarHeavyAttackLS.frames = heavyAttackAnimationLS;
    avatarHeavyAttackLS.numFrames = 1;
    avatarHeavyAttackLS.offsetX = -16;
};

void initHeavyAttackAnimationRS()
{
    heavyAttackAnimationRS[0] = HEAVY_ATTACK_F1_RS;

    avatarHeavyAttackRS.frames = heavyAttackAnimationRS;
    avatarHeavyAttackRS.numFrames = 1;
    avatarHeavyAttackRS.offsetX = 0;
};

void initSuperAnimationLS()
{
    superAnimationLS[0] = SUPER_F1_LS;
    superAnimationLS[1] = SUPER_F2_LS;
    superAnimationLS[2] = SUPER_F3_LS;
    superAnimationLS[3] = SUPER_F4_LS;
    superAnimationLS[4] = SUPER_F5_LS;
    superAnimationLS[5] = SUPER_F6_LS;
    superAnimationLS[6] = SUPER_F7_LS;

    avatarSuperLS.frames = superAnimationLS;
    avatarSuperLS.numFrames = 7;
    avatarSuperLS.offsetX = 0;
    avatarSuperLS.duration = 3;
};

void initIdleFrames(){
    IDLE_F1_LS.bitmap = bm_avatarIdleF1_LS;
    IDLE_F1_LS.width = 48;
    IDLE_F1_LS.height = 80;
    IDLE_F1_LS.offsetX = 0;
    IDLE_F1_LS.offsetY = 0;

    IDLE_F2_LS.bitmap = bm_avatarIdleF2_LS;
    IDLE_F2_LS.width = 48;
    IDLE_F2_LS.height = 80;
    IDLE_F2_LS.offsetX = 0;
    IDLE_F2_LS.offsetY = 0;

    IDLE_F1_RS.bitmap = bm_avatarIdleF1_RS;
    IDLE_F1_RS.width = 48;
    IDLE_F1_RS.height = 80;
    IDLE_F1_LS.offsetX = 0;
    IDLE_F1_LS.offsetY = 0;

    IDLE_F2_RS.bitmap = bm_avatarIdleF2_RS;
    IDLE_F2_RS.width = 48;
    IDLE_F2_RS.height = 80;
    IDLE_F2_LS.offsetX = 0;
    IDLE_F2_LS.offsetY = 0;

}

void initBlockFrames(){
    BLOCK_F1_LS.bitmap = bm_avatarBlockF1_LS;
    BLOCK_F1_LS.width = 48;
    BLOCK_F1_LS.height = 80;
    BLOCK_F1_LS.offsetX = 0;
    BLOCK_F1_LS.offsetY = 0;

    BLOCK_F1_RS.bitmap = bm_avatarBlockF1_RS;
    BLOCK_F1_RS.width = 48;
    BLOCK_F1_RS.height = 80;
    BLOCK_F1_RS.offsetX = 0;
    BLOCK_F1_RS.offsetY = 0;
}

void initRunFrames(){
    RUN_F1_LS.bitmap = bm_avatarRunF1_LS;
    RUN_F1_LS.width = 48;
    RUN_F1_LS.height = 80;
    RUN_F1_LS.offsetX = 0;
    RUN_F1_LS.offsetY = 0;


    RUN_F2_LS.bitmap = bm_avatarRunF2_LS;
    RUN_F2_LS.width = 48;
    RUN_F2_LS.height = 82;
    RUN_F2_LS.offsetX = 0;
    RUN_F2_LS.offsetY = -2;

    RUN_F3_LS.bitmap = bm_avatarRunF3_LS;
    RUN_F3_LS.width = 48;
    RUN_F3_LS.height = 80;
    RUN_F3_LS.offsetX = 0;
    RUN_F3_LS.offsetY = 0;

    RUN_F4_LS.bitmap = bm_avatarRunF4_LS;
    RUN_F4_LS.width = 48;
    RUN_F4_LS.height = 68;
    RUN_F4_LS.offsetX = 0;
    RUN_F4_LS.offsetY = 2;

    RUN_F1_RS.bitmap = bm_avatarRunF1_RS;
    RUN_F1_RS.width = 48;
    RUN_F1_RS.height = 80;
    RUN_F1_RS.offsetX = 0;
    RUN_F1_RS.offsetY = 0;

    RUN_F2_RS.bitmap = bm_avatarRunF2_RS;
    RUN_F2_RS.width = 48;
    RUN_F2_RS.height = 82;
    RUN_F2_RS.offsetX = 0;
    RUN_F2_RS.offsetY = -2;

    RUN_F3_RS.bitmap = bm_avatarRunF3_RS;
    RUN_F3_RS.width = 48;
    RUN_F3_RS.height = 80;
    RUN_F3_RS.offsetX = 0;
    RUN_F3_RS.offsetY = 0;

    RUN_F4_RS.bitmap = bm_avatarRunF4_RS;
    RUN_F4_RS.width = 48;
    RUN_F4_RS.height = 68;
    RUN_F4_RS.offsetX = 0;
    RUN_F4_RS.offsetY = 2;


}

void initLightAttackFrames(){
    LIGHT_ATTACK_F1_LS.bitmap = bm_avatarLightAttackF1_LS;
    LIGHT_ATTACK_F1_LS.width = 64;
    LIGHT_ATTACK_F1_LS.height = 80;
    LIGHT_ATTACK_F1_LS.offsetX = -16;
    LIGHT_ATTACK_F1_LS.offsetY = 0;

    LIGHT_ATTACK_F1_RS.bitmap = bm_avatarLightAttackF1_RS;
    LIGHT_ATTACK_F1_RS.width = 64;
    LIGHT_ATTACK_F1_RS.height = 80;
    LIGHT_ATTACK_F1_RS.offsetX = 0;
    LIGHT_ATTACK_F1_RS.offsetY = 0;
}

void initHeavyAttackFrames(){
    HEAVY_ATTACK_F1_LS.bitmap = bm_avatarHeavyAttackF1_LS;
    HEAVY_ATTACK_F1_LS.width = 64;
    HEAVY_ATTACK_F1_LS.height = 80;
    HEAVY_ATTACK_F1_LS.offsetX = -16;
    HEAVY_ATTACK_F1_LS.offsetY = 0;


    HEAVY_ATTACK_F1_RS.bitmap = bm_avatarHeavyAttackF1_RS;
    HEAVY_ATTACK_F1_RS.width = 64;
    HEAVY_ATTACK_F1_RS.height = 80;
    HEAVY_ATTACK_F1_RS.offsetX = 0;
    HEAVY_ATTACK_F1_RS.offsetY = 0;
}

void initSuperFrames(){
    SUPER_F1_LS.bitmap = bm_avatarSuperF1_LS;
    SUPER_F1_LS.width = 64;
    SUPER_F1_LS.height = 80;

    SUPER_F2_LS.bitmap = bm_avatarSuperF2_LS;
    SUPER_F2_LS.width = 64;
    SUPER_F2_LS.height = 80;

    SUPER_F3_LS.bitmap = bm_avatarSuperF3_LS;
    SUPER_F3_LS.width = 64;
    SUPER_F3_LS.height = 80;

    SUPER_F4_LS.bitmap = bm_avatarSuperF4_LS;
    SUPER_F4_LS.width = 64;
    SUPER_F4_LS.height = 80;

    SUPER_F5_LS.bitmap = bm_avatarSuperF5_LS;
    SUPER_F5_LS.width = 64;
    SUPER_F5_LS.height = 80;

    SUPER_F6_LS.bitmap = bm_avatarSuperF6_LS;
    SUPER_F6_LS.width = 64;
    SUPER_F6_LS.height = 80;

    SUPER_F7_LS.bitmap = bm_avatarSuperF7_LS;
    SUPER_F7_LS.width = 64;
    SUPER_F7_LS.height = 80;
}