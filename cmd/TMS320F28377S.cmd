/*
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 *  ======== TMS320F28377S.cmd ========
 *  Define the memory block start/length for the TMS320F28377S
 */
MEMORY
{
PAGE 0 :  /* Program Memory */
          /* BEGIN is used for the "boot to FLASH" bootloader mode   */

    D01SARAM   : origin = 0x00B000, length = 0x001000

	/* Local Shared Memory */
	LS03SARAM  : origin = 0x009800, length = 0x000800 /* on-chip RAM for CLA program */
	LS04SARAM  : origin = 0x00A000, length = 0x000800 /* on-chip RAM */


    /* Flash boot address */
    BEGIN   : origin = 0x080000, length = 0x000002

    /* Flash sectors */
    FLASHA  : origin = 0x080002, length = 0x001FFE  /* on-chip Flash */
    FLASHB  : origin = 0x082000, length = 0x002000  /* on-chip Flash */
    FLASHC  : origin = 0x084000, length = 0x002000  /* on-chip Flash, reserved for CLA*/
    FLASHD  : origin = 0x086000, length = 0x002000  /* on-chip Flash */
    FLASHE  : origin = 0x088000, length = 0x008000  /* on-chip Flash */
    FLASHF  : origin = 0x090000, length = 0x008000  /* on-chip Flash */
    FLASHG  : origin = 0x098000, length = 0x008000  /* on-chip Flash */
    FLASHH  : origin = 0x0A0000, length = 0x008000  /* on-chip Flash */
    FLASHI  : origin = 0x0A8000, length = 0x008000  /* on-chip Flash */
    FLASHJ  : origin = 0x0B0000, length = 0x008000  /* on-chip Flash */
    FLASHK  : origin = 0x0B8000, length = 0x002000  /* on-chip Flash */
    FLASHL  : origin = 0x0BA000, length = 0x002000  /* on-chip Flash */
    FLASHM  : origin = 0x0BC000, length = 0x002000  /* on-chip Flash */
    FLASHN  : origin = 0x0BE000, length = 0x002000  /* on-chip Flash */
    FLASHO  : origin = 0x0C0000, length = 0x002000	/* on-chip Flash */
    FLASHP  : origin = 0x0C2000, length = 0x002000	/* on-chip Flash */
    FLASHQ  : origin = 0x0C4000, length = 0x002000	/* on-chip Flash */
    FLASHR  : origin = 0x0C6000, length = 0x002000	/* on-chip Flash */
    FLASHS  : origin = 0x0C8000, length = 0x008000	/* on-chip Flash */
    FLASHT  : origin = 0x0D0000, length = 0x008000	/* on-chip Flash */
    FLASHU  : origin = 0x0D8000, length = 0x008000	/* on-chip Flash */
    FLASHV  : origin = 0x0E0000, length = 0x008000	/* on-chip Flash */
    FLASHW  : origin = 0x0E8000, length = 0x008000	/* on-chip Flash */
    FLASHX  : origin = 0x0F0000, length = 0x008000	/* on-chip Flash */
    FLASHY  : origin = 0x0F8000, length = 0x002000	/* on-chip Flash */
    FLASHZ  : origin = 0x0FA000, length = 0x002000	/* on-chip Flash */
    FLASHAA : origin = 0x0FC000, length = 0x002000	/* on-chip Flash */
    FLASHAB : origin = 0x0FE000, length = 0x002000	/* on-chip Flash */
    RESET   : origin = 0x3FFFC0, length = 0x000002

PAGE 1 : /* Data Memory */

    BOOT_RSVD : origin = 0x000002, length = 0x000120 /* Part of M0, BOOT rom
                                                        will use this for
                                                        stack */

    M01SARAM : origin = 0x000122, length = 0x0006DE  /* on-chip RAM */
	/* Local Shared Memory */

	LS00SARAM          	: origin = 0x008000, length = 0x000800 	/* on-chip RAM for CLA data */
   	LS01SARAM          	: origin = 0x008800, length = 0x000800	/* on-chip RAM for CLA data and scratchpad*/
   	LS02SARAM      		: origin = 0x009000, length = 0x000800	/* on-chip RAM */
   	LS05SARAM      		: origin = 0x00A800, length = 0x000800	/* on-chip RAM */

	/* Message Memory */

	CLA1_MSGRAMLOW			: origin = 0x001480, length = 0x000080
	CLA1_MSGRAMHIGH			: origin = 0x001500, length = 0x000080

    /* on-chip Global shared RAMs */
    RAMGS0  : origin = 0x00C000, length = 0x001000
    RAMGS1  : origin = 0x00D000, length = 0x001000
    RAMGS2  : origin = 0x00E000, length = 0x001000
    RAMGS3  : origin = 0x00F000, length = 0x001000
    RAMGS4  : origin = 0x010000, length = 0x001000
    RAMGS5  : origin = 0x011000, length = 0x001000
    RAMGS6  : origin = 0x012000, length = 0x001000
    RAMGS7  : origin = 0x013000, length = 0x001000
    RAMGS8  : origin = 0x014000, length = 0x001000
    RAMGS9  : origin = 0x015000, length = 0x001000
    RAMGS10 : origin = 0x016000, length = 0x001000
    RAMGS11 : origin = 0x017000, length = 0x001000
    RAMGS12 : origin = 0x018000, length = 0x001000
    RAMGS13 : origin = 0x019000, length = 0x001000
    RAMGS14 : origin = 0x01A000, length = 0x001000
    RAMGS15 : origin = 0x01B000, length = 0x001000
}


SECTIONS
{
    /* Allocate program areas: */
    .cinit              : > FLASHA | FLASHB | FLASHD | FLASHE |
                            FLASHF | FLASHG | FLASHH | FLASHI | FLASHJ |
                            FLASHK | FLASHL | FLASHM | FLASHN | FLASHO |
                            FLASHP | FLASHQ | FLASHR | FLASHS | FLASHT |
                            FLASHU | FLASHV | FLASHW | FLASHX | FLASHY |
                            FLASHZ | FLASHAA | FLASHAB PAGE = 0
    .binit              : > FLASHA | FLASHB | FLASHD | FLASHE |
                            FLASHF | FLASHG | FLASHH | FLASHI | FLASHJ |
                            FLASHK | FLASHL | FLASHM | FLASHN | FLASHO |
                            FLASHP | FLASHQ | FLASHR | FLASHS | FLASHT |
                            FLASHU | FLASHV | FLASHW | FLASHX | FLASHY |
                            FLASHZ | FLASHAA | FLASHAB PAGE = 0
    .pinit              : > FLASHA | FLASHB | FLASHD | FLASHE |
                            FLASHF | FLASHG | FLASHH | FLASHI | FLASHJ |
                            FLASHK | FLASHL | FLASHM | FLASHN | FLASHO |
                            FLASHP | FLASHQ | FLASHR | FLASHS | FLASHT |
                            FLASHU | FLASHV | FLASHW | FLASHX | FLASHY |
                            FLASHZ | FLASHAA | FLASHAB PAGE = 0
    .text               : > FLASHA | FLASHB | FLASHD | FLASHE |
                            FLASHF | FLASHG | FLASHH | FLASHI | FLASHJ |
                            FLASHK | FLASHL | FLASHM | FLASHN | FLASHO |
                            FLASHP | FLASHQ | FLASHR | FLASHS | FLASHT |
                            FLASHU | FLASHV | FLASHW | FLASHX | FLASHY |
                            FLASHZ | FLASHAA | FLASHAB PAGE = 0
    codestart           : > BEGIN   PAGE = 0
    ramfuncs            : LOAD = FLASHA | FLASHB | FLASHD | FLASHE |
                                 FLASHF | FLASHG | FLASHH | FLASHI | FLASHJ |
                                 FLASHK | FLASHL | FLASHM | FLASHN | FLASHO |
                                 FLASHP | FLASHQ | FLASHR | FLASHS | FLASHT |
                                 FLASHU | FLASHV | FLASHW | FLASHX | FLASHY |
                                 FLASHZ | FLASHAA | FLASHAB PAGE = 0
                          RUN  = LS05SARAM  PAGE = 1
                          LOAD_START(_RamfuncsLoadStart),
                          LOAD_SIZE(_RamfuncsLoadSize),
                          LOAD_END(_RamfuncsLoadEnd),
                          RUN_START(_RamfuncsRunStart),
                          RUN_SIZE(_RamfuncsRunSize),
                          RUN_END(_RamfuncsRunEnd)

#ifdef __TI_COMPILER_VERSION
#if __TI_COMPILER_VERSION >= 15009000
    .TI.ramfunc : {} LOAD = FLASHA | FLASHB | FLASHD | FLASHE |
                            FLASHF | FLASHG | FLASHH | FLASHI | FLASHJ |
                            FLASHK | FLASHL | FLASHM | FLASHN | FLASHO |
                            FLASHP | FLASHQ | FLASHR | FLASHS | FLASHT |
                            FLASHU | FLASHV | FLASHW | FLASHX | FLASHY |
                            FLASHZ | FLASHAA | FLASHAB PAGE = 0,
                     RUN  = LS05SARAM PAGE = 1,
                     table(BINIT)
#endif
#endif

	/* CLA specific sections */

   Cla1Prog         : LOAD = FLASHC,
                      RUN = LS03SARAM,
                      LOAD_START(_Cla1funcsLoadStart),
                      LOAD_END(_Cla1funcsLoadEnd),
                      RUN_START(_Cla1funcsRunStart),
                      LOAD_SIZE(_Cla1funcsLoadSize),
                      PAGE = 0, ALIGN(4)

	CLADataLS0		: > LS00SARAM, PAGE=1
	CLADataLS1		: > LS01SARAM, PAGE=1

	Cla1ToCpuMsgRAM  : > CLA1_MSGRAMLOW,   PAGE = 1
	CpuToCla1MsgRAM  : > CLA1_MSGRAMHIGH,  PAGE = 1

   	/* CLA C compiler sections */
   	//
   	// Must be allocated to memory the CLA has write access to
   	//
   	.scratchpad      : > LS01SARAM,       PAGE = 1
   	.bss_cla		 : > LS01SARAM,       PAGE = 1
   	.const_cla	    :  LOAD = FLASHC,
                       RUN = LS01SARAM,
                       RUN_START(_Cla1ConstRunStart),
                       LOAD_START(_Cla1ConstLoadStart),
                       LOAD_SIZE(_Cla1ConstLoadSize),
                       PAGE = 1

    /* Allocate uninitalized data sections: */
    .stack              : > M01SARAM | LS05SARAM | LS02SARAM    PAGE = 1
    .ebss               : >> M01SARAM | LS05SARAM | LS02SARAM | RAMGS0 | RAMGS1 PAGE = 1
    .esysmem            : > LS05SARAM | LS02SARAM | M01SARAM    PAGE = 1
    .cio                : > LS05SARAM | LS02SARAM | M01SARAM    PAGE = 1

    /* Initalized sections go in Flash */
    .econst             : > FLASHA | FLASHB | FLASHD | FLASHE |
                            FLASHF | FLASHG | FLASHH | FLASHI | FLASHJ |
                            FLASHK | FLASHL | FLASHM | FLASHN | FLASHO |
                            FLASHP | FLASHQ | FLASHR | FLASHS | FLASHT |
                            FLASHU | FLASHV | FLASHW | FLASHX | FLASHY |
                            FLASHZ | FLASHAA | FLASHAB PAGE = 0
    .switch             : > FLASHA | FLASHB | FLASHD | FLASHE |
                            FLASHF | FLASHG | FLASHH | FLASHI | FLASHJ |
                            FLASHK | FLASHL | FLASHM | FLASHN | FLASHO |
                            FLASHP | FLASHQ | FLASHR | FLASHS | FLASHT |
                            FLASHU | FLASHV | FLASHW | FLASHX | FLASHY |
                            FLASHZ | FLASHAA | FLASHAB PAGE = 0
    .args               : > FLASHA | FLASHB | FLASHD | FLASHE |
                            FLASHF | FLASHG | FLASHH | FLASHI | FLASHJ |
                            FLASHK | FLASHL | FLASHM | FLASHN | FLASHO |
                            FLASHP | FLASHQ | FLASHR | FLASHS | FLASHT |
                            FLASHU | FLASHV | FLASHW | FLASHX | FLASHY |
                            FLASHZ | FLASHAA | FLASHAB PAGE = 0
    .reset              : > RESET,     PAGE = 0, TYPE = DSECT /* not used, */
}
