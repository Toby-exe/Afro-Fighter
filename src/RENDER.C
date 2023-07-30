/********************************************************************
 *   File:       RENDER.C
 *
 *   Author(s):  Tobias W
 *               Jayden M
 *
 *   Date:       2022-03-29
 ********************************************************************/
#include "render.h"

/********************************************************************
 * Name:        renderHUD
 *
 * Purpose:     Renders the head up display (HUD) for the game
 *
 * Inputs:      model - pointer to the model
 *              base - pointer to the base of the screen
 ********************************************************************/
void renderHUD(Model *model, UINT16 *base_16)
{
    renderHealthBars(model, base_16);
    renderProfilePics(model, base_16);

    renderName(model->opponent.name, base_16, 560, 42);
    renderName(model->player.name, base_16, 60, 42);
    return;
}

/********************************************************************
 * Name:      renderEnvironment
 *
 * Purpose:   Renders the all objects part of game environment (just
 *            the floor for now)
 *
 * Inputs:    model - pointer to the model
 *            base - pointer to the base of the screen
 ********************************************************************/
void renderEnvironment(Model *model, UINT16 *base_16)
{
    UINT8 *base8 = (UINT8 *)base_16;

    plotRectFill(base8, 640, 26, 0, 374);
    return;
}

/********************************************************************
 * Name:        renderProfilePics
 *
 * Purpose:   Renders the profile pictures of the player and the
 *            opponent
 *
 * Inputs:    model - pointer to the model
 *            base - pointer to the base of the screen
 ********************************************************************/
void renderProfilePics(Model *model, UINT16 *base_16)
{
    UINT8 *base8 = (UINT8 *)base_16;

    /*this should be updated in the future to work with model, so that different
    avatars can load thier profile picture*/
    /*avatar*/
    plotRect(base8, 48, 48, 5, 5);
    plotBitmap16(base_16, 5, 5, bm_profilePic_LS, 48, 48);
    /*opponent*/
    plotRect(base8, 48, 48, 587, 5);
    plotBitmap16(base_16, 587, 5, bm_profilePic_LS, 48, 48);
}

/********************************************************************
 * Name:    RenderName
 *
 * Purpose: Renders the name of the player and the opponent
 *
 * Inputs:  model - pointer to the model
 *          base - pointer to the base of the screen
 *          x - x coordinate of the name
 *          y - y coordinate of the name
 ********************************************************************/
void renderName(char *name, UINT16 *base_16, int x, int y)
{
    printString((UINT8 *)base_16, x, y, NAME_SPACING, name);
}

/********************************************************************
 * Name:    renderAvatarAnim
 *
 * Purpose: Renders the current animation of the avatar
 *
 * Inputs:  avatar - pointer to the avatar
 *          base - pointer to the base of the screen
 ********************************************************************/
void renderAvatarAnim(Avatar *avatar, UINT16 *base_16)
{
    plotBitmap16(
        base_16,
        avatar->x + avatar->currAnim.frames[avatar->currFrame].offsetX,
        avatar->y + avatar->currAnim.frames[avatar->currFrame].offsetY,
        avatar->currAnim.frames[avatar->currFrame].bitmap,
        avatar->currAnim.frames[avatar->currFrame].width,
        avatar->currAnim.frames[avatar->currFrame].height);
}

/********************************************************************
 * Name:     renderHealthBars
 *
 * Purpose:  Renders the health bars of an avatar
 *
 * Inputs:   model - pointer to the model
 *           base - pointer to the base of the screen
 ********************************************************************/
void renderHealthBars(Model *model, UINT16 *base_16)
{
    UINT8 *base8 = (UINT8 *)base_16;
    int currentHealth = model->player.hud.health.currHealth;

    /*avatar*/
    plotRectFill(base8,
                 model->player.hud.health.barWidth * currentHealth / MAX_HEALTH,
                 model->player.hud.health.barHeight,
                 387 + model->player.hud.health.barWidth - model->player.hud.health.barWidth * currentHealth / MAX_HEALTH,
                 8);
    plotRect(base8, model->player.hud.health.barWidth, model->player.hud.health.barHeight, 387, 8);
    /*opponent*/
    plotRectFill(base8, model->opponent.hud.health.currHealth, model->opponent.hud.health.barHeight, 53, 8);
    plotRect(base8, model->opponent.hud.health.barWidth, model->opponent.hud.health.barHeight, 53, 8);

    return;
}

void DEBUG_RENDER_HITBOX(Avatar *avatar, UINT16 *base_16)
{
    UINT8 *base_8 = (UINT8 *)base_16;

    plotRect(
        base_8,
        avatar->hitbox.width,
        avatar->hitbox.height,
        avatar->hitbox.x,
        avatar->hitbox.y);

    return;
}

/********************************************************************
 * Name:     renderRequestHndlr
 *
 * Purpose:  Handles the rendering requests
 *
 * Inputs:   model - pointer to the model
 ********************************************************************/
void renderRequestHndlr(Model *model)
{
    /*check if player health was damaged*/
    if (model->player.hud.health.damaged)
    {
        REQUEST_HUD_RENDER = 2;
        model->player.hud.health.damaged = false;
    }

    /*check if opponent health was damaged*/
    if (model->opponent.hud.health.damaged)
    {
        REQUEST_HUD_RENDER = 2;
        model->opponent.hud.health.damaged = false;
    }

    /*TODO: check if enviroment has changed*/
}

/********************************************************************
 * Name:    renderMenuBackground
 *
 * Purpose: Renders the background of the menu
 *
 * Inputs:  menu - pointer to the menu
 *          base - pointer to the base of the screen
 ********************************************************************/
void renderMenuBackground(Menu *menu, UINT32 *base_32)
{
    plotBitmap32(base_32, 0, 0, menu->bitmap, SCREEN_WIDTH, SCREEN_HEIGHT);
    return;
}

/********************************************************************
 * Name:    renderMenuUpdate
 *
 * Purpose: Renders the menu item updates
 *
 * Inputs:  menu - pointer to the menu
 *          base - pointer to the base of the screen
 ********************************************************************/
void renderMenuUpdate(Menu *menu, UINT16 *base16)
{

    /*render mouse prev location*/
    xorHorizontalLine((UINT8 *)base16, menu->prevmX, menu->prevmY, menu->mWidth);
    xorHorizontalLine((UINT8 *)base16, menu->prevmX, menu->prevmY + 1, menu->mWidth + 1);
    xorHorizontalLine((UINT8 *)base16, menu->prevmX, menu->prevmY + 2, menu->mWidth + 2);
    xorHorizontalLine((UINT8 *)base16, menu->prevmX, menu->prevmY + 3, menu->mWidth + 3);
    xorHorizontalLine((UINT8 *)base16, menu->prevmX, menu->prevmY + 4, menu->mWidth + 4);

    /*TODO: update selectors here*/

    /*render mouse new location*/
    xorHorizontalLine((UINT8 *)base16, menu->mX, menu->mY, menu->mWidth);
    xorHorizontalLine((UINT8 *)base16, menu->mX, menu->mY + 1, menu->mWidth + 1);
    xorHorizontalLine((UINT8 *)base16, menu->mX, menu->mY + 2, menu->mWidth + 2);
    xorHorizontalLine((UINT8 *)base16, menu->mX, menu->mY + 3, menu->mWidth + 3);
    xorHorizontalLine((UINT8 *)base16, menu->mX, menu->mY + 4, menu->mWidth + 4);
}

/********************************************************************
 * Name:    render
 *
 * Purpose: Renders all game objects during fight
 *
 * Inputs:  model - pointer to the model
 *          base - pointer to the base of the screen
 ********************************************************************/
void render(Model *model, UINT16 *base_16)
{
    renderRequestHndlr(model);
    renderAvatarAnim(&model->player, base_16);
    renderAvatarAnim(&model->opponent, base_16);

    /*renderSuperBall(base_16);*/

    if (REQUEST_HUD_RENDER > 0)
    {
        clear_hud((UINT8 *)base_16);
        renderHUD(model, base_16);
        REQUEST_HUD_RENDER--;
    }

    if (REQUEST_UI_RENDER > 0)
    {
        renderEnvironment(model, base_16);
        REQUEST_UI_RENDER--;
    }

    /*
     DEBUG_RENDER_HITBOX(&model->player, base_16);
     DEBUG_RENDER_HITBOX(&model->opponent, base_16);
    */
}
