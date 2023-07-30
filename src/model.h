#ifndef MODEL_H
#define MODEL_H

#include "TYPES.H"
#include "string.h"
#include "sprites.h"
#include "raster.h"
#include "effects.h"
#include "anims.h"
#include "splash.h"
#include "eSplash.h"
#include <osbind.h>

#define moveSpeed 4
#define strafeSpeed 12
#define floorLvl 374
#define gravity 4

#define xposInBounds(x) (x >= 0 && x < SCREEN_WIDTH)
#define yposInBounds(y) (y >= 0 && y < floorLvl)

#define MAX_NAME_LEN 20
#define NAME_SPACING 8

#define a_KEY 0x0061         /*move right*/
#define d_KEY 0x0064         /*move left*/
#define space_KEY 0x0020     /*jump*/
#define l_KEY 0x006C         /*crouch*/
#define w_KEY 0x0077         /*light attack*/
#define i_KEY 0x0069         /*heavy attack*/
#define f_KEY 0x0066         /*super attack*/
#define j_KEY 0x006A         /*block*/
#define q_KEY 0x0071         /*quit*/
#define tab_KEY 0x0009       /*next button*/
#define esc_KEY 0x001B       /*back button*/
#define mouseClick_LS 0x00FA /*left mouse click*/
#define mouseClick_RS 0x00FB /*right mouse click*/

#define MAX_HEALTH 200
#define SUPER_DAMAGE 20
#define HEAVY_DAMAGE 10
#define LIGHT_DAMAGE 5
#define BLOCK_DAMAGE 4


extern bool avatarStateChange;

typedef enum
{
    Idle,
    Running,
    Jumping,
    InAir,
    Crouching,
    LightAttack,
    HeavyAttack,
    Blocking,
    Super,
    Dead
} avatarStates;

typedef enum
{
    OnePlayer,
    TwoPlayer,
    Quit,
    Splash,
    PlayerWin,
    OpponentWin
} GameStates;

typedef enum
{
    left,
    right
} hDirection;

typedef enum
{
    down,
    up
} vDirection;

typedef enum
{
    player,
    opponent

} Origin;

typedef struct
{
    unsigned int width;
    unsigned int height;
    unsigned int x, y;
} Hitbox;

typedef struct
{
    unsigned int x, y;
    unsigned int barWidth, barHeight;
    int currHealth;
    bool damaged;
} Healthbar;

typedef struct
{
    Healthbar health;
    char p1Name[MAX_NAME_LEN];
    UINT8 *p1_pfpBitmap; /*includes avatar image and decorative borders*/
    UINT8 *p1_superLvl[2];
} HUD;

typedef struct
{
    Hitbox hitbox;
    unsigned int x, y;
    Origin origin;
    int hSpeed;
} Superball;

typedef struct
{   
    char *name;
    avatarStates state;
    Hitbox hitbox;
    hDirection dirx;
    vDirection diry;
    HUD hud;
    unsigned int currFrame;
    Animation currAnim;
    unsigned int x, y;  /*position coordinates*/
    int hSpeed, vSpeed; /*horiz. & vert. displacement per clock tick*/
    bool strafe;
} Avatar;

typedef struct
{
    unsigned int x, y;
    unsigned int width, height;
    bool hovered;
} Button;

typedef struct
{
    unsigned int x, y;
    unsigned int width, height;
} Banana;

typedef struct
{
    /*for player1*/
    UINT32 *bitmap;
    Banana selectorLs;
    Banana selectorRs;
    int prevmX;
    int prevmY;
    int mX;
    int mY;
    int mWidth;

} Menu;

typedef struct
{
    Button playAgainBtn;
    Button menuBtn;
    int btnCount;
    Menu menu;
    GameStates winner;
    UINT32 *endBitmap;

} EndScreen;

typedef struct
{
    Button onePlayerBtn;
    Button twoPlayerBtn;
    Button quitBtn;
    int btnCount;
    Menu menu;

} SplashScreen;

/*contains all game objects*/
typedef struct
{
    Avatar player;
    Avatar opponent;
    bool combatCollision;
    /*bool superCollision*/
} Model;

/*this will become useful if game becomes more complex in the future*/
typedef struct
{
    GameStates state;
    SplashScreen splashScreen;
    EndScreen endScreen;
    Model model;
} Game;

/*function prototypes*/
void sceneController(Model *);
void updateAvatar(Avatar *);

void updateMenuSelection(Menu *, int);
void buttonHoverd(int mx, int my, Button *btn);


/*initialization*/
/*menus*/
void initGame(Game *game);
void initSplashScreen(SplashScreen *);
void initEndScreen(EndScreen *);
void resetMouse(Menu *menu);
void chooseEndScreen(EndScreen *, GameStates);
/*
void initEndScreen(EndScreen *);
*/

void initModel(Model *);
void initModelGraphics();
void initAvatar(Avatar *, int, int, char *);
void initGame(Game *game);
void createSuperball(Avatar *);

/*model operations*/
void avatar_idle(Avatar *);
void avatar_move(Avatar *, int);
void player_jump(Avatar *);
void player_crouch(Avatar *);
void avatarLightAttack(Avatar *);
void avatarHeavyAttack(Avatar *);
void player_block(Avatar *);
void player_super(Avatar *);

/*handle collisions*/
/*on environment*/
void wallCollisionsHndlr(Avatar *); /*might need later for super object*/
void floorCollisionsHndlr(Avatar *);

/*on avatar*/
void combatCollisionsHndlr(Avatar *, Avatar *);
void registerLightHit(Avatar *);
void registerHeavyHit(Avatar *);
void registerSuperHit(Avatar *);
void updateHitbox(Avatar *);
/*"physics"*/
void player_inAir(Avatar *);

/*helper methods*/
int sign(int);

#endif