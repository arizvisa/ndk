/*++ NDK Version: 0098

Copyright (c) Alex Ionescu.  All rights reserved.

Header Name:

    dbgkfuncs.h

Abstract:

    Function definitions for the User Mode Debugging Facility.

Author:

    Alex Ionescu (alexi@tinykrnl.org) - Updated - 27-Feb-2006

--*/

#ifndef _DBGKFUNCS_H
#define _DBGKFUNCS_H

//
// Dependencies
//
#include <ndk/umtypes.h>
#include <ndk/dbgktypes.h>
#include <ndk/ntstrsafe.h>

//
// Native calls
//
NTSYSCALLAPI
NTSTATUS
NTAPI
NtDebugActiveProcess(
    _In_ HANDLE Process,
    _In_ HANDLE DebugObject
);

NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateDebugObject(
    _Out_ PHANDLE DebugHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG Flags
);

NTSYSCALLAPI
NTSTATUS
NTAPI
NtDebugContinue(
    _In_ HANDLE DebugObject,
    _In_ PCLIENT_ID AppClientId,
    _In_ NTSTATUS ContinueStatus
);

NTSYSCALLAPI
NTSTATUS
NTAPI
NtWaitForDebugEvent(
    _In_ HANDLE DebugObject,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout,
    _Out_ PDBGUI_WAIT_STATE_CHANGE StateChange
);

NTSYSCALLAPI
NTSTATUS
NTAPI
NtRemoveProcessDebug(
    _In_ HANDLE Process,
    _In_ HANDLE DebugObject
);

NTSYSCALLAPI
NTSTATUS
NTAPI
NtSetInformationDebugObject(
    _In_ HANDLE DebugObject,
    _In_ DEBUGOBJECTINFOCLASS InformationClass,
    _In_ PVOID Information,
    _In_ ULONG InformationLength,
    _Out_opt_ PULONG ReturnLength
);

NTSYSAPI
NTSTATUS
NTAPI
ZwDebugActiveProcess(
    _In_ HANDLE Process,
    _In_ HANDLE DebugObject
);

NTSYSAPI
NTSTATUS
NTAPI
ZwCreateDebugObject(
    _Out_ PHANDLE DebugHandle,
    _In_ ACCESS_MASK DesiredAccess,
    _In_ POBJECT_ATTRIBUTES ObjectAttributes,
    _In_ ULONG Flags
);

NTSYSAPI
NTSTATUS
NTAPI
ZwDebugContinue(
    _In_ HANDLE DebugObject,
    _In_ PCLIENT_ID AppClientId,
    _In_ NTSTATUS ContinueStatus
);

NTSYSAPI
NTSTATUS
NTAPI
ZwRemoveProcessDebug(
    _In_ HANDLE Process,
    _In_ HANDLE DebugObject
);

NTSYSAPI
NTSTATUS
NTAPI
ZwWaitForDebugEvent(
    _In_ HANDLE DebugObject,
    _In_ BOOLEAN Alertable,
    _In_opt_ PLARGE_INTEGER Timeout,
    _Out_ PDBGUI_WAIT_STATE_CHANGE StateChange
);

NTSYSAPI
NTSTATUS
NTAPI
ZwSetInformationDebugObject(
    _In_ HANDLE DebugObject,
    _In_ DEBUGOBJECTINFOCLASS InformationClass,
    _In_ PVOID Information,
    _In_ ULONG InformationLength,
    _Out_opt_ PULONG ReturnLength
);

typedef struct _DBGOUT_STATIC_STORAGE {
	USHORT lineNum;
	USHORT currentWchar;
} DBGOUT_STATIC_STORAGE, *PDBGOUT_STATIC_STORAGE;

#if defined(NTOS_MODE_USER)
#if !defined(BOOTSCR_OUTPUT)
#define ALPHABET_LETTER_COUNT 26
static void myWPrintf(const WCHAR* pFormatString, ...){
	WCHAR szPrintBuf[512];
	WCHAR szValueName[4];
	va_list args; 

	///Get ourselves per-thread static storage for storing the current line number as well as the current
	///output key. As the field is highly undocumented it might not work in the future
	///if Microsoft decides to actually use the field for something other than a neither correctly working
	///nor useful ProcessInstrumentationCallback implementation.
	PDBGOUT_STATIC_STORAGE pStaticInfoStorage = (PDBGOUT_STATIC_STORAGE)NtCurrentTeb()->SpareBytes1;

	WCHAR szVPrintfErrorString[] = { L'R', L't', L'l', L'S', L't', L'r', L'i', L'n', L'g', L'V', L'P', L'r', L'i', L'n', L't', L'f', L'W', L'o', L'r', L'k', L'e', L'r', L'W', L' ', L'e', L'r', L'r', L'o', L'r', L'!', 0x0};
	WCHAR szParentOutputKey[] = { L'D', L'b', L'g', L'O', L'u', L't', 0x0 };
	WCHAR szOutputKeyPath[] = { L'D', L'b', L'g', L'O', L'u', L't', L'\\', L'O', L'u', L't', L'p', L'u', L't', L' ', L'A', 0x0 };

	NTSTATUS status = STATUS_UNSUCCESSFUL;

#if defined (BOOT_APP)
	ULONG relativeTo = RTL_REGISTRY_CONTROL;
#else
	ULONG relativeTo = RTL_REGISTRY_USER;
#endif

	if (!pFormatString || !pStaticInfoStorage)
		return;

	///DANGEROUS! Not invoking the API calls by function pointers will lead to non PIC code.
	///We must never forget about that if we want to write PIC code.
	status = RtlCreateRegistryKey(relativeTo, szParentOutputKey);

	if (!pStaticInfoStorage->lineNum){
		for (USHORT i = 0; i < ALPHABET_LETTER_COUNT; i++){
			szOutputKeyPath[sizeof(szOutputKeyPath) / sizeof(WCHAR) - 2] = L'A' + i;
			status = RtlCheckRegistryKey(relativeTo, szOutputKeyPath);
			if (STATUS_OBJECT_NAME_NOT_FOUND == status) {
				pStaticInfoStorage->currentWchar = L'A' + i;
				break;
			}
		}
	}
	else {
		szOutputKeyPath[sizeof(szOutputKeyPath) / sizeof(WCHAR) - 2] = pStaticInfoStorage->currentWchar;
	}

	(pStaticInfoStorage->lineNum)++;
	szValueName[2] = L'a' + (pStaticInfoStorage->lineNum) % ALPHABET_LETTER_COUNT;
	szValueName[1] = L'a' + (pStaticInfoStorage->lineNum) / ALPHABET_LETTER_COUNT;
	szValueName[0] = L'a' + (pStaticInfoStorage->lineNum) / (ALPHABET_LETTER_COUNT * ALPHABET_LETTER_COUNT);

	szValueName[sizeof(szValueName) / sizeof(WCHAR) - 1] = 0x0;
	RtlSecureZeroMemory(szPrintBuf, sizeof(szPrintBuf));

	va_start(args, pFormatString);
#pragma warning(push)
#pragma warning(disable:4995) ///name was marked as #pragma deprecated
	status = RtlStringVPrintfWorkerW(szPrintBuf, sizeof(szPrintBuf) / sizeof(WCHAR), NULL, pFormatString, args);
#pragma warning(pop)
	va_end(args);
	if (status){
		RtlWriteRegistryValue(relativeTo, szOutputKeyPath, szValueName, REG_SZ, szVPrintfErrorString, sizeof(szVPrintfErrorString));
		return;
	}

	RtlWriteRegistryValue(relativeTo, szOutputKeyPath, szValueName, REG_MULTI_SZ, szPrintBuf, sizeof(szPrintBuf));
}
#endif ///!BOOTSCR_OUTPUT


#endif ///UM
#endif ///DBGKFUNCS_H


