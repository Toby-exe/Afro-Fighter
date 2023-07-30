#include "game.h"
      
unsigned int REQUEST_HUD_RENDER = 2; /*0 = no render, 1 = render, 2 = render and reset*/
unsigned int REQUEST_UI_RENDER = 2; /*0 = no render, 1 = render, 2 = render and reset*/

const UINT8 backBuffer[32256];      /*second buffer*/
                                    /*32000 + 256 since frame buffers on the st must be 256 byte aligned */

/****************************************************************************************
*
* Name: updateGameStates
*
* Purpose: Updates the game state
*
* Details: Updates the game finite state machine
*
* Inputs: gameState - the current game state
*         newState - the new game state 
****************************************************************************************/
void updateGameState(GameStates *gameState, GameStates newState)
{
    *gameState = newState;
    return;
}


/****************************************************************************************
 * Name: main
 * 
 * Purpose: The main function of the game
 ****************************************************************************************/
int main()
{
    /*install vectors for IKBD and VBL*/
    Vector origVBL = installVector(VBL_ISR, vbl_isr);
    Vector origIKBD = installVector(IKBD_ISR, ikbd_isr);

    UINT16 *base16 = (UINT16 *) get_video_base();
    UINT16 *secondBase16 = (UINT16 *) shiftBase(backBuffer);
    GameStates newState;
    Game game;

    initGame(&game);

    setgTicks();
    setgSeconds();
    setVblFlag();

    /*master game state machine*/
    while (game.state != Quit)
    {
        switch (game.state)
        {
        case Splash:
            newState = splashScreen(base16, secondBase16, &game.splashScreen);
            break;

        case OnePlayer:
            newState = gameLoop(base16, secondBase16, &game.model);
            break;

        case TwoPlayer:
            newState = gameLoop(base16, secondBase16, &game.model);
            break;

        case PlayerWin:
            newState = gameOverScreen(base16, secondBase16, &game.endScreen, PlayerWin);
            initModel(&game.model);
            break;

        case OpponentWin:
            newState = gameOverScreen(base16, secondBase16, &game.endScreen, OpponentWin);
            initModel(&game.model);
            break;
        case Quit:
            stop_sound();
            break;

        default:
            break;
        }

        clear_screen((UINT32 *)base16);
        clear_screen((UINT32 *)secondBase16);
        updateGameState(&game.state, newState);
    }

    /*uninstall vectors for IKBD and VBL*/
    stop_sound();
    installVector(IKBD_ISR, origIKBD);
    installVector(VBL_ISR, origVBL);

    return 0;
}

/****************************************************************************************
 * Name: splashScreen
 * 
 * Purpose: The splash screen state
 * 
 * Details: Handles splash screen state, it handles the splash screen
 *         and returns the new game state based on user input/selection from menu
 * 
 * Inputs: base16 - the base address of the screen
 *         secondBase16 - the second base address of the screen
 *         screen - the splash screen
 * 
 * Returns: The new game state
 ****************************************************************************************/
GameStates splashScreen(UINT16 *base16, UINT16 *secondBase16, SplashScreen *screen)
{
    UINT8 input;
    UINT32 timeNow, timeThen, timeDelta;
    GameStates gState = Splash;
    /*SplashScreen splashScreen;*/

    /*initSplashScreen(&splashScreen);*/
    set_video_base(base16);
    resetMouse(&screen->menu);

    screen->menu.mX = keyBufferQueue.mX;
    screen->menu.mY = keyBufferQueue.mY;

    renderMenuBackground(&screen->menu, (UINT32 *)base16);
    renderMenuUpdate(&screen->menu, base16);

    start_music();
    timeThen = getTime();

    while (gState == Splash)
    {

        timeNow = getTime();
        timeDelta = timeNow - timeThen;

        if (keyPending())
        {
            input = keyBuffDequeue();

            buttonHoverd(screen->menu.mX, screen->menu.mY, &screen->onePlayerBtn);
            buttonHoverd(screen->menu.mX, screen->menu.mY, &screen->twoPlayerBtn);
            buttonHoverd(screen->menu.mX, screen->menu.mY, &screen->quitBtn);

            switch (input)
            {
            case mouseClick_LS: /*left mouse button pressed*/

                /*check to see which button mouse is hovering over when clicked*/
                if (screen->onePlayerBtn.hovered == true)
                    gState = OnePlayer;

                if (screen->twoPlayerBtn.hovered == true)
                    gState = TwoPlayer;

                if (screen->quitBtn.hovered == true)
                    gState = Quit;

                break;

            case esc_KEY:
                gState = Quit;
                break;

            default:
                gState = Splash;
                break;
            }
        }

        if (timeDelta >= 1)
        {
            screen->menu.prevmX = screen->menu.mX;
            screen->menu.prevmY = screen->menu.mY;
            screen->menu.mX = keyBufferQueue.mX;
            screen->menu.mY = keyBufferQueue.mY;
            
            renderMenuUpdate(&screen->menu, base16);
        }
        timeThen = timeNow;
    }

    return gState;
}


/****************************************************************************************
 * Name: processAsync
 * 
 * Purpose: Process the asynchronous events
 * 
 * Details: This function processes all the asynchronous events
 * 
 * Inputs: model - the game model
 *        gameState - the current game state
 * 
 * Returns: None
 ****************************************************************************************/
void processAsync(Model *model, GameStates *gameState)
{
    UINT8 input;
    avatarEvents newEvent = noEv;

    if (keyPending()) /* continuous input */
    {

        if (keyRepeat == true)
        {
            input = getPrev();

            switch (input)
            {

            case a_KEY:
                newEvent = moveEv;
                break;

            case d_KEY:
                newEvent = moveEv;
                break;

            case f_KEY:
                newEvent = superEv;
                break;

            case j_KEY:
                newEvent = blockEv;
                break;

            case l_KEY:
                newEvent = crouchEv;
                break;

            case space_KEY:
                newEvent = jumpEv;
                break;

            default:
                break;
            }
        }
        else /* discrete input */
        {
            input = keyBuffDequeue();

            switch (input)
            {
            case q_KEY:
                *gameState = Splash;
                break;

            case esc_KEY:
                *gameState = Quit;
                break;

            case w_KEY:
                newEvent = lightAttackEv;
                break;

            case i_KEY:
                newEvent = heavyAttackEv;
                break;

            default:
                break;
            }
        }
    }

    if (*gameState != Quit && *gameState != Splash)
    {
        update(&model->player, newEvent, input);
    }
}



/****************************************************************************************
 * Name: processSync
 * 
 * Purpose: Process the synchronous events
 * 
 * Details: This function processes all the synchronous events
 * 
 * Inputs: model - the game model
 * 
 * Returns: None
 ****************************************************************************************/
void processSync(Model *model)
{   
    avatarEvents newEvent = noEv;
    oppScript(model);
    collisionCheck(model);
    if (model->player.hud.health.currHealth <= 0)
    {
        newEvent = deathEv;
        update(&model->player, newEvent, 0);
    }
    if (model->opponent.hud.health.currHealth <= 0)
    {
        newEvent = deathEv;
        update(&model->opponent, newEvent, 0);
    }
    sceneController(model);

    return;
}



/****************************************************************************************
 * Name: gameLoop
 * 
 * Purpose: The game loop state
 * 
 * Details: This function is the game loop state, returns the new game state based on
 *          user input (quit, pause, etc.) or game state (player death, opponent death)
 * 
 * Inputs: base16 - the base address of the screen
 *         secondBase16 - the second base address of the screen
 *         model - the game model
 * 
 * Returns: The new game state
 ****************************************************************************************/
GameStates gameLoop(UINT16 *base16, UINT16 *secondBase16, Model *model)
{

    UINT32 timeNow, timeThen, timeDelta;
    bool updateBuffer = true;
    GameStates gState = OnePlayer;

    set_video_base(secondBase16);
    render(model, base16);
    render(model, secondBase16);
    REQUEST_HUD_RENDER = 2;
    REQUEST_UI_RENDER = 2;

    timeThen = getTime();

    while (gState == OnePlayer && model->player.state != Dead && model->opponent.state != Dead)
    {

        timeNow = getTime();
        timeDelta = timeNow - timeThen;

        /*clear the buffer*/
        processAsync(model, &gState);

        if (timeDelta >= 1)
        {
     
            processSync(model);

            if (updateBuffer == true)
            {
                clear_game_space((UINT8 *)base16);
                render(model, base16);
                set_video_base(base16);
                myVsync();
                updateBuffer = false;
            }
            else if (updateBuffer == false)
            {
                clear_game_space((UINT8 *)secondBase16);
                render(model, secondBase16);
                set_video_base(secondBase16);
                myVsync();
                updateBuffer = true;
            }
        }

        timeThen = timeNow;
    }
    set_video_base(base16);
    myVsync();

    if (model->player.state == Dead)
    {
        gState = OpponentWin;
    }
    else if (model->opponent.state == Dead)
    {
        gState = PlayerWin;
    }

    return gState;
}

/****************************************************************************************
 * Name: gameOverScreen
 * 
 * Purpose: The game over screen state
 * 
 * Details: This function is the game over screen state, returns the new game state based on
 *         user input/selection (quit or play again)
 * 
 * Inputs: base16 - the base address of the screen
 *         secondBase16 - the second base address of the screen
 *         screen - the game over screen
 *         winner - the winner of the game of the most recent game
 * 
 * Returns: The new game state
 ****************************************************************************************/
GameStates gameOverScreen(UINT16 *base16, UINT16 *secondBase16, EndScreen *screen, GameStates winner)
{
    GameStates gState = winner;

    UINT8 input;
    UINT32 timeNow, timeThen, timeDelta;
    /*SplashScreen splashScreen;*/

    /*initSplashScreen(&splashScreen);*/
    set_video_base(base16);
    resetMouse(&screen->menu);
    screen->menu.mX = keyBufferQueue.mX;
    screen->menu.mY = keyBufferQueue.mY;

    chooseEndScreen(screen, winner);
    renderMenuBackground(&screen->menu, (UINT32 *)base16);
    renderMenuUpdate(&screen->menu, base16);

    timeThen = getTime();

    while (gState == winner)
    {

        timeNow = getTime();
        timeDelta = timeNow - timeThen;

        /*clear the buffer*/
        if (keyPending())
        {
            input = keyBuffDequeue();

            buttonHoverd(screen->menu.mX, screen->menu.mY, &screen->playAgainBtn);
            buttonHoverd(screen->menu.mX, screen->menu.mY, &screen->menuBtn);
           
            switch (input)
            {
            case mouseClick_LS: /*left mouse button pressed*/
                /*check to see which button mouse is hovering over when clicked*/
                if (screen->playAgainBtn.hovered == true)
                    gState = OnePlayer;

                if (screen->menuBtn.hovered == true)
                    gState = Splash;
                break;

            case esc_KEY:
                gState = Quit;
                break;
            
            default:
                gState = winner;
                break;
            }
        }

        if (timeDelta >= 1)
        {
            screen->menu.prevmX = screen->menu.mX;
            screen->menu.prevmY = screen->menu.mY;
            screen->menu.mX = keyBufferQueue.mX;
            screen->menu.mY = keyBufferQueue.mY;
            /*this is where we update the menu buttons*/
            renderMenuUpdate(&screen->menu, base16);
        }
        timeThen = timeNow;
    }
    return gState;
}

