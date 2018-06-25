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
* File name:           $Workfile: uslProto.h $
* Last revision:       $Revision: 1 $
* Last change:         $Date: 17.11.17 15:34 $   ($Author: Geit $)
*
* File description:    USTER QUANTUM 3 CCU to SENTINEL machine station (MS) interface.
*                      Here, the protocol structures are defined.
*
*-----------------------------------------------------------------------------
*
* Prog.-language:      ANSI-C
* Operating system:    VxWorks
*
******************************************************************************
* Modification history see end of file.
******************************************************************************
*/

#ifndef USL_PROTO_H
#define USL_PROTO_H

/*--------------------------------------------------------------------------*/
/* Includes                                                                 */
/*--------------------------------------------------------------------------*/
#include "typedef.h"


/*--------------------------------------------------------------------------*/
/* Constants and macros                                                     */
/*--------------------------------------------------------------------------*/
#define USL_INVALID              0xFFFF  /* Some data use this value to indicate invalid data */


/*--------------------------------------------------------------------------*/
/* Communication error codes                                                */
/*--------------------------------------------------------------------------*/
#define USL_ERR_OK               0x00    /* No error, command call was successful. */
                                         /* 0x01 is not defined. */
#define USL_ERR_DISCONNECTED     0x02    /* The CCU tries to call a function in disconnected state. */
#define USL_ERR_CRC              0x03    /* The MS has detected a CRC error in the command. */
#define USL_ERR_COMMAND          0x04    /* Invalid command. The MS has no command for the given protocol version. */
#define USL_ERR_BUSY             0x05    /* The MS is busy. Try again. */
#define USL_ERR_SPINDLE          0x10    /* The spindle number given in the command is out of range. */
#define USL_ERR_WRONG_ARG        0x11    /* An argument was wrong or out of range. */
#define USL_ERR_NOT_AVAIL        0x12    /* The requested data is not available because of data loss or not yet implemented feature. */
#define USL_ERR_GENERAL          0xFF    /* An unspecified error occurred in the MS. The CCU will retry the command if this happens. */


/*--------------------------------------------------------------------------*/
/* Command ID                                                               */
/*--------------------------------------------------------------------------*/
#define USL_CMD_CONNECT          0x01
#define USL_CMD_DISCONNECT       0x02
#define USL_CMD_LIFECHECK        0x03
#define USL_CMD_CONFIG_GET       0x04
#define USL_CMD_STATUS_GET       0x05
#define USL_CMD_COP_SHAPE_GET    0x10
#define USL_CMD_COP_QUALITY_GET  0x11
#define USL_CMD_END_BREAKS_GET   0x12
#define USL_CMD_ALARM_SET        0x80
#define USL_CMD_STATUS_RESTORE   0x81


/*--------------------------------------------------------------------------*/
/* Command header                                                           */
/*--------------------------------------------------------------------------*/
/* This header is used for command and response. The byte order is according to transport layer (big endian). */
typedef struct {
    uint8 startHigh;    /* Start sequence high byte (always 0xAA) */
    uint8 startLow;     /* Start sequence low byte (always 0x55) */
    uint8 command;      /* Command code */
    uint8 verOrErr;     /* For command: Protocol version; for response: Error code */
    uint8 lengthHigh;   /* Data length high byte */
    uint8 lengthLow;    /* Data length low byte */
} UslCmdHeader;


/*--------------------------------------------------------------------------*/
/* Spindle number to request range of spindle data                          */
/*--------------------------------------------------------------------------*/
/* This structure is used in:
 * USL_CMD_COP_SHAPE_GET, USL_CMD_COP_QUALITY_GET, USL_CMD_END_BREAKS_GET */
typedef struct {
    uint16 firstSp;     /* First spindle number of the requested range */
} UslSpNumber;


/*--------------------------------------------------------------------------*/
/* Spindle range in response                                                */
/*--------------------------------------------------------------------------*/
/* This structure is used in:
 * USL_CMD_COP_SHAPE_GET, USL_CMD_COP_QUALITY_GET, USL_CMD_END_BREAKS_GET */
typedef struct {
    uint16 firstSp;     /* First spindle number of the requested range */
    uint16 nSpindles;   /* Number of spindles in the range */
} UslSpRange;


/*----------------------------------------------------------------------------
 * Command: USL_CMD_CONNNECT           Protocol V0(all)             CCU --> MS
 *
 * Command  data: UslConnect
 * Response data: UslConnect
 *----------------------------------------------------------------------------
 */
typedef struct {
    uint8 maxVersion;   /* Highest supported protocol version */
} UslConnect;


/*----------------------------------------------------------------------------
 * Command: USL_CMD_DISCONNNECT        Protocol V0(all)             CCU --> MS
 *
 * Command  data: none
 * Response data: none
 *----------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------
 * Command: USL_CMD_LIFECHECK          Protocol V0(all)             CCU --> MS
 *
 * Command  data: none
 * Response data: none
 *----------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------
 * Command: USL_CMD_CONFIG_GET         Protocol V1                  CCU <-- MS
 *
 * Command  data: none
 * Response data: UslConfig_1
 *----------------------------------------------------------------------------
 */
/* String sizes (including null terminator) */
#define USL_MAX_MA_TYPE    20
#define USL_MAX_MA_ID      20
#define USL_MAX_SP_MAPPING 6

typedef struct {
    uint8  maType   [USL_MAX_MA_TYPE];     /* Machine type as string */
    uint8  maId     [USL_MAX_MA_ID];       /* Machine ID as string */
    uint16 nSpindles;                      /* Number of spindles of the spinning machine */
    uint8  spMapping[USL_MAX_SP_MAPPING];  /* Spindle number mapping */
} UslConfig_1;


/*----------------------------------------------------------------------------
 * Command: USL_CMD_STATUS_GET         Protocol V1                  CCU <-- MS
 *
 * Command  data: none
 * Response data: UslStatus_1
 *----------------------------------------------------------------------------
 */
/* Machine states */
#define USL_MA_STATE_UNKNOWN          0
#define USL_MA_STATE_STANDING         1
#define USL_MA_STATE_RUNNING          2
#define USL_MA_STATE_DOFFING          3

/* Spindle data available bits */
#define USL_BIT_AVAIL_COP_SHAPE       0
#define USL_BIT_AVAIL_SP_QUALITY      1

#define USL_MASK_AVAIL_COP_SHAPE      (1<<USL_BIT_AVAIL_COP_SHAPE)
#define USL_MASK_AVAIL_SP_QUALITY     (1<<USL_BIT_AVAIL_SP_QUALITY)

typedef struct {
    uint8  maStatus;           /* [0..3]      Machine status (uses USL_MA_STATE_...) */
    uint8  spDataAvail;        /* [bitfield]  Spindle data available flags (uses USL_BIT_AVAIL_...) */
    uint32 yarnCount;          /* [0.0001Nm]  Yarn count (invalid = 0) */
    uint16 timeToDoff;         /* [s]         Time to doff (invalid = USL_INVALID) */
    uint16 doffNumber;         /* [1..0xFFFF] Doff number (invalid = 0) */
    uint16 temperature;        /* [0.1C]      Temperature (invalid = 0) */
    uint16 humidity;           /* [0.1%rh]    Humidity (invalid = 0) */
} UslStatus_1;


/*----------------------------------------------------------------------------
 * Command: USL_CMD_COP_SHAPE_GET      Protocol V1                  CCU <-- MS
 *
 * Command  data: UslSpNumber
 * Response data: UslSpRange + uint8[nSpindles] (cop shape ID)
 *----------------------------------------------------------------------------
 */
/* Cop shape ID */
#define USL_COP_SHAPE_UNKNOWN         0
#define USL_COP_SHAPE_FULL            1
#define USL_COP_SHAPE_BOTTOM_FILLED   2
#define USL_COP_SHAPE_MIDDLE_FILLED   3
#define USL_COP_SHAPE_TOP_FILLED      4
#define USL_COP_SHAPE_COCA_COLA       5
#define USL_COP_SHAPE_EMPTY           6


/*----------------------------------------------------------------------------
 * Command: USL_CMD_COP_QUALITY_GET    Protocol V1                  CCU <-- MS
 *
 * Command data:  UslSpNumber
 * Response data: UslSpRange + uint8[nSpindles] (cop quality bits)
 *----------------------------------------------------------------------------
 */
/* Cop quality bits */
#define USL_BIT_COP_Q_OFF_QUALITY 0
#define USL_BIT_COP_Q_ROGUE_SP    1
#define USL_BIT_COP_Q_SLIP_SP     2

#define USL_MASK_COP_Q_OFF_QUALITY (1<<USL_BIT_COP_Q_OFF_QUALITY)
#define USL_MASK_COP_Q_ROGUE_SP    (1<<USL_BIT_COP_Q_ROGUE_SP)
#define USL_MASK_COP_Q_SLIP_SP     (1<<USL_BIT_COP_Q_SLIP_SP)


/*----------------------------------------------------------------------------
 * Command: USL_CMD_END_BREAKS_GET     Protocol V1                  CCU <-- MS
 *
 * Command data:  UslSpNumber
 * Response data: UslSpRange + uint8[nSpindles] (counters)
 *----------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------
 * Command: USL_CMD_ALARM_SET          Protocol V1                  CCU --> MS
 *
 * Command  data: UslAlarm_1
 * Response data: none
 *----------------------------------------------------------------------------
 */
/* Alarm codes */
#define USL_ALARM_NSA     "NSA"     /* Too many neps and short thick places */
#define USL_ALARM_LA      "LA"      /* Too many long faults */
#define USL_ALARM_TA      "TA"      /* Too many thin places */
#define USL_ALARM_CA      "CA"      /* Too many yarn count deviations at startup */
#define USL_ALARM_CCA     "CCA"     /* Too many yarn count deviations during winding */
#define USL_ALARM_PFA     "PFA"     /* Too many periodic faults */
#define USL_ALARM_OCA     "OCA"     /* Too many off center core faults */
#define USL_ALARM_MCA     "MCA"     /* Too many missing core faults */
#define USL_ALARM_SVA     "SVA"     /* Too many shade variation faults at startup */
#define USL_ALARM_CSVA    "CSVA"    /* Too many shade variation faults during winding */
#define USL_ALARM_CVA     "CVA"     /* Too high CV compared with group average */
#define USL_ALARM_HA      "HA"      /* Too high hairiness compared with group average */
#define USL_ALARM_YA1     "YA1"     /* Too many N,S,L,T,C,CC faults */

#define USL_MAX_ALARM_CODE  10 /* Maximum length of the alarm code string (including null terminator) */

typedef struct {
    uint16 spNumber;
    uint8  alarmCode[USL_MAX_ALARM_CODE];
} UslAlarm_1;


/*----------------------------------------------------------------------------
 * Command: USL_CMD_STATUS_RESTORE     Protocol V1                  CCU --> MS
 *
 * Command  data: UslStatusRestore_1
 * Response data: none
 *---------------------------------------------------------------------------
 */
typedef struct {
    uint16 timeToDoff;  /* [s]         Time to doff (always a valid time is set) */
    uint16 doffNumber;  /* [1..0xFFFF] Doff number (always a valid doff number is set) */
} UslStatusRestore_1;



/*--------------------------------------------------------------------------*/
/* Union of all structures                                                  */
/*--------------------------------------------------------------------------*/
typedef union {
    UslCmdHeader       header;
    UslSpNumber        spNumber;
    UslSpRange         spRange;
    UslConnect         connect;
    UslConfig_1        config_1;
    UslStatus_1        status_1;
    UslAlarm_1         alarm_1;
    UslStatusRestore_1 statusRestore_1;
} UslAllDataUnion;



#endif /* USL_PROTO_H */
/**************************** End of code ************************************
*
* Modification history
* --------------------
* Rev   Date           Visum
*$Log: /CCU/UQC3_100/SRC/USL/uslProto.h $
* 
* 1     17.11.17 15:34 Geit
* created
*
***************************** End of file ************************************/
