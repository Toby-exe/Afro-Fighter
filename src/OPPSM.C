#include "OPPSM.H"
int currAction = 0;

/*state machine for a non-human player. operates on a series of timers allowing moves to occur both
at random and under specific conditions*/
void oppScript(Model *model)
{

    int rand_action, num_actions;
    /*num_actions = 4;    4 possible scripted actions*/

    /*center of an avatar's hitbox*/
    int opp_xpos, plyr_xpos;
    opp_xpos = model->opponent.x + model->opponent.hitbox.width / 2;
    plyr_xpos = model->player.x + model->player.hitbox.width / 2;

    /*always face the player*/
    model->opponent.dirx = (opp_xpos > plyr_xpos) ? left : right;

    /*approach the human player until they're within _px of it*/
    if (abs(opp_xpos - plyr_xpos) > 128 && model->opponent.state != InAir)
    {
        model->opponent.state = Running;
    }
    else
    {
        actionSelect(model);
    }
}

void actionSelect(Model *model)
{

    avatarEvents newEvent = noEv;
    int input;
    /*possible actions*/
    currAction = currAction % 6;
    switch (currAction)
    {
    case 0:
        if (TIMER_AI_ACTION <= 5)
        {
            input = w_KEY;
        }
        else
        {
            TIMER_AI_ACTION = 0;
            currAction++; /*move to next scripted action*/
        }
        break;

    case 1:
        if (TIMER_AI_ACTION <= 35)
        {
            input = space_KEY;
        }
        else if (model->opponent.state != InAir)
        {
            TIMER_AI_ACTION = 0;
            currAction++; /*move to next scripted action*/
        }
        break;

    case 2:
        if (TIMER_AI_ACTION <= 35)
        {
            input = j_KEY;
        }
        else
        {
            TIMER_AI_ACTION = 0;
            currAction++; /*move to next scripted action*/
        }
        break;

    case 3:
        if (TIMER_AI_ACTION <= 35)
        {
            input = d_KEY;
        }
        else
        {
            TIMER_AI_ACTION = 0;
            currAction++; /*move to next scripted action*/
        }
        break;

    case 4:
        if (TIMER_AI_ACTION <= 35)
        {
            input = a_KEY;
        }
        else
        {
            TIMER_AI_ACTION = 0;
            currAction++; /*move to next scripted action*/
        }
        break;

    case 5:
        if (TIMER_AI_ACTION <= 5)
        {
            input = i_KEY;
        }
        else
        {
            TIMER_AI_ACTION = 0;
            currAction++; /*move to next scripted action*/
        }
        break;

    default:
        break;
    }

    switch (input)
    {
    case a_KEY:
        newEvent = moveEv;
        break;

    case d_KEY:
        newEvent = moveEv;
        break;

    case space_KEY:
        newEvent = jumpEv;
        break;

    case l_KEY:
        newEvent = crouchEv;
        break;

    case w_KEY:
        newEvent = lightAttackEv;
        break;

    case i_KEY:
        newEvent = heavyAttackEv;
        break;

    case f_KEY:
        newEvent = superEv;
        break;

    case j_KEY:
        newEvent = blockEv;
        break;

    default:
        break;
    }

    update(&model->opponent, newEvent, input);
}