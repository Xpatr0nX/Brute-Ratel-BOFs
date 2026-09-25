#include <windows.h>
#include <unistd.h>
#include "badger_exports.h"

#define printf(format, args...) { BadgerDispatch(dispatch, format, ## args); }

DECLSPEC_IMPORT DWORD WINAPI Kernel32$GetLastError();
DECLSPEC_IMPORT HANDLE WINAPI Kernel32$CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
DECLSPEC_IMPORT BOOL WINAPI Kernel32$SetFileTime(HANDLE hFile, CONST FILETIME *lpCreationTime, CONST FILETIME *lpLastAccessTime, CONST FILETIME *lpLastWriteTime);
DECLSPEC_IMPORT BOOL WINAPI Kernel32$SystemTimeToFileTime(CONST SYSTEMTIME *lpSystemTime, LPFILETIME lpFileTime);
DECLSPEC_IMPORT BOOL WINAPI Kernel32$CloseHandle(HANDLE hObject);
DECLSPEC_IMPORT int __cdecl Msvcrt$sscanf_s(const char *_Src, const char *_Format, ...);
DECLSPEC_IMPORT int __cdecl Msvcrt$_access(const char *_Filename, int _AccessMode);
