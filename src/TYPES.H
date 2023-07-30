#ifndef TYPES_H
#define TYPES_H


typedef enum { false, true } bool;
typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;
typedef UINT8 SCANCODE;

typedef enum { CH_A, CH_B, CH_C } channel;

typedef struct Note
{ 
    int tuning;     /*12-bit tuning*/
    int duration;   /*Hz for counter*/
} Note;

typedef struct Frame
{
    UINT16 *bitmap;
    unsigned int width;
    unsigned int height;
    unsigned int offsetX;
    unsigned int offsetY;
} Frame;

typedef struct Animation
{
    Frame *frames;
    unsigned int numFrames;
    unsigned int offsetX;
    int duration;
} Animation;

#endif