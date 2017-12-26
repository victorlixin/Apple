/***
*sect_attribs.h - section attributes for IA64 CRTs
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Revision History:
*       04-14-98  JWM   File created
*       04-28-99  PML   Wrap for IA64 only, define _CRTALLOC
*       08-10-99  RMS   Add .RTC initializer/terminator sections
*       11-06-01  GB    Add CRT$XPXA
*       02-13-04  PML   Add CRT$XD? for dynamic TLS support
*       03-16-04  PML   Add back CRT$XLZ
*       03-18-04  AC    Add CRT$XID for loosefpmath.obj
*       03-29-04  AL    Add #pragma section for CRTVT
*       02-11-05  AC    Remove redundant #pragma section
*                       VSW#445138
*
****/

/* TEMP (alecont): Remove this in the next lkg */
#if _MSC_FULL_VER >= 140050214 /*IFSTRIP=IGN*/

#define _ATTRIBUTES read

#else

#if defined(_M_IA64) || defined(_M_AMD64)
#define _ATTRIBUTES read
#else
#define _ATTRIBUTES read,write
#endif

#endif

#pragma section(".CRTMP$XCA",_ATTRIBUTES)
#pragma section(".CRTMP$XCZ",_ATTRIBUTES)
#pragma section(".CRTMP$XIA",_ATTRIBUTES)
#pragma section(".CRTMP$XIZ",_ATTRIBUTES)

#pragma section(".CRTMA$XCA",_ATTRIBUTES)
#pragma section(".CRTMA$XCZ",_ATTRIBUTES)
#pragma section(".CRTMA$XIA",_ATTRIBUTES)
#pragma section(".CRTMA$XIZ",_ATTRIBUTES)

#pragma section(".CRTVT$XCA",_ATTRIBUTES)
#pragma section(".CRTVT$XCZ",_ATTRIBUTES)

#pragma section(".CRT$XCA",_ATTRIBUTES)
#pragma section(".CRT$XCAA",_ATTRIBUTES)
#pragma section(".CRT$XCC",_ATTRIBUTES)
#pragma section(".CRT$XCZ",_ATTRIBUTES)
#pragma section(".CRT$XDA",_ATTRIBUTES)
#pragma section(".CRT$XDC",_ATTRIBUTES)
#pragma section(".CRT$XDZ",_ATTRIBUTES)
#pragma section(".CRT$XIA",_ATTRIBUTES)
#pragma section(".CRT$XIAA",_ATTRIBUTES)
#pragma section(".CRT$XIC",_ATTRIBUTES)
#pragma section(".CRT$XID",_ATTRIBUTES)
#pragma section(".CRT$XIY",_ATTRIBUTES)
#pragma section(".CRT$XIZ",_ATTRIBUTES)
#pragma section(".CRT$XLA",_ATTRIBUTES)
#pragma section(".CRT$XLC",_ATTRIBUTES)
#pragma section(".CRT$XLD",_ATTRIBUTES)
#pragma section(".CRT$XLZ",_ATTRIBUTES)
#pragma section(".CRT$XPA",_ATTRIBUTES)
#pragma section(".CRT$XPX",_ATTRIBUTES)
#pragma section(".CRT$XPXA",_ATTRIBUTES)
#pragma section(".CRT$XPZ",_ATTRIBUTES)
#pragma section(".CRT$XTA",_ATTRIBUTES)
#pragma section(".CRT$XTB",_ATTRIBUTES)
#pragma section(".CRT$XTX",_ATTRIBUTES)
#pragma section(".CRT$XTZ",_ATTRIBUTES)
#pragma section(".rdata$T",read)
#pragma section(".rtc$IAA",read)
#pragma section(".rtc$IZZ",read)
#pragma section(".rtc$TAA",read)
#pragma section(".rtc$TZZ",read)


#define _CRTALLOC(x) __declspec(allocate(x))
