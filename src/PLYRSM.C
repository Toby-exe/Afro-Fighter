#include "events.h"
#include "types.h"
#include "model.h"
#include "plyrsm.h"

bool avatarStateChange = false;

avatarStates checkIdleNext(Avatar *player, avatarEvents event, UINT16 input)
{
    switch (event)
    {
    case moveEv:
        return on_move(player, input);
        break;

    case jumpEv:
        return Jumping; /*no special avatar modifications occur during the initial jump*/
        break;

    case crouchEv:
        return on_crouch(player, input);
        break;

    case lightAttackEv:
        return on_lightAttack(player, input);
        break;

    case heavyAttackEv:
        return on_heavyAttack(player, input);
        break;

    case blockEv:
        return on_block(player, input);
        break;

    case superEv:
        return on_super(player, input);
        break;

    case deathEv:
        return Dead;
        break;
    default:
        return Idle;
        break;
    }
}

/*void update(Model *model, enum gameStates state) <--- parameters for the game state machine*/
void update(Avatar *player, avatarEvents newEvent, UINT16 input)
{
    /*stuff that always happens should go here*/

    switch (player->state)
    {
    case Idle:
        player->state = checkIdleNext(player, newEvent, input);
        break;

    case Running:
        /*if currently moving then keep moving*/
        if (newEvent == moveEv)
        {
            player->state = on_move(player, input);
        }
        else
        {
            player->state = Idle;
        }
        break;

    case Jumping:
        player->state = InAir;
        break;

    case InAir:
        /*air strafing*/
        if (newEvent == moveEv)
        {
            player->state = on_jump(player, input);
        }
        if (player->vSpeed == 0 && (!yposInBounds(player->y + player->hitbox.height + 1)))
        {
            player->state = Idle;
        }
        break;

    case Crouching:
        /*if currently crouching then keep crouching*/
        if (newEvent == crouchEv)
        {
            player->state = on_crouch(player, input);
        }
        else
        {
            player->state = Idle;
        }
        break;

    case LightAttack:
        if (newEvent == lightAttackEv)
        {
            player->state = on_lightAttack(player, input);
        }
        else
        {
            player->state = Idle;
        }
        break;

    case HeavyAttack:
        if (newEvent == heavyAttackEv)
        {
            player->state = on_heavyAttack(player, input);
        }
        else
        {
            player->state = Idle;
        }
        break;

    case Blocking:
        /*if currently blocking then keep blocking*/
        if (newEvent == blockEv)
        {
            player->state = on_block(player, input);
        }
        else
        {
            player->state = Idle;
        }
        break;

    case Super:
        if (newEvent == superEv)
        {
            player->state = on_super(player, input);
        }
        else
        {
            player->state = Idle;
        }
        break;
    case Dead:
        player->state = Dead;
        break;

    default:
        break;
    }
}