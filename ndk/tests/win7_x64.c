/* Version definitions */
#undef NTDDI_VERSION
#define NTDDI_VERSION NTDDI_WIN7
#undef _WIN32_WINNT
#define _WIN32_WINNT _WIN32_WINNT_WIN7

#include <ndk/ntifs.h>
#include <ndk/ndk/ntndk.h>

#define C_ASSERT_FIELD(Type, Offset, MemberType, MemberName) C_ASSERT(FIELD_OFFSET(Type, MemberName) == Offset);

/* KTHREAD */

C_ASSERT_FIELD(KTHREAD, 0x000, DISPATCHER_HEADER, Header)
C_ASSERT_FIELD(KTHREAD, 0x018, ULONG64, CycleTime)
C_ASSERT_FIELD(KTHREAD, 0x020, ULONG64, QuantumTarget)
C_ASSERT_FIELD(KTHREAD, 0x028, PVOID, InitialStack)
C_ASSERT_FIELD(KTHREAD, 0x030, PVOID, StackLimit)
C_ASSERT_FIELD(KTHREAD, 0x038, PVOID, KernelStack)
C_ASSERT_FIELD(KTHREAD, 0x040, ULONG64, ThreadLock)
C_ASSERT_FIELD(KTHREAD, 0x048, KWAIT_STATUS_REGISTER, WaitRegister)
C_ASSERT_FIELD(KTHREAD, 0x049, UCHAR, Running)
C_ASSERT_FIELD(KTHREAD, 0x04A, UCHAR, Alerted)
C_ASSERT_FIELD(KTHREAD, 0x04C, LONG, MiscFlags)
C_ASSERT_FIELD(KTHREAD, 0x050, KAPC_STATE, ApcState)
C_ASSERT_FIELD(KTHREAD, 0x050, UCHAR, ApcStateFill)
C_ASSERT_FIELD(KTHREAD, 0x07B, CHAR, Priority)
C_ASSERT_FIELD(KTHREAD, 0x07C, ULONG, NextProcessor)
C_ASSERT_FIELD(KTHREAD, 0x080, ULONG, DeferredProcessor)
C_ASSERT_FIELD(KTHREAD, 0x088, ULONG64, ApcQueueLock)
C_ASSERT_FIELD(KTHREAD, 0x090, LONG64, WaitStatus)
C_ASSERT_FIELD(KTHREAD, 0x098, KWAIT_BLOCK*, WaitBlockList)
C_ASSERT_FIELD(KTHREAD, 0x0A0, LIST_ENTRY, WaitListEntry)
C_ASSERT_FIELD(KTHREAD, 0x0A0, SINGLE_LIST_ENTRY, SwapListEntry)
C_ASSERT_FIELD(KTHREAD, 0x0B0, KQUEUE*, Queue)
C_ASSERT_FIELD(KTHREAD, 0x0B8, PVOID, Teb)
C_ASSERT_FIELD(KTHREAD, 0x0C0, KTIMER, Timer)
C_ASSERT_FIELD(KTHREAD, 0x100, LONG, ThreadFlags)
C_ASSERT_FIELD(KTHREAD, 0x104, ULONG, Spare0)
C_ASSERT_FIELD(KTHREAD, 0x108, KWAIT_BLOCK, WaitBlock)
C_ASSERT_FIELD(KTHREAD, 0x108, UCHAR, WaitBlockFill4)
C_ASSERT_FIELD(KTHREAD, 0x134, ULONG, ContextSwitches)
C_ASSERT_FIELD(KTHREAD, 0x108, UCHAR, WaitBlockFill5)
C_ASSERT_FIELD(KTHREAD, 0x164, UCHAR, State)
C_ASSERT_FIELD(KTHREAD, 0x165, CHAR, NpxState)
C_ASSERT_FIELD(KTHREAD, 0x166, UCHAR, WaitIrql)
C_ASSERT_FIELD(KTHREAD, 0x167, CHAR, WaitMode)
C_ASSERT_FIELD(KTHREAD, 0x108, UCHAR, WaitBlockFill6)
C_ASSERT_FIELD(KTHREAD, 0x194, ULONG, WaitTime)
C_ASSERT_FIELD(KTHREAD, 0x108, UCHAR, WaitBlockFill7)
C_ASSERT_FIELD(KTHREAD, 0x1B0, PVOID, TebMappedLowVa)
C_ASSERT_FIELD(KTHREAD, 0x1B8, UMS_CONTROL_BLOCK*, Ucb)
C_ASSERT_FIELD(KTHREAD, 0x108, UCHAR, WaitBlockFill8)
C_ASSERT_FIELD(KTHREAD, 0x1C4, SHORT, KernelApcDisable)
C_ASSERT_FIELD(KTHREAD, 0x1C6, SHORT, SpecialApcDisable)
C_ASSERT_FIELD(KTHREAD, 0x1C4, ULONG, CombinedApcDisable)
C_ASSERT_FIELD(KTHREAD, 0x1C8, LIST_ENTRY, QueueListEntry)
C_ASSERT_FIELD(KTHREAD, 0x1D8, KTRAP_FRAME*, TrapFrame)
C_ASSERT_FIELD(KTHREAD, 0x1E0, PVOID, FirstArgument)
C_ASSERT_FIELD(KTHREAD, 0x1E8, PVOID, CallbackStack)
C_ASSERT_FIELD(KTHREAD, 0x1E8, ULONG64, CallbackDepth)
C_ASSERT_FIELD(KTHREAD, 0x1F0, UCHAR, ApcStateIndex)
C_ASSERT_FIELD(KTHREAD, 0x1F1, CHAR, BasePriority)
C_ASSERT_FIELD(KTHREAD, 0x1F2, CHAR, PriorityDecrement)
C_ASSERT_FIELD(KTHREAD, 0x1F3, UCHAR, Preempted)
C_ASSERT_FIELD(KTHREAD, 0x1F4, UCHAR, AdjustReason)
C_ASSERT_FIELD(KTHREAD, 0x1F5, CHAR, AdjustIncrement)
C_ASSERT_FIELD(KTHREAD, 0x1F6, CHAR, PreviousMode)
C_ASSERT_FIELD(KTHREAD, 0x1F7, CHAR, Saturation)
C_ASSERT_FIELD(KTHREAD, 0x1F8, ULONG, SystemCallNumber)
C_ASSERT_FIELD(KTHREAD, 0x1FC, ULONG, FreezeCount)
C_ASSERT_FIELD(KTHREAD, 0x200, GROUP_AFFINITY, UserAffinity)
C_ASSERT_FIELD(KTHREAD, 0x210, KPROCESS*, Process)
C_ASSERT_FIELD(KTHREAD, 0x218, GROUP_AFFINITY, Affinity)
C_ASSERT_FIELD(KTHREAD, 0x228, ULONG, IdealProcessor)
C_ASSERT_FIELD(KTHREAD, 0x22C, ULONG, UserIdealProcessor)
C_ASSERT_FIELD(KTHREAD, 0x230, KAPC_STATE*, ApcStatePointer)
C_ASSERT_FIELD(KTHREAD, 0x240, KAPC_STATE, SavedApcState)
C_ASSERT_FIELD(KTHREAD, 0x240, UCHAR, SavedApcStateFill)
C_ASSERT_FIELD(KTHREAD, 0x26B, UCHAR, WaitReason)
C_ASSERT_FIELD(KTHREAD, 0x26C, CHAR, SuspendCount)
C_ASSERT_FIELD(KTHREAD, 0x26D, CHAR, Spare1)
C_ASSERT_FIELD(KTHREAD, 0x26E, UCHAR, CodePatchInProgress)
C_ASSERT_FIELD(KTHREAD, 0x270, PVOID, Win32Thread)
C_ASSERT_FIELD(KTHREAD, 0x278, PVOID, StackBase)
C_ASSERT_FIELD(KTHREAD, 0x280, KAPC, SuspendApc)
C_ASSERT_FIELD(KTHREAD, 0x280, UCHAR, SuspendApcFill0)
C_ASSERT_FIELD(KTHREAD, 0x281, UCHAR, ResourceIndex)
C_ASSERT_FIELD(KTHREAD, 0x280, UCHAR, SuspendApcFill1)
C_ASSERT_FIELD(KTHREAD, 0x283, UCHAR, QuantumReset)
C_ASSERT_FIELD(KTHREAD, 0x280, UCHAR, SuspendApcFill2)
C_ASSERT_FIELD(KTHREAD, 0x284, ULONG, KernelTime)
C_ASSERT_FIELD(KTHREAD, 0x280, UCHAR, SuspendApcFill3)
C_ASSERT_FIELD(KTHREAD, 0x2C0, KPRCB*, WaitPrcb)
C_ASSERT_FIELD(KTHREAD, 0x280, UCHAR, SuspendApcFill4)
C_ASSERT_FIELD(KTHREAD, 0x2C8, PVOID, LegoData)
C_ASSERT_FIELD(KTHREAD, 0x280, UCHAR, SuspendApcFill5)
C_ASSERT_FIELD(KTHREAD, 0x2D3, UCHAR, LargeStack)
C_ASSERT_FIELD(KTHREAD, 0x2D4, ULONG, UserTime)
C_ASSERT_FIELD(KTHREAD, 0x2D8, KSEMAPHORE, SuspendSemaphore)
C_ASSERT_FIELD(KTHREAD, 0x2D8, UCHAR, SuspendSemaphorefill)
C_ASSERT_FIELD(KTHREAD, 0x2F4, ULONG, SListFaultCount)
C_ASSERT_FIELD(KTHREAD, 0x2F8, LIST_ENTRY, ThreadListEntry)
C_ASSERT_FIELD(KTHREAD, 0x308, LIST_ENTRY, MutantListHead)
C_ASSERT_FIELD(KTHREAD, 0x318, PVOID, SListFaultAddress)
C_ASSERT_FIELD(KTHREAD, 0x320, LONG64, ReadOperationCount)
C_ASSERT_FIELD(KTHREAD, 0x328, LONG64, WriteOperationCount)
C_ASSERT_FIELD(KTHREAD, 0x330, LONG64, OtherOperationCount)
C_ASSERT_FIELD(KTHREAD, 0x338, LONG64, ReadTransferCount)
C_ASSERT_FIELD(KTHREAD, 0x340, LONG64, WriteTransferCount)
C_ASSERT_FIELD(KTHREAD, 0x348, LONG64, OtherTransferCount)
C_ASSERT_FIELD(KTHREAD, 0x350, KTHREAD_COUNTERS*, ThreadCounters)
C_ASSERT_FIELD(KTHREAD, 0x358, XSTATE_SAVE*, XStateSave)