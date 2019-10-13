/*++ NDK Version: 0098

Copyright (c) Alex Ionescu.  All rights reserved.

Header Name:

    umfuncs.h

Abstract:

    Function definitions for Native DLL (ntdll) APIs exclusive to User Mode.

Author:

    Alex Ionescu (alexi@tinykrnl.org) - Updated - 27-Feb-2006
    Ali Rizvi-Santiago (arizvisa@gmail.com) - Updated - 11-Oct-2019

--*/
#ifdef NTOS_MODE_USER
#ifndef _UMFUNCS_H
#define _UMFUNCS_H

//
// Dependencies
//
#include <ndk/umtypes.h>
#include <ndk/dbgktypes.h>

struct _CSR_API_MESSAGE;
struct _CSR_CAPTURE_BUFFER;

//
// CSR Functions
//
PVOID
NTAPI
CsrAllocateCaptureBuffer(
ULONG ArgumentCount,
ULONG BufferSize
);

ULONG
NTAPI
CsrAllocateMessagePointer(
struct _CSR_CAPTURE_BUFFER *CaptureBuffer,
	ULONG MessageLength,
	PVOID *CaptureData
	);

VOID
NTAPI
CsrCaptureMessageBuffer(
struct _CSR_CAPTURE_BUFFER *CaptureBuffer,
	PVOID MessageString,
	ULONG StringLength,
	PVOID *CapturedData
	);

NTSTATUS
NTAPI
CsrClientConnectToServer(
PWSTR ObjectDirectory,
ULONG ServerId,
PVOID ConnectionInfo,
PULONG ConnectionInfoSize,
PBOOLEAN ServerToServerCall
);

NTSTATUS
NTAPI
CsrClientCallServer(
struct _CSR_API_MESSAGE *Request,
struct _CSR_CAPTURE_BUFFER *CaptureBuffer OPTIONAL,
	ULONG ApiNumber,
	ULONG RequestLength
	);

NTSTATUS
NTAPI
CsrIdentifyAlertableThread(
VOID
);

VOID
NTAPI
CsrFreeCaptureBuffer(
struct _CSR_CAPTURE_BUFFER *CaptureBuffer
	);

HANDLE
NTAPI
CsrGetProcessId(
VOID
);

NTSTATUS
NTAPI
CsrNewThread(VOID);

NTSTATUS
NTAPI
CsrSetPriorityClass(
HANDLE Process,
PULONG PriorityClass
);

VOID
NTAPI
CsrProbeForRead(
IN PVOID Address,
IN ULONG Length,
IN ULONG Alignment
);

VOID
NTAPI
CsrProbeForWrite(
IN PVOID Address,
IN ULONG Length,
IN ULONG Alignment
);


//
// Debug Functions
//
__analysis_noreturn
NTSYSAPI
VOID
NTAPI
DbgBreakPointWithStatus(
    _In_ ULONG Status
);

NTSTATUS
NTAPI
DbgUiConnectToDbg(
    VOID
);

NTSTATUS
NTAPI
DbgUiContinue(
    _In_ PCLIENT_ID ClientId,
    _In_ NTSTATUS ContinueStatus
);

NTSTATUS
NTAPI
DbgUiDebugActiveProcess(
    _In_ HANDLE Process
);

NTSTATUS
NTAPI
DbgUiStopDebugging(
    _In_ HANDLE Process
);

NTSYSAPI
NTSTATUS
NTAPI
DbgUiWaitStateChange(
    _In_ PDBGUI_WAIT_STATE_CHANGE DbgUiWaitStateCange,
    _In_ PLARGE_INTEGER TimeOut
);

NTSTATUS
NTAPI
DbgUiConvertStateChangeStructure(
    _In_ PDBGUI_WAIT_STATE_CHANGE WaitStateChange,
    _In_ PVOID DebugEvent
);

VOID
NTAPI
DbgUiRemoteBreakin(
    VOID
);

NTSTATUS
NTAPI
DbgUiIssueRemoteBreakin(
    _In_ HANDLE Process
);

HANDLE
NTAPI
DbgUiGetThreadDebugObject(
    VOID
);

//
// Loader Functions
//

NTSTATUS
NTAPI
LdrAddRefDll(
    _In_ ULONG Flags,
    _In_ PVOID BaseAddress
);

NTSTATUS
NTAPI
LdrDisableThreadCalloutsForDll(
    _In_ PVOID BaseAddress
);

NTSTATUS
NTAPI
LdrGetDllHandle(
    _In_opt_ PWSTR DllPath,
    _In_ PULONG DllCharacteristics,
    _In_ PUNICODE_STRING DllName,
    _Out_ PVOID *DllHandle
);

NTSTATUS
NTAPI
LdrGetDllHandleEx(
    _In_ ULONG Flags,
    _In_opt_ PWSTR DllPath,
    _In_opt_ PULONG DllCharacteristics,
    _In_ PUNICODE_STRING DllName,
    _Out_opt_ PVOID *DllHandle);

NTSTATUS
NTAPI
LdrFindEntryForAddress(
    _In_ PVOID Address,
    _Out_ PLDR_DATA_TABLE_ENTRY *Module
);

NTSTATUS
NTAPI
LdrGetProcedureAddress(
    _In_ PVOID BaseAddress,
    _In_ PANSI_STRING Name,
    _In_ ULONG Ordinal,
    _Out_ FARPROC* ProcedureAddress
);

VOID
NTAPI
LdrInitializeThunk(
    ULONG Unknown1,
    ULONG Unknown2,
    ULONG Unknown3,
    ULONG Unknown4
);

NTSTATUS
NTAPI
LdrLoadDll(
    _In_opt_ PWSTR SearchPath,
    _In_opt_ PULONG LoadFlags,
    _In_ PUNICODE_STRING Name,
    _Out_opt_ PVOID *BaseAddress
);

PIMAGE_BASE_RELOCATION
NTAPI
LdrProcessRelocationBlock(
    _In_ ULONG_PTR Address,
    _In_ ULONG Count,
    _In_ PUSHORT TypeOffset,
    _In_ LONG_PTR Delta
);

NTSTATUS
NTAPI
LdrQueryImageFileExecutionOptions(
    _In_ PUNICODE_STRING SubKey,
    _In_ PCWSTR ValueName,
    _In_ ULONG ValueSize,
    _Out_ PVOID Buffer,
    _In_ ULONG BufferSize,
    _Out_opt_ PULONG RetunedLength
);

NTSTATUS
NTAPI
LdrQueryProcessModuleInformation(
    _In_opt_ PRTL_PROCESS_MODULES ModuleInformation,
    _In_opt_ ULONG Size,
    _Out_ PULONG ReturnedSize
);

VOID
NTAPI
LdrSetDllManifestProber(
    _In_ PLDR_MANIFEST_PROBER_ROUTINE Routine);

NTSTATUS
NTAPI
LdrShutdownProcess(
    VOID
);

NTSTATUS
NTAPI
LdrShutdownThread(
    VOID
);

NTSTATUS
NTAPI
LdrUnloadDll(
    _In_ PVOID BaseAddress
);

typedef VOID (NTAPI *PLDR_CALLBACK)(PVOID CallbackContext, PCHAR Name);
NTSTATUS
NTAPI
LdrVerifyImageMatchesChecksum(
    _In_ HANDLE FileHandle,
    _In_ PLDR_CALLBACK Callback,
    _In_ PVOID CallbackContext,
    _Out_ PUSHORT ImageCharacterstics
);

NTSTATUS
NTAPI
LdrOpenImageFileOptionsKey(
    _In_ PUNICODE_STRING SubKey,
    _In_ BOOLEAN Wow64,
    _Out_ PHANDLE NewKeyHandle
);

NTSTATUS
NTAPI
LdrQueryImageFileKeyOption(
    _In_ HANDLE KeyHandle,
    _In_ PCWSTR ValueName,
    _In_ ULONG Type,
    _Out_ PVOID Buffer,
    _In_ ULONG BufferSize,
    _Out_opt_ PULONG ReturnedLength
);


//This is Google's cache of http://www.howzatt.demon.co.uk/NtTrace/NtTrace.cfg. It is a snapshot of the page as it appeared on 2 Apr 2015 20:42:42 GMT. The current page could have changed in the meantime. Learn more
//Tip: To quickly find your search term on this page, press Ctrl + F or ? - F(Mac) and use the find bar.
//
//
//	 Text - only version
//
//
//
//	 // NTDLL Native Interface entry points
//
//	 // @author Roger Orr <rogero@howzatt.demon.co.uk>
//
//	 // Copyright &copy; 2002,2012.
//	 // This software is distributed in the hope that it will be useful, but
//	 // without WITHOUT ANY WARRANTY; without even the implied warranty of
//	 // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
//	 // Permission is granted to anyone to make or distribute verbatim
//	 // copies of this software provided that the copyright notice and
//	 // this permission notice are preserved, and that the distributor
//	 // grants the recipient permission for further distribution as permitted
//	 // by this notice.
//
//	 // Comments and suggestions are always welcome.
//	 // Please report bugs to rogero@howzatt.demon.co.uk.
//
//	 // $Id: NtTrace.cfg 1405 2013-11-12 23:57:17Z Roger $
//
//	 typedef USHORT RTL_ATOM;
//
//typedef ULONG_PTR KAFFINITY;
//
//typedef PULONG PNTSTATUS;
//typedef PULONG PACCESS_MASK;
//typedef PULONG PDEVICE_POWER_STATE;
//
//typedef PUSHORT PRTL_ATOM;
//

typedef struct _ALPC_CONTEXT_ATTRIBUTES
{
    PVOID PortContext;
    PVOID MessageContext;
    ULONG SequenceNumber;
    ULONG MessageID;
    ULONG CallbackID;
} ALPC_CONTEXT_ATTRIBUTES, *PALPC_CONTEXT_ATTRIBUTES;

#define ALPC_DATA_VIEW_FLAG_NONE        0x00000000
#define ALPC_DATA_VIEW_FLAG_RELEASEVIEW 0x00010000  // Use in a reply to release the view
#define ALPC_DATA_VIEW_FLAG_AUTORELEASE 0x00020000  // Automatically release the view once it's passed to the receiver
#define ALPC_DATA_VIEW_FLAG_SECURE      0x00040000  // Make the data view secure

typedef struct _ALPC_DATA_VIEW
{
    ULONG Flags;
    HANDLE SectionHandle;
    PVOID ViewBase;
    SIZE_T ViewSize;
} ALPC_DATA_VIEW, *PALPC_DATA_VIEW;

#define ALPC_MESSAGE_ATTRIBUTES_NONE                0x00000000
#define ALPC_MESSAGE_ATTRIBUTES_WORK_ON_BEHALF_OF   0x02000000
#define ALPC_MESSAGE_ATTRIBUTES_DIRECT              0x04000000
#define ALPC_MESSAGE_ATTRIBUTES_TOKEN               0x08000000
#define ALPC_MESSAGE_ATTRIBUTES_HANDLE              0x10000000
#define ALPC_MESSAGE_ATTRIBUTES_CONTEXT             0x20000000
#define ALPC_MESSAGE_ATTRIBUTES_VIEW                0x40000000
#define ALPC_MESSAGE_ATTRIBUTES_SECURITY            0x80000000
#define ALPC_MESSAGE_ATTRIBUTES_ALL                 (ALPC_MESSAGE_ATTRIBUTES_WORK_ON_BEHALF_OF|ALPC_MESSAGE_ATTRIBUTES_DIRECT|ALPC_MESSAGE_ATTRIBUTES_TOKEN|ALPC_MESSAGE_ATTRIBUTES_HANDLE|ALPC_MESSAGE_ATTRIBUTES_CONTEXT|ALPC_MESSAGE_ATTRIBUTES_VIEW|ALPC_MESSAGE_ATTRIBUTES_SECURITY)

typedef struct _ALPC_MESSAGE_ATTRIBUTES
{
    ULONG AllocatedAttributes;
    ULONG ValidAttributes;
} ALPC_MESSAGE_ATTRIBUTES, *PALPC_MESSAGE_ATTRIBUTES;

#define ALPC_PORT_ATTRIBUTE_FLAG_NONE                   0x00000000
#define ALPC_PORT_ATTRIBUTE_FLAG_LPC_PORT               0x00001000  // Not accessible outside the kernel.
#define ALPC_PORT_ATTRIBUTE_FLAG_ALLOW_IMPERSONATION    0x00010000
#define ALPC_PORT_ATTRIBUTE_FLAG_ALLOW_LPC_REQUESTS     0x00020000
#define ALPC_PORT_ATTRIBUTE_FLAG_WAITABLE_PORT          0x00040000
#define ALPC_PORT_ATTRIBUTE_FLAG_ALLOW_DUP_OBJECT       0x00080000
#define ALPC_PORT_ATTRIBUTE_FLAG_SYSTEM_PROCESS         0x00100000  // Not accessible outside the kernel.
#define ALPC_PORT_ATTRIBUTE_FLAG_LRPC_WAKEPOLICY1       0x00200000
#define ALPC_PORT_ATTRIBUTE_FLAG_LRPC_WAKEPOLICY2       0x00400000
#define ALPC_PORT_ATTRIBUTE_FLAG_LRPC_WAKEPOLICY3       0x00800000
#define ALPC_PORT_ATTRIBUTE_FLAG_DIRECT_MESSAGE         0x01000000

/// If set then object duplication won't complete. Used by RPC to ensure
/// multi-handle attributes don't fail when receiving.
#define ALPC_PORT_ATTRIBUTE_FLAG_ALLOW_MULTIHANDLE_ATTRIBUTE       0x02000000

typedef struct _ALPC_PORT_ATTRIBUTES
{
    ULONG Flags;
    SECURITY_QUALITY_OF_SERVICE SecurityQos;
    SIZE_T MaxMessageLength;
    SIZE_T MemoryBandwidth;
    SIZE_T MaxPoolUsage;
    SIZE_T MaxSectionSize;
    SIZE_T MaxViewSize;
    SIZE_T MaxTotalSectionSize;
    ULONG DupObjectTypes;
#ifdef _WIN64
    ULONG Reserved;
#endif
} ALPC_PORT_ATTRIBUTES, *PALPC_PORT_ATTRIBUTES;

#define ALPC_HANDLE_ATTRIBUTES_FLAG_NONE            0x00000000
#define ALPC_HANDLE_ATTRIBUTES_FLAG_SAME_ACCESS     0x00010000
#define ALPC_HANDLE_ATTRIBUTES_FLAG_SAME_ATTRIBUTES 0x00020000
#define ALPC_HANDLE_ATTRIBUTES_FLAG_INDIRECT        0x00040000
#define ALPC_HANDLE_ATTRIBUTES_FLAG_INHERIT         0x00080000

#define ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_NONE         0x00000000
#define ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_FILE         0x00000001
#define ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_INVALID0002  0x00000002
#define ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_THREAD       0x00000004
#define ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_SEMAPHORE    0x00000008
#define ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_EVENT        0x00000010
#define ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_PROCESS      0x00000020
#define ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_MUTEX        0x00000040
#define ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_SECTION      0x00000080
#define ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_REGKEY       0x00000100
#define ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_TOKEN        0x00000200
#define ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_COMPOSITION  0x00000400
#define ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_JOB          0x00000800

#define ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_ALL_OBJECTS  (ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_FILE|ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_THREAD|ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_SEMAPHORE|ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_EVENT|ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_PROCESS|ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_MUTEX|ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_SECTION|ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_REGKEY|ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_TOKEN|ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_COMPOSITION|ALPC_HANDLE_ATTRIBUTES_OBJECT_TYPE_JOB)

typedef struct _ALPC_HANDLE_ATTRIBUTES
{
    ULONG Flags;
    HANDLE Handle;
    ULONG ObjectType;
    ACCESS_MASK DesiredAccess;
} ALPC_HANDLE_ATTRIBUTES, *PALPC_HANDLE_ATTRIBUTES;

#define ALPC_SECURITY_ATTRIBUTES_FLAG_NONE              0x00000000
#define ALPC_SECURITY_ATTRIBUTES_FLAG_RELEASE_HANDLE    0x00010000
#define ALPC_SECURITY_ATTRIBUTES_FLAG_CREATE_HANDLE     0x00020000

typedef struct _ALPC_SECURITY_ATTRIBUTES
{
    ULONG Flags;
    PSECURITY_QUALITY_OF_SERVICE SecurityQos;
    HANDLE ContextHandle;
    ULONG Reserved1;
    ULONG Reserved2;
} ALPC_SECURITY_ATTRIBUTES, *PALPC_SECURITY_ATTRIBUTES;

//typedef PVOID PBOOT_ENTRY;
//typedef PVOID PCONTEXT;
//typedef PVOID PDRIVER_ENTRY;
//typedef PVOID PEXCEPTION_RECORD;
//typedef PVOID PGENERIC_MAPPING;
//typedef PVOID PGROUP_AFFINITY;
typedef PVOID PGUID;
//typedef PVOID PLUID;
//typedef PVOID PIO_APC_ROUTINE;
//typedef PVOID PPLUGPLAY_EVENT_BLOCK;
//typedef PVOID PPORT_VIEW;
//typedef PVOID PPROCESSOR_NUMBER;
//typedef PVOID PREMOTE_PORT_VIEW;
//typedef PVOID PRTL_USER_PROCESS_PARAMETERS;
//typedef PVOID POBJECT_TYPE_LIST;
//typedef PVOID PPRIVILEGE_SET;
typedef PVOID PSID;
//typedef PVOID PSECURITY_ATTRIBUTES;
typedef PVOID PSECURITY_DESCRIPTOR;
//typedef PVOID PTIMER_APC_ROUTINE;
//typedef PVOID PKTMOBJECT_CURSOR;
//typedef PVOID PTOKEN_DEFAULT_DACL;
//typedef PVOID PTOKEN_GROUPS;
//typedef PVOID PTOKEN_OWNER;
//typedef PVOID PTOKEN_PRIMARY_GROUP;
//typedef PVOID PTOKEN_PRIVILEGES;
//typedef PVOID PTOKEN_SOURCE;
//typedef PVOID PTOKEN_USER;
//typedef PVOID PTRANSACTION_NOTIFICATION;

#define LPC_TYPE_FLAG_NONE                  0x00000000
#define LPC_TYPE_FLAG_UNKNOWN_1000          0x00001000
#define LPC_TYPE_FLAG_CONTINUATION_REQUIRED 0x00002000
#define LPC_TYPE_FLAG_UNKNOWN_4000          0x00004000

typedef struct _LPC_MESSAGE {
	USHORT                  DataLength;
	USHORT                  Length;
	USHORT                  MessageType;
	USHORT                  DataInfoOffset;
	CLIENT_ID               ClientId;
	ULONG                   MessageId;
	ULONG                   CallbackId;
} LPC_MESSAGE, *PLPC_MESSAGE;

typedef struct _CHANNEL_MESSAGE {
    ULONG unknown;
} CHANNEL_MESSAGE, *PCHANNEL_MESSAGE;

//
//// Alternate name for LPC_MESSAGE
//typedef PLPC_MESSAGE PPORT_MESSAGE;


//[Atom]
//NTSTATUS
//NTAPI
//NtAddAtom(
//IN PWSTR AtomName,
//IN ULONG AtomNameLength,
//OUT PRTL_ATOM Atom
//);

//[Atom]
//NTSTATUS
//NTAPI
//NtDeleteAtom(
//IN RTL_ATOM Atom
//);

//[Atom]
//NTSTATUS
//NTAPI
//NtFindAtom(
//IN PWSTR AtomName,
//IN ULONG AtomNameLength,
//OUT PRTL_ATOM Atom OPTIONAL
//);

//[Atom]
//NTSTATUS
//NTAPI
//NtQueryInformationAtom(
//IN RTL_ATOM Atom,
//IN ATOM_INFORMATION_CLASS AtomInformationClass,
//OUT PVOID AtomInformation,
//IN ULONG Length,
//OUT PULONG ReturnLength OPTIONAL
//);

//[Debug]
//NTSTATUS
//NTAPI
//NtCreateProfile(
//OUT PHANDLE ProfileHandle,
//IN HANDLE Process,
//IN PVOID ProfileBase,
//IN ULONG ProfileSize,
//IN ULONG BucketSize,
//IN PULONG Buffer,
//IN ULONG BufferSize,
//IN KPROFILE_SOURCE ProfileSource,
//IN KAFFINITY Affinity
//);

//[Debug]
NTSTATUS
NTAPI
NtCreateProfileEx(
__out PHANDLE ProfileHandle,
__in_opt HANDLE Process,
__in PVOID ProfileBase,
__in ULONG ProfileSize,
__in ULONG BucketSize,
__in PULONG Buffer,
__in ULONG BufferSize,
__in ULONG ProfileSource,
__in ULONG GroupAffinityCount,
__in_opt PGROUP_AFFINITY GroupAffinity
);

//[Debug]
//NTSTATUS
//NTAPI
//NtDebugActiveProcess(
//IN HANDLE Process,
//IN HANDLE DebugHandle
//);

//[Debug]
//NTSTATUS
//NTAPI
//NtDebugContinue(
//IN HANDLE DebugHandle,
//IN PCLIENT_ID ClientId,
//IN NTSTATUS Status
//);

//[Debug]
//NTSTATUS
//NTAPI
//NtQueryDebugFilterState(
//IN ULONG Component,
//IN ULONG Level
//);

//[Debug]
//NTSTATUS
//NTAPI
//NtQueryIntervalProfile(
//IN KPROFILE_SOURCE Source,
//OUT PULONG Interval
//);

//[Debug]
//NTSTATUS
//NTAPI
//NtQueryPerformanceCounter(
//OUT PLARGE_INTEGER Counter,
//OUT PLARGE_INTEGER Freq OPTIONAL
//);

//[Debug]
//NTSTATUS
//NTAPI
//NtRegisterThreadTerminatePort(
//IN HANDLE PortHandle
//);

//[Debug]
//NTSTATUS
//NTAPI
//NtRemoveProcessDebug(
//IN HANDLE ProcessHandle,
//IN HANDLE DebugHandle
//);

//[Debug]
//NTSTATUS
//NTAPI
//NtSetDebugFilterState(
//IN ULONG Component,
//IN ULONG Level,
//IN BOOLEAN State
//);

//[Debug]
//NTSTATUS
//NTAPI
//NtSetInformationDebugObject(
//IN HANDLE DebugHandle,
//IN DEBUGOBJECTINFOCLASS Class,
//IN PVOID Buffer,
//IN ULONG Length,
//OUT PULONG ReturnLength OPTIONAL
//);

//[Debug]
//NTSTATUS
//NTAPI
//NtSetIntervalProfile(
//IN ULONG Interval,
//IN KPROFILE_SOURCE Source
//);

//[Debug]
//NTSTATUS
//NTAPI
//NtStartProfile(
//IN HANDLE ProfileHandle
//);

//[Debug]
//NTSTATUS
//NTAPI
//NtStopProfile(
//IN HANDLE ProfileHandle
//);

typedef enum _DEBUG_CONTROL_CODE {
	DebugGetTraceInformation = 1,
	DebugSetInternalBreakpoint,
	DebugSetSpecialCall,
	DebugClearSpecialCalls,
	DebugQuerySpecialCalls,
	DebugDbgBreakPoint,
	DebugMaximum,
	DebugSysReadPhysicalMemory = 10,
	DebugSysReadIoSpace = 14,
	DebugSysWriteIoSpace = 15
} DEBUG_CONTROL_CODE;
//[Debug]
//NTSTATUS
//NTAPI
//NtSystemDebugControl(
//IN DEBUG_CONTROL_CODE Command,
//IN PVOID InputBuffer,
//IN ULONG InputBufferLength,
//OUT PVOID OutputBuffer,
//IN ULONG OutputBufferLength,
//OUT PULONG ReturnLength
//);

//[Debug]
//NTSTATUS
//NTAPI
//NtWaitForDebugEvent(
//IN HANDLE DebugHandle,
//IN BOOLEAN Alertable,
//IN PLARGE_INTEGER Timeout OPTIONAL,
//OUT PULONG Result
//);

//[Device]
//NTSTATUS
//NTAPI
//NtAddBootEntry(
//IN PUNICODE_STRING Name,
//IN PUNICODE_STRING Value
//);

//[Device]
//NTSTATUS
//NTAPI
//NtAddDriverEntry(
//IN PUNICODE_STRING Name,
//IN PUNICODE_STRING Path
//);

//[Device]
//NTSTATUS
//NTAPI
//NtCancelDeviceWakeupRequest(
//IN HANDLE DeviceHandle
//);

//[Device]
//NTSTATUS
//NTAPI
//NtDeleteBootEntry(
//IN PUNICODE_STRING Name
//);

//[Device]
//NTSTATUS
//NTAPI
//NtDeleteDriverEntry(
//IN PUNICODE_STRING Name
//);

//[Device]
NTSTATUS
NTAPI
NtDisableLastKnownGood(
);

//[Device]
NTSTATUS
NTAPI
NtEnableLastKnownGood(
);

//[Device]
//NTSTATUS
//NTAPI
//NtEnumerateBootEntries(
//IN PVOID Buffer,
//IN PULONG BufferLength
//);

//[Device]
//NTSTATUS
//NTAPI
//NtEnumerateDriverEntries(
//IN PVOID Buffer,
//IN PULONG BufferLength
//);

//[Device]
//NTSTATUS
//NTAPI
//NtGetDevicePowerState(
//IN HANDLE DeviceHandle,
//OUT PDEVICE_POWER_STATE State
//);

//[Device]
//NTSTATUS
//NTAPI
//NtGetPlugPlayEvent(
//__in HANDLE EventHandle,
//__in_opt PVOID Context,
//__out PPLUGPLAY_EVENT_BLOCK EventBlock,
//__in ULONG EventBufferSize
//);

//[Device]
//NTSTATUS
//NTAPI
//NtInitiatePowerAction(
//IN POWER_ACTION Action,
//IN SYSTEM_POWER_STATE State,
//IN ULONG Flags,
//IN BOOLEAN Asynch
//);

//[Device]
//NTSTATUS
//NTAPI
//NtLoadDriver(
//IN PUNICODE_STRING DriverName
//);

//[Device]
//NTSTATUS
//NTAPI
//NtModifyBootEntry(
//IN PBOOT_ENTRY BootEntry
//);

//[Device]
//typedef struct _DRIVER_ENTRY{
//	20 	// Original Driver Object 
//		21 	PDRIVER_OBJECT			DriverObject;
//	22 	// Original Dispatch Functions 
//		23 	PDRIVER_DISPATCH		DriverDispatch[IRP_MJ_MAXIMUM_FUNCTION + 1];
//	24 	struct _DRIVER_ENTRY *  Next;
//	25 } DRIVER_ENTRY, *PDRIVER_ENTRY;


//NTSTATUS
//NTAPI
//NtModifyDriverEntry(
//IN PEFI_DRIVER_ENTRY DriverEntry
//);

//[Device]
//NTSTATUS
//NTAPI
//NtPlugPlayControl(
//IN ULONG Class,
//IN OUT PVOID Buffer,
//IN ULONG BufferSize
//);

//[Device]
//NTSTATUS
//NTAPI
//NtPowerInformation(
//IN POWER_INFORMATION_LEVEL InformationLevel,
//IN PVOID InputBuffer OPTIONAL,
//IN ULONG InputLength,
//OUT PVOID OutputBuffer,
//IN ULONG OutputLength
//);

//[Device]
//NTSTATUS
//NTAPI
//NtQueryBootEntryOrder(
//IN PULONG OrderArray OPTIONAL,
//IN OUT PULONG OrderCount
//);

//[Device]
//NTSTATUS
//NTAPI
//NtQueryBootOptions(
//OUT PVOID Buffer OPTIONAL,
//IN OUT PULONG BufferLength
//);

//[Device]
NTSTATUS
NTAPI
NtQueryDriverEntryOrder(
OUT PULONG OrderArray OPTIONAL,
IN OUT PULONG OrderCount
);

//[Device]
NTSTATUS
NTAPI
NtReplacePartitionUnit(
__in PUNICODE_STRING TargetInstancePath,
__in PUNICODE_STRING SpareInstancePath,
__in ULONG Flags
);

//[Device]
//NTSTATUS
//NTAPI
//NtRequestDeviceWakeup(
//IN HANDLE DeviceHandle
//);

//[Device]
//NTSTATUS
//NTAPI
//NtRequestWakeupLatency(
//IN ULONG LatencyTime
//);

//[Device]
NTSTATUS
NTAPI
NtSerializeBoot(
);

//[Device]
//NTSTATUS
//NTAPI
//NtSetBootEntryOrder(
//IN PULONG OrderArray,
//IN ULONG OrderCount
//);

//[Device]
//NTSTATUS
//NTAPI
//NtSetBootOptions(
//IN PVOID Buffer,
//IN ULONG BufferLength
//);

//[Device]
//NTSTATUS
//NTAPI
//NtSetDriverEntryOrder(
//IN PULONG OrderArray,
//IN ULONG OrderCount
//);

//[Device]
//NTSTATUS
//NTAPI
//NtSetSystemPowerState(
//IN POWER_ACTION Action,
//IN SYSTEM_POWER_STATE State,
//IN ULONG Flags
//);

//[Device]
//NTSTATUS
//NTAPI
//NtSetThreadExecutionState(
//IN ULONG State,
//OUT PULONG PreviousState
//);

//[Device]
//NTSTATUS
//NTAPI
//NtUnloadDriver(
//IN PUNICODE_STRING DriverName
//);

//[Device]
//NTSTATUS
//NTAPI
//NtVdmControl(
//IN ULONG ControlCode,
//IN PVOID ControlData
//);

//[Environment]
//NTSTATUS
//NTAPI
//NtEnumerateSystemEnvironmentValuesEx(
//IN ULONG Class,
//OUT PVOID Buffer,
//IN ULONG BufferLength
//);

//[Environment]
//NTSTATUS
//NTAPI
//NtGetCurrentProcessorNumber(
//);

//[Environment]
//NTSTATUS
//NTAPI
//NtIsSystemResumeAutomatic(
//);

//[Environment]
//NTSTATUS
//NTAPI
//NtQueryDefaultLocale(
//IN BOOLEAN UserProfile,
//OUT PLCID DefaultLocaleId
//);

//[Environment]
//NTSTATUS
//NTAPI
//NtQueryDefaultUILanguage(
//OUT PULONG LanguageId
//);

//[Environment]
//NTSTATUS
//NTAPI
//NtQueryInstallUILanguage(
//OUT PULONG LanguageId
//);

//[Environment]
//NTSTATUS
//NTAPI
//NtQuerySystemEnvironmentValue(
//IN PUNICODE_STRING Name,
//OUT PWSTR Value,
//IN ULONG Length,
//OUT PULONG ReturnLength OPTIONAL
//);

//[Environment]
//NTSTATUS
//NTAPI
//NtQuerySystemEnvironmentValueEx(
//IN PUNICODE_STRING VariableName,
//IN PVOID Guid,
//OUT PVOID Buffer,
//IN OUT PULONG BufferLength,
//IN OUT PULONG Attributes
//);

//[Environment]
//NTSTATUS
//NTAPI
//NtSetDefaultLocale(
//IN BOOLEAN UserProfile,
//IN LCID LocaleId
//);

//[Environment]
//NTSTATUS
//NTAPI
//NtSetDefaultUILanguage(
//IN ULONG LanguageId
//);

//[Environment]
//NTSTATUS
//NTAPI
//NtSetSystemEnvironmentValue(
//IN PUNICODE_STRING Name,
//IN PUNICODE_STRING Value
//);

//[Environment]
//NTSTATUS
//NTAPI
//NtSetSystemEnvironmentValueEx(
//IN PUNICODE_STRING Name,
//IN PVOID Guid,
//IN PVOID Buffer,
//IN ULONG BufferLength,
//IN ULONG Attributes
//);

//[File]
//NTSTATUS
//NTAPI
//NtAreMappedFilesTheSame(
//IN PVOID Address1,
//IN PVOID Address2
//);

//[File]
//NTSTATUS
//NTAPI
//NtCancelIoFile(
//IN HANDLE FileHandle,
//OUT PIO_STATUS_BLOCK IoStatusBlock
//);

//[File]
NTSTATUS
NTAPI
NtCancelIoFileEx(
IN HANDLE hFile,
IN PIO_STATUS_BLOCK IoStatusBlockIn,
OUT PIO_STATUS_BLOCK IoStatusBlock
);

//[File]
NTSTATUS
NTAPI
NtCancelSynchronousIoFile(
IN HANDLE ThreadHandle,
IN PIO_STATUS_BLOCK IoStatusBlockIn OPTIONAL,
OUT PIO_STATUS_BLOCK IoStatusBlock
);

//[File]
//NTSTATUS
//NTAPI
//NtClose(
//IN HANDLE Handle
//);

//[File]
//NTSTATUS
//NTAPI
//NtCreateFile(
//OUT PHANDLE FileHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes,
//OUT PIO_STATUS_BLOCK IoStatusBlock,
//IN PLARGE_INTEGER AllocationSize OPTIONAL,
//IN ULONG FileAttributes,
//IN ULONG ShareAccess,
//IN ULONG CreateDisposition,
//IN ULONG CreateOptions,
//IN PVOID EaBuffer OPTIONAL,
//IN ULONG EaLength
//);

//[File]
//NTSTATUS
//NTAPI
//NtCreateIoCompletion(
//OUT PHANDLE IoHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes,
//IN ULONG NumberOfConcurrentThreads
//);

//[File]
//NTSTATUS
//NTAPI
//NtCreateMailslotFile(
//OUT PHANDLE Handle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes,
//OUT PIO_STATUS_BLOCK IoStatusBlock,
//IN ULONG CreateOptions,
//IN ULONG InBufferSize,
//IN ULONG MaxMessageSize,
//IN PLARGE_INTEGER ReadTimeout OPTIONAL
//);

//[File]
//NTSTATUS
//NTAPI
//NtCreateNamedPipeFile(
//OUT PHANDLE NamedPipeHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes,
//OUT PIO_STATUS_BLOCK IoStatusBlock,
//IN ULONG ShareAccess,
//IN ULONG CreateDisposition,
//IN ULONG CreateOptions,
//IN BOOLEAN MessageType,
//IN BOOLEAN MessageRead,
//IN BOOLEAN NonBlocking,
//IN ULONG MaxInstances,
//IN ULONG InBufferSize,
//IN ULONG OutBufferSize,
//IN PLARGE_INTEGER Timeout OPTIONAL
//);

//[File]
//NTSTATUS
//NTAPI
//NtCreatePagingFile(
//IN PUNICODE_STRING PageFileName,
//IN PLARGE_INTEGER MinSize,
//IN PLARGE_INTEGER MaxSize,
//OUT PLARGE_INTEGER ActualSize OPTIONAL
//);

//[File]
//NTSTATUS
//NTAPI
//NtDeleteFile(
//IN POBJECT_ATTRIBUTES ObjectAttributes
//);

//[File]
//NTSTATUS
//NTAPI
//NtDeviceIoControlFile(
//IN HANDLE FileHandle,
//IN HANDLE Event,
//IN PIO_APC_ROUTINE ApcRoutine OPTIONAL,
//IN PVOID ApcContext OPTIONAL,
//OUT PIO_STATUS_BLOCK IoStatusBlock,
//IN ULONG IoControlCode,
//IN PVOID InputBuffer,
//IN ULONG InputBufferLength,
//OUT PVOID OutputBuffer,
//IN ULONG OutputBufferLength
//);

//[File]
//NTSTATUS
//NTAPI
//NtFlushBuffersFile(
//IN HANDLE FileHandle,
//OUT PIO_STATUS_BLOCK IoStatusBlock
//);

//[File]
//NTSTATUS
//NTAPI
//NtFsControlFile(
//IN HANDLE FileHandle,
//IN HANDLE Event,
//IN PIO_APC_ROUTINE UserApcRoutine OPTIONAL,
//IN PVOID UserApcContext OPTIONAL,
//OUT PIO_STATUS_BLOCK UserIoStatus,
//IN ULONG FsControlCode,
//IN PVOID InputBuffer OPTIONAL,
//IN ULONG InputBufferLength OPTIONAL,
//OUT PVOID OutputBuffer OPTIONAL,
//IN ULONG OutputBufferLength OPTIONAL
//);

//[File]
//NTSTATUS
//NTAPI
//NtLockFile(
//IN HANDLE FileHandle,
//IN HANDLE Event,
//IN PIO_APC_ROUTINE ApcRoutine OPTIONAL,
//IN PVOID ApcContext OPTIONAL,
//OUT PIO_STATUS_BLOCK IoStatusBlock,
//IN PLARGE_INTEGER Offset,
//IN PLARGE_INTEGER Length,
//IN ULONG Key,
//IN BOOLEAN FailImmediately,
//IN BOOLEAN ExclusiveLock
//);

//[File]
//NTSTATUS
//NTAPI
//NtNotifyChangeDirectoryFile(
//IN HANDLE DirectoryHandle,
//IN HANDLE EventHandle,
//IN PIO_APC_ROUTINE ApcRoutine OPTIONAL,
//IN PVOID ApcContext OPTIONAL,
//OUT PIO_STATUS_BLOCK IoStatusBlock,
//OUT PVOID Buffer,
//IN ULONG BufferLength,
//IN ULONG CompletionFilter,
//IN BOOLEAN Recursive
//);

//[File]
//NTSTATUS
//NTAPI
//NtOpenFile(
//OUT PHANDLE FileHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes,
//OUT PIO_STATUS_BLOCK IoStatusBlock,
//IN ULONG ShareAccess,
//IN ULONG OpenOptions
//);

//[File]
//NTSTATUS
//NTAPI
//NtOpenIoCompletion(
//OUT PHANDLE Handle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes
//);

//[File]
//NTSTATUS
//NTAPI
//NtQueryAttributesFile(
//IN POBJECT_ATTRIBUTES ObjectAttributes,
//OUT PFILE_BASIC_INFORMATION Attributes
//);

//[File]
//NTSTATUS
//NTAPI
//NtQueryDirectoryFile(
//IN HANDLE FileHandle,
//IN HANDLE Event OPTIONAL,
//IN PIO_APC_ROUTINE ApcRoutine OPTIONAL,
//IN PVOID ApcContext OPTIONAL,
//OUT PIO_STATUS_BLOCK IoStatusBlock,
//OUT PVOID FileInformation,
//IN ULONG Length,
//IN FILE_INFORMATION_CLASS FileInformationClass,
//IN BOOLEAN ReturnSingleEntry,
//IN PUNICODE_STRING FileName OPTIONAL,
//IN BOOLEAN RestartScan
//);

//[File]
//NTSTATUS
//NTAPI
//NtQueryEaFile(
//IN HANDLE FileHandle,
//OUT PIO_STATUS_BLOCK IoStatusBlock,
//OUT PVOID Buffer,
//IN ULONG Length,
//IN BOOLEAN SingleEntry,
//IN PVOID Eas OPTIONAL,
//IN ULONG EasLength,
//IN PULONG Index OPTIONAL,
//IN BOOLEAN Restart
//);

//[File]
//NTSTATUS
//NTAPI
//NtQueryFullAttributesFile(
//IN POBJECT_ATTRIBUTES ObjectAttributes,
//OUT PFILE_NETWORK_OPEN_INFORMATION Attributes
//);

//[File]
//NTSTATUS
//NTAPI
//NtQueryInformationFile(
//IN HANDLE FileHandle,
//OUT PIO_STATUS_BLOCK IoStatusBlock,
//OUT PVOID FileInformation,
//IN ULONG Length,
//IN FILE_INFORMATION_CLASS FileInformationClass
//);

//[File]
//NTSTATUS
//NTAPI
//NtQueryIoCompletion(
//IN HANDLE IoHandle,
//IN ULONG Class,
//OUT PVOID IoInformation,
//IN ULONG Length,
//OUT PULONG ReturnLength OPTIONAL
//);

//[File]
NTSTATUS
NTAPI
NtQueryOleDirectoryFile(
);

//[File]
//NTSTATUS
//NTAPI
//NtQueryQuotaInformationFile(
//__in      HANDLE FileHandle,
//__out     PIO_STATUS_BLOCK IoStatusBlock,
//__out     PVOID Buffer,
//__in      ULONG Length,
//__in      BOOLEAN ReturnSingleEntry,
//__in_opt  PVOID SidList,
//__in      ULONG SidListLength,
//__in_opt  PSID StartSid,
//__in      BOOLEAN RestartScan
//);

//[File]
//NTSTATUS
//NTAPI
//NtQueryVolumeInformationFile(
//IN HANDLE FileHandle,
//OUT PIO_STATUS_BLOCK IoStatusBlock,
//OUT PVOID FsInformation,
//IN ULONG Length,
//IN FS_INFORMATION_CLASS FsInformationClass
//);

//[File]
//NTSTATUS
//NTAPI
//NtReadFile(
//IN HANDLE FileHandle,
//IN HANDLE Event OPTIONAL,
//IN PIO_APC_ROUTINE ApcRoutine OPTIONAL,
//IN PVOID ApcContext OPTIONAL,
//OUT PIO_STATUS_BLOCK IoStatusBlock,
//OUT PVOID Buffer,
//IN ULONG Length,
//IN PLARGE_INTEGER ByteOffset OPTIONAL,
//IN PULONG Key OPTIONAL
//);

//[File]
//NTSTATUS
//NTAPI
//NtReadFileScatter(
//IN HANDLE FileHandle,
//IN HANDLE Event OPTIONAL,
//IN PIO_APC_ROUTINE ApcRoutine OPTIONAL,
//IN PVOID ApcContext OPTIONAL,
//OUT PIO_STATUS_BLOCK IoStatusBlock,
//IN PVOID Buffer,
//IN ULONG BufferLength,
//IN PLARGE_INTEGER Offset,
//IN PULONG Key OPTIONAL
//);

//[File]
//NTSTATUS
//NTAPI
//NtRemoveIoCompletion(
//IN HANDLE IoHandle,
//OUT PULONG Key,
//OUT PVOID Overlapped,
//OUT PIO_STATUS_BLOCK IoStatusBlock,
//IN PLARGE_INTEGER Timeout
//);

//[File]
NTSTATUS
NTAPI
NtRemoveIoCompletionEx(
__in HANDLE IoCompletionHandle,
__out PVOID IoCompletionInformation,
__in ULONG Count,
__out PULONG NumEntriesRemoved,
__in_opt PLARGE_INTEGER Timeout,
__in BOOLEAN Alertable
);

//[File]
//NTSTATUS
//NTAPI
//NtSetEaFile(
//IN HANDLE FileHandle,
//OUT PIO_STATUS_BLOCK IoStatusBlock,
//IN PVOID Buffer,
//IN ULONG BufferLength
//);

//[File]
//NTSTATUS
//NTAPI
//NtSetInformationFile(
//IN HANDLE FileHandle,
//OUT PIO_STATUS_BLOCK IoStatusBlock,
//IN PVOID FileInformation,
//IN ULONG Length,
//IN FILE_INFORMATION_CLASS FileInformationClass
//);

//[File]
//NTSTATUS
//NTAPI
//NtSetIoCompletion(
//IN HANDLE IoHandle,
//IN ULONG Key,
//IN OUT PVOID Overlapped,
//IN NTSTATUS Status,
//IN ULONG DataLength
//);

//[File]
NTSTATUS
NTAPI
NtSetIoCompletionEx(
__in HANDLE IoCompletionHandle,
__in HANDLE IoCompletionReserveHandle,
__in PVOID KeyContext,
__in_opt PVOID ApcContext,
__in NTSTATUS IoStatus,
__in ULONG IoStatusInformation
);

//[File]
//NTSTATUS
//NTAPI
//NtSetQuotaInformationFile(
//__in   HANDLE FileHandle,
//__out  PIO_STATUS_BLOCK IoStatusBlock,
//__in   PVOID Buffer,
//__in   ULONG Length
//);

//[File]
//NTSTATUS
//NTAPI
//NtSetVolumeInformationFile(
//__in   HANDLE FileHandle,
//__out  PIO_STATUS_BLOCK IoStatusBlock,
//__in   PVOID FsInformation,
//__in   ULONG Length,
//__in   FS_INFORMATION_CLASS FsInformationClass
//);

//[File]
//NTSTATUS
//NTAPI
//NtTranslateFilePath(
//IN PVOID InputPath,
//IN ULONG OutputType,
//OUT PVOID OutputFilePath,
//IN ULONG OutputFilePathLength
//);

//[File]
//NTSTATUS
//NTAPI
//NtUnlockFile(
//IN HANDLE FileHandle,
//OUT PIO_STATUS_BLOCK IoStatusBlock,
//IN PLARGE_INTEGER Offset,
//IN PLARGE_INTEGER Length,
//IN ULONG Key
//);

//[File]
//NTSTATUS
//NTAPI
//NtWriteFile(
//IN HANDLE FileHandle,
//IN HANDLE Event OPTIONAL,
//IN PIO_APC_ROUTINE ApcRoutine OPTIONAL,
//IN PVOID ApcContext OPTIONAL,
//OUT PIO_STATUS_BLOCK IoStatusBlock,
//IN PVOID Buffer,
//IN ULONG Length,
//IN PLARGE_INTEGER ByteOffset OPTIONAL,
//IN PULONG Key OPTIONAL
//);

//[File]
//NTSTATUS
//NTAPI
//NtWriteFileGather(
//IN HANDLE FileHandle,
//IN HANDLE Event OPTIONAL,
//IN PIO_APC_ROUTINE ApcRoutine OPTIONAL,
//IN PVOID ApcContext OPTIONAL,
//OUT PIO_STATUS_BLOCK IoStatusBlock,
//IN PVOID Segments,
//IN ULONG Length,
//IN PLARGE_INTEGER ByteOffset,
//IN PULONG Key OPTIONAL
//);

//[Job]
//NTSTATUS
//NTAPI
//NtAssignProcessToJobObject(
//IN HANDLE JobHandle,
//IN HANDLE ProcessHandle
//);

//[Job]
//NTSTATUS
//NTAPI
//NtCreateJobObject(
//OUT PHANDLE JobHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes
//);

//[Job]
//NTSTATUS
//NTAPI
//NtCreateJobSet(
//IN ULONG JobNumber,
//IN PVOID UserJobSet,
//IN ULONG Flags
//);

//[Job]
//NTSTATUS
//NTAPI
//NtIsProcessInJob(
//IN HANDLE hProcess,
//IN HANDLE hJob OPTIONAL
//);

//[Job]
//NTSTATUS
//NTAPI
//NtOpenJobObject(
//OUT PHANDLE JobHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes
//);
//JOBOBJECTINFOCLASS
//typedef enum _JOB_INFO
//[Job]
//NTSTATUS
//NTAPI
//NtQueryInformationJobObject(
//IN HANDLE JobHandle,
//IN JOBOBJECTINFOCLASS JobInformationClass,
//OUT PVOID JobInformation,
//IN ULONG Length,
//OUT PULONG ReturnLength OPTIONAL
//);

//[Job]
//NTSTATUS
//NTAPI
//NtSetInformationJobObject(
//IN HANDLE Handle,
//IN JOBOBJECTINFOCLASS Class,
//IN PVOID Buffer,
//IN ULONG BufferLength
//);

//[Job]
//NTSTATUS
//NTAPI
//NtTerminateJobObject(
//IN HANDLE JobHandle,
//IN NTSTATUS ExitStatus
//);

//[LPC]
//NTSTATUS
//NTAPI
//NtAcceptConnectPort(
//OUT PHANDLE PortHandle,
//IN PVOID PortContext OPTIONAL,
//IN PPORT_MESSAGE ConnectionRequest,
//IN BOOLEAN AcceptConnection,
//IN OUT PPORT_VIEW ServerView OPTIONAL,
//OUT PREMOTE_PORT_VIEW ClientView OPTIONAL
//);



//[LPC]
NTSTATUS
NTAPI
NtAlpcAcceptConnectPort(
OUT PHANDLE PortHandle,
IN HANDLE ConnectionPortHandle,
IN ULONG Flags,
IN POBJECT_ATTRIBUTES ObjectAttributes,
IN PALPC_PORT_ATTRIBUTES PortAttributes,
IN PVOID PortContext OPTIONAL,
IN PPORT_MESSAGE ConnectionRequest,
IN OUT PALPC_MESSAGE_ATTRIBUTES ConnectionMessageAttributes OPTIONAL,
IN BOOLEAN AcceptConnection
);

//[LPC]
NTSTATUS
NTAPI
NtAlpcCancelMessage(
IN HANDLE PortHandle,
IN ULONG Flags,
IN PALPC_CONTEXT_ATTRIBUTES MessageContext
);

//[LPC]
NTSTATUS
NTAPI
NtAlpcConnectPort(
__out PHANDLE PortHandle,
__in PUNICODE_STRING PortName,
__in POBJECT_ATTRIBUTES ObjectAttributes,
__in_opt PALPC_PORT_ATTRIBUTES PortAttributes,
__in ULONG Flags,
__in_opt PSID RequiredServerSid,
__inout PPORT_MESSAGE ConnectionMessage,
__inout_opt PULONG BufferLength,
__inout_opt PALPC_MESSAGE_ATTRIBUTES OutMessageAttributes,
__inout_opt PALPC_MESSAGE_ATTRIBUTES InMessageAttributes,
__in_opt PLARGE_INTEGER Timeout
);

//[LPC]
NTSTATUS
NTAPI
NtAlpcCreatePort(
OUT PHANDLE PortHandle,
IN POBJECT_ATTRIBUTES ObjectAttributes,
IN OUT PALPC_PORT_ATTRIBUTES PortAttributes OPTIONAL
);

//[LPC]
NTSTATUS
NTAPI
NtAlpcCreatePortSection(
HANDLE PortHandle,
ULONG AlpcSectionFlag,
HANDLE SectionHandle OPTIONAL,
ULONG SectionSize,
PHANDLE AlpcSectionHandle,
PULONG ResSize
);

//[LPC]
NTSTATUS
NTAPI
NtAlpcCreateResourceReserve(
__in HANDLE PortHandle,
__in ULONG Flags,
__in ULONG MessageSize,
__out PHANDLE ResourceId
);

//[LPC]
NTSTATUS
NTAPI
NtAlpcCreateSectionView(
HANDLE PortHandle,
ULONG FlagUnusedMustbeZero,
PALPC_DATA_VIEW ViewAttributes
);

//[LPC]
NTSTATUS
NTAPI
NtAlpcCreateSecurityContext(
__in HANDLE PortHandle,
__in ULONG Flags,
__inout PALPC_SECURITY_ATTRIBUTES SecurityAttribute
);

//[LPC]
NTSTATUS
NTAPI
NtAlpcDeletePortSection(
__in HANDLE PortHandle,
__in ULONG Flags,
__in HANDLE SectionHandle
);

//[LPC]
NTSTATUS
NTAPI
NtAlpcDeleteResourceReserve(
__in HANDLE PortHandle,
__in ULONG Flags,
__in HANDLE ResourceHandle
);

//[LPC]
NTSTATUS
NTAPI
NtAlpcDeleteSectionView(
__in HANDLE PortHandle,
__in ULONG Flags,
__in PVOID ViewBase
);

//[LPC]
NTSTATUS
NTAPI
NtAlpcDeleteSecurityContext(
__in HANDLE PortHandle,
__in ULONG Flags,
__in HANDLE ContextHandle
);

//[LPC]
NTSTATUS
NTAPI
NtAlpcDisconnectPort(
__in HANDLE PortHandle,
__in ULONG Flags
);

//[LPC]
NTSTATUS
NTAPI
NtAlpcImpersonateClientOfPort(
__in HANDLE PortHandle,
__in PPORT_MESSAGE PortMessage,
__in PVOID Reserved
);

//[LPC]
NTSTATUS
NTAPI
NtAlpcOpenSenderProcess(
__out PHANDLE ProcessHandle,
__in HANDLE PortHandle,
__in PPORT_MESSAGE PortMessage,
__in ULONG Flags,
__in ACCESS_MASK DesiredAccess,
__in POBJECT_ATTRIBUTES ObjectAttributes
);

//[LPC]
NTSTATUS
NTAPI
NtAlpcOpenSenderThread(
__out PHANDLE ThreadHandle,
__in HANDLE PortHandle,
__in PPORT_MESSAGE PortMessage,
__in ULONG Flags,
__in ACCESS_MASK DesiredAccess,
__in POBJECT_ATTRIBUTES ObjectAttributes
);

typedef enum _ALPC_PORT_INFORMATION_CLASS
{
	AlpcBasicInformation,
	AlpcPortInformation,
	AlpcAssociateCompletionPortInformation,
	AlpcConnectedSIDInformation,
	AlpcServerInformation,
	AlpcMessageZoneInformation,
	AlpcRegisterCompletionListInformation,
	AlpcUnregisterCompletionListInformation,
	AlpcAdjustCompletionListConcurrencyCountInformation,
	AlpcRegisterCallbackInformation,
	AlpcCompletionListRundownInformation,
	AlpcWaitForPortReferences
} ALPC_PORT_INFORMATION_CLASS;

//[LPC]
NTSTATUS
NTAPI
NtAlpcQueryInformation(
__in HANDLE PortHandle,
__in ALPC_PORT_INFORMATION_CLASS PortInformationClass,
__out PVOID PortInformation,
__in ULONG Length,
__out_opt PULONG ReturnLength
);

typedef enum _ALPC_MESSAGE_INFORMATION_CLASS
{
	AlpcMessageSidInformation,
	AlpcMessageTokenModifiedIdInformation,
	AlpcMessageDirectStatusInformation,
	AlpcMessageHandleInformation,
	MaxAlpcMessageInfoClass
} ALPC_MESSAGE_INFORMATION_CLASS;

//[LPC]
NTSTATUS
NTAPI
NtAlpcQueryInformationMessage(
__in HANDLE PortHandle,
__in PPORT_MESSAGE PortMessage,
__in ALPC_MESSAGE_INFORMATION_CLASS MessageInformationClass,
__out PVOID MessageInformation,
__in ULONG Length,
__out_opt PULONG ReturnLength
);

//[LPC]
NTSTATUS
NTAPI
NtAlpcRevokeSecurityContext(
__in HANDLE PortHandle,
__in ULONG Flags,
__in HANDLE ContextHandle
);

//[LPC]
NTSTATUS
NTAPI
NtAlpcSendWaitReceivePort(
HANDLE PortHandle,
ULONG SendFlags,
PLPC_MESSAGE SendMessage OPTIONAL,
PVOID InMessageBuffer OPTIONAL,
PLPC_MESSAGE ReceiveBuffer OPTIONAL,
PULONG ReceiveBufferSize OPTIONAL,
PVOID OutMessageBuffer OPTIONAL,
PLARGE_INTEGER Timeout OPTIONAL
);

//[LPC]
NTSTATUS
NTAPI
NtAlpcSetInformation(
__in HANDLE PortHandle,
__in ALPC_PORT_INFORMATION_CLASS PortInformationClass,
__in PVOID PortInformation,
__in ULONG Length
);

//[LPC]
//NTSTATUS
//NTAPI
//NtCompleteConnectPort(
//IN HANDLE PortHandle
//);

//[LPC]
//NTSTATUS
//NTAPI
//NtConnectPort(
//OUT PHANDLE PortHandle,
//IN PUNICODE_STRING PortName,
//IN PVOID SecurityQos,
//IN OUT PPORT_VIEW ClientView OPTIONAL,
//OUT PREMOTE_PORT_VIEW ServerView OPTIONAL,
//OUT PULONG MaxMsgLength OPTIONAL,
//IN OUT PVOID ConnectionInfo OPTIONAL,
//IN OUT PULONG ConnectionInfoLength OPTIONAL
//);

//[LPC]
NTSTATUS
NTAPI
NtCreateChannel(
OUT PHANDLE ChannelHandle,
IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL
);

//[LPC]
//NTSTATUS
//NTAPI
//NtCreatePort(
//OUT PHANDLE PortHandle,
//IN POBJECT_ATTRIBUTES ObjectAttributes,
//IN ULONG MaxConnectionInfoLength,
//IN ULONG MaxMsgLength,
//IN ULONG MaxPoolUsage
//);

//[LPC]
//NTSTATUS
//NTAPI
//NtCreateWaitablePort(
//OUT PHANDLE PortHandle,
//IN POBJECT_ATTRIBUTES ObjectAttributes,
//IN ULONG MaxConnectionInfoLength,
//IN ULONG MaxMsgLength,
//IN ULONG MaxPoolUsage
//);

//[LPC]
//NTSTATUS
//NTAPI
//NtImpersonateClientOfPort(
//IN HANDLE PortHandle,
//IN PLPC_MESSAGE Message
//);

//[LPC]
NTSTATUS
NTAPI
NtListenChannel(
IN HANDLE Handle,
OUT PCHANNEL_MESSAGE Message
);

//[LPC]
//NTSTATUS
//NTAPI
//NtListenPort(
//IN HANDLE Handle,
//OUT PLPC_MESSAGE ConnectionData
//);

//[LPC]
NTSTATUS
NTAPI
NtOpenChannel(
OUT PHANDLE ChannelHandle,
IN POBJECT_ATTRIBUTES ObjectAttributes
);

//[LPC]
//NTSTATUS
//NTAPI
//NtQueryInformationPort(
//IN HANDLE JobHandle,
//IN PORT_INFORMATION_CLASS PortInformationClass,
//OUT PVOID PortInformation,
//IN ULONG Length,
//OUT PULONG ReturnLength OPTIONAL
//);

//[LPC]
NTSTATUS
NTAPI
NtQueryPortInformationProcess(
);

//[LPC]
//NTSTATUS
//NTAPI
//NtReadRequestData(
//IN HANDLE Handle,
//IN PLPC_MESSAGE Request,
//IN ULONG Index,
//OUT PVOID Buffer,
//IN ULONG BufferLength,
//OUT PULONG ReturnLength OPTIONAL
//);

//[LPC]
//NTSTATUS
//NTAPI
//NtReplyPort(
//IN HANDLE PortHandle,
//IN PLPC_MESSAGE pMessage
//);

//[LPC]
//NTSTATUS
//NTAPI
//NtReplyWaitReceivePort(
//IN HANDLE PortHandle,
//OUT PHANDLE ReceiveHandle,
//IN PLPC_MESSAGE pMessage,
//OUT PLPC_MESSAGE pMessage2
//);

//[LPC]
//NTSTATUS
//NTAPI
//NtReplyWaitReceivePortEx(
//IN HANDLE PortHandle,
//OUT PHANDLE ReceiveHandle,
//IN PLPC_MESSAGE pMessage,
//OUT PLPC_MESSAGE pMessage2,
//IN PLARGE_INTEGER Timeout
//);

//[LPC]
//NTSTATUS
//NTAPI
//NtReplyWaitReplyPort(
//IN HANDLE PortHandle,
//IN OUT PLPC_MESSAGE pMessage
//);

//[LPC]
NTSTATUS
NTAPI
NtReplyWaitSendChannel(
IN HANDLE ChannelHandle,
IN PVOID ReplyMessage OPTIONAL,
OUT PCHANNEL_MESSAGE Message
);

//[LPC]
//NTSTATUS
//NTAPI
//NtRequestPort(
//IN HANDLE PortHandle,
//IN PLPC_MESSAGE RequestMessage
//);

//[LPC]
//NTSTATUS
//NTAPI
//NtRequestWaitReplyPort(
//IN HANDLE PortHandle,
//IN PLPC_MESSAGE pRequestMessage,
//OUT PLPC_MESSAGE pReplyMessage
//);

//[LPC]
//NTSTATUS
//NTAPI
//NtSecureConnectPort(
//OUT PHANDLE PortHandle,
//IN PUNICODE_STRING Name,
//IN ULONG QOS,
//IN OUT PPORT_VIEW pSectionInfo,
//IN PSID SecurityInfo,
//IN OUT PREMOTE_PORT_VIEW pSectionMapInfo,
//OUT PULONG MaxMsgLength,
//IN OUT PVOID ConnectData OPTIONAL,
//IN OUT PULONG ConnectDataLength OPTIONAL
//);

//[LPC]
NTSTATUS
NTAPI
NtSendWaitReplyChannel(
IN HANDLE ChannelHandle,
IN PVOID RequestMessage,
OUT PCHANNEL_MESSAGE ReplyMessage,
IN PLARGE_INTEGER Timeout
);

//[LPC]
NTSTATUS
NTAPI
NtSetContextChannel(
IN HANDLE ChannelHandle
);

//[LPC]
//NTSTATUS
//NTAPI
//NtWriteRequestData(
//IN HANDLE PortHandle,
//IN PLPC_MESSAGE Message,
//IN ULONG Index,
//IN PVOID Buffer,
//IN ULONG BufferLength,
//OUT PULONG ReturnLength OPTIONAL
//);

//[Memory]
//NTSTATUS
//NTAPI
//NtAllocateUserPhysicalPages(
//__in     HANDLE hProcess,
//__inout  PULONG NumberOfPages,
//__out    PULONG UserPfnArray
//);

//[Memory]
//NTSTATUS
//NTAPI
//NtAllocateVirtualMemory(
//IN HANDLE ProcessHandle,
//IN OUT PVOID* lpAddress,
//IN ULONG_PTR ZeroBits,
//IN OUT PSIZE_T pSize,
//IN ULONG flAllocationType,
//IN ULONG flProtect
//);

//[Memory]
//NTSTATUS
//NTAPI
//NtCreateSection(
//OUT PHANDLE SectionHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes,
//IN PLARGE_INTEGER SectionSize OPTIONAL,
//IN ULONG Protect,
//IN ULONG Attributes,
//IN HANDLE FileHandle
//);

//[Memory]
//NTSTATUS
//NTAPI
//NtExtendSection(
//IN HANDLE SectionHandle,
//IN PLARGE_INTEGER SectionSize
//);

//[Memory]
//NTSTATUS
//NTAPI
//NtFlushInstructionCache(
//IN HANDLE Process,
//IN PVOID BaseAddress,
//IN ULONG Size
//);

//[Memory]
NTSTATUS
NTAPI
NtFlushProcessWriteBuffers(
);

//[Memory]
//NTSTATUS
//NTAPI
//NtFlushVirtualMemory(
//__in     HANDLE ProcessHandle,
//__inout  PVOID* BaseAddress,
//__inout  PSIZE_T RegionSize,
//__out    PIO_STATUS_BLOCK IoStatus
//);

//[Memory]
//NTSTATUS
//NTAPI
//NtFlushWriteBuffer(
//);

//[Memory]
//NTSTATUS
//NTAPI
//NtFreeUserPhysicalPages(
//__in     HANDLE hProcess,
//__inout  PULONG NumberOfPages,
//__in     PULONG UserPfnArray
//);

//[Memory]
//NTSTATUS
//NTAPI
//NtFreeVirtualMemory(
//IN HANDLE ProcessHandle,
//IN OUT PVOID* lpAddress,
//IN OUT PSIZE_T pSize,
//IN ULONG flFreeType
//);

//[Memory]
//NTSTATUS
//NTAPI
//NtLockVirtualMemory(
//IN HANDLE ProcessHandle,
//IN OUT PVOID* lpAddress,
//IN OUT PSIZE_T pSize,
//IN ULONG LockOption
//);

//[Memory]
//NTSTATUS
//NTAPI
//NtMapUserPhysicalPages(
//__in  PVOID lpAddress,
//__in  ULONG NumberOfPages,
//__in  PULONG UserPfnArray
//);

//[Memory]
//NTSTATUS
//NTAPI
//NtMapUserPhysicalPagesScatter(
//__in PVOID* VirtualAddresses,
//__in ULONG NumberOfPages,
//__in PULONG PageArray
//);

//[Memory]
//NTSTATUS
//NTAPI
//NtMapViewOfSection(
//IN HANDLE SectionHandle,
//IN HANDLE ProcessHandle,
//IN OUT PVOID* BaseAddress,
//IN ULONG ZeroBits,
//IN ULONG CommitSize,
//IN OUT PLARGE_INTEGER SectionOffset OPTIONAL,
//IN OUT PSIZE_T ViewSize,
//IN SECTION_INHERIT InheritDisposition,
//IN ULONG AllocationType,
//IN ULONG Protect
//);

//[Memory]
//NTSTATUS
//NTAPI
//NtOpenSection(
//OUT PHANDLE SectionHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes
//);

//[Memory]
//NTSTATUS
//NTAPI
//NtProtectVirtualMemory(
//IN HANDLE ProcessHandle,
//IN OUT PVOID* BaseAddress,
//IN OUT PULONG Size,
//IN ULONG NewProtect,
//OUT PULONG OldProtect
//);

//[Memory]
//NTSTATUS
//NTAPI
//NtQuerySection(
//IN HANDLE SectionHandle,
//IN SECTION_INFORMATION_CLASS SectionInformationClass,
//OUT PVOID SectionInformation,
//IN ULONG Length,
//OUT PULONG ReturnLength OPTIONAL
//);

//[Memory]
//NTSTATUS
//NTAPI
//NtQueryVirtualMemory(
//IN HANDLE ProcessHandle,
//IN PVOID BaseAddress,
//IN MEMORY_INFORMATION_CLASS MemoryInformationClass,
//OUT PVOID MemoryInformation,
//IN ULONG Length,
//OUT PULONG ReturnLength OPTIONAL
//);

//[Memory]
//NTSTATUS
//NTAPI
//NtReadVirtualMemory(
//IN HANDLE ProcessHandle,
//IN PVOID BaseAddress,
//OUT PVOID Buffer,
//IN ULONG BufferSize,
//OUT PULONG BytesRead
//);

//[Memory]
//NTSTATUS
//NTAPI
//NtUnlockVirtualMemory(
//IN HANDLE ProcessHandle,
//IN OUT PVOID* lpAddress,
//IN OUT PSIZE_T pSize,
//IN ULONG LockOption
//);

//[Memory]
//NTSTATUS
//NTAPI
//NtUnmapViewOfSection(
//IN HANDLE ProcessHandle,
//IN PVOID BaseAddress OPTIONAL
//);

//[Memory]
//NTSTATUS
//NTAPI
//NtWriteVirtualMemory(
//IN HANDLE ProcessHandle,
//IN PVOID BaseAddress,
//IN PVOID Buffer,
//IN ULONG BufferLength,
//OUT PULONG ReturnedLength OPTIONAL
//);

//[Object]
NTSTATUS
NTAPI
NtAllocateReserveObject(
__out PHANDLE MemoryReserveHandle,
__in_opt POBJECT_ATTRIBUTES ObjectAttributes,
__in ULONG Type
);

//[Object]
//NTSTATUS
//NTAPI
//NtCreateDebugObject(
//OUT PHANDLE DebugHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes,
//IN ULONG Flags
//);

//[Object]
//NTSTATUS
//NTAPI
//NtCreateDirectoryObject(
//OUT PHANDLE DirectoryHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes
//);

//[Object]
NTSTATUS
NTAPI
NtCreatePrivateNamespace(
OUT PHANDLE NamespaceHandle,
IN PSECURITY_ATTRIBUTES Attributes OPTIONAL,
IN PVOID BoundaryDescriptor,
IN PUNICODE_STRING AliasPrefix
);

//[Object]
//NTSTATUS
//NTAPI
//NtCreateSymbolicLinkObject(
//OUT PHANDLE LinkHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes,
//IN PUNICODE_STRING SymbolicLink
//);

//[Object]
NTSTATUS
NTAPI
NtDeletePrivateNamespace(
IN HANDLE NamespaceHandle
);

//[Object]
//NTSTATUS
//NTAPI
//NtDuplicateObject(
//IN HANDLE SourceProcess,
//IN HANDLE SourceHandle,
//IN HANDLE TargetProcess,
//OUT PHANDLE TargetHandle,
//IN ACCESS_MASK DesiredAccess,
//IN BOOL InheritMode,
//IN ULONG Options
//);

//[Object]
//NTSTATUS
//NTAPI
//NtMakePermanentObject(
//IN HANDLE Object
//);

//[Object]
//NTSTATUS
//NTAPI
//NtMakeTemporaryObject(
//IN HANDLE Handle
//);

//[Object]
//NTSTATUS
//NTAPI
//NtOpenDirectoryObject(
//OUT PHANDLE DirectoryHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes
//);

//[Object]
//NTSTATUS
//NTAPI
//NtOpenObjectAuditAlarm(
//IN PUNICODE_STRING SubsystemName,
//IN PHANDLE HandleId,
//IN PUNICODE_STRING ObjectTypeName,
//IN PUNICODE_STRING ObjectName,
//IN PSECURITY_DESCRIPTOR SecurityDescriptor,
//IN HANDLE ClientToken,
//IN ACCESS_MASK DesiredAccess,
//IN ACCESS_MASK GrantedAccess,
//IN PPRIVILEGE_SET PrivilegeSet,
//IN BOOLEAN ObjectCreation,
//IN BOOLEAN AccessGranted,
//OUT PBOOLEAN OnClose
//);

//[Object]
NTSTATUS
NTAPI
NtOpenPrivateNamespace(
OUT PHANDLE NamespaceHandle,
IN ACCESS_MASK DesiredAccess,
IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
IN PVOID Buffer
);

//[Object]
//NTSTATUS
//NTAPI
//NtOpenSymbolicLinkObject(
//OUT PHANDLE LinkHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes
//);

//[Object]
//NTSTATUS
//NTAPI
//NtQueryDirectoryObject(
//IN HANDLE DirectoryHandle,
//OUT PVOID DirectoryBuffer,
//IN ULONG BufferLength,
//IN ULONG OnlyFirstEntry,
//IN ULONG FirstEntry,
//IN OUT PULONG Index,
//OUT PULONG ReturnedLength OPTIONAL
//);

//[Object]
//NTSTATUS
//NTAPI
//NtQueryObject(
//IN HANDLE ObjectHandle,
//IN OBJECT_INFORMATION_CLASS ObjectInformationClass,
//OUT PVOID ObjectInformation,
//IN ULONG Length,
//OUT PULONG ReturnLength OPTIONAL
//);

//[Object]
//NTSTATUS
//NTAPI
//NtQuerySymbolicLinkObject(
//IN HANDLE LinkHandle,
//IN OUT PUNICODE_STRING LinkTarget,
//OUT PULONG ReturnedLength OPTIONAL
//);

//[Object]
//NTSTATUS
//NTAPI
//NtSetInformationObject(
//IN HANDLE Handle,
//IN OBJECT_INFORMATION_CLASS Class,
//IN PVOID Buffer,
//IN ULONG BufferLength
//);

//[Other]
NTSTATUS
NTAPI
NtAcquireCMFViewOwnership(
__out PLARGE_INTEGER TimeStamp,
__out PBOOLEAN TokenTaken,
__in BOOLEAN ReplaceExisting
);

//[Other]
//NTSTATUS
//NTAPI
//NtAllocateLocallyUniqueId(
//OUT PLUID Luid
//);

//[Other]
//NTSTATUS
//NTAPI
//NtAllocateUuids(
//OUT PLARGE_INTEGER UuidLastTimeAllocated,
//OUT PULONG UuidDeltaTime,
//OUT PULONG UuidSequenceNumber,
//OUT PUCHAR UuidSeed
//);

//[Other]
//NTSTATUS
//NTAPI
//NtCallbackReturn(
//IN PVOID Result OPTIONAL,
//IN ULONG ResultLength,
//IN NTSTATUS Status
//);

//[Other]
//NTSTATUS
//NTAPI
//NtCancelTimer(
//IN HANDLE TimerHandle,
//OUT PBOOLEAN CurrentState OPTIONAL
//);

//[Other]
//NTSTATUS
//NTAPI
//NtCreateTimer(
//OUT PHANDLE TimerHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
//IN TIMER_TYPE TimerType
//);

// This one is odd.
//[-Other]
//struct _TEB *
//	NtCurrentTeb(
//	);

//[Other]
//NTSTATUS
//NTAPI
//NtDisplayString(
//IN PUNICODE_STRING Message
//);

//[Other]
NTSTATUS
NTAPI
NtDrawText(
__in PUNICODE_STRING Text
);

//[Other]
NTSTATUS
NTAPI
NtFlushInstallUILanguage(
__in ULONG InstallUILanguage,
__in ULONG SetComittedFlag
);

//[Other]
NTSTATUS
NTAPI
NtGetMUIRegistryInfo(
__in ULONG Flags,
__inout PULONG BufferLength,
__out PVOID Buffer
);

//[Other]
NTSTATUS
NTAPI
NtGetNlsSectionPtr(
__in ULONG SectionType,
__in ULONG SectionData,
__in PVOID ContextData,
__out PVOID* SectionPointer,
__out PULONG SectionSize
);

//[-Other]
//NTSTATUS
//NTAPI
//NtGetTickCount(
//);

//[Other]
//NTSTATUS
//NTAPI
//NtGetWriteWatch(
//IN HANDLE ProcessHandle,
//IN ULONG Flags,
//IN PVOID BaseAddress,
//IN ULONG RegionSize,
//OUT PULONG Buffer,
//IN OUT PULONG BufferEntries,
//OUT PULONG Granularity
//);

//[Other]
NTSTATUS
NTAPI
NtInitializeNlsFiles(
__out PVOID* BaseAddress,
__out PLCID DefaultLocaleId,
__out PLARGE_INTEGER DefaultCasingTableSize
);

//[Other]
NTSTATUS
NTAPI
NtIsUILanguageComitted(
);

//[Other]
NTSTATUS
NTAPI
NtLockProductActivationKeys(
IN PULONG ProductBuild,
IN PULONG SafeMode
);

//[Other]
NTSTATUS
NTAPI
NtMapCMFModule(
__in ULONG What,
__in ULONG Index,
__out_opt PULONG CacheIndexOut,
__out_opt PULONG CacheFlagsOut,
__out_opt PULONG ViewSizeOut,
__out_opt PVOID* BaseAddress
);
typedef enum _IO_SESSION_STATE {
	IoSessionStateCreated = 1,
	IoSessionStateInitialized = 2,
	IoSessionStateConnected = 3,
	IoSessionStateDisconnected = 4,
	IoSessionStateDisconnectedLoggedOn = 5,
	IoSessionStateLoggedOn = 6,
	IoSessionStateLoggedOff = 7,
	IoSessionStateTerminated = 8,
	IoSessionStateMax = 9
} IO_SESSION_STATE, *PIO_SESSION_STATE;
//[Other]
NTSTATUS
NTAPI
NtNotifyChangeSession(
__in HANDLE Session,
__in ULONG IoStateSequence,
__in PVOID Reserved,
__in ULONG Action,
__in IO_SESSION_STATE IoState,
__in IO_SESSION_STATE IoState2,
__in PVOID Buffer,
__in ULONG BufferSize
);

//[Other]
NTSTATUS
NTAPI
NtOpenSession(
__out PHANDLE SessionHandle,
__in ACCESS_MASK DesiredAccess,
__in POBJECT_ATTRIBUTES ObjectAttributes
);

//[Other]
//NTSTATUS
//NTAPI
//NtOpenTimer(
//OUT PHANDLE TimerHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes
//);

//[Other]
NTSTATUS
NTAPI
NtQueryLicenseValue(
IN PUNICODE_STRING Name,
OUT PULONG Type OPTIONAL,
OUT PVOID Buffer,
IN ULONG Length,
OUT PULONG ReturnedLength
);

//[Other]
//NTSTATUS
//NTAPI
//NtQuerySystemInformation(
//IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
//OUT PVOID SystemInformation,
//IN ULONG Length,
//OUT PULONG ReturnLength OPTIONAL
//);

//[Other]
NTSTATUS
NTAPI
NtQuerySystemInformationEx(
IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
IN PULONG QueryType,
IN ULONG Alignment,
OUT PVOID SystemInformation,
IN ULONG Length,
OUT PULONG ReturnLength OPTIONAL
);

//[Other]
NTSTATUS
NTAPI
NtReleaseCMFViewOwnership(
);

//[Other]
//NTSTATUS
//NTAPI
//NtResetWriteWatch(
//IN HANDLE ProcessHandle,
//IN PVOID BaseAddress,
//IN ULONG RegionSize
//);

//[Other]
//NTSTATUS
//NTAPI
//NtSetLdtEntries(
//IN ULONG Selector1,
//IN ULONG LdtEntry1L,
//IN ULONG LdtEntry1H,
//IN ULONG Selector2,
//IN ULONG LdtEntry2L,
//IN ULONG LdtEntry2H
//);

//[Other]
//NTSTATUS
//NTAPI
//NtSetSystemInformation(
//IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
//IN PVOID SystemInformation,
//IN ULONG Length
//);

//[Other]
//NTSTATUS
//NTAPI
//NtSetTimer(
//IN HANDLE TimerHandle,
//IN PLARGE_INTEGER DueTime,
//IN PTIMER_APC_ROUTINE TimerApcRoutine OPTIONAL,
//IN PVOID TimerContext OPTIONAL,
//IN BOOLEAN WakeTimer,
//IN LONG Period OPTIONAL,
//OUT PBOOLEAN PreviousState OPTIONAL
//);

//[Other]
NTSTATUS
NTAPI
NtSetTimerEx(
__in HANDLE TimerHandle,
__in TIMER_INFORMATION_CLASS TimerSetInformationClass,
__inout PVOID TimerSetInformation,
__in ULONG Length
);

//[Other]
//NTSTATUS
//NTAPI
//NtSetUuidSeed(
//IN PUCHAR UuidSeed
//);

//[Other]
//NTSTATUS
//NTAPI
//NtShutdownSystem(
//IN SHUTDOWN_ACTION Action
//);

//[Other]
NTSTATUS
NTAPI
NtTraceControl(
IN ULONG CtrlCode,
IN PVOID InputBuffer,
IN ULONG InputBufferLength,
OUT PVOID OutputBuffer,
IN ULONG OutputBufferLength,
OUT PULONG ReturnLength
);

//[Process]
//NTSTATUS
//NTAPI
//NtAlertResumeThread(
//HANDLE ThreadHandle,
//OUT PULONG pSuspendCount
//);

//[Process]
//NTSTATUS
//NTAPI
//NtAlertThread(
//IN HANDLE ThreadHandle
//);

//[Process]
//NTSTATUS
//NTAPI
//NtApphelpCacheControl(
//IN ULONG ServiceClass,
//IN PUNICODE_STRING ServiceData
//);

//[Process]
//NTSTATUS
//NTAPI
//NtContinue(
//IN PCONTEXT Context,
//IN BOOLEAN bTest
//);

//[Process]
//NTSTATUS
//NTAPI
//NtCreateProcess(
//OUT PHANDLE ProcessHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
//IN HANDLE ParentProcessHandle,
//IN BOOL Inherit,
//IN HANDLE SectionHandle OPTIONAL,
//IN HANDLE DebugPort OPTIONAL,
//IN HANDLE ExceptionPort OPTIONAL
//);

//[Process]
//NTSTATUS
//NTAPI
//NtCreateProcessEx(
//OUT PHANDLE ProcessHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
//IN HANDLE ParentProcessHandle,
//IN BOOL Inherit,
//IN HANDLE SectionHandle OPTIONAL,
//IN HANDLE DebugPort OPTIONAL,
//IN HANDLE ExceptionPort OPTIONAL,
//IN BOOLEAN InJob
//);

//[Process]
//NTSTATUS
//NTAPI
//NtCreateThread(
//OUT PHANDLE ThreadHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
//IN HANDLE ProcessHandle,
//OUT PCLIENT_ID ClientId,
//IN PCONTEXT ThreadContext,
//IN PVOID UserStack,
//IN BOOLEAN CreateSuspended
//);

//[Process]
//NTSTATUS
//NTAPI
//NtCreateThreadEx(
//__out PHANDLE ThreadHandle,
//__in ACCESS_MASK DesiredAccess,
//__in_opt POBJECT_ATTRIBUTES ObjectAttributes,
//__in HANDLE ProcessHandle,
//__in PVOID StartRoutine,
//__in_opt PVOID Argument,
//__in ULONG CreateFlags,
//__in_opt ULONG ZeroBits,
//__in_opt ULONG StackSize,
//__in_opt ULONG MaximumStackSize,
//__in_opt PVOID AttributeList
//);

//[Process]
NTSTATUS
NTAPI
NtCreateUserProcess(
__out PHANDLE ProcessHandle,
__out PHANDLE ThreadHandle,
__in ACCESS_MASK ProcessDesiredAccess,
__in ACCESS_MASK ThreadDesiredAccess,
__in_opt POBJECT_ATTRIBUTES ProcessObjectAttributes,
__in_opt POBJECT_ATTRIBUTES ThreadObjectAttributes,
__in ULONGLONG ProcessFlags,
__in ULONGLONG ThreadFlags,
__in_opt PRTL_USER_PROCESS_PARAMETERS ProcessParameters,
__inout PVOID CreateInfo,
__in_opt PVOID AttributeList
);

//[Process]
NTSTATUS
NTAPI
NtCreateWorkerFactory(
__out PHANDLE WorkerFactoryHandleReturn,
__in ACCESS_MASK DesiredAccess,
__in_opt POBJECT_ATTRIBUTES ObjectAttributes,
__in HANDLE CompletionPortHandle,
__in HANDLE WorkerProcessHandle,
__in PVOID StartRoutine,
__in_opt PVOID StartParameter,
__in_opt ULONG MaxThreadCount,
__in_opt ULONG StackReserve,
__in_opt ULONG StackCommit
);

//[Process]
//NTSTATUS
//NTAPI
//NtDelayExecution(
//IN BOOLEAN Alertable,
//IN PLARGE_INTEGER DelayInterval
//);

//[Process]
//NTSTATUS
//NTAPI
//NtGetContextThread(
//IN HANDLE ThreadHandle,
//OUT PCONTEXT pContext
//);

//[Process]
NTSTATUS
NTAPI
NtGetNextProcess(
HANDLE ProcessHandle,
ACCESS_MASK DesiredAccess,
ULONG HandleAttributes,
ULONG Flags,
PHANDLE NewProcessHandle
);

//[Process]
NTSTATUS
NTAPI
NtGetNextThread(
HANDLE ProcessHandle,
HANDLE ThreadHandle,
ACCESS_MASK DesiredAccess,
ULONG HandleAttributes,
ULONG Flags,
PHANDLE NewThreadHandle
);

//[Process]
//NTSTATUS
//NTAPI
//NtOpenProcess(
//OUT PHANDLE ProcessHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes,
//IN PCLIENT_ID ClientId OPTIONAL
//);

//[Process]
//NTSTATUS
//NTAPI
//NtOpenThread(
//OUT PHANDLE ThreadHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes,
//IN PCLIENT_ID ClientId OPTIONAL
//);

//[Process]
//NTSTATUS
//NTAPI
//NtQueryInformationProcess(
//IN HANDLE ProcessHandle,
//IN PROCESSINFOCLASS ProcessInformationClass,
//OUT PVOID ProcessInformation,
//IN ULONG Length,
//OUT PULONG ReturnLength OPTIONAL
//);

//[Process]
//NTSTATUS
//NTAPI
//NtQueryInformationThread(
//IN HANDLE ThreadHandle,
//IN THREADINFOCLASS ThreadInformationClass,
//OUT PVOID ThreadInformation,
//IN ULONG Length,
//OUT PULONG ReturnLength OPTIONAL
//);

typedef enum _WORKERFACTORYINFOCLASS
{
	WorkerFactoryTimeout,
	WorkerFactoryRetryTimeout,
	WorkerFactoryIdleTimeout,
	WorkerFactoryBindingCount,
	WorkerFactoryThreadMinimum,
	WorkerFactoryThreadMaximum,
	WorkerFactoryPaused,
	WorkerFactoryBasicInformation, // name:wow64:whNtQueryInformationWorkerFactory_WorkerFactoryBasicInformation 
	WorkerFactoryAdjustThreadGoal,
	WorkerFactoryCallbackType,
	WorkerFactoryStackInformation, // name:wow64:whNtQueryInformationWorkerFactory_WorkerFactoryStackInformation 
	MaxWorkerFactoryInfoClass
} WORKERFACTORYINFOCLASS, *PWORKERFACTORYINFOCLASS;

//[Process]
NTSTATUS
NTAPI
NtQueryInformationWorkerFactory(
__in HANDLE WorkerFactoryHandle,
__in WORKERFACTORYINFOCLASS WorkerFactoryInformationClass,
__out PVOID Buffer,
__in ULONG BufferLength,
__out_opt PULONG ReturnLength OPTIONAL
);

//[Process]
//NTSTATUS
//NTAPI
//NtQueueApcThread(
//IN HANDLE ThreadHandle,
//IN PVOID ApcRoutine,
//IN PVOID Context,
//IN PVOID Argument1,
//IN PVOID Argument2
//);

//[Process]
NTSTATUS
NTAPI
NtQueueApcThreadEx(
IN HANDLE ThreadHandle,
IN HANDLE ApcReserve,
IN PVOID ApcRoutine,
IN PVOID Context,
IN PVOID Argument1,
IN PVOID Argument2
);

//[Process]
//NTSTATUS
//NTAPI
//NtRaiseException(
//IN PEXCEPTION_RECORD Record,
//IN PCONTEXT Context,
//IN BOOL SearchFrames
//);

//[Process]
//NTSTATUS
//NTAPI
//NtRaiseHardError(
//IN NTSTATUS ErrorStatus,
//IN ULONG NumberOfParameters,
//IN ULONG ParameterMask,
//IN PULONG_PTR Parameters,
//IN HARDERROR_RESPONSE_OPTION ResponseOptions,
//OUT PULONG Response
//);

//[Process]
NTSTATUS
NTAPI
NtReleaseWorkerFactoryWorker(
IN HANDLE WorkerFactoryHandle
);

//[Process]
//NTSTATUS
//NTAPI
//NtResumeProcess(
//IN HANDLE hProcess
//);

//[Process]
//NTSTATUS
//NTAPI
//NtResumeThread(
//IN HANDLE ThreadHandle,
//OUT PULONG SuspendCount
//);

//[Process]
//NTSTATUS
//NTAPI
//NtSetContextThread(
//IN HANDLE ThreadHandle,
//IN PCONTEXT pContext
//);

//[Process]
//NTSTATUS
//NTAPI
//NtSetDefaultHardErrorPort(
//IN HANDLE Port
//);

//[Process]
//NTSTATUS
//NTAPI
//NtSetInformationProcess(
//IN HANDLE ProcessHandle,
//IN PROCESSINFOCLASS ProcessInformationClass,
//IN PVOID ProcessInformation,
//IN ULONG Length
//);

//[Process]
//NTSTATUS
//NTAPI
//NtSetInformationThread(
//IN HANDLE ThreadHandle,
//IN THREADINFOCLASS ThreadInformationClass,
//IN PVOID ThreadInformation,
//IN ULONG Length
//);

//[Process]
NTSTATUS
NTAPI
NtSetInformationWorkerFactory(
__in HANDLE WorkerFactoryHandle,
__in WORKERFACTORYINFOCLASS InformationClass,
__in PVOID Buffer,
__in ULONG BufferLength
);

//[Process]
NTSTATUS
NTAPI
NtShutdownWorkerFactory(
__in HANDLE WorkerFactoryHandle,
__inout PULONG PendingWorkerCount
);

//[Process]
//NTSTATUS
//NTAPI
//NtSuspendProcess(
//IN HANDLE ProcessHandle
//);

//[Process]
//NTSTATUS
//NTAPI
//NtSuspendThread(
//IN HANDLE ThreadHandle,
//OUT PULONG PreviousSuspendCount OPTIONAL
//);

//[Process]
//NTSTATUS
//NTAPI
//NtTerminateProcess(
//IN HANDLE ProcessHandle,
//IN NTSTATUS ExitStatus
//);

//[Process]
//NTSTATUS
//NTAPI
//NtTerminateThread(
//IN HANDLE ThreadHandle,
//IN NTSTATUS ExitStatus
//);

//[Process]
//NTSTATUS
//NTAPI
//NtTestAlert(
//);

//[Process]
NTSTATUS
NTAPI
NtUmsThreadYield(
__in  PVOID SchedulerParam
);

//[Process]
NTSTATUS
NTAPI
NtWaitForWorkViaWorkerFactory(
__in HANDLE WorkerFactoryHandle,
__out PVOID MiniPacket
);

//[Process]
NTSTATUS
NTAPI
NtWorkerFactoryWorkerReady(
IN HANDLE WorkerFactoryHandle
);

//[Process]
//NTSTATUS
//NTAPI
//NtYieldExecution(
//);

//[Registry]
//NTSTATUS
//NTAPI
//NtCompactKeys(
//IN ULONG NumberOfKeys,
//IN PVOID KeyHandles
//);

//[Registry]
NTSTATUS
NTAPI
NtCompressKey(
IN HANDLE KeyHandle
);

//[Registry]
//NTSTATUS
//NTAPI
//NtCreateKey(
//OUT PHANDLE KeyHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes,
//IN ULONG TitleIndex,
//IN PUNICODE_STRING Class OPTIONAL,
//IN ULONG CreateOptions,
//OUT PULONG Disposition OPTIONAL
//);

//[Registry]
NTSTATUS
NTAPI
NtCreateKeyTransacted(
__out       PHANDLE KeyHandle,
__in        ACCESS_MASK DesiredAccess,
__in        POBJECT_ATTRIBUTES ObjectAttributes,
__reserved  ULONG TitleIndex,
__in_opt    PUNICODE_STRING Class,
__in        ULONG CreateOptions,
__in        HANDLE TransactionHandle,
__out_opt   PULONG Disposition
);

//[Registry]
//NTSTATUS
//NTAPI
//NtDeleteKey(
//IN HANDLE KeyHandle
//);

//[Registry]
//NTSTATUS
//NTAPI
//NtDeleteValueKey(
//IN HANDLE KeyHandle,
//IN PUNICODE_STRING ValueName
//);

//[Registry]
//NTSTATUS
//NTAPI
//NtEnumerateKey(
//IN HANDLE KeyHandle,
//IN ULONG Index,
//IN KEY_INFORMATION_CLASS KeyInformationClass,
//OUT PVOID KeyInformation,
//IN ULONG Length,
//OUT PULONG ResultLength
//);

//[Registry]
//NTSTATUS
//NTAPI
//NtEnumerateValueKey(
//IN HANDLE KeyHandle,
//IN ULONG Index,
//IN KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
//OUT PVOID KeyValueInformation,
//IN ULONG Length,
//OUT PULONG ResultLength
//);

//[Registry]
//NTSTATUS
//NTAPI
//NtFlushKey(
//IN HANDLE KeyHandle
//);

//[Registry]
NTSTATUS
NTAPI
NtFreezeRegistry(
__in ULONG TimeOutInSeconds
);

//[Registry]
//NTSTATUS
//NTAPI
//NtInitializeRegistry(
//IN ULONG Options
//);

//[Registry]
//NTSTATUS
//NTAPI
//NtLoadKey(
//IN POBJECT_ATTRIBUTES KeyObjectAttributes,
//IN POBJECT_ATTRIBUTES FileObjectAttributes
//);

//[Registry]
//NTSTATUS
//NTAPI
//NtLoadKey2(
//IN POBJECT_ATTRIBUTES KeyObjectAttributes,
//IN POBJECT_ATTRIBUTES FileObjectAttributes,
//IN ULONG Flags
//);

//[Registry]
//NTSTATUS
//NTAPI
//NtLoadKeyEx(
//__in POBJECT_ATTRIBUTES TargetKey,
//__in POBJECT_ATTRIBUTES SourceFile,
//__in ULONG Flags,
//__in_opt HANDLE TrustClassKey,
//__in PVOID Reserved,
//__in PVOID ObjectContext,
//__in PVOID CallbackReserved,
//__out PIO_STATUS_BLOCK IoStatusBlock
//);

//[Registry]
NTSTATUS
NTAPI
NtLockRegistryKey(
IN HANDLE KeyHandle
);

//[Registry]
//NTSTATUS
//NTAPI
//NtNotifyChangeKey(
//IN HANDLE KeyHandle,
//IN HANDLE Event,
//IN PIO_APC_ROUTINE ApcRoutine OPTIONAL,
//IN PVOID ApcContext OPTIONAL,
//OUT PIO_STATUS_BLOCK IoStatusBlock,
//IN ULONG CompletionFilter,
//IN BOOLEAN WatchTree,
//OUT PVOID Buffer,
//IN ULONG BufferSize,
//IN BOOLEAN Asynchronous
//);

//[Registry]
//NTSTATUS
//NTAPI
//NtNotifyChangeMultipleKeys(
//__in       HANDLE MasterKeyHandle,
//__in_opt   ULONG Count,
//__in_opt   POBJECT_ATTRIBUTES SubordinateObjects,
//__in_opt   HANDLE Event,
//__in_opt   PIO_APC_ROUTINE ApcRoutine,
//__in_opt   PVOID ApcContext,
//__out      PIO_STATUS_BLOCK IoStatusBlock,
//__in       ULONG CompletionFilter,
//__in       BOOLEAN WatchTree,
//__out_opt  PVOID Buffer,
//__in       ULONG BufferSize,
//__in       BOOLEAN Asynchronous
//);

//[Registry]
//NTSTATUS
//NTAPI
//NtOpenKey(
//OUT PHANDLE KeyHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes
//);

//[Registry]
NTSTATUS
NTAPI
NtOpenKeyEx(
__out  PHANDLE KeyHandle,
__in   ACCESS_MASK DesiredAccess,
__in   POBJECT_ATTRIBUTES ObjectAttributes,
__in   ULONG OpenOptions
);

//[Registry]
NTSTATUS
NTAPI
NtOpenKeyTransacted(
__out  PHANDLE KeyHandle,
__in   ACCESS_MASK DesiredAccess,
__in   POBJECT_ATTRIBUTES ObjectAttributes,
__in   HANDLE TransactionHandle
);

//[Registry]
NTSTATUS
NTAPI
NtOpenKeyTransactedEx(
__out  PHANDLE KeyHandle,
__in   ACCESS_MASK DesiredAccess,
__in   POBJECT_ATTRIBUTES ObjectAttributes,
__in   ULONG OpenOptions,
__in   HANDLE TransactionHandle
);

//[Registry]
//NTSTATUS
//NTAPI
//NtQueryKey(
//IN HANDLE KeyHandle,
//IN KEY_INFORMATION_CLASS KeyInformationClass,
//OUT PVOID KeyInformation,
//IN ULONG Length,
//OUT PULONG ResultLength
//);

//[Registry]
//NTSTATUS
//NTAPI
//NtQueryMultipleValueKey(
//IN HANDLE KeyHandle,
//IN PVOID ListOfValuesToQuery,
//IN ULONG NumberOfItems,
//OUT PVOID ValueInformation,
//IN OUT PULONG Length,
//OUT PULONG ReturnLength OPTIONAL
//);

//[Registry]
NTSTATUS
NTAPI
NtQueryOpenSubKeys(
IN POBJECT_ATTRIBUTES TargetKey,
OUT PULONG HandleCount
);

//[Registry]
NTSTATUS
NTAPI
NtQueryOpenSubKeysEx(
IN POBJECT_ATTRIBUTES TargetKey,
IN ULONG BufferLength,
OUT PVOID Buffer,
OUT PULONG ResultLength
);

//[Registry]
//NTSTATUS
//NTAPI
//NtQueryValueKey(
//IN HANDLE KeyHandle,
//IN PUNICODE_STRING ValueName,
//IN KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
//OUT PVOID KeyValueInformation,
//IN ULONG Length,
//OUT PULONG ResultLength
//);

//[Registry]
//NTSTATUS
//NTAPI
//NtRenameKey(
//IN HANDLE KeyHandle,
//IN PUNICODE_STRING ReplacementName
//);

//[Registry]
//NTSTATUS
//NTAPI
//NtReplaceKey(
//IN POBJECT_ATTRIBUTES ObjectAttributes,
//IN HANDLE Key,
//IN POBJECT_ATTRIBUTES ReplacedObjectAttributes
//);

//[Registry]
//NTSTATUS
//NTAPI
//NtRestoreKey(
//IN HANDLE KeyHandle,
//IN HANDLE FileHandle,
//IN ULONG RestoreFlags
//);

//[Registry]
//NTSTATUS
//NTAPI
//NtSaveKey(
//IN HANDLE KeyHandle,
//IN HANDLE FileHandle
//);

//[Registry]
//NTSTATUS
//NTAPI
//NtSaveKeyEx(
//IN HANDLE KeyHandle,
//IN HANDLE FileHandle,
//IN ULONG Flags
//);

//[Registry]
NTSTATUS
NTAPI
NtSaveMergedKeys(
IN HANDLE HighPrecedenceKeyHandle,
IN HANDLE LowPrecedenceKeyHandle,
IN HANDLE FileHandle
);

//[Registry]
//NTSTATUS
//NTAPI
//NtSetInformationKey(
//IN HANDLE KeyHandle,
//IN KEY_SET_INFORMATION_CLASS KeySetInformationClass,
//IN PVOID KeyInformation,
//IN ULONG Length
//);

//[Registry]
//NTSTATUS
//NTAPI
//NtSetValueKey(
//IN HANDLE KeyHandle,
//IN PUNICODE_STRING ValueName,
//IN ULONG TitleIndex OPTIONAL,
//IN ULONG Type,
//IN PVOID Data,
//IN ULONG DataSize
//);

//[Registry]
NTSTATUS
NTAPI
NtThawRegistry(
);

//[Registry]
//NTSTATUS
//NTAPI
//NtUnloadKey(
//IN POBJECT_ATTRIBUTES TargetKey
//);

//[Registry]
NTSTATUS
NTAPI
NtUnloadKey2(
IN POBJECT_ATTRIBUTES TargetKey,
IN ULONG Flags
);

//[Registry]
NTSTATUS
NTAPI
NtUnloadKeyEx(
IN POBJECT_ATTRIBUTES TargetKey,
IN HANDLE Event
);

//[Security]
//NTSTATUS
//NTAPI
//NtAccessCheck(
//IN PSECURITY_DESCRIPTOR SecurityDescriptor,
//IN HANDLE ClientToken,
//IN ACCESS_MASK DesiredAccess,
//IN PGENERIC_MAPPING GenericMapping,
//OUT PPRIVILEGE_SET PrivilegeSet,
//OUT PULONG ReturnLength,
//OUT PACCESS_MASK GrantedAccess,
//OUT PNTSTATUS AccessStatus
//);

//[Security]
//NTSTATUS
//NTAPI
//NtAccessCheckAndAuditAlarm(
//IN PUNICODE_STRING SubsystemName OPTIONAL,
//IN HANDLE ObjectHandle OPTIONAL,
//IN PUNICODE_STRING ObjectTypeName OPTIONAL,
//IN PUNICODE_STRING ObjectName OPTIONAL,
//IN PSECURITY_DESCRIPTOR SecurityDescriptor,
//IN ACCESS_MASK DesiredAccess,
//IN PGENERIC_MAPPING GenericMapping,
//IN BOOLEAN ObjectCreation,
//OUT PACCESS_MASK GrantedAccess,
//OUT PNTSTATUS AccessStatus,
//OUT PBOOLEAN GenerateOnClose
//);

//[Security]
NTSTATUS
NTAPI
NtAccessCheckByType(
IN PSECURITY_DESCRIPTOR SecurityDescriptor,
IN PSID PrincipalSelfSid,
IN HANDLE ClientToken,
IN ACCESS_MASK DesiredAccess,
IN POBJECT_TYPE_LIST ObjectTypeList,
IN ULONG ObjectTypeListLength,
IN PGENERIC_MAPPING GenericMapping,
OUT PPRIVILEGE_SET PrivilegeSet,
OUT PULONG ReturnedLength,
OUT PACCESS_MASK GrantedAccess,
OUT PNTSTATUS AccessStatus
);

//[Security]
NTSTATUS
NTAPI
NtAccessCheckByTypeAndAuditAlarm(
IN PUNICODE_STRING SubsystemName,
IN PVOID HandleId,
IN PUNICODE_STRING ObjectTypeName,
IN PUNICODE_STRING ObjectName,
IN PSECURITY_DESCRIPTOR SecurityDescriptor,
IN PSID PrincipalSelfSid,
IN ACCESS_MASK DesiredAccess,
IN ULONG AuditType,
IN ULONG Flags,
IN POBJECT_TYPE_LIST ObjectTypeList,
IN ULONG ObjectTypeListLength,
IN PGENERIC_MAPPING GenericMapping,
IN BOOLEAN ObjectCreation,
OUT PACCESS_MASK GrantedAccess,
OUT PULONG AccessStatus,
OUT PBOOLEAN GenerateOnClose
);

//[Security]
//NTSTATUS
//NTAPI
//NtAccessCheckByTypeResultList(
//IN PSECURITY_DESCRIPTOR SecurityDescriptor,
//IN PSID PrincipalSelfSid,
//IN HANDLE TokenHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_TYPE_LIST ObjectTypeList,
//IN ULONG ObjectTypeListLength,
//IN PGENERIC_MAPPING GenericMapping,
//IN PPRIVILEGE_SET PrivilegeSet,
//IN ULONG PrivilegeSetLength,
//OUT PACCESS_MASK GrantedAccessList,
//OUT PNTSTATUS AccessStatusList
//);

//[Security]
NTSTATUS
NTAPI
NtAccessCheckByTypeResultListAndAuditAlarm(
IN PUNICODE_STRING SubsystemName,
IN PVOID HandleId,
IN PUNICODE_STRING ObjectTypeName,
IN PUNICODE_STRING ObjectName,
IN PSECURITY_DESCRIPTOR SecurityDescriptor,
IN PSID PrincipalSelfSid,
IN ACCESS_MASK DesiredAccess,
IN ULONG AuditType,
IN ULONG Flags,
IN POBJECT_TYPE_LIST ObjectTypeList,
IN ULONG ObjectTypeListLength,
IN PVOID GenericMapping,
IN BOOLEAN ObjectCreation,
OUT PACCESS_MASK GrantedAccessList,
OUT PNTSTATUS AccessStatusList,
OUT PULONG GenerateOnClose
);

//[Security]
NTSTATUS
NTAPI
NtAccessCheckByTypeResultListAndAuditAlarmByHandle(
IN PUNICODE_STRING SubsystemName,
IN PVOID HandleId,
IN HANDLE TokenHandle,
IN PUNICODE_STRING ObjectTypeName,
IN PUNICODE_STRING ObjectName,
IN PSECURITY_DESCRIPTOR SecurityDescriptor,
IN PSID PrincipalSelfSid,
IN ACCESS_MASK DesiredAccess,
IN AUDIT_EVENT_TYPE AuditType,
IN ULONG Flags,
IN POBJECT_TYPE_LIST ObjectTypeList,
IN ULONG ObjectTypeListLength,
IN PGENERIC_MAPPING GenericMapping,
IN BOOLEAN ObjectCreation,
OUT PACCESS_MASK GrantedAccessList,
OUT PNTSTATUS AccessStatusList,
OUT PULONG GenerateOnClose
);

//[Security]
//NTSTATUS
//NTAPI
//NtAdjustGroupsToken(
//IN HANDLE TokenHandle,
//IN BOOLEAN ResetToDefault,
//IN PTOKEN_GROUPS NewTokenGroups,
//IN ULONG TokenGroupsLength,
//OUT PTOKEN_GROUPS PrevTokenGroups,
//OUT PULONG ReturnedLength OPTIONAL
//);

//[Security]
//NTSTATUS
//NTAPI
//NtAdjustPrivilegesToken(
//IN HANDLE TokenHandle,
//IN BOOLEAN DisableAllPrivileges,
//IN PTOKEN_PRIVILEGES NewState,
//IN ULONG BufferLength,
//OUT PTOKEN_PRIVILEGES PreviousState OPTIONAL,
//OUT PULONG ReturnLength
//);

//[Security]
//NTSTATUS
//NTAPI
//NtCloseObjectAuditAlarm(
//IN PUNICODE_STRING SubsystemName,
//IN HANDLE ObjectHandle OPTIONAL,
//IN BOOLEAN OnClose
//);

//[Security]
//NTSTATUS
//NTAPI
//NtCompareTokens(
//__in   HANDLE FirstTokenHandle,
//__in   HANDLE SecondTokenHandle,
//__out  PBOOLEAN Equal
//);

//[Security]
//NTSTATUS
//NTAPI
//NtCreateToken(
//OUT PHANDLE TokenHandle,
//IN ACCESS_MASK          DesiredAccess,
//IN POBJECT_ATTRIBUTES   ObjectAttributes,
//IN TOKEN_TYPE           TokenType,
//IN PLUID                AuthenticationId,
//IN PLARGE_INTEGER       ExpirationTime,
//IN PTOKEN_USER          TokenUser,
//IN PTOKEN_GROUPS        TokenGroups,
//IN PTOKEN_PRIVILEGES    TokenPrivileges,
//IN PTOKEN_OWNER         TokenOwner,
//IN PTOKEN_PRIMARY_GROUP TokenPrimaryGroup,
//IN PTOKEN_DEFAULT_DACL  TokenDefaultDacl,
//IN PTOKEN_SOURCE        TokenSource
//);

//[Security]
//NTSTATUS
//NTAPI
//NtDeleteObjectAuditAlarm(
//IN PUNICODE_STRING SubsystemName,
//IN HANDLE ObjectHandle OPTIONAL,
//IN BOOLEAN OnClose
//);

//[Security]
//NTSTATUS
//NTAPI
//NtDuplicateToken(
//IN HANDLE ExistingTokenHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes,
//IN BOOLEAN EffectiveOnly,
//IN TOKEN_TYPE TokenType,
//OUT PHANDLE NewTokenHandle
//);

//[Security]
NTSTATUS
NTAPI
NtFilterToken(
IN HANDLE ExistingTokenHandle,
IN ULONG Flags,
IN PTOKEN_GROUPS SidsToDisable OPTIONAL,
IN PTOKEN_PRIVILEGES PrivilegesToDelete OPTIONAL,
IN PTOKEN_GROUPS RestrictedSids OPTIONAL,
OUT PHANDLE NewTokenHandle
);

//[Security]
//NTSTATUS
//NTAPI
//NtImpersonateAnonymousToken(
//IN HANDLE THreadHandle
//);

//[Security]
//NTSTATUS
//NTAPI
//NtImpersonateThread(
//IN HANDLE ThreadHandle,
//IN HANDLE ThreadToImpersonate,
//IN PULONG SecurityQualityOfService
//);

//[Security]
//NTSTATUS
//NTAPI
//NtOpenProcessToken(
//IN HANDLE ProcessHandle,
//IN ACCESS_MASK DesiredAccess,
//OUT PHANDLE TokenHandle
//);

//[Security]
//NTSTATUS
//NTAPI
//NtOpenProcessTokenEx(
//IN HANDLE ProcessHandle,
//IN ACCESS_MASK DesiredAccess,
//IN ULONG HandleAttributes,
//OUT PHANDLE TokenHandle
//);

//[Security]
//NTSTATUS
//NTAPI
//NtOpenThreadToken(
//IN HANDLE ThreadHandle,
//IN ACCESS_MASK DesiredAccess,
//IN BOOL OpenAsSelf,
//OUT PHANDLE TokenHandle
//);

//[Security]
//NTSTATUS
//NTAPI
//NtOpenThreadTokenEx(
//IN HANDLE ThreadHandle,
//IN ACCESS_MASK DesiredAccess,
//IN BOOL OpenAsSelf,
//IN ULONG HandleAttributes,
//OUT PHANDLE TokenHandle
//);

//[Security]
//NTSTATUS
//NTAPI
//NtPrivilegeCheck(
//IN HANDLE TokenHandle,
//IN PPRIVILEGE_SET PrivilegeSet,
//OUT PBOOLEAN HasPrivilege
//);

//[Security]
//NTSTATUS
//NTAPI
//NtPrivilegeObjectAuditAlarm(
//IN PUNICODE_STRING SubsystemName,
//IN PVOID HandleId,
//IN HANDLE TokenHandle,
//IN ACCESS_MASK DesiredAccess,
//IN PPRIVILEGE_SET PrivilegeSet,
//IN BOOLEAN AccessGranted
//);

//[Security]
//NTSTATUS
//NTAPI
//NtPrivilegedServiceAuditAlarm(
//IN PUNICODE_STRING SubsystemName,
//IN PUNICODE_STRING ServiceName,
//IN HANDLE TokenHandle,
//IN PPRIVILEGE_SET PrivilegeSet,
//IN BOOLEAN AccessGranted
//);

//[Security]
//NTSTATUS
//NTAPI
//NtQueryInformationToken(
//IN HANDLE TokenHandle,
//IN TOKEN_INFORMATION_CLASS TokenInformationClass,
//OUT PVOID TokenInformation,
//IN ULONG Length,
//OUT PULONG ReturnLength
//);

//[Security]
NTSTATUS
NTAPI
NtQuerySecurityAttributesToken(
__in HANDLE TokenHandle,
__in PUNICODE_STRING Attributes,
__in ULONG NumberOfAttributes,
__out PVOID Buffer,
__in ULONG Length,
__out PULONG ReturnLength
);

//[Security]
//NTSTATUS
//NTAPI
//NtQuerySecurityObject(
//IN HANDLE Handle,
//IN SECURITY_INFORMATION SecurityInformation,
//OUT PSECURITY_DESCRIPTOR SecurityDescriptor,
//IN ULONG SecurityDescriptorLength,
//OUT PULONG ReturnLength
//);

//[Security]
//NTSTATUS
//NTAPI
//NtSetInformationToken(
//IN HANDLE TokenHandle,
//IN TOKEN_INFORMATION_CLASS Class,
//IN PVOID Buffer,
//IN ULONG BufferLength
//);

//[Security]
//NTSTATUS
//NTAPI
//NtSetSecurityObject(
//IN HANDLE Handle,
//IN SECURITY_INFORMATION SecurityInformation,
//IN PSECURITY_DESCRIPTOR SecurityDescriptor
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtClearEvent(
//IN HANDLE EventHandle
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtCreateEvent(
//OUT PHANDLE EventHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes,
//IN EVENT_TYPE EventType,
//IN BOOLEAN InitialState
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtCreateEventPair(
//OUT PHANDLE EventHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtCreateKeyedEvent(
//OUT PHANDLE KeyedEventHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
//IN ULONG Reserved
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtCreateMutant(
//OUT PHANDLE MutantHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes,
//IN BOOLEAN InitialOwner
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtCreateSemaphore(
//OUT PHANDLE SemaphoreHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes,
//IN LONG InitialCount,
//IN LONG MaxCount
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtOpenEvent(
//OUT PHANDLE EventHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtOpenEventPair(
//OUT PHANDLE EventHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtOpenKeyedEvent(
//OUT PHANDLE KeyedEventHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtOpenMutant(
//OUT PHANDLE MutantHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtOpenSemaphore(
//OUT PHANDLE SemaphoreHandle,
//IN ACCESS_MASK DesiredAccess,
//IN POBJECT_ATTRIBUTES ObjectAttributes
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtPulseEvent(
//IN HANDLE EventHandle,
//OUT PULONG PrevState OPTIONAL
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtQueryEvent(
//IN HANDLE EventHandle,
//IN EVENT_INFORMATION_CLASS EventInformationClass,
//OUT PVOID EventInformation,
//IN ULONG Length,
//OUT PULONG ReturnLength OPTIONAL
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtQueryMutant(
//IN HANDLE MutantHandle,
//IN MUTANT_INFORMATION_CLASS MutantInformationClass,
//OUT PVOID MutantInformation,
//IN ULONG Length,
//OUT PULONG ReturnLength OPTIONAL
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtQuerySemaphore(
//IN HANDLE SemaphoreHandle,
//IN SEMAPHORE_INFORMATION_CLASS SemaphoreInformationClass,
//OUT PVOID SemaphoreInformation,
//IN ULONG Length,
//OUT PULONG ReturnLength OPTIONAL
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtReleaseKeyedEvent(
//IN HANDLE KeyedEventHandle,
//IN PVOID Key,
//IN BOOLEAN Alertable,
//IN PLARGE_INTEGER Timeout OPTIONAL
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtReleaseMutant(
//IN HANDLE MutantHandle,
//OUT PULONG PreviousCount OPTIONAL
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtReleaseSemaphore(
//IN HANDLE SemaphoreHandle,
//IN ULONG Count,
//OUT PULONG PreviousCount OPTIONAL
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtResetEvent(
//IN HANDLE EventHandle,
//OUT PULONG PrevState OPTIONAL
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtSetEvent(
//IN HANDLE EventHandle,
//OUT PULONG PrevState OPTIONAL
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtSetEventBoostPriority(
//IN HANDLE EventHandle
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtSetHighEventPair(
//IN HANDLE EventHandle
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtSetHighWaitLowEventPair(
//IN HANDLE EventHandle
//);

//[Synchronization]
NTSTATUS
NTAPI
NtSetHighWaitLowThread(
);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtSetLowEventPair(
//IN HANDLE EventHandle
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtSetLowWaitHighEventPair(
//IN HANDLE EventHandle
//);

//[Synchronization]
NTSTATUS
NTAPI
NtSetLowWaitHighThread(
);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtSignalAndWaitForSingleObject(
//IN HANDLE SignalHandle,
//IN HANDLE ObjectHandle,
//IN BOOLEAN Alertable,
//IN PLARGE_INTEGER Timeout
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtTraceEvent(
//__in HANDLE TraceHandle,
//__in ULONG Flags,
//__in ULONG FieldSize,
//__in PVOID Fields
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtWaitForKeyedEvent(
//IN HANDLE               KeyedEventHandle,
//IN PVOID                Key,
//IN BOOLEAN              Alertable,
//IN PLARGE_INTEGER       Timeout OPTIONAL
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtWaitForMultipleObjects(
//IN ULONG Count,
//IN PHANDLE Handles,
//IN WAIT_TYPE WaitType,
//IN BOOLEAN Alertable,
//IN PLARGE_INTEGER Timeout OPTIONAL
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtWaitForMultipleObjects32(
//IN ULONG ObjectCount,
//IN PHANDLE Handles,
//IN WAIT_TYPE WaitType,
//IN BOOLEAN Alertable,
//IN PLARGE_INTEGER Timeout OPTIONAL
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtWaitForSingleObject(
//IN HANDLE Handle,
//IN BOOLEAN Alertable,
//IN PLARGE_INTEGER Timeout OPTIONAL
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtWaitHighEventPair(
//IN HANDLE EventHandle
//);

//[Synchronization]
//NTSTATUS
//NTAPI
//NtWaitLowEventPair(
//IN HANDLE EventHandle
//);

//[-Time]
//NTSTATUS
//NTAPI
//NtQuerySystemTime(
//OUT PLARGE_INTEGER SystemTime
//);

//[Time]
//NTSTATUS
//NTAPI
//NtQueryTimer(
//IN HANDLE TimerHandle,
//IN TIMER_INFORMATION_CLASS TimerInformationClass,
//OUT PVOID TimerInformation,
//IN ULONG Length,
//OUT PULONG ReturnLength OPTIONAL
//);

//[Time]
//NTSTATUS
//NTAPI
//NtQueryTimerResolution(
//OUT PULONG MaxTime,
//OUT PULONG MinTime,
//OUT PULONG CurrTime
//);

//[Time]
//NTSTATUS
//NTAPI
//NtSetSystemTime(
//IN PLARGE_INTEGER SystemTime,
//OUT PLARGE_INTEGER PrevSystemTime OPTIONAL
//);

//[Time]
//NTSTATUS
//NTAPI
//NtSetTimerResolution(
//IN ULONG DesiredTime,
//IN BOOLEAN SetResolution,
//OUT PULONG ActualTime
//);

//[Transaction]
NTSTATUS
NTAPI
NtClearAllSavepointsTransaction(
__in HANDLE TransactionHandle
);

//[Transaction]
NTSTATUS
NTAPI
NtClearSavepointTransaction(
__in HANDLE TransactionHandle,
__in ULONG SavePointId
);

//[Transaction]
NTSTATUS
NTAPI
NtCommitComplete(
__in      HANDLE EnlistmentHandle,
__in_opt  PLARGE_INTEGER TmVirtualClock
);

//[Transaction]
NTSTATUS
NTAPI
NtCommitEnlistment(
__in      HANDLE EnlistmentHandle,
__in_opt  PLARGE_INTEGER TmVirtualClock
);

//[Transaction]
NTSTATUS
NTAPI
NtCommitTransaction(
__in  HANDLE TransactionHandle,
__in  BOOLEAN Wait
);

//[Transaction]
NTSTATUS
NTAPI
NtCreateEnlistment(
__out     PHANDLE EnlistmentHandle,
__in      ACCESS_MASK DesiredAccess,
__in      HANDLE ResourceManagerHandle,
__in      HANDLE TransactionHandle,
__in_opt  POBJECT_ATTRIBUTES ObjectAttributes,
__in_opt  ULONG CreateOptions,
__in      NOTIFICATION_MASK NotificationMask,
__in_opt  PVOID EnlistmentKey
);

//[Transaction]
NTSTATUS
NTAPI
NtCreateResourceManager(
__out     PHANDLE ResourceManagerHandle,
__in      ACCESS_MASK DesiredAccess,
__in      HANDLE TmHandle,
__in_opt  PGUID ResourceManagerGuid,
__in_opt  POBJECT_ATTRIBUTES ObjectAttributes,
__in_opt  ULONG CreateOptions,
__in_opt  PUNICODE_STRING Description
);

//[Transaction]
NTSTATUS
NTAPI
NtCreateTransaction(
__out     PHANDLE TransactionHandle,
__in      ACCESS_MASK DesiredAccess,
__in_opt  POBJECT_ATTRIBUTES ObjectAttributes,
__in_opt  PVOID Uow,
__in_opt  HANDLE TmHandle,
__in_opt  ULONG CreateOptions,
__in_opt  ULONG IsolationLevel,
__in_opt  ULONG IsolationFlags,
__in_opt  PLARGE_INTEGER Timeout,
__in_opt  PUNICODE_STRING Description
);

//[Transaction]
NTSTATUS
NTAPI
NtCreateTransactionManager(
__out     PHANDLE TmHandle,
__in      ACCESS_MASK DesiredAccess,
__in_opt  POBJECT_ATTRIBUTES ObjectAttributes,
__in_opt  PUNICODE_STRING LogFileName,
__in_opt  ULONG CreateOptions,
__in_opt  ULONG CommitStrength
);

//[Transaction]
NTSTATUS
NTAPI
NtEnumerateTransactionObject(
__in_opt  HANDLE RootObjectHandle,
__in      KTMOBJECT_TYPE QueryType,
__inout   PKTMOBJECT_CURSOR ObjectCursor,
__in      ULONG ObjectCursorLength,
__out     PULONG ReturnLength
);

//[Transaction]
NTSTATUS
NTAPI
NtFreezeTransactions(
__in PLARGE_INTEGER FreezeTimeout,
__in PLARGE_INTEGER ThawTimeout
);

//[Transaction]
NTSTATUS
NTAPI
NtGetNotificationResourceManager(
__in       HANDLE ResourceManagerHandle,
__out      PTRANSACTION_NOTIFICATION TransactionNotification,
__in       ULONG NotificationLength,
__in       PLARGE_INTEGER Timeout,
__out_opt  PULONG ReturnLength,
__in       ULONG Asynchronous,
__in_opt   ULONG_PTR AsynchronousContext
);

//[Transaction]
NTSTATUS
NTAPI
NtListTransactions(
);

//[Transaction]
NTSTATUS
NTAPI
NtMarshallTransaction(
);

//[Transaction]
NTSTATUS
NTAPI
NtOpenEnlistment(
__out     PHANDLE EnlistmentHandle,
__in      ACCESS_MASK DesiredAccess,
__in      HANDLE RmHandle,
__in      PVOID EnlistmentGuid,
__in_opt  POBJECT_ATTRIBUTES ObjectAttributes
);

//[Transaction]
NTSTATUS
NTAPI
NtOpenResourceManager(
__out     PHANDLE ResourceManagerHandle,
__in      ACCESS_MASK DesiredAccess,
__in      HANDLE TmHandle,
__in      PGUID ResourceManagerGuid,
__in_opt  POBJECT_ATTRIBUTES ObjectAttributes
);

//[Transaction]
NTSTATUS
NTAPI
NtOpenTransaction(
__out     PHANDLE TransactionHandle,
__in      ACCESS_MASK DesiredAccess,
__in_opt  POBJECT_ATTRIBUTES ObjectAttributes,
__in      PVOID Uow,
__in_opt  HANDLE TmHandle
);

//[Transaction]
NTSTATUS
NTAPI
NtOpenTransactionManager(
__out     PHANDLE TmHandle,
__in      ACCESS_MASK DesiredAccess,
__in_opt  POBJECT_ATTRIBUTES ObjectAttributes,
__in_opt  PUNICODE_STRING LogFileName,
__in_opt  PVOID TmIdentity,
__in_opt  ULONG OpenOptions
);

//[Transaction]
NTSTATUS
NTAPI
NtPrePrepareComplete(
__in      HANDLE EnlistmentHandle,
__in_opt  PLARGE_INTEGER TmVirtualClock
);

//[Transaction]
NTSTATUS
NTAPI
NtPrePrepareEnlistment(
__in      HANDLE EnlistmentHandle,
__in_opt  PLARGE_INTEGER TmVirtualClock
);

//[Transaction]
NTSTATUS
NTAPI
NtPrepareComplete(
__in      HANDLE EnlistmentHandle,
__in_opt  PLARGE_INTEGER TmVirtualClock
);

//[Transaction]
NTSTATUS
NTAPI
NtPrepareEnlistment(
__in      HANDLE EnlistmentHandle,
__in_opt  PLARGE_INTEGER TmVirtualClock
);

//[Transaction]
NTSTATUS
NTAPI
NtPropagationComplete(
__in HANDLE ResourceManagerHandle,
__in ULONG RequestCookie,
__in ULONG BufferLength,
__in PVOID Buffer
);

//[Transaction]
NTSTATUS
NTAPI
NtPropagationFailed(
__in HANDLE ResourceManagerHandle,
__in ULONG RequestCookie,
__in NTSTATUS PropStatus
);

//[Transaction]
NTSTATUS
NTAPI
NtPullTransaction(
);

//[Transaction]
NTSTATUS
NTAPI
NtQueryInformationEnlistment(
__in       HANDLE EnlistmentHandle,
__in       ENLISTMENT_INFORMATION_CLASS EnlistmentInformationClass,
__out      PVOID EnlistmentInformation,
__in       ULONG Length,
__out_opt  PULONG ReturnLength
);

//[Transaction]
NTSTATUS
NTAPI
NtQueryInformationResourceManager(
__in       HANDLE ResourceManagerHandle,
__in       RESOURCEMANAGER_INFORMATION_CLASS ResourceManagerInformationClass,
__out      PVOID ResourceManagerInformation,
__in       ULONG Length,
__out_opt  PULONG ReturnLength
);

//[Transaction]
NTSTATUS
NTAPI
NtQueryInformationTransaction(
__in       HANDLE TransactionHandle,
__in       TRANSACTION_INFORMATION_CLASS TransactionInformationClass,
__out      PVOID TransactionInformation,
__in       ULONG Length,
__out_opt  PULONG ReturnLength
);

//[Transaction]
NTSTATUS
NTAPI
NtQueryInformationTransactionManager(
__in       HANDLE TransactionManagerHandle,
__in       TRANSACTIONMANAGER_INFORMATION_CLASS TransactionManagerInformationClass,
__out      PVOID TransactionManagerInformation,
__in       ULONG Length,
__out_opt  PULONG ReturnLength
);

//[Transaction]
NTSTATUS
NTAPI
NtReadOnlyEnlistment(
__in      HANDLE EnlistmentHandle,
__in_opt  PLARGE_INTEGER TmVirtualClock
);

//[Transaction]
NTSTATUS
NTAPI
NtRecoverEnlistment(
__in      HANDLE EnlistmentHandle,
__in_opt  PVOID EnlistmentKey
);

//[Transaction]
NTSTATUS
NTAPI
NtRecoverResourceManager(
__in  HANDLE ResourceManagerHandle
);

//[Transaction]
NTSTATUS
NTAPI
NtRecoverTransactionManager(
__in  HANDLE TransactionManagerHandle
);

//[Transaction]
NTSTATUS
NTAPI
NtRegisterProtocolAddressInformation(
IN HANDLE ResourceManager,
IN PGUID ProtocolId,
IN ULONG ProtocolInformationSize,
IN PVOID ProtocolInformation,
IN ULONG CreateOptions
);

//[Transaction]
NTSTATUS
NTAPI
NtRenameTransactionManager(
__in PUNICODE_STRING LogFileName,
__in PGUID ExistingTransactionManagerGuid
);

//[Transaction]
NTSTATUS
NTAPI
NtRollbackComplete(
__in      HANDLE EnlistmentHandle,
__in_opt  PLARGE_INTEGER TmVirtualClock
);

//[Transaction]
NTSTATUS
NTAPI
NtRollbackEnlistment(
__in      HANDLE EnlistmentHandle,
__in_opt  PLARGE_INTEGER TmVirtualClock
);

//[Transaction]
NTSTATUS
NTAPI
NtRollbackSavepointTransaction(
__in HANDLE TransactionHandle,
__in ULONG SavePointId
);

//[Transaction]
NTSTATUS
NTAPI
NtRollbackTransaction(
__in  HANDLE TransactionHandle,
__in  BOOLEAN Wait
);

//[Transaction]
NTSTATUS
NTAPI
NtRollforwardTransactionManager(
__in      HANDLE TransactionManagerHandle,
__in_opt  PLARGE_INTEGER TmVirtualClock
);

//[Transaction]
NTSTATUS
NTAPI
NtSavepointComplete(
__in      HANDLE TransactionHandle,
__in_opt  PLARGE_INTEGER TmVirtualClock
);

//[Transaction]
NTSTATUS
NTAPI
NtSavepointTransaction(
IN HANDLE TransactionHandle,
IN BOOLEAN Flag,
OUT PULONG SavePointId
);

//[Transaction]
NTSTATUS
NTAPI
NtSetInformationEnlistment(
__in  HANDLE EnlistmentHandle,
__in  ENLISTMENT_INFORMATION_CLASS EnlistmentInformationClass,
__in  PVOID EnlistmentInformation,
__in  ULONG Length
);

//[Transaction]
NTSTATUS
NTAPI
NtSetInformationResourceManager(
__in  HANDLE ResourceManagerHandle,
__in  RESOURCEMANAGER_INFORMATION_CLASS ResourceManagerInformationClass,
__in  PVOID ResourceManagerInformation,
__in  ULONG Length
);

//[Transaction]
NTSTATUS
NTAPI
NtSetInformationTransaction(
__in  HANDLE TransactionHandle,
__in  TRANSACTION_INFORMATION_CLASS TransactionInformationClass,
__in  PVOID TransactionInformation,
__in  ULONG Length
);

//[Transaction]
NTSTATUS
NTAPI
NtSetInformationTransactionManager(
__in  HANDLE TransactionManagerHandle,
__in  TRANSACTIONMANAGER_INFORMATION_CLASS TransactionManagerInformationClass,
__in  PVOID TransactionManagerInformation,
__in  ULONG Length
);

//[Transaction]
NTSTATUS
NTAPI
NtSinglePhaseReject(
__in HANDLE EnlistmentHandle,
__in_opt PLARGE_INTEGER TmVirtualClock
);

//[Transaction]
NTSTATUS
NTAPI
NtStartTm(
);

//[Transaction]
NTSTATUS
NTAPI
NtThawTransactions(
);

//[WOW64]
NTSTATUS
NTAPI
NtWow64CallFunction64(
IN ULONG FunctionIndex,
IN ULONG Flags,
IN ULONG InputBufferLength,
IN PVOID InputBuffer,
IN ULONG OutputBufferLength,
OUT PVOID OutputBuffer,
OUT PULONG ReturnStatus
);

//[WOW64]
NTSTATUS
NTAPI
NtWow64CsrAllocateCaptureBuffer(
ULONG ArgumentCount,
ULONG BufferSize
);

//[WOW64]
NTSTATUS
NTAPI
NtWow64CsrAllocateMessagePointer(
IN PVOID CaptureBuffer,
IN ULONG MessageLength,
OUT PVOID* CaptureData
);

//[WOW64]
NTSTATUS
NTAPI
NtWow64CsrCaptureMessageBuffer(
IN PVOID CaptureBuffer,
IN PVOID MessageBuffer,
IN ULONG MessageLength,
OUT PVOID* CaptureData
);

//[WOW64]
NTSTATUS
NTAPI
NtWow64CsrCaptureMessageString(
IN PVOID CaptureBuffer,
IN PSTR String,
IN ULONG StringLength,
IN ULONG MaximumLength,
OUT PVOID CapturedString
);

//[WOW64]
NTSTATUS
NTAPI
NtWow64CsrClientCallServer(
IN OUT PVOID ApiMessage,
IN OUT PVOID CaptureBuffer OPTIONAL,
IN ULONG ApiNumber,
IN ULONG RequestLength
);

//[WOW64]
NTSTATUS
NTAPI
NtWow64CsrClientConnectToServer(
IN PWSTR ObjectDirectory,
IN ULONG ServerId,
IN PVOID ConnectionInfo,
IN OUT PULONG ConnectionInfoSize,
OUT PBOOLEAN ServerToServerCall
);

//[WOW64]
NTSTATUS
NTAPI
NtWow64CsrFreeCaptureBuffer(
IN PVOID CaptureBuffer
);

//[WOW64]
NTSTATUS
NTAPI
NtWow64CsrGetProcessId(
);

//[WOW64]
NTSTATUS
NTAPI
NtWow64CsrIdentifyAlertableThread(
);

//[WOW64]
NTSTATUS
NTAPI
NtWow64CsrVerifyRegion(
PVOID IN Buffer,
ULONG IN Length
);

//[WOW64]
NTSTATUS
NTAPI
NtWow64DebuggerCall(
ULONG Function,
ULONG Arg1,
ULONG Arg2,
ULONG Arg3,
ULONG arg4
);

//[WOW64]
NTSTATUS
NTAPI
NtWow64GetCurrentProcessorNumberEx(
__out PPROCESSOR_NUMBER ProcNumber
);

//[WOW64]
NTSTATUS
NTAPI
NtWow64GetNativeSystemInformation(
IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
OUT PVOID SystemInformation,
IN ULONG Length,
OUT PULONG ReturnLength OPTIONAL
);

//[WOW64]
NTSTATUS
NTAPI
NtWow64InterlockedPopEntrySList(
__inout PVOID ListHead
);

//[WOW64]
NTSTATUS
NTAPI
NtWow64QueryInformationProcess64(
IN HANDLE ProcessHandle,
IN PROCESSINFOCLASS ProcessInformationClass,
OUT PVOID ProcessInformation64,
IN ULONG Length,
OUT PULONG ReturnLength OPTIONAL
);

//[WOW64]
NTSTATUS
NTAPI
NtWow64QueryVirtualMemory64(
IN HANDLE ProcessHandle,
IN PVOID BaseAddressLow,
IN PVOID BaseAddressHigh,
IN MEMORY_INFORMATION_CLASS MemoryInformationClass,
OUT PVOID MemoryInformation, /* NB must be 64bit aligned */
IN ULONG LengthLow,
IN ULONG LengthHigh,
OUT PULONGLONG ReturnLength OPTIONAL
);

//[WOW64]
NTSTATUS
NTAPI
NtWow64ReadVirtualMemory64(
IN HANDLE ProcessHandle,
IN PVOID AddressLow,
IN PVOID AddressHigh,
OUT PVOID Buffer,
IN ULONG BufferSizeLow,
IN ULONG BufferSizeHigh,
OUT PULONGLONG BytesRead OPTIONAL
);

//[WOW64]
NTSTATUS
NTAPI
NtWow64WriteVirtualMemory64(
IN HANDLE ProcessHandle,
IN PVOID AddressLow,
IN PVOID AddressHigh,
IN PVOID Buffer,
IN ULONG BufferSizeLow,
IN ULONG BufferSizeHigh,
OUT PULONGLONG BytesWritten OPTIONAL
);



#endif
#endif
