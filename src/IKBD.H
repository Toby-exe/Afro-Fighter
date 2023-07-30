/************************************************************************
*   File:       IKBD.H
*
*   Author(s):  Tobias W
*               Jayden M
*
*   Date:       2022-03-29  
*   Purpose:    This module contains the IKBD interrupt service routine
*               and the keyboard buffer queue.
*
*   Details:    The IKBD interrupt service routine is responsible for
*               reading the keyboard buffer and storing the scan codes
*               in a queue.
*
*               The IKBD interrupt service routine is also responsible
*               for reading the mouse buffer and storing the mouse
*               coordinates in a queue.
***********************************************************************/
#ifndef IKBD_H
#define IKBD_H

#include "types.h"
#include "isr.h"
#include "vbl.h"
#include <osbind.h>

#define RDR_FULL ((UINT8)0x01)
#define IKBD_MOUSE_MOVE 0xF8 
#define IKBD_BUFFER_SIZE 256
#define TABLE_SIZE 0x73
#define BREAK_CODE 0x80
/*default pos of cusrsor is the center of the screen*/
#define MX_DEFAULT 0x320 
#define MY_DEFAULT 0x200
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

extern volatile UINT8 *const IKBD_CONTROL = 0xFFFC00; /*control register (write only)*/
extern volatile UINT8 *const IKBD_SR = 0xFFFC00;      /*status register (read only)*/
extern volatile SCANCODE *const IKBD_RDR = 0xFFFC02;  /*data register (read only)*/
extern bool keyRepeat;

extern const UINT8 ASCII_TABLE[TABLE_SIZE];


struct KeyQueue
{
    UINT8 buffer[256];
    UINT8 tail;
    UINT8 head;
    UINT16 fillLevel;
    int mX; /*mouse x*/
    int mY; /*mouse y*/
};

extern UINT8  ikbdSM;  
extern struct KeyQueue keyBufferQueue;

void do_ikbd_isr();
void keyBuffEnqueue(UINT8 );
UINT8 keyBuffDequeue();
UINT8 getScanCode();
bool keyPending();
UINT8 getAscii(SCANCODE scancode);
UINT8 getPrev();

#endif