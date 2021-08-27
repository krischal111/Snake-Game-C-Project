#include <stdio.h>
#include <windows.h>
#include "Custom Headers\soundthings.h"

int main()
{
    // LPCTSTR = LPCWSTR;
    // LPCWSTR = const WCHAR *
    
    //LPTSTR = LPWSTR;
    //LPWSTR = WCHAR *;
    //WCHAR = wchar_t;
    //wchar_t = unsigned short;

// Thus, LPCTSTR     is constant wide string, LPTSTR    is wide string, LPSTR is string.

    //LPSTR = CHAR *;
    //CHAR = char;

    playtuneusing(gameovertune);
    return 0;
}