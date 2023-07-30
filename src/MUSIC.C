#include "music.h"

int curr_note_a = 0;
int curr_note_b = 0;
int curr_note_c = 0;

/*Still D.R.E - Dr.Dre (feat Snoop Dogg)*/
const Note song_ch_a[] = {

    /*BAR 1*/
    {C5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {C5_KEY, QUARTER_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},

    /*BAR 2*/
    {B4_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {B4_KEY, QUARTER_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {G5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},

    /*BAR 3*/
    {C5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {C5_KEY, QUARTER_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},

    /*BAR 4*/
    {B4_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {B4_KEY, QUARTER_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {G5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},

    /*BAR 5*/
    {C5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {C5_KEY, QUARTER_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},

    /*BAR 6*/
    {B4_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {B4_KEY, QUARTER_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {G5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},

    /*BAR 7*/
    {C5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {C5_KEY, QUARTER_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},

    /*BAR 8*/
    {B4_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {B4_KEY, QUARTER_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {G5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},

    /*BAR 9*/
    {A5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},

    /*BAR 10*/
    {A5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {G5_KEY, EIGHTH_NOTE},
    {G5_KEY, EIGHTH_NOTE},
    {G5_KEY, EIGHTH_NOTE},
    {G5_KEY, EIGHTH_NOTE},
    {G5_KEY, EIGHTH_NOTE},

    /*BAR 11*/
    {A5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},

    /*BAR 12*/
    {A5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {A5_KEY, EIGHTH_NOTE},
    {G5_KEY, EIGHTH_NOTE},
    {G5_KEY, EIGHTH_NOTE},
    {G5_KEY, EIGHTH_NOTE},
    {G5_KEY, EIGHTH_NOTE},
    {G5_KEY, EIGHTH_NOTE},
};

const Note song_ch_b[] = {
    /*BAR 1*/
    {REST, WHOLE_NOTE},

    /*BAR 2*/
    {REST, WHOLE_NOTE},

    /*BAR 3*/
    {REST, WHOLE_NOTE},

    /*BAR 4*/
    {REST, WHOLE_NOTE},

    /*BAR 5*/
    {A2_KEY, HALF_NOTE + QUARTER_NOTE},
    {B2_KEY, QUARTER_NOTE},

    /*BAR 6*/
    {E2_KEY, HALF_NOTE + QUARTER_NOTE},
    {E2_KEY, QUARTER_NOTE},

    /*BAR 7*/
    {A2_KEY, HALF_NOTE + QUARTER_NOTE},
    {B2_KEY, QUARTER_NOTE},

    /*BAR 8*/
    {E2_KEY, QUARTER_NOTE},
    {E2_KEY, EIGHTH_NOTE + SIXTEENTH_NOTE},
    {E2_KEY, SIXTEENTH_NOTE},
    {E2_KEY, EIGHTH_NOTE},
    {E2_KEY, EIGHTH_NOTE},
    {E2_KEY, EIGHTH_NOTE},
    {E2_KEY, EIGHTH_NOTE},

    /*BAR 9*/
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},

    /*BAR 10*/
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},

    /*BAR 11*/
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},

    /*BAR 12*/
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
    {E5_KEY, EIGHTH_NOTE},
};

const Note song_ch_c[] = {
    /*BAR 1*/
    {REST, WHOLE_NOTE},

    /*BAR 2*/
    {REST, WHOLE_NOTE},

    /*BAR 3*/
    {REST, WHOLE_NOTE},

    /*BAR 4*/
    {REST, WHOLE_NOTE},

    /*BAR 5*/
    {A1_KEY, HALF_NOTE + QUARTER_NOTE},
    {B1_KEY, QUARTER_NOTE},

    /*BAR 6*/
    {E1_KEY, HALF_NOTE + QUARTER_NOTE},
    {E1_KEY, QUARTER_NOTE},

    /*BAR 7*/
    {A1_KEY, HALF_NOTE + QUARTER_NOTE},
    {B1_KEY, QUARTER_NOTE},

    /*BAR 8*/
    {E1_KEY, QUARTER_NOTE},
    {E1_KEY, EIGHTH_NOTE + SIXTEENTH_NOTE},
    {E1_KEY, SIXTEENTH_NOTE},
    {E1_KEY, EIGHTH_NOTE},
    {E1_KEY, EIGHTH_NOTE},
    {E1_KEY, EIGHTH_NOTE},
    {E1_KEY, EIGHTH_NOTE},

    /*BAR 9*/
    {C5_KEY, EIGHTH_NOTE},
    {C5_KEY, EIGHTH_NOTE},
    {C5_KEY, EIGHTH_NOTE},
    {C5_KEY, EIGHTH_NOTE},
    {C5_KEY, EIGHTH_NOTE},
    {C5_KEY, EIGHTH_NOTE},
    {C5_KEY, EIGHTH_NOTE},
    {C5_KEY, EIGHTH_NOTE},

    /*BAR 10*/
    {B4_KEY, EIGHTH_NOTE},
    {B4_KEY, EIGHTH_NOTE},
    {B4_KEY, EIGHTH_NOTE},
    {B4_KEY, EIGHTH_NOTE},
    {B4_KEY, EIGHTH_NOTE},
    {B4_KEY, EIGHTH_NOTE},
    {B4_KEY, EIGHTH_NOTE},
    {B4_KEY, EIGHTH_NOTE},

    /*BAR 11*/
    {C5_KEY, EIGHTH_NOTE},
    {C5_KEY, EIGHTH_NOTE},
    {C5_KEY, EIGHTH_NOTE},
    {C5_KEY, EIGHTH_NOTE},
    {C5_KEY, EIGHTH_NOTE},
    {C5_KEY, EIGHTH_NOTE},
    {C5_KEY, EIGHTH_NOTE},
    {C5_KEY, EIGHTH_NOTE},

    /*BAR 12*/
    {B4_KEY, EIGHTH_NOTE},
    {B4_KEY, EIGHTH_NOTE},
    {B4_KEY, EIGHTH_NOTE},
    {B4_KEY, EIGHTH_NOTE},
    {B4_KEY, EIGHTH_NOTE},
    {B4_KEY, EIGHTH_NOTE},
    {B4_KEY, EIGHTH_NOTE},
    {B4_KEY, EIGHTH_NOTE},
};

int SONG_SZ_A = sizeof(song_ch_a) / sizeof(song_ch_a[0]);
int SONG_SZ_B = sizeof(song_ch_b) / sizeof(song_ch_b[0]);
int SONG_SZ_C = sizeof(song_ch_c) / sizeof(song_ch_c[0]);

/***********************************************************************
 * Name: start_music
 * 
 * Purpose: initializes the registers used for music
 * 
 * Details: Channels A,B, and C are enabled and their volume levels are raised. 
 *          The first note of the song on each channel is written onto the
 *          fine and course tuning registers for each channel.
 * 
 * Inputs: None
 * Outputs: the first note of the song
 * Returns: None
 ***********************************************************************/
void start_music()
{
    long oldssp = Super(0);

    write_psg(MIXER_REG, MIXER_NONE);   /*put mixer into default state*/
    
    /*first note of the song*/
    set_tone(CH_A, song_ch_a[curr_note_a].tuning);     
    set_tone(CH_B, song_ch_b[curr_note_b].tuning);  
    set_tone(CH_C, song_ch_c[curr_note_c].tuning);

    enable_channel(CH_A, true, false);
    enable_channel(CH_B, true, false);
    enable_channel(CH_C, true, false);

    set_volume(CH_A, 0x0C);
    set_volume(CH_B, 0x0C);
    set_volume(CH_C, 0x0C);

    Super(oldssp);
}

/***********************************************************************
 * Name: update_music
 * 
 * Purpose: Advances to the next note of the song as determined by the amount of time
 *          that a note lasts.
 * 
 * Details: At any point when a change to a psg register is about to happen, we check
 *          if a sound effect is playing. Since noise doesn't blend very well with 
 *          music, we make no changes to the music and sound is taken over by an effect
 *          for as long as the effect lasts. The song timing still proceeds as it is 
 *          still audible so that when music resumes, it continues from where is would've
*           been.
 * 
 * Inputs:  sndfx_on - whether or not a sound effect is playing
 *
 * Outputs: the current note of the song on each channel
 *
 * Returns: None
 ***********************************************************************/
void update_music(bool sndfx_on)
{
    bool new_note_a = false;
    bool new_note_b = false;
    bool new_note_c = false;

    /*
    slight pause between notes so they don't blend together
    */
    /*only use channel C for music if it is not currently being used for sound effects*/
    if(sndfx_on == false)
    {
        if(TIMER_MUSIC_A >= song_ch_a[curr_note_a].duration - 5 &&
            TIMER_MUSIC_A <= song_ch_a[curr_note_a].duration){
            disable_channel(CH_A);
        }

        if(TIMER_MUSIC_B >= song_ch_b[curr_note_b].duration - 5 &&
            TIMER_MUSIC_B <= song_ch_b[curr_note_b].duration){
            disable_channel(CH_B);
        }

        if(TIMER_MUSIC_C >= song_ch_c[curr_note_c].duration - 5 &&
           TIMER_MUSIC_C <= song_ch_c[curr_note_c].duration){
            disable_channel(CH_C);
        }
    }

    /*
    Move to the next note on each channel where applicable
    */
    if(TIMER_MUSIC_A >= song_ch_a[curr_note_a].duration) {

        /*restart from the first note when the song finishes; otherwise, move on to the next note*/
        curr_note_a = (curr_note_a >= SONG_SZ_A - 1) ? 0 : curr_note_a + 1;
        TIMER_MUSIC_A = 0;
        new_note_a = true;
    }

    if(TIMER_MUSIC_B >= song_ch_b[curr_note_b].duration) {

        /*restart from the first note when the song finishes; otherwise, move on to the next note*/
        curr_note_b = (curr_note_b >= SONG_SZ_B - 1) ? 0 : curr_note_b + 1;
        TIMER_MUSIC_B = 0;
        new_note_b = true;
    }

    if(TIMER_MUSIC_C >= song_ch_c[curr_note_c].duration) {

        /*restart from the first note when the song finishes; otherwise, move on to the next note*/
        curr_note_c = (curr_note_c >= SONG_SZ_C - 1) ? 0 : curr_note_c + 1;
        TIMER_MUSIC_C = 0;
        new_note_c = true;
    }
    
    /*
    get the tone of the current note on each channel
    */
    /*only use channel C for music if it is not currently being used for sound effects*/
    if(sndfx_on == false)
    {
        set_tone(CH_A, song_ch_a[curr_note_a].tuning);
        set_tone(CH_B, song_ch_b[curr_note_b].tuning);
        set_tone(CH_C, song_ch_c[curr_note_c].tuning);
    }

    /*
    only turn volume back on if a new note has begun
    */
    /*only use channel C for music if it is not currently being used for sound effects*/
    if(sndfx_on == false)
    {
        if(new_note_a == true){
            enable_channel(CH_A, true, false);
        }
        if(new_note_b == true){
            enable_channel(CH_B, true, false);
        }
        if(new_note_c == true){
            enable_channel(CH_C, true, false);
        }
    }
}