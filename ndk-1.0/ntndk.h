/*++ NDK Version: 0098

Copyright (c) Alex Ionescu.  All rights reserved.

Header Name:

    ntndk.h

Abstract:

    Master include file for the Native Development Kit.

Author:

    Alex Ionescu (alexi@tinykrnl.org) - Updated - 27-Feb-2006

--*/

#ifndef _NTNDK_
#define _NTNDK_

//
// Disable some warnings that we'd get on /W4.
// Only active for compilers which support this feature.
//
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4001)
#pragma warning(disable:4201)
#pragma warning(disable:4115)
#pragma warning(disable:4214)
#endif

//
// Headers needed for NDK
//
#include <stdio.h>          // C Standard Header
#include <excpt.h>          // C Standard Header
#include <stdarg.h>         // C Standard Header
#include <ndk-1.0/umtypes.h>        // General Definitions

//
// Type Headers
//
#include <ndk-1.0/cctypes.h>        // Cache Manager Types
#include <ndk-1.0/cmtypes.h>        // Configuration Manager Types
#include <ndk-1.0/dbgktypes.h>      // User-Mode Kernel Debugging Types
#include <ndk-1.0/extypes.h>        // Executive Types
#include <ndk-1.0/kdtypes.h>        // Kernel Debugger Types
#include <ndk-1.0/ketypes.h>        // Kernel Types
#include <ndk-1.0/haltypes.h>       // Hardware Abstraction Layer Types
#include <ndk-1.0/ifssupp.h>        // IFS Support Header
#include <ndk-1.0/iotypes.h>        // Input/Output Manager Types
#include <ndk-1.0/ldrtypes.h>       // Loader Types
#include <ndk-1.0/lpctypes.h>       // Local Procedure Call Types
#include <ndk-1.0/mmtypes.h>        // Memory Manager Types
#include <ndk-1.0/obtypes.h>        // Object Manager Types
#include <ndk-1.0/potypes.h>        // Power Manager Types
#include <ndk-1.0/pstypes.h>        // Process Manager Types
#include <ndk-1.0/rtltypes.h>       // Runtime Library Types
#include <ndk-1.0/setypes.h>        // Security Subsystem Types

//
// Function Headers
//
#include <ndk-1.0/cmfuncs.h>        // Configuration Manager Functions
#include <ndk-1.0/dbgkfuncs.h>      // User-Mode Kernel Debugging Functions
#include <ndk-1.0/kdfuncs.h>        // Kernel Debugger Functions
#include <ndk-1.0/kefuncs.h>        // Kernel Functions
#include <ndk-1.0/exfuncs.h>        // Executive Functions
#include <ndk-1.0/halfuncs.h>       // Hardware Abstraction Layer Functions
#include <ndk-1.0/iofuncs.h>        // Input/Output Manager Functions
#include <ndk-1.0/inbvfuncs.h>      // Initialization Boot Video Functions
#include <ndk-1.0/ldrfuncs.h>       // Loader Functions
#include <ndk-1.0/lpcfuncs.h>       // Local Procedure Call Functions
#include <ndk-1.0/mmfuncs.h>        // Memory Manager Functions
#include <ndk-1.0/obfuncs.h>        // Object Manager Functions
#include <ndk-1.0/pofuncs.h>        // Power Manager Functions
#include <ndk-1.0/psfuncs.h>        // Process Manager Functions
#include <ndk-1.0/rtlfuncs.h>       // Runtime Library Functions
#include <ndk-1.0/sefuncs.h>        // Security Subsystem Functions
#include <ndk-1.0/umfuncs.h>        // User-Mode NT Library Functions

//
// Assembly Support
//
#include <ndk-1.0/asm.h>            // Assembly Offsets

#ifdef _MSC_VER
#pragma warning(pop)
#endif
#endif // _NTNDK_
