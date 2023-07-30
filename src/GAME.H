/******************************************************************************
*   File:       GAME.H
*
*   Author(s):  Tobias W
*               Jayden M
*
*   Date:       2022-03-29     
*   Purpose:    This module contains the game loop and the game 
*               states + logic for the award winning
*               AfroFighter game.
*
*   Details:   The over all game is controlled by the game finite state machine
*              where as the gameplay is controlled by the game loop and each
*              avatar by its own finite state machine. 
*              
*              Rules:
*                   - Fight computer opponent to the death
*                   - Only use one move at a time
*                   - Jump to evade attacks
*                   - Block to reduce damage from oncoming attacks
*
*              How to play:
*                   A     - move right
*                   D     - move left
*                   SPACE - Jump
*                   L     - Crouch 
*                   W     - Light attack
*                   I     - Heavy attack
*                   F     - Super attack (Coming soon)
*                   J     - Block
*
*
*   Known Bugs: 
*        -  1. Player continues to move in direction of last key press
*
*              How to reproduce: move in any direction, then press and hold
*              the key for the opposite direction. Player will continue to
*              move in the direction of the previous key press.
*
*              Likely cause: The custom IKBD does not check to see what the 
*              previous key press was. It only checks to see if the key is
*              currently pressed. 
*
*        -  2. Extreme mouse flickering as mouch approches the top 15 percent 
*              of the screen, the flickering is gradual and becomes more 
*              noticable as the mouse approaches the top of the screen. At the 
*              top of the screen the mouse is virtually invisible.
*
*              How to reproduce: Move mouse to the top 15 percent of the screen
*
*              Likely cause: no leads as of yet
*         
******************************************************************************/ 
#ifndef GAME_H
#define GAME_H

#include <osbind.h>
#include <stdio.h>
#include "raster.h"
#include "sprites.h"
#include "plyrsm.h"
#include "oppsm.h"
#include "events.h"
#include "render.h"
#include "isr.h"
#include "ikbd.h"
#include "vbl.h"
#include "splash.h"
#include "eSplash.h"
#include "effects.h"
#include "music.h"

GameStates splashScreen(UINT16 *base16, UINT16 *secondBase16, SplashScreen *screen);
GameStates gameLoop(UINT16 *base16, UINT16 *secondBase16, Model *model);
GameStates gameOverScreen(UINT16 *base16, UINT16 *secondBase16, EndScreen *screen, GameStates winner);
void processAsync(Model *, GameStates *);
void processSync(Model *);

#endif