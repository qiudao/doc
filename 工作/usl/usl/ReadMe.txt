CCU-MS Interface
================

Files:

- typedef.h         Type definitions used in the CCU
- uslProto.h        Definitions of the protocol structures and constants.
- hwbgen.exe        Tool to generate byte order functions for each structure in uslProto.hwbgen
- uslHwb_make.bat   Calls the hwbgen.exe tool for uslProto.h. This is an example as it is used in the CCU development environment.
- uslHwb.h          Generated header file of hwbgen
- uslHwb.c          Generated implementation file fo hwbgen
- hwb.h             Definitions of hwb core functions
- hwb.c             Implementation of hwb core functions

Explanations:

HWB means Hardware Buffer and was implemented to achieve the right byte order for communication with other systems.
The core functions hwb.c do the job of bringing the byte order of the external system to the one of the host system.

Usage:

HwbBuf hwb;
uint8  buf[SIZE]

hwb_init(&hwb, buf, sizeof(buf), HWB_ORDER_MOTOROLA, HWB_ENCODE);  // Initialize the hwb for encoding (sending) in Motorola format (high byte first)
hwb_uintXX(&hwb, &dataXX);                                         // Convert dataXX of type uintXX
hwb_uintYY(&hwb, &dataYY);                                         // Convert next dataYY of type uintYY

...

hwb_size(&hwb);                                                    // Get size of hwb buffer
