#pragma once
#include <Windows.h>
#include <winternl.h>

typedef NTSTATUS(WINAPI* NtAlloc)(
    HANDLE ProcessHandle,
    PVOID* BaseAddress,
    ULONG_PTR ZeroBits,
    PSIZE_T RegionSize,
    ULONG AllocationType,
    ULONG Protect
    );

typedef NTSTATUS(WINAPI* NtWrite)(
    HANDLE ProcessHandle,
    PVOID BaseAddress,
    PVOID Buffer,
    ULONG NumberOfBytesToWrite,
    PULONG NumberOfBytesWritten
    );

typedef NTSTATUS(WINAPI* NtProtect)(
    HANDLE ProcessHandle,
    PVOID* BaseAddress,
    PSIZE_T RegionSize,
    ULONG NewProtect,
    PULONG OldProtect
    );

typedef NTSTATUS(WINAPI* NtThreadEx)(
    PHANDLE hThread,
    ACCESS_MASK DesiredAccess,
    LPVOID ObjectAttributes,
    HANDLE ProcessHandle,
    LPTHREAD_START_ROUTINE lpStartAddress,
    LPVOID lpParameter,
    BOOL CreateSuspended,
    DWORD dwStackSize,
    DWORD dw1,
    DWORD dw2,
    LPVOID Unknown
    );

// Function pointers resolved at runtime
static NtAlloc NtAllocateVirtualMemory = (NtAlloc)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtAllocateVirtualMemory");
static NtWrite NtWriteVirtualMemory = (NtWrite)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtWriteVirtualMemory");
static NtProtect NtProtectVirtualMemory = (NtProtect)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtProtectVirtualMemory");
static NtThreadEx NtCreateThreadEx = (NtThreadEx)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtCreateThreadEx");
