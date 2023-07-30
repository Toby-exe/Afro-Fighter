/********************************************************************
*   File:       RASTER.H
*
*   Author(s):  Tobias W
*               Jayden M
*
*   Date:       2022-03-29     
*   Purpose:    This file contains all the functions for drawing
*               shapes, lines, and bitmaps of different sizes to
*               the screen.
*
*   Details:    All functions are designed to work and assumed to be 
*               working with a 640x480 monochrome screen.
********************************************************************/ 

#ifndef RASTER_H
#define RASTER_H

#include <stdio.h>
#include "types.h"
#include "fonts.h"
#include "vbl.h"
#include "string.h"
#include <osbind.h>

/*  Macros  */
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 400
#define bit_or(a, b) (a |= b)


/*  system  */
UINT16 *get_video_base();
void *get_buffer();
UINT8 *shiftBase(UINT8 *back_buffer);
void set_video_base(UINT16 *newBase);
void set_buffer(UINT16 *);

/*  Basic   */
void plotPixel(UINT8 *base, int x, int y);
void plotByte(UINT8 *base, int x, int y);
void clearPixel(UINT8 *, unsigned int, unsigned int);
void clearByte(UINT8 *, unsigned int, unsigned int);

/* Lines */
void plotVertical(UINT8 *base, int y1, int y2, int x);
void clearHorizontal(UINT8 *base, unsigned int x1, unsigned int x2, unsigned int y);
void clearHorizontalLine(UINT8* base, int x, int y, int width);
void plotHorizontalLine(UINT8* base, int x, int y, int width);
void xorHorizontalLine(UINT8 *base, int x, int y, int width);
void xorCircle(UINT8 *base, int x0, int y0, int radius);

/* Shapes */
void plotRect(UINT8 *base, int width, int height, int xPos, int yPos);
void plotRectFill(UINT8 *base, int width, int height, int xPos, int yPos);
void plotRectClear(UINT8 *base, int width, int height, int xPos, int yPos);

/* Text */
void printCharacter(UINT8 *base, int x, int y, char c);
void printString(UINT8 *base, int x, int y, int spacing, const char string[]);

/*Bitmaps*/
void plotBitmap8(UINT8 *base, int x, int y, const UINT8 *bitmap, unsigned int width, unsigned int height);
void plotBitmap16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int width, unsigned int height);
void plotBitmap32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int width, unsigned int height);
void clearRegion(UINT8 *base, unsigned int xPos, unsigned int yPos, unsigned int width, unsigned int height);


/*ASM Subroutines*/
void clear_screen(UINT32 *); 
void clear_game_space(UINT8 *);
void fill_screen(UINT8 *);
void clear_hud(UINT8 *);


/* redacted */
void plotHorizontal(UINT8 *base, int x1, int x2, int y);

#endif
