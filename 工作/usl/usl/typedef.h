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
* File name:           $Workfile: typedef.h $
* Last revision:       $Revision: 8 $
* Last change:         $Date: 9.05.12 15:19 $   ($Author: Geit $)
*
* File description:    Standard data types useful in several CPU-types        
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

#ifndef TYPEDEF_H
#define TYPEDEF_H

/*----------------------------------------------------------------------------*/
/* Includes                                                                   */
/*----------------------------------------------------------------------------*/
#ifdef __vxworks__  
    /* VxWorks System */
    #include <vxworks.h>
    #include <sys/types.h>
    #include <limits.h>
#endif

#ifdef __BORLANDC__  
    /* Borland C++ Builder */
    #include <vcl.h>
#endif

#ifdef __VCC__
    /* Visual C++ */
    #include <windows.h>
#endif

#ifdef __EXPERT__
    /* C# + C++ DLL */
    #include <windows.h>
#endif

#include <time.h>
 
/*----------------------------------------------------------------------------*/
/* Global types                                                               */
/*----------------------------------------------------------------------------*/

/* Basic types */
/*-------------*/

#ifdef __vxworks__ 
    /* VxWorks System */
    #define DllExport extern

    #if CPU == PPC32
    #define INCLUDE_SG2008
    #endif

    #if CPU == PPC603
    #define INCLUDE_SG2005
    #define INCLUDE_SG2006
    #endif

    #if CPU == I80386
    #define INCLUDE_SGPC
    #define INCLUDE_SG1999
    #define INCLUDE_SG2000
    #endif


    typedef unsigned        char     uint8;
    typedef unsigned short  int      uint16;
    typedef unsigned long   int      uint32;
    typedef signed          char     int8;
    typedef signed   short  int      int16;
    typedef signed   long   int      int32;
    typedef float                    float4;
    typedef int                      Boolean;    /* The definition as "enum {False
                                                 True}" would implement two int-
                                                 values, whatever that means!     */

    #define UINT32_MAX      ULONG_MAX

    /* TASK_ID is defined by newer versions of VxWorks and is a pointer to a struct.
     * Define an own type. */
    typedef int TaskID;
    #define TASK_ID_NULL ((TaskID)ERROR)

    /* defines for file descriptors, open,read,write,close */
    typedef int FD_ID;                         
    #define FD_ID_NULL ((FD_ID)ERROR)
#endif


#ifdef __BORLANDC__
    /* Borland C++ Builder */
    typedef unsigned        char     uint8;
    typedef unsigned short  int      uint16;
    typedef unsigned long   int      uint32;
    typedef signed          char     int8;
    typedef signed   short  int      int16;
    typedef signed   long   int      int32;
    typedef float                    float4;
    typedef HANDLE                   TaskID;
    typedef TASK_ID TaskID;
#endif


#ifdef __VCC__ 
    /* Visual C++ */
    #define DllExport extern
    typedef TASK_ID TaskID;
    typedef int16                    Boolean;
    typedef HANDLE                   TaskID;
#endif


#ifdef __EXPERT__
    /* C# + C++ DLL */
    #define DllExport   __declspec( dllexport ) 
    typedef unsigned short  int      Boolean;
    typedef unsigned        char     uint8;
    typedef unsigned short  int      uint16;
    typedef unsigned long   int      uint32;
    typedef signed          char     int8;
    typedef signed   short  int      int16;
    typedef signed   long   int      int32;
    typedef float                    float4;
    typedef HANDLE                   TaskID;

    #ifndef TRUE
    #define TRUE 1
    #endif

    #ifndef FALSE
    #define FALSE 0
    #endif
        
    #define PLUTO_100
#endif


#if (defined(_OSK) || defined(_OS9000)) /* OS9/68k or OS9000/PowerPC System */
    #define DllExport extern
    typedef unsigned        char     uint8;
    typedef unsigned short  int      uint16;
    typedef unsigned long   int      uint32;
    typedef signed   short  int      int16;
    typedef float                    float4;
    typedef int16                    Boolean;    /* The definition as "enum {False
                                                 True}" would implement two int-
                                                 values, whatever that means!     */
#endif

typedef int8                     SByte;      /* Signed byte    for binary data*/
typedef unsigned        char     UByte;      /* Unsigned byte  for binary data*/

typedef char                     CString;    /* e.g. CString str[8]
                                             means that str is a printable
                                             string of up to 7 characters.    */


/* Derived types */
/*---------------*/
typedef int16                    Error_Type; /* Return value from functions, 
                                             also useful for status-variables.*/


/*----------------------------------------------------------------------------*/
/* Global constants                                                           */
/*----------------------------------------------------------------------------*/
#ifdef __vxworks__  
    #define ON          1
    #define OFF         0
    #define NO_PARAM    0  /* No Parameter */

    #define FILE_SEPARATOR '/'
#endif

#ifdef _OSK 
    /* OS9 / 68k System */
    #ifndef TRUE
    #define TRUE 1
    #endif

    #ifndef FALSE
    #define FALSE 0
    #endif

    #ifndef ERROR
    #define ERROR -1
    #endif
    
    #ifndef OK
    #define OK 0
    #endif

    #define ON          1
    #define OFF         0
    #define NO_PARAM    0  /* No Parameter */

    #define FILE_SEPARATOR '/'
#endif

#ifdef _OS9000 
    /* OS9000 / PPC System */
    #ifndef TRUE
    #define TRUE 1
    #endif

    #ifndef FALSE
    #define FALSE 0
    #endif

    #ifndef ERROR
    #define ERROR -1
    #endif
    
    #ifndef OK
    #define OK 0
    #endif

    #define ON          1
    #define OFF         0
    #define NO_PARAM    0  /* No Parameter */

    #define FILE_SEPARATOR '/'
#endif

#ifdef __BORLANDC__ 
    /* Borland C++ Builder */
    #ifndef ERROR
    #define ERROR -1
    #endif

    #ifndef OK
    #define OK 0
    #endif

    #define ON          1
    #define OFF         0
    #define NO_PARAM    0  /* No Parameter */

    #define FILE_SEPARATOR '\\'
#endif

#ifdef __VCC__ 
    /* Visual C++ */
    #define ON          1
    #define OFF         0
    #define NO_PARAM    0  /* No Parameter */

    #define FILE_SEPARATOR '\\'
#endif

#define NoError     0


#ifndef NIL
    #define NIL (void *) 0
#endif

/*----------------------------------------------------------------------------*/
/* Task priorities                                                            */
/*----------------------------------------------------------------------------*/
/* Priority schema: */
/*   System (OS) and drivers:  0..60 */

/*   Jamaica (Java) high prio: 71 */

/*   APP very critical parts as power fail signal */
#define T_PRIO_CRITICAL  10

/*   APP high prioritiy tasks as communication protocols with timeouts */
#define T_PRIO_HIGH      70

/*   APP normal tasks as servers */
#define T_PRIO_NORMAL    80

/*   APP low priority tasks as gui, printers ... */
#define T_PRIO_LOW       90

/*   Jamaica (Java) low prio: >= 100 */

/*----------------------------------------------------------------------------*/
/* Global macros                                                              */
/*----------------------------------------------------------------------------*/

/*
c-macros
=========
*/
#define size_1_typ unsigned char
#define size_2_typ unsigned short
#define size_4_typ unsigned long

#define HIGH_w(a)     ((size_2_typ) ((a) >> 16))
#define HIGH_b(a)     ((size_1_typ) ((a) >> 8 ))
#define HIGH(a)       (sizeof(a) == sizeof(size_2_typ) ? (HIGH_b(a)) : (HIGH_w(a)) )

#define LOW_w(a)      ((size_2_typ) ((a) & 0xFFFF))
#define LOW_b(a)      ((size_1_typ) ((a) & 0xFF  ))
#define LOW(a)        (sizeof(a) == sizeof(size_2_typ) ? (LOW_b(a)) : (LOW_w(a)) )

#define DOUBLE_w(a)   ((size_4_typ) (a))
#define DOUBLE_b(a)   ((size_2_typ) (a))
#define DOUBLE(a)     (sizeof(a) == sizeof(size_2_typ) ? (DOUBLE_w(a)) : (DOUBLE_b(a)) )

#define ROR_w(a,b)    ((a) >> (b) | (a) << 16-(b))
#define ROR_b(a,b)    ((a) >> (b) | (a) <<  8-(b))
#define ROR(a,b)      (sizeof(a) == sizeof(size_1_typ) ? (ROR_b(a,b)) : (ROR_w(a,b)) )

#define ROL_w(a,b)    ((a) << (b) | (a) >> 16-(b))
#define ROL_b(a,b)    ((a) << (b) | (a) >>  8-(b))
#define ROL(a,b)      (sizeof(a) == sizeof(size_1_typ) ? (ROL_b(a,b)) : (ROL_w(a,b)) )

#define SHL(a,b)      ((a) << (b))

#define SHR(a,b)      ((a) >> (b))

#define N_Elements(_array)  (sizeof(_array)/sizeof(_array[0]))

#endif /* TYPEDEF_H */
/**************************** End of code ************************************
*
* Modification history
* --------------------
* Rev   Date           Visum
*$Log: /CCU/UQC2_500/INC/typedef.h $
* 
* 8     9.05.12 15:19 Geit
* Removed _WRS_IOCHAR because we create errors with sysLib.h of VxWorks
* 6.6
* 
* 7     9.05.12 12:57 Geit
* Added limits.h for ULONG_MAX
* 
* 6     27.04.12 8:56 Geit
* Cleanup: Module number in file header removed. Changed Boolean to int.
* Fixed type incompatibilities by casting. Removed unused variables.
* Removed useless variable initializations. Removed redundant code.
* Removed not reached code. Removed conditions that are always
* true/false.
* 
* 5     5.04.12 16:26 Geit
* Added UINT32_MAX
* 
* 4     7.02.11 16:14 Gehs
* smart module also used in expert.
* 
* 3     10.12.09 10:47 Geit
* Task priorities are now not CCU dependent anymore.
* 
* 2     28.11.08 10:01 Geit
* New CCU Type: INCLUDE_SG2008 is set when compiled by the VxWorks 6.6 /
* Workbench
* Migration VxWorks 6.6: Changed TASK_ID --> TaskID
 * 
 * 1     5.02.08 13:36 Geit
 * Import from Quantum
* 
* 18    31.05.06 10:29 Geit
* Defined TRUE for _OSK and _OS9000
* 
* 17    19.12.05 11:49 Gehs
* CCU_2006 added
* 
* 16    5.10.05 16:49 Gehs
* temporary different task priorities for CCU2005
* 
* 15    19.09.05 11:29 Gehs
* 4 different task priorities
* 
* 14    17.06.05 11:13 Gehs
* FILE_SEPARATOR added
* 
* 13    27.04.05 18:12 Gehs
* platforms ppc added
* 
* 12    8.04.05 16:43 Gehs
* TASK_ID defined here
* 
* 11    6.04.05 15:23 Gehs
* switches for visual c and borland added
* 
* 10    16.04.03 14:02 Geit
* 
* 9     16.04.03 12:38 Geit
* Uster Technologies AG
* 
* 8     14.02.03 15:41 Geit
* Adapted for PowerPC.
* 
* 7     17.06.02 15:24 Geit
* Added N_Elements().
* 
* 6     3.06.02 10:22 Geit
* Rearranged modification history.
*
*          28-Sep-93   H.K.M  created                                         
*          30-Sep-93   H.K.M  uint-types added.                               
*          17-Dec-93   H.K.M  Conditional compilation of Boolean              
* 2.10     04.07.1997  GEHS   no_param -> NO_PARAM                            
***************************** End of file ************************************/
