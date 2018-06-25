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
* File name:           $Workfile: hwb.h $
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
* Modification history see end of file.
******************************************************************************
*/

#ifndef HWB_H
#define HWB_H


/*----------------------------------------------------------------------------*/
/* Includes                                                                   */
/*----------------------------------------------------------------------------*/
#include <stdio.h>

#include "typedef.h"



/*==========================================================================*/
/* HwbOrder
   Two different order rules at the moment, Motorola and Intel.
   We could also make additional orders which also
   include alignment of data
*/
typedef enum {
    HWB_ORDER_INTEL,
    HWB_ORDER_MOTOROLA
} HwbOrder;


/*==========================================================================*/
/* HwbDirection
   Encode puts data into buffer.
   Decode takes data from buffer.
*/
typedef enum {
    HWB_ENCODE,
    HWB_DECODE
} HwbDirection;


/*==========================================================================*/
/* HwbBuf
   Hardware buffer structure contains: 
       base  = pointer to start of buffer
       end   = pointer to start of buffer + total
       act   = actual write and read position
       total = total size of buffer starting from base
       order = rule how to put data from and to buffer
*/
typedef struct {
    uint8* base;
    uint8* end;
    uint8* act;
    int total;
    HwbOrder order;
    HwbDirection direction;
} HwbBuf;


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
extern
void
hwb_init(HwbBuf* hwb, uint8* base, int total, HwbOrder order, HwbDirection dir);


/*==========================================================================*/
/* Function:              hwb_rewind
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  rewind buffer to zero position with same settings     
 * Return:       -
 */
extern
void
hwb_rewind(HwbBuf* hwb);


/*==========================================================================*/
/* Function:              hwb_size
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  number of data actually in buffer.
 * Return:       -
 */
extern
int
hwb_size(HwbBuf* hwb);


/*==========================================================================*/
/* Function:              hwb_empty
 * Created: 29.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  returns true if full buffer is used
 * Return:       -
 */
extern
Boolean
hwb_empty(HwbBuf* hwb);


/*==========================================================================*/
/* Function:              hwb_uint8
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  add byte to buffer                        
 * Return:       
 */
extern
Boolean
hwb_uint8(HwbBuf* hwb, uint8* val);


/*==========================================================================*/
/* Function:              hwb_uint16
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  add word to buffer
 * Return:       
 */
extern
Boolean
hwb_uint16(HwbBuf* hwb, uint16* val);


/*==========================================================================*/
/* Function:              hwb_uint32
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  add double word to buffer
 * Return:       
 */
extern
Boolean
hwb_uint32(HwbBuf* hwb, uint32* val);


/*==========================================================================*/
/* Function:              hwb_int8
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  add byte to buffer                        
 * Return:       
 */
extern
Boolean
hwb_int8(HwbBuf* hwb, int8* val);


/*==========================================================================*/
/* Function:              hwb_int16
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  add word to buffer
 * Return:       
 */
extern
Boolean
hwb_int16(HwbBuf* hwb, int16* val);


/*==========================================================================*/
/* Function:              hwb_int32
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  add double word to buffer
 * Return:       
 */
extern
Boolean
hwb_int32(HwbBuf* hwb, int32* val);


/*==========================================================================*/
/* Function:              hwb_raw
 * Created: 12.05.2005    Last change: --.--.----    Author: GEHS
 *---------------------------------------------------------------------------
 * Description:  add double word to buffer
 * Return:       
 */
extern
Boolean
hwb_raw(HwbBuf* hwb, void* ptr, int len);


#endif /* HWB_H */
