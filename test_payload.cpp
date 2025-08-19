
#include <Windows.h>

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        MessageBoxA(NULL, "PhantomBlack DLL Loaded", "Success", MB_OK | MB_ICONINFORMATION);
    }
    return TRUE;
}
