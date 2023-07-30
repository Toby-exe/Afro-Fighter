/********************************************************************
*   File:       RENDER.H
*
*   Author(s):  Tobias W
*               Jayden M
*
*   Date:       2023-03-29   
*   Purpose:    Contains all functions related to rendering the all
*               game objects to the screen based on their states
*               and positions.
*
*   Details:    The render functions use the raster library to draw
********************************************************************/

#ifndef RENDER_H
#define RENDER_H

#include "TYPES.H"
#include "sprites.h"
#include "model.h"
#include "raster.h"
#include "anims.h"
#include "splash.h"
#include "string.h"

extern unsigned int REQUEST_UI_RENDER;
extern unsigned int REQUEST_HUD_RENDER;

/*render menu*/
void renderMenuBackground(Menu *menu, UINT32 *base_32);
void renderMenuUpdate(Menu *, UINT16 *);

/*render game*/
void render(Model *, UINT16 *);
void renderHUD(Model *, UINT16 *);
void renderHealthBars(Model *, UINT16 *);
void renderProfilePics(Model *, UINT16 *);
void renderEnvironment(Model *, UINT16 *);
void renderName(char *name, UINT16 *base_16, int x, int y);

void clearAvatar(Model *);

/*movement*/
void renderAvatarIdle(Avatar *, UINT16 *);
void renderAvatarRun(Avatar *, UINT16 *);
void renderAvatarAttacking(Avatar *, UINT16 *);
void renderAvatarHeavyAttack(Avatar *, UINT16 *);
void renderAvatarBlocking(Avatar *, UINT16 *);
void renderAvatarSuper(Avatar *, UINT16 *);
/*void renderSuperBall(Avatar *, UINT16 *);*/
void DEBUG_RENDER_HITBOX(Avatar *, UINT16 *);

#endif

