#ifndef PSG_H
#define PSG_H

#include <osbind.h>
#include "types.h"

/*SSG (Software-controlled Sound Generator) 
is the YM2149's PSG(Programmable sound generator)*/

/*according to page 7 of YM2149 documentation*/
/*fine tune registers*/
#define CH_A_FINE 0x0
#define CH_B_FINE 0x2
#define CH_C_FINE 0x4

/*coarse tune registers*/
#define CH_A_COARSE 0x1
#define CH_B_COARSE 0x3
#define CH_C_COARSE 0x5

/*volume registers*/
#define CH_A_VOL 0x8
#define CH_B_VOL 0x9
#define CH_C_VOL 0xA

/*mixer and noise*/
#define NOISE_FREQ_REG 0x6
#define MIXER_REG 0x7


/*
enable channels on mixer (to mix tone and noise include &'s)

Details of the YM2149 Mixer Register (pg.20):

if noise bit = 0 AND tone bit = 0 then output is combined by the mixer
if noise bit = 0 AND tone bit = 1 then output noise signal
if noise bit = 1 AND tone bit = 0 then output tone signal
if noise bit = 1 AND tone bit = 1 then output nothing

B0 - B2 ==> tone
B3 - B5 ==> noise
B6 - B7 ==> I/O (if both bits are =0 then Input is selected)

| B7 | B6 | B5 | B4 | B3 | B2 | B1 | B0 |
-----------------------------------------
| B  | A  | C  | B  | A  | C  | B  | A  |
*/
#define MIXER_NONE 0x3F         /*(<--- binary: 0 0 111 111)*/

#define MIXER_TONE_CH_A 0x3E    /*(<--- binary: 0 0 111 110)*/
#define MIXER_TONE_CH_B 0x3D    /*(<--- binary: 0 0 111 101)*/
#define MIXER_TONE_CH_C 0x3B    /*(<--- binary: 0 0 111 011)*/

#define MIXER_NOISE_CH_A 0x37   /*(<--- binary: 0 0 110 111)*/
#define MIXER_NOISE_CH_B 0x2F   /*(<--- binary: 0 0 101 111)*/
#define MIXER_NOISE_CH_C 0x1F   /*(<--- binary: 0 0 011 111)*/


/*envelopes*/
/*page 34 talks about how sound effects can be made using noise.
envelopes aren't neccessarily required but are on pg.24*/
#define ENV_FINE 0xB
#define ENV_ROUGH 0xC
#define ENV_SHAPE_CONTROL 0xD

/**
 * envelope shape bit patterns (see pg.34 shapes truth table)
 * 
 * the shape determines when sound is active (every point when the
 * shape touches the top, sound is active)
 * 
 * sustain determines speed
 * 
 *  B3   B2    B1   B0
 * CONT  ATT  ALT  HOLD
 * 
 *   0    0    x    x       \_______________________      0x0
 *   0    1    x    x       / |_____________________      0x4
 *   1    0    0    0       \ |\ |\ |\ |\ |\ |\ |\        0x8
 *   1    0    0    1       \_______________________      0x9
 *   1    0    1    0       \  /\  /\  /\  /\  /\  /      0xA
 *   1    0    1    1       \ |"""""""""""""""""""""      0xB
 *   1    1    0    0       / | /| /| /| /| /| /| /|      0xC
 *   1    1    0    1       / ______________________      0xD
 *   1    1    1    0       / \  /\  /\  /\  /\  /\       0xE
 *   1    1    1    1       / |_____________________      0xF
 */
#define SHAPE_CONT_OFF_ATT_OFF 0x0
#define SHAPE_CONT_OFF_ATT_ON 0x4
#define SHAPE_CONT_ON_ATT_OFF_ALT_OFF_HOLD_OFF 0x8
#define SHAPE_CONT_ON_ATT_OFF_ALT_OFF_HOLD_ON 0x9
#define SHAPE_CONT_ON_ATT_OFF_ALT_ON_HOLD_OFF 0xA
#define SHAPE_CONT_ON_ATT_OFF_ALT_ON_HOLD_ON 0xB
#define SHAPE_CONT_ON_ATT_ON_ALT_OFF_HOLD_OFF 0xC
#define SHAPE_CONT_ON_ATT_ON_ALT_OFF_HOLD_ON 0xD
#define SHAPE_CONT_ON_ATT_ON_ALT_ON_HOLD_OFF 0xE
#define SHAPE_CONT_ON_ATT_ON_ALT_ON_HOLD_ON 0xF


/**
 * Writes the given byte value to the given PSG register (0-15)
 * This helper function used by other functions in the psg module
 * 
 * @param reg - PSG register (0 - 15)
 * @param val - value to write (0 - 255)
 */
void write_psg(int reg, UINT8 val);

/**
 * Read value of a register (for testing purposes)
 * 
 * @param reg - PSG register (0 - 15)
 * @return UINT8 - value stored in the given register
 */
UINT8 read_psg(int reg);

/**
 * Loads the tone registers (coarse and fine) for the given channel
 * (0 = A, 1 = B, 2 = C) with the given 12-bit tuning
 * 
 * @param channel - channel being modified
 * @param tuning - fine and coarse tuning values to load into the given channel
 */
void set_tone(channel channel, int tuning);

/**
 * Loads the volume register for the given channel
 * 
 * @param channel - channel being modified
 * @param vol - volume to load into the given channel
 */
void set_volume(channel channel, int vol);

/**
 * Load the noise register with the given tuning
 * 
 * @param tuning - tuning to load into the noise register
 */
void set_noise(int tuning);

/**
 * Loads the PSG envelope control registers with the given envelope
 * shape and 16-bit sustain
 * 
 * @param shape - cont, att, alt, and hold bits to load into the shape
 *                control register
 * @param sustain - fine and rough sustain values to load into the envelope
 */
void set_envelope(int shape, UINT16 sustain);


/**
 * Turns the given channel's tone and noise signals on/off
 * 
 * @param channel - channel being modified
 * @param tone_on - if true, to turn on, otherwise false
 * @param noise_on - if true, to turn on, otherwise false
 */
void enable_channel(channel channel, bool tone_on, bool noise_on);

/**
 * Turns the given channel's tone and noise bits off
 * 
 * @param channel - channel being modified on the mixer
 */
void disable_channel(channel channel);

/**
 * Silences all PSG sound production
 */
void stop_sound();


#endif