#include "psg.h"

volatile char *PSG_reg_select = 0xFF8800;
volatile char *PSG_reg_write  = 0xFF8802;

void write_psg(int reg, UINT8 val)
{
    /*check if register and value to write are both valid*/
    if(reg >= 0 && reg <= 15 && val >= 0 && val <= 255)
    {    
        *PSG_reg_select = reg;
        *PSG_reg_write  = val;
    }
}

UINT8 read_psg(int reg)
{
    UINT8 val;  

    /*default value if register is invalid; this way, if it
    is combined with another value using bitwise &, the 
    result won't be affected by this value*/
    val = 0xFF;

    if(reg >= 0 && reg <= 15)
    {   
        *PSG_reg_select = reg;
        val = *PSG_reg_select;
    }

    return val;
}

void set_tone(channel ch, int tuning)
{
    /*separate 12-bit tuning into individual 8-bit and 4-bit values*/
    UINT8 fineTuning = tuning & 0x00FF;           /*LSB*/
    UINT8 coarseTuning = (tuning & 0x0F00) >> 8;  /*MSB*/

    switch(ch)
    {
        case CH_A:
            write_psg(CH_A_FINE, fineTuning);
            write_psg(CH_A_COARSE, coarseTuning);
            break;

        case CH_B:
            write_psg(CH_B_FINE, fineTuning);
            write_psg(CH_B_COARSE, coarseTuning);
            break;

        case CH_C:
            write_psg(CH_C_FINE, fineTuning);
            write_psg(CH_C_COARSE, coarseTuning);
            break;

        default:
            break;
    }
}

void set_volume(channel ch, int vol)
{
    /*get the 5-bit value from the int*/
    UINT8 volume = vol & 0x001F;

    switch(ch)
    {
        case CH_A:
            write_psg(CH_A_VOL, volume);
            break;

        case CH_B:
            write_psg(CH_B_VOL, volume);
            break;

        case CH_C:
            write_psg(CH_C_VOL, volume);
            break;

        default:
            break;  
    }
}

void set_noise(int tuning)
{
    /*get the 5-bit value from the int*/
    UINT8 freq = tuning & 0x001F;
    write_psg(NOISE_FREQ_REG, freq);
}

void set_envelope(int shape, UINT16 sustain)
{
    UINT8 sustainFine, sustainRough, shapeBits;

    /*separate 16-bit sustain into 2 individual 8-bit values*/
    sustainFine = sustain & 0x00FF;           /*LSB*/
    sustainRough = (sustain & 0xFF00) >> 8;   /*MSB*/

    write_psg(ENV_FINE, sustainFine);
    write_psg(ENV_ROUGH, sustainRough);

    /*get the cont, att, alt, and hold bits to control shape*/
    shapeBits = shape & 0x000F;

    write_psg(ENV_SHAPE_CONTROL, shapeBits);
}

void enable_channel(channel channel, bool tone_on, bool noise_on)
{
    /*by default, keep the value that is currently in the mixer*/
    UINT8 mixer_val = read_psg(MIXER_REG);

    switch (channel)
    {
        case CH_A:

            if(tone_on == true && noise_on == true){
                mixer_val &= MIXER_TONE_CH_A & MIXER_NOISE_CH_A;
            }
            else if(tone_on == true && noise_on == false){
                mixer_val &= MIXER_TONE_CH_A;
            }
            else if(tone_on == false && noise_on == true){
                mixer_val &= MIXER_NOISE_CH_A;
            }
            /*if both are false, do nothing since neither bit is set*/
            break;


        case CH_B:

            if(tone_on == true && noise_on == true){
                mixer_val &= MIXER_TONE_CH_B & MIXER_NOISE_CH_B;
            }
            else if(tone_on == true && noise_on == false){
                mixer_val &= MIXER_TONE_CH_B;
            }
            else if(tone_on == false && noise_on == true){
                mixer_val &= MIXER_NOISE_CH_B;
            }
            /*if both are false, do nothing since neither bit is set*/
            break;


        case CH_C:

            if(tone_on == true && noise_on == true){
                mixer_val &= MIXER_TONE_CH_C & MIXER_NOISE_CH_C;
            }
            else if(tone_on == true && noise_on == false){
                mixer_val &= MIXER_TONE_CH_C;
            }
            else if(tone_on == false && noise_on == true){
                mixer_val &= MIXER_NOISE_CH_C;
            }
            /*if both are false, do nothing since neither bit is set*/
            break;

        default:
            break;
    }

    write_psg(MIXER_REG, mixer_val);
}

void disable_channel(channel channel)
{
    /*by default, keep the value that is currently in the mixer*/
    UINT8 mixer_val = read_psg(MIXER_REG);

    /*setting the appropriate bits on the mixer to 1 to disable the channel*/
    switch (channel)
    {
        case CH_A:
            mixer_val |= 0x09;      /*(<--- binary: 0 0 001 001)*/
            break;

        case CH_B:
            mixer_val |= 0x12;      /*(<--- binary: 0 0 010 010)*/
            break;

        case CH_C:
            mixer_val |= 0x24;      /*(<--- binary: 0 0 100 100)*/
            break;

        default:
            break;
    }

    write_psg(MIXER_REG, mixer_val);
}

void stop_sound()
{
    long oldssp = Super(0);
    /*turn all channels off in the mixer*/
    write_psg(MIXER_REG, MIXER_NONE);     /*should this be MIXER_NONE since 0's mean on*/

    /*disable noise bits*/
    write_psg(NOISE_FREQ_REG, 0x00);

    /*disable envelope bits*/
    write_psg(ENV_FINE, 0x00);
    write_psg(ENV_ROUGH, 0x00);
    write_psg(ENV_SHAPE_CONTROL, 0x00);

    /*disable the volume of all channels*/
    set_volume(CH_A, 0);
    set_volume(CH_B, 0);
    set_volume(CH_C, 0);

    Super(oldssp);
}