/********************************************************************
*   File:       RASTER.H
*
*   Author(s):  Tobias W
*               Jayden M
*
*   Date:       2022-03-29     
********************************************************************/
#include "raster.h"

/***********************************************************************
* Name: get_video_base
*
* Purpose: Gets the base address of the video buffer
*
* Details: getting the base address of the video buffer is a two step process
*          that must be done in supervisor mode. 
*
* Inputs: None
*
* Returns: The base address of the video buffer as a pointer to a UINT16
***********************************************************************/
UINT16 *get_video_base()
{
	UINT16 *base;
	long oldSsp;

	oldSsp = Super(0);
	base = get_buffer();
	Super(oldSsp);

	return (UINT16 *)base;
}

/***********************************************************************
 * Name: set_video_base
 * 	
 * Purpose: Sets the base address of the video buffer
 * 	
 * Details: setting the base address of the video buffer is a two step process
 * 			that must be done in supervisor mode.
 * 	
 * Inputs: newBase - the new base address of the video buffer
 * 	
 * Returns: None
 * ***********************************************************************/
void set_video_base(UINT16 *newBase)
{
	long oldSsp;
	oldSsp = Super(0);
	set_buffer(newBase);
	Super(oldSsp);
	myVsync();
	return;
}

/***********************************************************************
 * Name: get_base
 * 	
 * Purpose: Gets the base address of the back buffer
 * 	
 * Details: The back buffer is a 640x480 monochrome screen that is used
 * 			to draw to before being copied to the video buffer. This
 * 			function gets the base address of the back buffer.
 * 	
 * Inputs: back_buffer - the base address of the back buffer
 * 	
 * Returns: The base address of the back buffer as a pointer to a UINT8
 * ***********************************************************************/
UINT8 *shiftBase(UINT8 *back_buffer)
{
    UINT8 *base;
    UINT16 diff;
    base = back_buffer;
    diff = (int)base;
    diff %= 0x100;
    diff = 0x100 - diff;
    return base + diff;
}
/***********************************************************************
 * Name: plotPixel
 * 	
 * Purpose: Plots a pixel at the given coordinates
 * 	
 * Details: Takes a base address and coordinates and plots
 * 			a pixel at that location. 
 * 	
 * Inputs: 	base - the base address of the screen
 * 			x - the x coordinate of the pixel to be plotted
 * 			y - the y coordinate of the pixel to be plotted
 * 	
 * Returns: None
 * ***********************************************************************/
void plotPixel(UINT8 *base, int x, int y)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
		*(base + y * 80 + (x >> 3)) |= 1 << (7 - (x & 7));
	/* -----------            ^                    ^
						   (x / 8)               (x % 8)
		this is the original code in the parentheses but lsl and AND
		are faster processes than divide and mod
	*/
}

/***********************************************************************
 * Name: plotByte
 * 	
 * Purpose: Plots a byte at the given coordinates
 * 	
 * Details: Takes a base address and coordinates and plots
 * 			a byte at that location. 
 * 	
 * Inputs: 	base - the base address of the screen
 * 			x - the x coordinate of the byte to be plotted
 * 			y - the y coordinate of the byte to be plotted
 * 	
 * Returns: None
 * ***********************************************************************/
void plotByte(UINT8 *base, int x, int y)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
		*(base + y * 80 + (x >> 3)) = 0xFF;
}

/***********************************************************************
 * Name: plotVertical 
 * 	
 * Purpose: Plots a vertical line from the given coordinates
 * 	
 * Details: Takes a base address and coordinates and plots
 * 			a line from the first point to the second point. 
 * 	
 * Inputs: 	base - the base address of the screen
 * 			x  - the x coordinate of the first point
 * 			y1 - the y coordinate of the first point
 * 			y2 - the y coordinate of the second point
 * 	
 * Returns: None
 * ***********************************************************************/
void plotVertical(UINT8 *base, int y1, int y2, int x)
{
	/*assume y2 > y1*/
	int i, y, length;
	y = y1;
	length = y2 - y1;

	for (i = 0; i < length; i++)
	{
		plotPixel(base, x, y);
		y++;
	}
}

/***********************************************************************
 * Name: plotHorizontal (redacted)
 * 
 * Purpose: Plots a horizontal line from the given coordinates
 * 
 * Details: Takes a base address and coordinates and plots
 * 			a line from the first point to the second point.
 * 
 * Inputs: 	base - the base address of the screen
 * 			x1 - the x coordinate of the first point
 * 			y1 - the y coordinate of the first point
 * 			x2 - the x coordinate of the second point
 * 			y2 - the y coordinate of the second point
 * 
 * Returns: None
 *
 * ***********************************************************************/
void plotHorizontal(UINT8 *base, int x1, int x2, int y)
{
	/*assume x2 > x1*/
	int i, x, remainder;
	x = x1;
	remainder = (x2 - x1) % 8;

	while (x <= (x1 + remainder) || x % 8 != 0)
	{
		plotPixel(base, x, y);
		x++;
	}

	remainder = (x2 - x) / 8;

	for (i = 0; i < remainder; i++)
	{
		plotByte(base, x, y);
		x += 8;
	}

	while (x <= x2)
	{
		/**(base + y * 80 + (x >> 3)) = 0xFF;*/ /*plot_byte*/
		plotPixel(base, x, y);
		x++;
	}
}


/***********************************************************************
 * Name: 	plotRect
 * 
 * Purpose: Plots a rectangle from the given coordinates
 * 
 * Details: Takes a base address and coordinates and plots
 * 
 * Inputs: 	base - the base address of the screen
 * 			width - the width of the rectangle
 * 			height - the height of the rectangle
 * 			xPos - the x coordinate of the first point
 * 			yPos - the y coordinate of the first point
 * 
 * Returns: None
 * ***********************************************************************/
void plotRect(UINT8 *base, int width, int height, int xPos, int yPos)
{

	int x, y;

	plotHorizontalLine(base, xPos, yPos, width);
	plotHorizontalLine(base, xPos, yPos + height, width);
	plotVertical(base, yPos, yPos + height, xPos);
	plotVertical(base, yPos, yPos + height, xPos + width);
}


/***********************************************************************
 * Name: plotRectFill
 * 	
 * Purpose: Plots a filled rectangle from the given coordinates
 * 	
 * Details: Takes a base address and coordinates and plots
 * 			a filled rectangle from the first point to the second point. 
 * 	
 * Inputs: 	base - the base address of the screen
 * 			width - the width of the rectangle
 * 			height - the height of the rectangle
 * 			xPos - the x coordinate of the first point
 * 			yPos - the y coordinate of the first point
 * 	
 * Returns: None
 * ***********************************************************************/
void plotRectFill(UINT8 *base, int width, int height, int xPos, int yPos)
{
	int currRow;

	if (xPos >= 0 && xPos < SCREEN_WIDTH && yPos >= 0 && yPos < SCREEN_HEIGHT)
	{
		for (currRow = 0; currRow < height && yPos < SCREEN_HEIGHT; currRow++)
		{
			plotHorizontalLine(base, xPos, yPos, width);
			yPos++;
		}
	}
}

/***********************************************************************
 * Name: plotRectClear
 * 	
 * Purpose: Clears a rectangle from the given coordinates
 * 	
 * Details: Takes a base address and coordinates and clears
 * 			a rectangle from the first point to the second point. 
 * 	
 * Inputs: 	base - the base address of the screen
 * 			width - the width of the rectangle
 * 			height - the height of the rectangle
 * 			xPos - the x coordinate of the first point
 * 			yPos - the y coordinate of the first point
 * 	
 * Returns: None
 * ***********************************************************************/
void plotRectClear(UINT8 *base, int width, int height, int xPos, int yPos)
{
	int currRow;

	if (xPos >= 0 && xPos < SCREEN_WIDTH && yPos >= 0 && yPos < SCREEN_HEIGHT)
	{
		for (currRow = 0; currRow < height && yPos < SCREEN_HEIGHT; currRow++)
		{
			clearHorizontalLine(base, xPos, yPos, width);
			yPos++;
		}
	}
}


/***********************************************************************
 * Name: printCharacter
 * 	
 * Purpose: Prints a character to the screen
 * 	
 * Details: Takes a base address and coordinates and prints
 * 			a character to the screen. 
 * 	
 * Inputs: 	base - the base address of the screen
 * 			x - the x coordinate of the first point
 * 			y - the y coordinate of the first point
 * 			c - the character to be printed
 * 	
 * Returns: None
 * ***********************************************************************/
void printCharacter(UINT8 *base, int x, int y, char c)
{
	int i;
	const UINT8 *hexOfChar = CUSTOMFONT_START(c);
	for (i = 0; i < FONT_HEIGHT; i++)
	{
		*(base + (y + i) * 80 + (x >> 3)) = *hexOfChar;
		hexOfChar++;
	}
}


/***********************************************************************
 * Name: printString
 * 	
 * Purpose: Prints a string to the screen
 * 	
 * Details: Takes a base address and coordinates and prints
 * 			a string to the screen. 
 * 	
 * Inputs: 	base - the base address of the screen
 * 			x - the x coordinate of the first point
 * 			y - the y coordinate of the first point
 * 			spacing - the spacing between characters
 * 			string - the string to be printed
 * 	
 * Returns: None
 * ***********************************************************************/

void printString(UINT8 *base, int x, int y, int spacing, const char string[])
{
	int i;
	for (i = 0; string[i] != '\0'; i++)
	{
		printCharacter(base, x, y, string[i]);
		x += spacing;
	}
}

/***********************************************************************
 * Name: plotBitmap8
 * 	
 * Purpose: Plots ANY size bitmap made of up 8 bit values to the screen
 * 	
 * Details: Takes a base address and coordinates and plots
 * 			a bitmap to the screen. Bitmap must be made of 8 bit values
 * 			but its dimensions can be any size. X coordinate does not 
 * 			need to be a multiple of 8 (ie byte aligned) 
 * 	
 * Inputs: 	base - the base address of the screen
 * 			x - the x coordinate of the first point
 * 			y - the y coordinate of the first point
 * 			bitmap - the bitmap to be printed
 * 			width - the width of the bitmap
 * 			height - the height of the bitmap
 * 	
 * Returns: None
 * ***********************************************************************/
void plotBitmap8(UINT8 *base, int x, int y, const UINT8 *bitmap, unsigned int width, unsigned int height)
{

	int i, h, currByte, nBytes;
	i = 0;
	nBytes = width / 8;

	/*vertical loop*/
	for (h = 0; h < height; h++)
	{
		/*single row loop*/
		for (currByte = 0; currByte < nBytes; currByte++)
		{
			if (x & 7)
			{
				*(base + y * 80 + (x >> 3) + currByte) |= bitmap[i + currByte] >> ((x + currByte * 8) & 7);
				*(base + y * 80 + (x >> 3) + currByte + 1) |= bitmap[i + currByte] << (7 - (x + currByte * 8) & 7);
			}
			else
			{
				*(base + y * 80 + (x >> 3) + currByte) = bitmap[i + currByte];
			}
		}
		i += nBytes;
		y++;
	}
}

/***********************************************************************
 * Name: plotBitmap16
 * 	
 * Purpose: Plots ANY size bitmap made of up 16 bit values to the screen
 * 	
 * Details: Takes a base address and coordinates and plots
 * 			a bitmap to the screen. Bitmap must be made of 16 bit values
 * 			but its dimensions can be any size. X coordinate does not 
 * 			need to be a multiple of 16 (ie word aligned) 
 * 	
 * Inputs: 	base - the base address of the screen
 * 			x - the x coordinate of the first point
 * 			y - the y coordinate of the first point
 * 			bitmap - the bitmap to be printed
 * 			width - the width of the bitmap
 * 			height - the height of the bitmap
 * 	
 * Returns: None
 * ***********************************************************************/
void plotBitmap16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int width, unsigned int height)
{

	int i, h, currWord, nWords;
	i = 0;
	nWords = width / 16;

	/*vertical loop*/
	for (h = 0; h < height; h++)
	{
		/*single row loop*/
		for (currWord = 0; currWord < nWords; currWord++)
		{
			*(base + y * 40 + (x >> 4) + currWord) |= bitmap[i + currWord] >> ((x + currWord * 16) & 15);
			*(base + y * 40 + (x >> 4) + currWord + 1) |= bitmap[i + currWord] << (15 - (x + currWord * 16) & 15);
		}
		i += nWords;
		y++;
	}
}

/***********************************************************************
 * Name: plotBitmap32
 * 	
 * Purpose: Plots ANY size bitmap made of up 32 bit values to the screen
 * 	
 * Details: Takes a base address and coordinates and plots
 * 			a bitmap to the screen. Bitmap must be made of 32 bit values
 * 			but its dimensions can be any size. X coordinate does not 
 * 			need to be a multiple of 32 (ie long aligned) 
 * 	
 * Inputs: 	base - the base address of the screen
 * 			x - the x coordinate of the first point
 * 			y - the y coordinate of the first point
 * 			bitmap - the bitmap to be printed
 * 			width - the width of the bitmap
 * 			height - the height of the bitmap
 * 	
 * Returns: None
 * ***********************************************************************/
void plotBitmap32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int width, unsigned int height)
{

	int i, h, currLong, nLongs;
	i = 0;
	nLongs = width / 32;

	/*Vertical loop*/
	for (h = 0; h < height; h++)
	{
		/*single row loop*/
		for (currLong = 0; currLong < nLongs; currLong++)
		{
			if (x & 31)
			{
				*(base + y * 20 + (x >> 5) + currLong) |= bitmap[i + currLong] >> ((x + currLong * 32) & 31);
				*(base + y * 20 + (x >> 5) + currLong + 1) |= bitmap[i + currLong] << (31 - (x + currLong * 32) & 31);
			}
			else
			{
				*(base + y * 20 + (x >> 5) + currLong) = bitmap[i + currLong];
			}
		}
		i += nLongs;
		y++;
	}
}

/***********************************************************************
 * Name: clearRegion
 * 
 * Purpose: Clears a region of the screen
 * 
 * Details: Takes a base address and coordinates and clears
 * 			a region of the screen.
 * 
 * Inputs: 	base - the base address of the screen
 * 			xPos - the x coordinate of the first point
 * 			yPos - the y coordinate of the first point
 * 			width - the width of the region
 * 			height - the height of the region
 * 	
 * Returns: None
 * ***********************************************************************/
void clearRegion(UINT8 *base, unsigned int xPos, unsigned int yPos, unsigned int width, unsigned int height)
{
	int currRow;

	if (xPos >= 0 && xPos < SCREEN_WIDTH && yPos >= 0 && yPos < SCREEN_HEIGHT)
	{
		for (currRow = 0; currRow < height && yPos < SCREEN_HEIGHT; currRow++)
		{
			clearHorizontalLine(base, xPos, yPos, width);
			yPos++;
		}
	}
}


/***********************************************************************
 * Name: plotHorizontalLine
 * 
 * Purpose: Plots a horizontal line to the screen
 * 
 * Details: Takes a base address and coordinates and plots
 * 			a horizontal line to the screen.
 * 	
 * Inputs: 	base - the base address of the screen
 * 			x - the x coordinate of the first point
 * 			y - the y coordinate of the first point
 * 			width - the width of the line
 * 
 * Returns: None
 * ***********************************************************************/
void plotHorizontalLine(UINT8 *base, int x, int y, int width)
{
	const UINT8 mask = 0xff;
	UINT8 *currByte;
	UINT8 *lastByte;
	int x2 = x + width - 1;
	currByte = base + (y * 80) + (x >> 3);
	lastByte = base + (y * 80) + (x2 >> 3);

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		if (x2 >= SCREEN_WIDTH)
		{
			x2 = SCREEN_WIDTH - 1;
			width = x2 - x + 1;
		}

		if (x & 7) /*same as x % 7, check if x is in the bounds of a byte*/
		{
			*currByte |= mask >> (x & 7);
			currByte++;

			while (currByte < lastByte)
			{
				*currByte = mask;
				currByte++;
			}

			*currByte |= mask << (7 - (x2 & 7));
		}
		else
		{
			while (currByte <= lastByte)
			{
				*currByte = mask;
				currByte++;
			}

			currByte--;
			*currByte |= mask >> (8 - width);
		}
	}
}


/***********************************************************************
 * Name: clearHorizontalLine
 * 
 * Purpose: Clears a horizontal line to the screen
 * 
 * Details: Takes a base address and coordinates and clears
 * 			a horizontal line to the screen.
 * 
 * Inputs: 	base - the base address of the screen
 * 			x - the x coordinate of the first point
 * 			y - the y coordinate of the first point
 * 			width - the width of the line
 * 
 * Returns: None
 * ***********************************************************************/
void clearHorizontalLine(UINT8 *base, int x, int y, int width)
{
	const UINT8 mask = 0xff;
	UINT8 *currByte;
	UINT8 *lastByte;
	int x2 = x + width - 1;
	currByte = base + (y * 80) + (x >> 3);
	lastByte = base + (y * 80) + (x2 >> 3);

	if (x & 7) /*same as x % 7, check if x is in the bounds of a byte*/
	{
		*currByte &= ~(mask >> (x & 7));
		currByte++;

		while (currByte < lastByte)
		{
			*currByte = 0;
			currByte++;
		}

		*currByte &= ~(mask << (7 - (x2 & 7)));
	}
	else
	{
		while (currByte <= lastByte)
		{
			*currByte = 0;
			currByte++;
		}

		currByte--;
		*currByte &= ~(mask >> (8 - width));
	}
}


/***********************************************************************
 * Name: xorHorizontalLine
 * 
 * Purpose: XORs a horizontal line to the screen
 * 
 * Details: Takes a base address and coordinates and XORs
 * 			a horizontal line to the screen.
 * 	
 * Inputs: 	base - the base address of the screen
 * 			x - the x coordinate of the first point
 * 			y - the y coordinate of the first point
 * 			width - the width of the line
 * 
 * Returns: None
 * ***********************************************************************/
void xorHorizontalLine(UINT8 *base, int x, int y, int width)
{
	const UINT8 mask = 0xff;
	int x2 = x + width - 1;
	UINT8 *row = base + (y * 80);
	UINT8 *currentByte = row + (x >> 3);
	UINT8 *lastByte = row + (x2 >> 3);

	if (currentByte == lastByte)
	{
		*currentByte ^= mask >> (x & 7) & mask << (~x2 & 7);
	}
	else
	{
		*currentByte++ ^= mask >> (x & 7);
		while (currentByte != lastByte)
		{
			*currentByte++ ^= mask;
		}
		*lastByte ^= mask << (~x2 & 7);
	}
}

/***********************************************************************
 * Name: clearHorizontal (redacted)
 * 
 * Purpose: Clears a horizontal line to the screen
 * 
 * Details: Takes a base address and coordinates and clears
 * 			a horizontal line to the screen.
 * 
 * Inputs: 	base - the base address of the screen
 * 			x - the x coordinate of the first point
 * 			y - the y coordinate of the first point
 * 			width - the width of the line
 * 
 * Returns: None
 * ***********************************************************************/
void clearHorizontal(UINT8 *base, unsigned int x1, unsigned int x2, unsigned int y)
{
	/*assume x2 > x1*/
	int i, x, remainder;
	x = x1;
	remainder = (x2 - x1) % 8;

	while (x <= (x1 + remainder) || x % 8 != 0)
	{
		clearPixel(base, x, y);
		x++;
	}

	remainder = (x2 - x) / 8;

	for (i = 0; i < remainder; i++)
	{
		clearByte(base, x, y);
		x += 8;
	}

	while (x <= x2)
	{
		/**(base + y * 80 + (x >> 3)) = 0xFF;*/ /*plot_byte*/
		clearPixel(base, x, y);
		x++;
	}
}

/***********************************************************************
 * Name: clearByte
 * 
 * Purpose: Clears a byte to the screen
 * 
 * Details: Takes a base address and coordinates and clears
 * 			a byte to the screen.
 * 			
 * Inputs: 	base - the base address of the screen
 * 			x - the x coordinate of the byte
 * 			y - the y coordinate of the byte
 * 			
 * Returns: None
 * ***********************************************************************/
void clearByte(UINT8 *base, unsigned int x, unsigned int y)
{
	*(base + y * 80 + (x >> 3)) = 0x00;
}


/***********************************************************************
 * Name: clearPixel
 * 
 * Purpose: Clears a pixel to the screen
 * 
 * Details: Takes a base address and coordinates and clears
 * 			a pixel to the screen.
 * 	
 * Inputs: 	base - the base address of the screen
 * 			x - the x coordinate of the pixel
 * 			y - the y coordinate of the pixel
 * 	
 * Returns: None
 * ***********************************************************************/
void clearPixel(UINT8 *base, unsigned int x, unsigned int y)
{
	*(base + y * 80 + (x >> 3)) &= ~(0x80 >> (x & 7));
}



/***********************************************************************
 * Name: xorCircle
 * 
 * Purpose: XORs a circle to the screen
 * 
 * Details: Takes a base address and coordinates and XORs
 * 			a circle to the screen.
 * 
 * Inputs: 	base - the base address of the screen
 * 			x0 - the x coordinate of the center
 * 			y0 - the y coordinate of the center
 * 			radius - the radius of the circle
 * 
 * Returns: None
 * ***********************************************************************/
void xorCircle(UINT8 *base, int x0, int y0, int radius)
{
	int x = radius;
	int y = 0;
	int decisionOver2 = 1 - x;

	while (y <= x)
	{
		xorHorizontalLine(base, x0 - x, y0 + y, 2 * x + 1);
		xorHorizontalLine(base, x0 - x, y0 - y, 2 * x + 1);
		xorHorizontalLine(base, x0 - y, y0 + x, 2 * y + 1);
		xorHorizontalLine(base, x0 - y, y0 - x, 2 * y + 1);
		y++;
		if (decisionOver2 <= 0)
		{
			decisionOver2 += 2 * y + 1;
		}
		else
		{
			x--;
			decisionOver2 += 2 * (y - x) + 1;
		}
	}
}

