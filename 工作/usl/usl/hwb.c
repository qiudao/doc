/*****************************************************************************
*             This program is an unpublished trade secret of the             *
*                                                                            *
*                      Uster Technologies AG, Switzerland,                   *
*                                                                            *
*      and all rights thereto are reserved. Use or copying of all or any     *
*      portion of this program is prohibited except with express written     *
*                 authorization from the Uster Technologies AG.              *
******************************************************************************
*                                                                            
* File name:           $Workfile: hwb.c $
* Last revision:       $Revision: 2 $
* Last change:         $Date: 27.04.12 8:56 $   ($Author: Geit $)
*
* File description:    Global definitions for a hardware buffer.
*                      You can select the byte order of the buffer
*
*----------------------------------------------------------------------------*
*
* Prog.-language:      ANSI-C
* Operating system:    VxWorks
*
******************************************************************************
* 
* List of functions:   
*                      u8Get
*                      u8Set
*                      u16Get
*                      u16Set
*                      u32Get
*                      u32Set
*                      rawGet
*                      rawSet
*
*                      hwb_init
*                      hwb_size
*
*                      hwb_u8Get
*                      hwb_u16Get
*                      hwb_u32Get
*                      hwb_u8Set
*                      hwb_u16Set
*                      hwb_u32Set
*
*                      hwb_uint8
*                      hwb_uint16
*                      hwb_uint32
*                      hwb_int8
*                      hwb_int16
*                      hwb_int32
*                      hwb_raw
*
******************************************************************************
* Modification history see end of file.
******************************************************************************
*/

/*-------------------------------------------------------------------------*/
/* Includes                                                                */
/*-------------------------------------------------------------------------*/
#include <string.h>

#include "hwb.h"
#include "log.h"

/*..........................................................................*/
/* Function:              u8Get
 * Created: 12.05.2005    Last change: 25.04.2012    Author: GEHS/GEIT
 *---------------------------------------------------------------------------
 * Description:  get byte from buffer
 * Return:       data byte
 */
static
uint8
u8Get(HwbBuf* hwb) {
    uint8 res;

    res = hwb->act[0];
    hwb->act += 1;
    return res;
}



/*..........................................................................*/
/* Function:              u16Get
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  get word from buffer
 * Return:       data word
 */
static
uint16
u16Get(HwbBuf* hwb) {
    uint16 res = 0;

    if (hwb->order == HWB_ORDER_INTEL) {
         res |= hwb->act[1]; res <<= 8;
         res |= hwb->act[0];            /* first byte in lo */
    }
    else
    if (hwb->order == HWB_ORDER_MOTOROLA) {
         res |= hwb->act[0]; res <<= 8; /* first byte in hi */
         res |= hwb->act[1];
    }
    hwb->act += 2;
    return res;
}


/*..........................................................................*/
/* Function:              u32Get
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  get double word from buffer
 * Return:       data double word
 */
static
uint32
u32Get(HwbBuf* hwb) {
    uint32 res = 0;

    if (hwb->order == HWB_ORDER_INTEL) {
         res |= hwb->act[3]; res <<= 8;
         res |= hwb->act[2]; res <<= 8;
         res |= hwb->act[1]; res <<= 8;
         res |= hwb->act[0];             /* first byte in lo */
    }
    else
    if (hwb->order == HWB_ORDER_MOTOROLA) {
         res |= hwb->act[0]; res <<= 8;  /* first byte in hi */
         res |= hwb->act[1]; res <<= 8;
         res |= hwb->act[2]; res <<= 8;
         res |= hwb->act[3];
    }
    hwb->act += 4;
    return res;
}


/*==========================================================================*/
/* Function:              rawGet
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  get raw data from buffer
 * Return:       
 */
void
rawGet(HwbBuf* hwb, char* from, int len) {
    memcpy( from, hwb->act, len);
    hwb->act += len;
}



/*..........................................................................*/
/* Function:              u8Set
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  add byte to buffer                        
 * Return:       
 */
static
void
u8Set(HwbBuf* hwb, uint8 val) {
    hwb->act[0] = val;
    hwb->act += 1;
}


/*..........................................................................*/
/* Function:              u16Set
 * Created: 12.05.2005    Last change: 26.04.2012    Author: GEHS/GEIT
 *---------------------------------------------------------------------------
 * Description:  add word to buffer
 * Return:       
 */
static
void
u16Set(HwbBuf* hwb, uint16 val) {

    if (hwb->order == HWB_ORDER_INTEL) {
        hwb->act[0] = (uint8)(val & 0xFF); val >>= 8; /* lo in first byte */
        hwb->act[1] = (uint8)(val & 0xFF);
    }
    else
    if (hwb->order == HWB_ORDER_MOTOROLA) {
        hwb->act[1] = (uint8)(val & 0xFF); val >>= 8; /* hi in first byte */
        hwb->act[0] = (uint8)(val & 0xFF);
    }
    hwb->act += 2;
}


/*..........................................................................*/
/* Function:              u32Set
 * Created: 12.05.2005    Last change: 26.04.2012    Author: GEHS/GEIT
 *---------------------------------------------------------------------------
 * Description:  add double word to buffer
 * Return:       
 */
static
void
u32Set(HwbBuf* hwb, uint32 val) {

    if (hwb->order == HWB_ORDER_INTEL) {
        hwb->act[0] = (uint8)(val & 0xFF); val >>= 8; /* lo in first byte */
        hwb->act[1] = (uint8)(val & 0xFF); val >>= 8;
        hwb->act[2] = (uint8)(val & 0xFF); val >>= 8;
        hwb->act[3] = (uint8)(val & 0xFF);
    }
    else
    if (hwb->order == HWB_ORDER_MOTOROLA) {
        hwb->act[3] = (uint8)(val & 0xFF); val >>= 8; /* hi in first byte */
        hwb->act[2] = (uint8)(val & 0xFF); val >>= 8;
        hwb->act[1] = (uint8)(val & 0xFF); val >>= 8;
        hwb->act[0] = (uint8)(val & 0xFF);
    }
    hwb->act += 4;
}


/*==========================================================================*/
/* Function:              rawSet
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  add raw data to buffer
 * Return:       
 */
void
rawSet(HwbBuf* hwb, char* from, int len) {
    memcpy( hwb->act, from, len);
    hwb->act += len;
}



/*..........................................................................*/
/* Function:              check
 * Created: 12.05.2005    Last change: 15.08.2017    Author: GEHS/GEIT
 *---------------------------------------------------------------------------
 * Description:  check that user doesn't overflow the given buffer
 * Return:       -
 */
static
Boolean
check(HwbBuf* hwb, int size) {
    char* fkt = "check";
    if (hwb->act + size > hwb->end) {
         log_error(fkt, "HWB exeeds size of buffer");
         return FALSE;
    }
    return TRUE;
}


/*==========================================================================*/
/* Function:              hwb_init
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  hwb is a buffer management structure,
 *               base is a given memory space of total length.
 *               order is the byte ordering of the data 
 *               which are put to the buffer or read from the buffer.        
 * Return:       -
 */
void
hwb_init(HwbBuf* hwb, uint8* base, int total, HwbOrder order, HwbDirection dir) {
    hwb->base  = base;
    hwb->end   = &base[total];
    hwb->act   = base;
    hwb->total = total;
    hwb->order = order;
    hwb->direction = dir;
}


/*==========================================================================*/
/* Function:              hwb_size
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  number of data actually in buffer.
 * Return:       -
 */
int
hwb_size(HwbBuf* hwb) {
    return (int) ( hwb->act - hwb->base );
}


/*==========================================================================*/
/* Function:              hwb_rewind
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  rewind read/write buffer
 * Return:       -
 */
void
hwb_rewind(HwbBuf* hwb) {
    hwb->act = hwb->base;
}


/*==========================================================================*/
/* Function:              hwb_empty
 * Created: 29.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  returns true if full buffer is used
 * Return:       -
 */
Boolean
hwb_empty(HwbBuf* hwb) {
    return hwb_size(hwb) == hwb->total;
}


/*==========================================================================*/
/* Function:              hwb_uint8
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  add/get byte to/from buffer                        
 * Return:       
 */
extern
Boolean
hwb_uint8(HwbBuf* hwb, uint8* val) {
    if (!check(hwb, 1))
        return FALSE;
    if (hwb->direction == HWB_ENCODE)
        u8Set(hwb, *val);
    else
        *val = u8Get(hwb);
    return TRUE;
}


/*==========================================================================*/
/* Function:              hwb_uint16
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  add/get word to/from buffer
 * Return:       
 */
extern
Boolean
hwb_uint16(HwbBuf* hwb, uint16* val) {
    if (!check(hwb, 2))
        return FALSE;
    if (hwb->direction == HWB_ENCODE)
        u16Set(hwb, *val);
    else
        *val = u16Get(hwb);
    return TRUE;
}


/*==========================================================================*/
/* Function:              hwb_uint32
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  add/get double word to/from buffer
 * Return:       
 */
extern
Boolean
hwb_uint32(HwbBuf* hwb, uint32* val) {
    if (!check(hwb, 4))
        return FALSE;
    if (hwb->direction == HWB_ENCODE)
        u32Set(hwb, *val);
    else
        *val = u32Get(hwb);
    return TRUE;
}


/*==========================================================================*/
/* Function:              hwb_int8
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  add/get byte to/from buffer                        
 * Return:       
 */
extern
Boolean
hwb_int8(HwbBuf* hwb, int8* val) {
    if (!check(hwb, 1))
        return FALSE;
    if (hwb->direction == HWB_ENCODE)
        u8Set(hwb, (uint8)*val);
    else
        *val = (int8)u8Get(hwb);
    return TRUE;
}


/*==========================================================================*/
/* Function:              hwb_int16
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  add/get word to/from buffer
 * Return:       
 */
extern
Boolean
hwb_int16(HwbBuf* hwb, int16* val) {
    if (!check(hwb, 2))
        return FALSE;
    if (hwb->direction == HWB_ENCODE)
        u16Set(hwb, (uint16)*val);
    else
        *val = (int16)u16Get(hwb);
    return TRUE;
}


/*==========================================================================*/
/* Function:              hwb_int32
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  add/get double word to/from buffer
 * Return:       
 */
extern
Boolean
hwb_int32(HwbBuf* hwb, int32* val) {
    if (!check(hwb, 4))
        return FALSE;
    if (hwb->direction == HWB_ENCODE)
        u32Set(hwb, (uint32)*val);
    else
        *val = (int32)u32Get(hwb);
    return TRUE;
}



/*==========================================================================*/
/* Function:              hwb_raw
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  add/get raw data to/from buffer
 * Return:       
 */
extern
Boolean
hwb_raw(HwbBuf* hwb, void* ptr, int len) {
    if (!check(hwb, len))
        return FALSE;
    if (hwb->direction == HWB_ENCODE)
        rawSet(hwb, ptr, len);
    else
        rawGet(hwb, ptr, len);
    return TRUE;
}



/**************************** End of code ************************************
*
* Modification history
* --------------------
* Rev   Date           Visum
*$Log: /CCU/UQC3_100/SRC/FNK/hwb.c $
* 
* 2     27.04.12 8:56 Geit
* Cleanup: Module number in file header removed. Changed Boolean to int.
* Fixed type incompatibilities by casting. Removed unused variables.
* Removed useless variable initializations. Removed redundant code.
* Removed not reached code. Removed conditions that are always
* true/false.
 * 
 * 1     6.02.08 14:43 Geit
 * Import from Quantum
* 
* 4     31.05.05 13:19 Gehs
* unused functions removed, new hwb_rewind and hwb_empty
* 
* 3     25.05.05 12:03 Gehs
* hwb adapted to hwbgen
* 
* 2     18.05.05 9:31 Gehs
* return 0 if hwb_u8Get fails
* 
* 1     13.05.05 15:15 Gehs
* hardware buffer byte ordering implemented
* 
***************************** End of file ************************************/
