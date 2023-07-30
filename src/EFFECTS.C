#include "effects.h"

bool effectsOn = false;

/***********************************************************************
 * Name: playHitEffect
 * 
 * Purpose: plays the sound effect for when an avatar's light attack
 *          connects with the other avatar
 * 
 * Details: This function uses a combination of noise and envelope control
 *          to create a short gunshot-like sound
 * 
 * Inputs: None
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void play_hit_effect() 
{
    int oldIpl;
    long oldSsp;

    /*interrupt masking*/
    oldSsp = Super(0);
    oldIpl = set_ipl(7);
    Super(oldSsp);

    oldSsp = Super(0);

    set_noise(0x0F);

    write_psg(MIXER_REG, MIXER_NONE);

    enable_channel(CH_A, false, true);
    enable_channel(CH_B, false, true);
    enable_channel(CH_C, false, true);

    /*set_volume(CH_A, 0x0C);
    set_volume(CH_B, 0x0C);
    set_volume(CH_C, 0x0C);*/

    set_envelope(SHAPE_CONT_OFF_ATT_OFF, 0x1000);
    
    TIMER_SNDFX = 0;    /*start timer*/
    effectsOn = true;

    Super(oldSsp);

    oldSsp = Super(0);
    set_ipl(oldIpl);
    Super(oldSsp);
}

/***********************************************************************
 * Name: playKickEffect
 * 
 * Purpose: plays the sound effect for when an avatar's heavy attack
 *          connects with the other avatar
 * 
 * Details: This function uses a combination of noise, tone, and 
 *          envelope control to create a short gunshot-like sound
 * 
 * Inputs: None
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void play_kick_effect() 
{
    int oldIpl;
    long oldSsp;

    /*interrupt masking*/
    oldSsp = Super(0);
    oldIpl = set_ipl(7);
    Super(oldSsp);

    oldSsp = Super(0);

    set_tone(CH_C, 0x0AA5);
    set_noise(0x0F);

    write_psg(MIXER_REG, MIXER_NONE);

    enable_channel(CH_A, true, true);
    enable_channel(CH_B, true, true);
    enable_channel(CH_C, true, true);

    /*set_volume(CH_A, 0x10);
    set_volume(CH_B, 0x10);
    set_volume(CH_C, 0x10);*/

    set_envelope(SHAPE_CONT_OFF_ATT_OFF, 0x3800);
    
    TIMER_SNDFX = 0;    /*start timer*/
    effectsOn = true;

    Super(oldSsp);

    oldSsp = Super(0);
    set_ipl(oldIpl);
    Super(oldSsp);
}

/***********************************************************************
 * Name: updateSndfx
 * 
 * Purpose: Syncronously updates sound effects
 * 
 * Details: If a timer or envelope indicates that a sound effect is 
 *          complete, the corresponding registers in the psg
 *          are cleared to avoid interfering with the music
 * 
 * Inputs: None
 * Outputs: N/A
 *
 * Returns: A boolean indicating whether or not a sound effect is
 *          currently playing
 ***********************************************************************/
bool update_sndfx()
{
    if(TIMER_SNDFX >= 42 && effectsOn == true){
        stop_effects();
        effectsOn = false;
    }

    return effectsOn;
}

/***********************************************************************
 * Name: updateSndfx
 * 
 * Purpose: disables and clears psg registers to avoid
 * 
 * Details: all channels used to create a sound effect are disabled on the
 *          mixer so that they can be appropriately updated for usage in 
 *          music. all noise and envelope related registers are cleared as
 *          they serve no purpose beyond sound effects.
 * 
 * Inputs: None
 * Outputs: N/A
 * Returns: None
 ***********************************************************************/
void stop_effects()
{
    /*disable c in mixer*/
    disable_channel(CH_A);
    disable_channel(CH_B);
    disable_channel(CH_C);

    /*disable noise bits*/
    write_psg(NOISE_FREQ_REG, 0x00);

    /*disable envelope bits remove this if envelopes are used for music too*/
    write_psg(ENV_FINE, 0x00);
    write_psg(ENV_ROUGH, 0x00);
    write_psg(ENV_SHAPE_CONTROL, 0x00);

    /*
    set_volume(CH_A, 0x0C);
    set_volume(CH_B, 0x0C);
    set_volume(CH_C, 0x0C);*/

    /*enable_channel(CH_A, true, false);
    enable_channel(CH_B, true, false);
    enable_channel(CH_C, true, false);*/

    /*disable the volume of effects channel*/
    /*set_volume(CH_C, 0);*/
}