/********************************************************************
*   File:       SPRITES.H
*
*   Author(s):  Tobias W
*               Jayden M
*
*   Date:       2022-03-29   
*   Purpose:    Simply initializes and the sprites for the avatar  
*               and stores them in the globaly accessible bitmaps
********************************************************************/

#ifndef SPRITES_H
#define SPRITES_H

#include "types.h"

/************Idle Bitmaps************************/

/*Left Facing*/
extern UINT16 bm_avatarIdleF1_LS [];
extern UINT16 bm_avatarIdleF2_LS [];
/*Right Facing*/
extern UINT16 bm_avatarIdleF1_RS [];
extern UINT16 bm_avatarIdleF2_RS [];

/**********Blocking Bitmaps *********************/

/*Left Facing*/
extern UINT16 bm_avatarBlockF1_LS [];
/*Right Facing*/
extern UINT16 bm_avatarBlockF1_RS [];

/************Run Bitmaps*************************/

/*Left Facing*/
extern UINT16 bm_avatarRunF1_LS [];
extern UINT16 bm_avatarRunF2_LS [];
extern UINT16 bm_avatarRunF3_LS [];
extern UINT16 bm_avatarRunF4_LS [];
/*Right Facing*/
extern UINT16 bm_avatarRunF1_RS [];
extern UINT16 bm_avatarRunF2_RS [];
extern UINT16 bm_avatarRunF3_RS [];
extern UINT16 bm_avatarRunF4_RS [];


/************Light Attack Bitmaps****************/

/*Left Facing*/
extern UINT16 bm_avatarLightAttackF1_LS[];
/*Right Facing*/
extern UINT16 bm_avatarLightAttackF1_RS[];

/************Heavy Attack Bitmaps****************/

/*Left Facing*/
extern UINT16 bm_avatarHeavyAttackF1_LS[];
/*Right Facing*/
extern UINT16 bm_avatarHeavyAttackF1_RS[];

/*************Super aAtack Bitmaps***************/

/*Left Facing*/
extern UINT16 bm_avatarSuperF1_LS[];
extern UINT16 bm_avatarSuperF2_LS[];
extern UINT16 bm_avatarSuperF3_LS[];
extern UINT16 bm_avatarSuperF4_LS[];
extern UINT16 bm_avatarSuperF5_LS[];
extern UINT16 bm_avatarSuperF6_LS[];
extern UINT16 bm_avatarSuperF7_LS[];
/*Right Facing*/
extern UINT16 bm_avatarSuperF1_RS[];
extern UINT16 bm_avatarSuperF2_RS[];
extern UINT16 bm_avatarSuperF3_RS[];
extern UINT16 bm_avatarSuperF4_RS[];
extern UINT16 bm_avatarSuperF5_RS[];
extern UINT16 bm_avatarSuperF6_RS[];
extern UINT16 bm_avatarSuperF7_RS[];

/*super ball projectile*/
/*left*/
extern UINT16 bm_superBallF1_LS[];
/*right*/
extern UINT16 bm_superBallF1_RS[];

/*profile picture*/
/*left*/
extern UINT16 bm_profilePic_LS[];
/*right*/
extern UINT16 bm_profilePic_RS[];



#endif
