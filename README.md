[README.md](https://github.com/user-attachments/files/21846092/README.md)
<h1 align="center">🕷️ PhantomBlackPublic</h1>
<p align="center">
  <b>Reflective DLL Loader · Manual PE Mapping · Red Team Injection Tool</b><br>
  <code>APT-Class | Clean | Undetectable | Precision Payload Delivery</code>
</p>

---

## 🔥 Overview

**PhantomBlackPublic** is a red-team-grade reflective DLL loader that performs **manual PE mapping** and memory-based DLL injection without using `LoadLibrary` or dropping files to disk.  
It's clean, surgical, and mimics the behavior of advanced threat actors (APT) while being suitable for public demonstration and education.

Built for operators who want public tools that still command respect.

---

## 🧬 Techniques Used (APT-Level)

| Technique | Description |
|----------|-------------|
| 🧠 Reflective DLL Injection | Loads DLL into memory directly and triggers its entry point. |
| 🧩 Manual PE Mapping | Parses PE headers, maps sections manually, processes relocations. |
| 🔗 EntryPoint Thread Execution | Calls DLL entry using `CreateThread`. |
| ❌ No LoadLibrary / No GetProcAddress | Evades common API tracing and userland hooking. |
| 📦 Memory-Only Execution | Allocates memory using `VirtualAlloc` and writes with `memcpy`. |
| 🧪 Header Parsing | Uses custom `PEParser` logic instead of OS loader. |
| 🪓 Optional PE Header Wipe | Simulates stealth behavior post-injection. |
| 🧷 Modular Header Structure | Organized with `Utils`, `Syscalls`, `PEParser`. |
| 🖥️ CLI Compatible | Operated via terminal for automation and scripting. |

These mimic the early stages of custom APT loaders, with controlled visibility and modular extensibility.

---

## 📂 Project Structure

```
phantomblackpublic/
├── include/
│   ├── PEParser.h        # PE parsing and mapping
│   ├── Syscalls.h        # NT function resolution
│   └── Utils.h           # Logging + file reader
├── payloads/
│   ├── test_payload.cpp  # Payload source (MessageBox)
│   └── payload.dll       # DLL compiled from above
├── src/
│   └── PhantomBlack.cpp  # Main loader logic
├── output/
│   └── PhantomBlackPublic.exe
├── build.bat
└── README.md
```

---

## ⚙️ Build Instructions

### 🧱 Compile Loader:

1. Open Visual Studio
2. Add `src/PhantomBlack.cpp`
3. Set configuration:
   - `x64`
   - `Release`
   - Configuration Type: `Application (.exe)`
4. Output: `output/PhantomBlackPublic.exe`

### 🔬 Compile Payload DLL:

1. Create `test_payload.cpp` with:
```cpp
#include <Windows.h>
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        MessageBoxA(NULL, "PhantomBlack DLL Loaded", "Payload Executed", MB_OK);
    }
    return TRUE;
}
```
2. Configuration Type: `Dynamic Library (.dll)`
3. Output: `payloads/payload.dll`

---

## 🚀 Execution

Open terminal and run:

```cmd
cd phantomblackpublic/output
PhantomBlackPublic.exe ../payloads/payload.dll
```

✅ If mapped correctly, you’ll see:
```
[+] DLL mapped reflectively to memory.
[+] Thread created. DLL is executing.
[*] Done.
```

🔔 If your DLL uses `MessageBoxA`, a pop-up will confirm successful payload execution.

---

## 🧪 Test Environment

| System        | Status     |
|---------------|------------|
| Windows 10 x64 | ✅ Passed |
| Defender      | ✅ No alert |
| Sysmon        | ⚠️ Detectable by memory pattern (can be obfuscated) |
| AV Scan       | ✅ Clean (public version) |

---

## 📛 Author

**Hugo Gabriel “Starls”**  
Operator of `GhostMind APT-Class`  
⚙️ `Built under GhostOps-X mode`  
💀 _"You don’t load payloads. You surgically map them into memory."_

---

## 🛡 Disclaimer

This repository is for **educational and red team simulation** purposes only.  
Do not use in unauthorized environments.  
The author assumes no responsibility for any misuse.

> If you're reading this, you're already inside.
