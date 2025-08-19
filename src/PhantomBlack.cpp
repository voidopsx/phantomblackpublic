#include <windows.h>
#include <winternl.h>
#include <iostream>
#include <fstream>

#include "../include/PEParser.h"
#include "../include/Syscalls.h"
#include "../include/Utils.h"

#pragma comment(lib, "ntdll.lib")

#pragma comment(lib, "ntdll.lib")

bool LoadDLLToMemory(LPCSTR path) {
    std::vector<BYTE> dllData;
    if (!ReadFileToMemory(path, dllData)) {
        LOG("[-] Failed to read DLL from disk.");
        return false;
    }

    BYTE* localImage = MapImageToMemory(dllData.data());
    if (!localImage) {
        LOG("[-] Failed to map image to local memory.");
        return false;
    }

    LPVOID remoteImage = VirtualAlloc(nullptr, GetImageSize(dllData.data()), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!remoteImage) {
        LOG("[-] Failed to allocate memory in remote process.");
        return false;
    }

    memcpy(remoteImage, localImage, GetImageSize(dllData.data()));
    LOG("[+] DLL mapped reflectively to memory.");

    DWORD entryOffset = GetEntryPointOffset(dllData.data());
    if (!entryOffset) {
        LOG("[-] Failed to get EntryPoint.");
        return false;
    }

    LPTHREAD_START_ROUTINE entry = (LPTHREAD_START_ROUTINE)((BYTE*)remoteImage + entryOffset);
    HANDLE hThread = CreateThread(nullptr, 0, entry, nullptr, 0, nullptr);
    if (!hThread) {
        LOG("[-] Failed to create thread.");
        return false;
    }

    LOG("[+] Thread created. DLL is executing.");
    WaitForSingleObject(hThread, INFINITE);
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: PhantomBlack.exe <path_to_dll>" << std::endl;
        return 1;
    }

    if (LoadDLLToMemory(argv[1])) {
        LOG("[*] Done.");
    } else {
        LOG("[-] Execution failed.");
    }

    return 0;
}
