#include "timestamp.h"
/* =========================================================================
 * ported by Xpatr0nX
 * original source: https://github.com/carlnykvist/Timestamp_BOF
 * ========================================================================= */
void coffee(char** argv, int argc, WCHAR** dispatch) {

    if (argc < 2) {
        BadgerDispatch(dispatch, "[!] Usage: coffexec timestamp.o <file_path> \"YYYY-MM-DD HH:MM:SS\"\n[!] Example: coffexec timestamp.o C:\\Windows\\temp\\test.exe \"2023-05-15 14:30:00\"\n");
        return;
    }

    CHAR *file = argv[0];
    CHAR *date = argv[1];
    SYSTEMTIME st;
    FILETIME ft;
    HANDLE hFile = NULL;

    if (Msvcrt$_access(file, F_OK) != 0) {
        BadgerDispatch(dispatch, "[-] File %s does not exist\n", file);
        return;
    }

    int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;
    if (Msvcrt$sscanf_s(date, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) != 6) {
        BadgerDispatch(dispatch, "[-] Invalid date format. Use \"YYYY-MM-DD HH:MM:SS\"\n");
        return;
    }

    st.wYear = (WORD)year;
    st.wMonth = (WORD)month;
    st.wDay = (WORD)day;
    st.wHour = (WORD)hour;
    st.wMinute = (WORD)minute;
    st.wSecond = (WORD)second;
    st.wMilliseconds = 0;
    st.wDayOfWeek = 0;

    if (!Kernel32$SystemTimeToFileTime(&st, &ft)) {
        BadgerDispatch(dispatch, "[-] SystemTimeToFileTime Error: %lu\n", Kernel32$GetLastError());
        return;
    }

    hFile = Kernel32$CreateFileA((LPCSTR)file, FILE_WRITE_ATTRIBUTES, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) {
        if (Kernel32$SetFileTime(hFile, &ft, &ft, &ft)) {
            BadgerDispatch(dispatch, "[+] Timestamp modified successfully for %s -> %s\n", file, date);
        } else {
            BadgerDispatch(dispatch, "[-] SetFileTime Error: %lu\n", Kernel32$GetLastError());
        }
        Kernel32$CloseHandle(hFile);
    } else {
        BadgerDispatch(dispatch, "[-] CreateFileA Error: %lu\n", Kernel32$GetLastError());
    }
}