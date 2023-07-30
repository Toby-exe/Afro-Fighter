#include "events.h"

/***********************************************************************
 * Name: on_move
 * 
 * Purpose: handles an avatar's transition into a state of movement 
 * 
 * Details: An avatar can only run left and right. This function requests
 *          this movement action by determining the avatar's horizontal
 *          direction from the input key and by changing their state
 *          to Running
 * 
 * Inputs:  avatar - the avatar being updated
 *          key - the keyboard input that was detected
 *
 * Outputs: N/A
 *
 * Returns: the updated avatar state
 ***********************************************************************/
avatarStates on_move(Avatar *avatar, UINT16 key)
{
    avatarStates state = Running;

    if (key == a_KEY)
    {
        avatar->dirx = left;
    }
    else if (key == d_KEY)
    {
        avatar->dirx = right;
    }

    return state;
}

/***********************************************************************
 * Name: on_jump
 * 
 * Purpose: handles an avatar's transition into a state of air strafing
 * 
 * Details: While airborne, an avatar has the ability to strafe left and right
 *          as if they were on the ground. This function requests
 *          this movement action by determining the avatar's horizontal
 *          direction from the input key and by changing their state
 *          to InAir
 * 
 * Inputs:  avatar - the avatar being updated
 *          key - the keyboard input that was detected
 *
 * Outputs: N/A
 *
 * Returns: the updated avatar state
 ***********************************************************************/
avatarStates on_jump(Avatar *avatar, UINT16 key)
{
    avatarStates state = InAir;

    /*air strafing*/
    if (key == a_KEY)
    {
        avatar->dirx = left;
        avatar->strafe = true;
    }
    else if (key == d_KEY)
    {
        avatar->dirx = right;
        avatar->strafe = true;
    }

    return state;
}

/***********************************************************************
 * Name: on_crouch
 * 
 * Purpose: handles an avatar's transition into a state of crouching
 * 
 * Details: This function requests a crouch action by changing the avatar's 
 *          state to Crouching
 * 
 * Inputs:  avatar - the avatar being updated
 *          key - the keyboard input that was detected
 *
 * Outputs: N/A
 *
 * Returns: the updated avatar state
 ***********************************************************************/
avatarStates on_crouch(Avatar *avatar, UINT16 key)
{
    avatarStates state = Crouching;

    return state;
}

/***********************************************************************
 * Name: on_lightAttack
 * 
 * Purpose: handles an avatar's transition into a state of punching
 * 
 * Details: This function requests a punch action by changing the avatar's 
 *          state to LightAttack
 * 
 * Inputs:  avatar - the avatar being updated
 *          key - the keyboard input that was detected
 *
 * Outputs: N/A
 *
 * Returns: the updated avatar state
 ***********************************************************************/
avatarStates on_lightAttack(Avatar *avatar, UINT16 key)
{
    avatarStates state = LightAttack;

    return state;
}

/***********************************************************************
 * Name: on_heavyAttack
 * 
 * Purpose: handles an avatar's transition into a state of kicking
 * 
 * Details: This function requests a kick action by changing the avatar's 
 *          state to HeavyAttack
 * 
 * Inputs:  avatar - the avatar being updated
 *          key - the keyboard input that was detected
 *
 * Outputs: N/A
 *
 * Returns: the updated avatar state
 ***********************************************************************/
avatarStates on_heavyAttack(Avatar *avatar, UINT16 key)
{
    avatarStates state = HeavyAttack;

    return state;
}

/***********************************************************************
 * Name: on_block
 * 
 * Purpose: handles an avatar's transition into a state of blocking
 * 
 * Details: This function requests a block action by changing the avatar's 
 *          state to Blocking
 * 
 * Inputs:  avatar - the avatar being updated
 *          key - the keyboard input that was detected
 *
 * Outputs: N/A
 *
 * Returns: the updated avatar state
 ***********************************************************************/
avatarStates on_block(Avatar *avatar, UINT16 key)
{
    avatarStates state = Blocking;

    return state;
}

/***********************************************************************
 * Name: on_death
 * 
 * Purpose: handles an avatar's transition into a state of death
 * 
 * Details: This function requests the end of a match by changing the avatar's 
 *          state to Dead
 * 
 * Inputs:  avatar - the avatar being updated
 *          key - the keyboard input that was detected
 *
 * Outputs: N/A
 *
 * Returns: the updated avatar state
 ***********************************************************************/
avatarStates on_death(Avatar *avatar)
{
    avatarStates state = Dead;

    return state;
}

/***********************************************************************
 * Name: on_super
 * 
 * Purpose: handles an avatar's transition into a state of charging up and
 *          releasing a super attack
 * 
 * Details: This function requests an action to initialize a super attack
 *          by changing the avatar's state to Super
 * 
 * Inputs:  avatar - the avatar being updated
 *          key - the keyboard input that was detected
 *
 * Outputs: N/A
 *
 * Returns: the updated avatar state
 ***********************************************************************/
avatarStates on_super(Avatar *avatar, UINT16 key)
{
    avatarStates state = Super;

    if (key == f_KEY)
    {
        /*init super projectile*/
    }

    return state;
}

/***********************************************************************
 * Name: collisionCheck
 * 
 * Purpose: Checks for a collision involving 2 avatars or a collision involving
 *          a super projectile and another surface anywhere in the model.
 * 
 * Details: If the hitboxes of a player or a super projectile overlap with
 *          another hitbox or boundary, the model is notified so it can appropriately
 *          handle what should happen next in the game environment
 * 
 * Inputs:  model - the model being checked
 *
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void collisionCheck(Model *model)
{
    /*checks for avatar on avatar collision in the x direction*/
    if (model->player.hitbox.x < model->opponent.hitbox.x + model->opponent.hitbox.width &&
        model->player.hitbox.x + model->player.hitbox.width > model->opponent.hitbox.x &&
        model->player.hitbox.y < model->opponent.hitbox.y + model->opponent.hitbox.height &&
        model->player.hitbox.y + model->player.hitbox.height > model->opponent.hitbox.y)
    {
        model->combatCollision = true;
    }
    /*if there is a super ball active in the enviroment check to see what it collides with*/
}