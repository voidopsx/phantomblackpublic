#pragma once
#include <Windows.h>
#include <vector>
#include "Utils.h"

inline DWORD GetImageSize(BYTE* imageBase) {
    PIMAGE_DOS_HEADER dos = (PIMAGE_DOS_HEADER)imageBase;
    PIMAGE_NT_HEADERS nt = (PIMAGE_NT_HEADERS)(imageBase + dos->e_lfanew);
    return nt->OptionalHeader.SizeOfImage;
}

inline DWORD GetEntryPointOffset(BYTE* imageBase) {
    PIMAGE_DOS_HEADER dos = (PIMAGE_DOS_HEADER)imageBase;
    PIMAGE_NT_HEADERS nt = (PIMAGE_NT_HEADERS)(imageBase + dos->e_lfanew);
    return nt->OptionalHeader.AddressOfEntryPoint;
}

inline BYTE* MapImageToMemory(BYTE* rawData) {
    PIMAGE_DOS_HEADER dos = (PIMAGE_DOS_HEADER)rawData;
    if (dos->e_magic != IMAGE_DOS_SIGNATURE) return nullptr;

    PIMAGE_NT_HEADERS nt = (PIMAGE_NT_HEADERS)(rawData + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE) return nullptr;

    BYTE* mapped = (BYTE*)VirtualAlloc(nullptr, nt->OptionalHeader.SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!mapped) return nullptr;

    memcpy(mapped, rawData, nt->OptionalHeader.SizeOfHeaders);

    PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION(nt);
    for (WORD i = 0; i < nt->FileHeader.NumberOfSections; ++i, ++section) {
        memcpy(mapped + section->VirtualAddress,
               rawData + section->PointerToRawData,
               section->SizeOfRawData);
    }

    // NOTE: This does not perform relocations or IAT fix — for public release only
    return mapped;
}
