#include "model.h"

int animSpeed = 5;

/***********************************************************************
 * Name: initModel
 * 
 * Purpose: initializes all the objects within the game model
 * 
 * Details: Calls the appropriate initialization methods for each
 *          object that exists in the game
 * 
 * Inputs:  model - the game model being initialized
 *
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void initModel(Model *model)
{
    model->combatCollision = false;
    initModelGraphics();
    initAvatar(&model->player, 500, 200, "TOBY");
    initAvatar(&model->opponent, 200, 200, "JAY");
}

/***********************************************************************
 * Name: initAvatar
 * 
 * Purpose: initializes an avatar
 * 
 * Inputs:  avatar - the avatar being initialized
 *          x - the desired starting x position
 *          y - the desired starting y position
 *          name - the avatar's name displayed on their healthbar
 *
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void initAvatar(Avatar *avatar, int x, int y, char *name)
{
    avatar->state = InAir;
    avatar->diry = down;
    avatar->dirx = left;
    avatar->hSpeed = 0;
    avatar->vSpeed = 0;
    avatar->x = x;
    avatar->y = y;
    avatar->strafe = false;

    /*if characters other than the default afroman are made, add parameter
    for an Animation*/
    avatar->currFrame = 0;
    avatar->currAnim = avatarIdleLS;

    /*init hitbox*/
    updateHitbox(avatar);
    avatar->hud.health.currHealth = 200;
    avatar->hud.health.barWidth = 200;
    avatar->hud.health.barHeight = 31;
    avatar->hud.health.damaged = false;
    avatar->hud.health.currHealth = 200;
    avatar->name = name;
}

/***********************************************************************
 * Name: initModel
 * 
 * Purpose: initializes the Game object
 * 
 * Details: initializes the game at the splash screen state
 * 
 * Inputs:  game - the Game being initialized
 *
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void initGame(Game *game)
{
    game->state = Splash;
    initSplashScreen(&game->splashScreen);
    initEndScreen(&game->endScreen);
    initModel(&game->model);
}

/***********************************************************************
 * Name: initSplashScreen
 * 
 * Purpose: initializes the the splash screen
 * 
 * Details: initializes the interactable buttons and the mouse's position
 * 
 * Inputs:  splashScreen - the SplashScreen being initialized
 *
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void initSplashScreen(SplashScreen *splashScreen)
{
    splashScreen->menu.selectorLs.height = 18;
    splashScreen->menu.selectorLs.width = 16;

    splashScreen->menu.selectorRs.height = 18;
    splashScreen->menu.selectorRs.width = 16;

    splashScreen->menu.selectorLs.x = 111;
    splashScreen->menu.selectorLs.y = 241;

    splashScreen->menu.selectorRs.x = 286;
    splashScreen->menu.selectorRs.y = 241;

    resetMouse(&splashScreen->menu);

    splashScreen->onePlayerBtn.x = 134;
    splashScreen->onePlayerBtn.y = 236;
    splashScreen->onePlayerBtn.width = 145;
    splashScreen->onePlayerBtn.height = 30;
    splashScreen->onePlayerBtn.hovered = false;

    splashScreen->twoPlayerBtn.x = 134;
    splashScreen->twoPlayerBtn.y = 275;
    splashScreen->twoPlayerBtn.width = 145;
    splashScreen->twoPlayerBtn.height = 30;
    splashScreen->twoPlayerBtn.hovered = false;

    splashScreen->quitBtn.x = 160;
    splashScreen->quitBtn.y = 314;
    splashScreen->quitBtn.width = 92;
    splashScreen->quitBtn.height = 30;
    splashScreen->quitBtn.hovered = false;

    splashScreen->btnCount = 3;
    splashScreen->menu.bitmap = title;
}

/***********************************************************************
 * Name: resetMouse
 * 
 * Purpose: sets the initial mouse position
 * 
 * Inputs:  menu - the Menu that the mouse exists in
 *
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void resetMouse(Menu *menu)
{
    menu->prevmX = -50;
    menu->prevmY = -50;
    menu->mX = 0;
    menu->mY = 0;
    menu->mWidth = 1;
}

/***********************************************************************
 * Name: initEndScreen
 * 
 * Purpose: initializes the screen at the end of a game session
 * 
 * Details: initializes the interactable buttons found on the end screen
 * 
 * Inputs:  endScreen - the end screen being initialized
 *
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void initEndScreen(EndScreen *endScreen)
{
    endScreen->menu.selectorLs.height = 18;
    endScreen->menu.selectorLs.width = 16;

    endScreen->menu.selectorRs.height = 18;
    endScreen->menu.selectorRs.width = 16;

    endScreen->menu.selectorLs.x = 111;
    endScreen->menu.selectorLs.y = 241;

    endScreen->menu.selectorRs.x = 286;
    endScreen->menu.selectorRs.y = 241;

    endScreen->menu.mX = 0;
    endScreen->menu.mY = 0;
    endScreen->menu.prevmX = -50;
    endScreen->menu.prevmY = -50;
    endScreen->menu.mWidth = 6;

    endScreen->playAgainBtn.x = 192;
    endScreen->playAgainBtn.y = 168;
    endScreen->playAgainBtn.width = 192;
    endScreen->playAgainBtn.height = 38;
    endScreen->playAgainBtn.hovered = false;

    endScreen->menuBtn.x = 257;
    endScreen->menuBtn.y = 215;
    endScreen->menuBtn.width = 114;
    endScreen->menuBtn.height = 38;
    endScreen->menuBtn.hovered = false;
}

/***********************************************************************
 * Name: initModelGraphics
 * 
 * Purpose: initializes the necessary sprites and animations in the model
 * 
 * Inputs:  None
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void initModelGraphics()
{
    initAnimations();
}

/***********************************************************************
 * Name: chooseEndScreen
 * 
 * Purpose: determines which screen appears at the end of a game session
 * 
 * Inputs:  endScreen - the end screen being initialized
 *          winner - PlayerWin state of the Game
 *
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void chooseEndScreen(EndScreen *endScreen, GameStates winner)
{
    winner == PlayerWin
        ? endScreen->menu.bitmap = playerWinSplash
        : endScreen->menu.bitmap = playerLoseSplash;
}

/***********************************************************************
 * Name: buttonHoverd
 * 
 * Purpose: Checks whether or not a button is being hovered over by the mouse
 * 
 * Inputs:  mx - mouse's x position
 *          my - mouse's y position
 *          button - the button being checked
 *
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void buttonHoverd(int mx, int my, Button *button)
{
    if (mx > button->x && mx < button->x + button->width &&
        my > button->y && my < button->y + button->height)
    {
        button->hovered = true;
    }
    else
    {
        button->hovered = false;
    }
}

/***********************************************************************
 * Name: updateMenuSelection
 * 
 * Purpose: updates the menu to use whichever menu has been selected
 * 
 * Inputs:  menu - menu to update
 *          selection - which menu to select
 *
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void updateMenuSelection(Menu *menu, int selection)
{
    menu->selectorLs.x = 111;
    menu->selectorRs.x = 286;

    switch (selection)
    {
    case 0:
        menu->selectorLs.y = 241;
        menu->selectorRs.y = 241;

        break;

    case 1:
        menu->selectorLs.y = 281;
        menu->selectorRs.y = 281;

        break;

    case 2:
        menu->selectorLs.y = 321;
        menu->selectorRs.y = 321;
        menu->selectorLs.x = 138;
        menu->selectorRs.x = 257;

        break;

    default:
        break;
    }
}

/***********************************************************************
 * Name: player_idle
 * 
 * Purpose: handles the changing of animation frames when the player is
 *          idleing
 *
 * Inputs:  avatar - the avatar 
 *
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void avatar_idle(Avatar *avatar)
{

    switch (avatar->dirx)
    {
    case left:
        avatar->currAnim = avatarIdleLS;
        break;

    case right:
        avatar->currAnim = avatarIdleRS;
        break;

    default:
        break;
    }
}

/***********************************************************************
 * Name: player_move
 * 
 * Purpose: handles the changing of animation frames when the player is
 *          moving and shifts the player position based on speed and direction
 *
 * Details: If the player requests to move and they're in the air, the jump
 *          animation is selected. Otherwise, they're on the ground and the
 *          run animation is selected.
 *
 * Inputs:  avatar - the avatar 
 *          speed - how many pixels to move in 1 clock tick
 *
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void avatar_move(Avatar *avatar, int speed)
{

    switch (avatar->dirx)
    {
    case left:

        avatar->hSpeed = -speed;
        if (avatar->state == InAir)
        {
            avatar->currAnim = avatarIdleLS;
        }
        else
        {
            avatar->currAnim = avatarRunLS;
        }

        /*checks if there will be an avatar on wall collision when the avatar moves horizontally*/
        if (!xposInBounds(avatar->x + avatar->hSpeed))
        {
            wallCollisionsHndlr(avatar);
        }
        break;

    case right:
        avatar->hSpeed = speed;

        if (avatar->state == InAir)
        {
            avatar->currAnim = avatarIdleRS;
        }
        else
        {
            avatar->currAnim = avatarRunRS;
        }

        /*checks if there will be an avatar on wall collision when the avatar moves horizontally*/
        if (!xposInBounds(avatar->x + avatar->hitbox.width + avatar->hSpeed))
        {
            wallCollisionsHndlr(avatar);
        }
        break;

    default:
        break;
    }

    /*increase/decrease xpos*/
    avatar->x += avatar->hSpeed;

    /*relocate when kbd drivers work*/
    avatar->hSpeed = 0; /*reset speed after a move is done*/
}

/***********************************************************************
 * Name: player_block
 * 
 * Purpose: begins the upward motion of an avatar when they request to jump
 *
 * Inputs:  avatar - the avatar 
 *
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void player_jump(Avatar *avatar)
{
    avatar->vSpeed = -32;
}

/***********************************************************************
 * Name: player_crouch
 * 
 * Purpose: handles the changing of animation frames when the player is
 *          crouching
 *
 * Inputs:  avatar - the avatar 
 *
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void player_crouch(Avatar *player)
{
    /*update hitbox to be shorter*/
}

/***********************************************************************
 * Name: playerLightAttack
 * 
 * Purpose: handles the changing of animation frames when the player has begun
 *          a light attack
 *
 * Inputs:  avatar - the avatar 
 *
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void avatarLightAttack(Avatar *avatar)
{
    switch (avatar->dirx)
    {
    case left:
        avatar->currAnim = avatarLightAttackLS;
        break;

    case right:
        avatar->currAnim = avatarLightAttackRS;
        break;

    default:
        break;
    }
}

/***********************************************************************
 * Name: playerHeavyAttack
 * 
 * Purpose: handles the changing of animation frames when the player has begun
 *          a heavy attack
 *
 * Inputs:  avatar - the avatar 
 *
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void avatarHeavyAttack(Avatar *avatar)
{
    switch (avatar->dirx)
    {
    case left:
        avatar->currAnim = avatarHeavyAttackLS;
        break;

    case right:
        avatar->currAnim = avatarHeavyAttackRS;
        break;

    default:
        break;
    }
}

/***********************************************************************
 * Name: player_block
 * 
 * Purpose: handles the changing of animation frames when the player is
 *          blocking
 *
 * Inputs:  avatar - the avatar 
 *
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void player_block(Avatar *player)
{
    switch (player->dirx)
    {
    case left:
        player->currAnim = avatarBlockLS;
        break;

    case right:
        player->currAnim = avatarBlockRS;
        break;

    default:
        break;
    }
}

/***********************************************************************
 * Name: player_super
 * 
 * Purpose: handles the changing of animation frames when the player has begun
 *          a super attack
 *
 * Inputs:  avatar - the avatar 
 *
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void player_super(Avatar *player)
{
    switch (player->dirx)
    {
    case left:
        player->currAnim = avatarSuperLS;
        break;

    case right:
        player->currAnim = avatarSuperLS;
        break;

    default:
        break;
    }
}

void createSuperball(Avatar *player)
{
}

/***********************************************************************
 * Name: wallCollisionsHndlr
 * 
 * Purpose: Checks for a collision involving an avatar and the left or right
 *          wall boundaries.
 * 
 * Inputs:  avatar - the avatar making contact with a wall
 *
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void wallCollisionsHndlr(Avatar *avatar)
{
    /*ensure player is perfectly touching the wall
    first condition is for approaching right wall
    second condition is for approaching left wall*/

    while (xposInBounds(avatar->x + sign(avatar->hSpeed)) &&
           xposInBounds(avatar->x + avatar->hitbox.width + sign(avatar->hSpeed)))
    {
        avatar->x += sign(avatar->hSpeed);
    }
    /*player is now stationary horizontally*/
    avatar->hSpeed = 0;
}

/***********************************************************************
 * Name: floorCollisionsHndlr
 * 
 * Purpose: Checks for a collision involving an avatar and the floor boundary
 *          anywhere in the model.
 * 
 * Inputs:  avatar - the avatar making contact with the floor
 *
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void floorCollisionsHndlr(Avatar *avatar)
{
    /*ensure player is perfectly touching the floor*/
    while (yposInBounds(avatar->y + avatar->hitbox.height + sign(avatar->vSpeed)))
    {
        avatar->y += sign(avatar->vSpeed);
    }
    /*player is now stationary vertically*/
    avatar->vSpeed = 0;
}

/***********************************************************************
 * Name: player_inAir
 * 
 * Purpose: handles the accelerated motion of the player while in the air
 *
 * Details: gravity is active at all times making vertical movement synchronous,
 *          However, while in the air, the player may also strafe left and right.
 *          As well as handling vertical movement, this function also handles
 *          strafing if it has been requested by input
 * 
 * Inputs:  avatar - the avatar 
 *
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void player_inAir(Avatar *avatar)
{
    avatar->vSpeed += gravity;

    avatar->diry = (avatar->vSpeed > 0) ? down : up;

    /*air strafe*/
    if (avatar->strafe == true)
    {
        avatar_move(avatar, strafeSpeed);
        avatar->strafe = false;
    }

    /*checks if there will be an avatar on floor collision when the avatar moves vertically*/
    if (!yposInBounds(avatar->y + avatar->hitbox.height + avatar->vSpeed))
    {
        floorCollisionsHndlr(avatar);
    }

    /*increase/decrease ypos*/
    avatar->y += avatar->vSpeed;
}

/***********************************************************************
 * Name: combatCollisionsHndlr
 * 
 * Purpose: Checks for a collision involving 2 avatars or a collision involving
 *          a super projectile and an avatar anywhere in the model. If a collision
 *          has occured, the hit is registered accordingly and victim receives
 *          damage
 * 
 * Inputs:  avatar - the avatar doing the attack
 *          other - the recipient of the attack
 *
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void combatCollisionsHndlr(Avatar *avatar, Avatar *other)
{
    /*check if avatar landed a hit*/
    switch (avatar->state)
    {
    case LightAttack:
        /*check if the hit box does not go past half the other avatar's hitbox*/
        if (avatar->dirx == left &&
            avatar->hitbox.x > other->hitbox.x)
        {
            registerLightHit(other);
        }
        else if (avatar->dirx == right &&
                 avatar->hitbox.x + avatar->hitbox.width < other->hitbox.x + other->hitbox.width)
        {
            registerLightHit(other);
        }
        break;
    case HeavyAttack:

       if (avatar->dirx == left &&
            avatar->hitbox.x > other->hitbox.x)
        {
            registerHeavyHit(other);
        }
        else if (avatar->dirx == right &&
                 avatar->hitbox.x + avatar->hitbox.width < other->hitbox.x + other->hitbox.width)
        {
            registerHeavyHit(other);
        }
        break;

    default:
        break;
    }
    /*TODO: check if either avatar was hit a by a super projectile*/
}

/*void superCollisionsHndlr(){
    registerSuperHit(other);
    change sprite to explosion on contact}*/


/***********************************************************************
 * Name: registerLightHit
 * 
 * Purpose: updates an avatar's health after receiving a hit from a light attack
 * 
 * Inputs:  avatar - the avatar being updated
 *
 * Outputs: N/A
 *
 * Returns: None
 ***********************************************************************/
void registerLightHit(Avatar *avatar)
{
    play_hit_effect();
    /*check if avatar is in blocking state*/
    avatar->hud.health.damaged = true;
    avatar->hud.health.currHealth = avatar->state == Blocking
                                        ? avatar->hud.health.currHealth - (LIGHT_DAMAGE - BLOCK_DAMAGE)
                                        : avatar->hud.health.currHealth - LIGHT_DAMAGE;
    if (avatar->hud.health.currHealth <= 0)
    {
        avatar->hud.health.currHealth = 0;
    }
}

/***********************************************************************
 * Name: registerHeavyHit
 * 
 * Purpose: updates an avatar's health after receiving a hit from a heavy attack
 * 
 * Inputs:  avatar - the avatar being updated
 *
 * Outputs: N/A
 *
 * Returns: None
 ***********************************************************************/
void registerHeavyHit(Avatar *avatar)
{
    play_kick_effect();
    /*check if avatar is in blocking state*/
    avatar->hud.health.damaged = true;
    avatar->hud.health.currHealth = avatar->state == Blocking
                                        ? avatar->hud.health.currHealth - (HEAVY_DAMAGE - BLOCK_DAMAGE)
                                        : avatar->hud.health.currHealth - HEAVY_DAMAGE;
    if (avatar->hud.health.currHealth <= 0)
    {
        avatar->hud.health.currHealth = 0;
    }
}

/***********************************************************************
 * Name: registerSuperHit
 * 
 * Purpose: updates an avatar's health after receiving a hit from a super attack
 * 
 * Inputs:  avatar - the avatar being updated
 *
 * Outputs: N/A
 *
 * Returns: None
 ***********************************************************************/
void registerSuperHit(Avatar *avatar)
{
    /*check if avatar is in blocking state*/
    avatar->hud.health.damaged = true;
    avatar->hud.health.currHealth = avatar->state == Blocking
                                        ? avatar->hud.health.currHealth - (SUPER_DAMAGE - BLOCK_DAMAGE)
                                        : avatar->hud.health.currHealth - SUPER_DAMAGE;
    if (avatar->hud.health.currHealth <= 0)
    {
        avatar->hud.health.currHealth = 0;
    }
}

/***********************************************************************
 * Name: updateAvatar
 * 
 * Purpose: updates an avatar by using its current state
 * 
 * Inputs:  avatar - the avatar being updated
 *
 * Outputs: N/A
 *
 * Returns: None
 ***********************************************************************/
void updateAvatar(Avatar *avatar)
{
    switch (avatar->state)
    {
    case Idle:
        avatar_idle(avatar);
        break;

    case Running:
        avatar_move(avatar, moveSpeed);
        break;

    case Jumping:
        player_jump(avatar);
        break;

    case InAir:
        player_inAir(avatar);
        break;

    case Crouching:
        player_crouch(avatar);
        break;

    case LightAttack:
        avatarLightAttack(avatar);
        break;

    case HeavyAttack:
        avatarHeavyAttack(avatar);
        break;

    case Blocking:
        player_block(avatar);
        break;

    case Super:
        player_super(avatar);
        break;

    case Dead:
        /*player_dead(avatar);*/
        return;
        break;
    }

    /*update the current frame of the avatar's animation if its duration is over*/
    if (avatar->currAnim.numFrames > 1)
    {
        if (animSpeed <= 0)
        {
            avatar->currFrame = (avatar->currFrame + 1) % avatar->currAnim.numFrames;
            animSpeed = avatar->currAnim.duration;
        }
        else
        {
            animSpeed--;
        }
    }
    else
    {
        avatar->currFrame = 0;
    }

    updateHitbox(avatar);
}

/***********************************************************************
 * Name: sceneController
 * 
 * Purpose: updates the entire game model
 * 
 * Inputs:  model - the model being updated
 *
 * Outputs: N/A
 *
 * Returns: None
 ***********************************************************************/
void sceneController(Model *model)
{
    /*event functions shouldnt call model*/
    updateAvatar(&model->player);
    updateAvatar(&model->opponent);

    if (model->combatCollision == true)
    {
        combatCollisionsHndlr(&model->player, &model->opponent);
        combatCollisionsHndlr(&model->opponent, &model->player);
        model->combatCollision = false;
    }
}

/***********************************************************************
 * Name: sign
 * 
 * Purpose: determines whether a number is positive, negative, or neither
 * 
 * Inputs:  x - number being checked
 *
 * Outputs: N/A
 *
 * Returns: 1 if positive, -1 if negative, or 0 if neither
 ***********************************************************************/
int sign(int x)
{
    if (x > 0)
    {
        return 1;
    }
    else if (x < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

/***********************************************************************
 * Name: updateHitbox
 * 
 * Purpose: updates an avatar's hitbox
 * 
 * Details: Since different frames of an animation may have varying heights
 *          and widths, the hitbox's coordinates must account for that and 
 *          the width and height are determined by the current frame. 
 *
 * Inputs:  avatar - the avatar being updated
 *
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void updateHitbox(Avatar *avatar)
{
    avatar->hitbox.width = avatar->currAnim.frames[avatar->currFrame].width;
    avatar->hitbox.height = avatar->currAnim.frames[avatar->currFrame].height;
    avatar->hitbox.x = avatar->x + avatar->currAnim.frames[avatar->currFrame].offsetX;
    avatar->hitbox.y = avatar->y + avatar->currAnim.frames[avatar->currFrame].offsetY;
}