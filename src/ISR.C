/********************************************************************
*   File:       ISR.C
*
*   Author(s):  Tobias W
*               Jayden M
*
*   Date:       2022-03-29     
********************************************************************/
#include "ISR.H"

/***********************************************************************
 * Name: installVector
 * 
 * Purpose: Installs a new interrupt vector
 * 
 * Details: This function installs a new interrupt vector.
 * 
 * Inputs: num - the interrupt vector number
 *         vector - the new interrupt vector
 * 
 * Returns: The original interrupt vector
 * 
 ***********************************************************************/
Vector installVector(int num, Vector vector)
{
    Vector orig;    
    Vector *vectp = (Vector *)((long)num << 2); /* convert to addr. */
    long old_ssp = Super(0); /* get supervisor mode */

    orig = *vectp; /* save original vector */
    *vectp = vector; /* install new vector */
    
    Super(old_ssp); /* restore previous mode */
    return orig;    
}