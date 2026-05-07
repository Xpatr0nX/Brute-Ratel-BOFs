#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "badger_exports.h"

/* =========================================================================
 * by Xpatr0nX
 * Utilize the built-in C:\Windows\System32\tar.exe
 * ========================================================================= */

DECLSPEC_IMPORT WINBASEAPI BOOL WINAPI KERNEL32$CreateProcessA(LPCSTR lpApplicationName, LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation);
DECLSPEC_IMPORT WINBASEAPI DWORD WINAPI KERNEL32$WaitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds);
DECLSPEC_IMPORT WINBASEAPI BOOL WINAPI KERNEL32$CloseHandle(HANDLE hObject);
DECLSPEC_IMPORT WINBASEAPI DWORD WINAPI KERNEL32$GetLastError(VOID);
DECLSPEC_IMPORT WINUSERAPI int WINAPI USER32$wsprintfA(LPSTR, LPCSTR, ...);

void coffee(char **argv, int argc, WCHAR **dispatch) {
    if (argc < 2) {
        BadgerDispatch(dispatch, "[-] Usage: coffexec compress_zip.o {source_folder_or_file} {output.zip}\n");
        return;
    }

    char *sourcePath = argv[0];
    char *destZip = argv[1];
    char cmdLine[MAX_PATH * 3];

    USER32$wsprintfA(cmdLine, "tar.exe -a -c -f \"%s\" \"%s\"", destZip, sourcePath);

    BadgerDispatch(dispatch, "[+] Compressing file or folder %s\n");

    STARTUPINFOA si = {0};
    PROCESS_INFORMATION pi = {0};
    si.cb = sizeof(si);

    BOOL success = KERNEL32$CreateProcessA(
        NULL, 
        cmdLine, 
        NULL, 
        NULL, 
        FALSE, 
        CREATE_NO_WINDOW,
        NULL, 
        NULL, 
        &si, 
        &pi
    );

    if (success) {
        BadgerDispatch(dispatch, "[+] Process spawned (PID: %d). Waiting for compression...\n", pi.dwProcessId);
        
        DWORD waitResult = KERNEL32$WaitForSingleObject(pi.hProcess, 60001);
        
        if (waitResult == WAIT_OBJECT_0) {
            BadgerDispatch(dispatch, "[+] Compression completed: %s\n", destZip);
        } else if (waitResult == WAIT_TIMEOUT) {
            BadgerDispatch(dispatch, "[-] Compression taking too long (Timeout > 60s). It may still be running in the background.\n");
        } else {
            BadgerDispatch(dispatch, "[-] Process execution failed.\n");
        }

        KERNEL32$CloseHandle(pi.hProcess);
        KERNEL32$CloseHandle(pi.hThread);
    } else {
        BadgerDispatch(dispatch, "[-] Failed to execute tar.exe. Error: %d\n", KERNEL32$GetLastError());
    }
}
