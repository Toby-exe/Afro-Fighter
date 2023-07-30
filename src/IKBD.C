/********************************************************************
*   File:       IKBD.C
*
*   Author(s):  Tobias W
*               Jayden M
*
*   Date:       2022-03-29     
********************************************************************/
#include "IKBD.H"
bool keyRepeat = false;
UINT8 ikbdSM = 0;

struct KeyQueue keyBufferQueue = {
    {0}, /*array of key buffers*/
    0,   /*tail*/
    0,   /*head*/
    0,   /*fill level*/
    MX_DEFAULT,
    MY_DEFAULT};

/*  
scancode that is passed in is simply the key number,
since this table is sorted in order it will parse to
the correct corresponding ascii
*/
const UINT8 ASCII_TABLE[TABLE_SIZE] = {
    0x00,
    0x1B,
    0x31,
    0x32,
    0x33,
    0x34,
    0x35,
    0x36,
    0x37,
    0x38,
    0x39,
    0x30,
    0x2D,
    0x3D,
    0x08,
    0x09,
    0x71,
    0x77,
    0x65,
    0x72,
    0x74,
    0x79,
    0x75,
    0x69,
    0x6F,
    0x70,
    0x5B,
    0x5D,
    0x0D,
    0x00,
    0x61,
    0x73,
    0x64,
    0x66,
    0x67,
    0x68,
    0x6A,
    0x6B,
    0x6C,
    0x3B,
    0x27,
    0x60,
    0x00,
    0x5C,
    0x7A,
    0x78,
    0x63,
    0x76,
    0x62,
    0x6E,
    0x6D,
    0x2C,
    0x2E,
    0x2F,
    0x00,
    0x00,
    0x00,
    0x20,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x2D,
    0x00,
    0x00,
    0x00,
    0x2B,
    0x00,
    0x00,
    0x00,
    0x00,
    0x7F,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x28,
    0x29,
    0x2F,
    0x2A,
    0x37,
    0x38,
    0x39,
    0x34,
    0x35,
    0x36,
    0x31,
    0x32,
    0x33,
    0x30,
    0x2E,
    0x0D};

/***********************************************************************
* Name: do_ikbd_isr
*
* Purpose: This function is the interrupt service routine for the
*          keyboard. 
*
* Details: Reads the keyboard (IKBD_RDR) converts the scan
*          code to ascii and enqueues the ascii value to the key board
*          buffer. Mouse movement is also handled here
***********************************************************************/    
void do_ikbd_isr()
{
    UINT8 ascii;
    UINT8 keyPacket;

    *IKBD_CONTROL = 0x16;

    keyPacket = getScanCode();

    if (ikbdSM == 0)
    {
        if (keyPacket < IKBD_MOUSE_MOVE) /*if the key is not a mouse move*/
        {
            if ((keyPacket & 0x80) != BREAK_CODE) /*if the key is not released (make code)*/
            {
                ascii = getAscii(keyPacket);
                keyBuffEnqueue(ascii); /*enqueue*/

                /*TODO: make sure the current key is the same as the prev key*/
                /*keyRepeat = (ascii == keyBufferQueue.buffer[keyBufferQueue.head]) ? true : false;*/
                keyRepeat = true;
            }
            else if ((keyPacket & 0x80) == BREAK_CODE) /*if the key is released (break code)*/
            {
                keyRepeat = false;
            }
        }
        else
        {
            keyBuffEnqueue(keyPacket); /*there is no ascii ?, throw the scancode on the queue*/
            ikbdSM++;
        }
    }
    else
    {
        ikbdSM >= 2
            ? (keyBufferQueue.mY = min(max(keyBufferQueue.mY + (char)keyPacket, 0), 400), ikbdSM = 0)
            : (keyBufferQueue.mX = min(max(keyBufferQueue.mX + (char)keyPacket, 0), 640), ikbdSM++);
    }

    *IKBD_CONTROL = 0x96;

    return;
}

/***********************************************************************
 * Name: keyBuffEnqueue
 * 
 * Purpose: This function enqueues the key buffer
 * 
 * Inputs: ascii value of a key
 ***********************************************************************/
void keyBuffEnqueue(UINT8 ascii)
{
    keyBufferQueue.tail += 1;
    keyBufferQueue.buffer[keyBufferQueue.tail] = ascii;
    keyBufferQueue.fillLevel += 1;
}


/***********************************************************************
 * Name: keyBuffDequeue
 * 
 * Purpose: This function dequeues the key buffer
 * 
 * Returns: ascii value of the key of size UINT8
 ***********************************************************************/
UINT8 keyBuffDequeue()
{
    UINT8 ascii;
    int oldIpl;
    long oldSsp;

    /*see lab 9 + notes and lecture notes 11 pg18*/
    oldSsp = Super(0);
    oldIpl = set_ipl(7);
    Super(oldSsp);

    keyBufferQueue.head += 1;
    ascii = keyBufferQueue.buffer[keyBufferQueue.head];
    keyBufferQueue.fillLevel -= 1;

    /*see lab 9 + notes and lecture notes 11 pg18*/
    oldSsp = Super(0);
    set_ipl(oldIpl);
    Super(oldSsp);

    return ascii;
}

/***********************************************************************
 * Name: getAscii
 * 
 * Purpose: Converts a scan code to an ascii value
 * 
 * Inputs: scan code
 * 
 * Returns: ascii value
 ***********************************************************************/
UINT8 getAscii(SCANCODE scancode)
{
    UINT8 ascii;
    ascii = ASCII_TABLE[scancode]; /*pass in the "key number"*/
    return ascii;
}

/***********************************************************************
 * Name: getScanCode
 * 
 * Purpose: Reads the IKDB
 * 
 * Returns: scan code
 ***********************************************************************/
UINT8 getScanCode()
{
    if (*IKBD_SR & 0x01)
        return *IKBD_RDR;
}

/***********************************************************************
 * Name: keyPending
 * 
 * Purpose: Checks if there is a key in the buffer
 * 
 * Returns: true if there is a key in the buffer, false otherwise
 ***********************************************************************/
bool keyPending()
{
    return keyBufferQueue.fillLevel > 0 ? true : false;
}

UINT8 getPrev()
{
    UINT8 ascii;
    int oldIpl;
    long oldSsp;

    /*see lab 9 + notes*/
    oldSsp = Super(0);
    oldIpl = set_ipl(7);
    Super(oldSsp);

    ascii = keyBufferQueue.buffer[keyBufferQueue.head + 1];

    /*see lab 9 + notes*/
    oldSsp = Super(0);
    set_ipl(oldIpl);
    Super(oldSsp);

    return ascii;
}