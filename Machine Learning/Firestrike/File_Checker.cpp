// Matthew Bringle
// File space checkers
//included in this file:
/*

std::wstring getCurrentDirectory()
std::vector<std::string> listFilesInDirectory() 




#ifndef File_Checker
#define File_Checker

//must include:
#include <windows.h>
#include <string>
#include <vector>

// states current directory 
// NOTE: Uses wstring!
std::wstring getCurrentDirectory() {
    WCHAR buffer[MAX_PATH];
    GetModuleFileNameW(NULL, buffer, MAX_PATH);
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
    return std::wstring(buffer).substr(0, pos);
}


// This function returns a vector that contains all the files in the current directory
std::vector<std::string> listFilesInDirectory() {
    std::vector<std::string> fileList;
    WIN32_FIND_DATAA fileData;
    HANDLE hFind;
    char path[MAX_PATH];

    GetCurrentDirectoryA(MAX_PATH, path); // Get current directory path

    strcat_s(path, "\\*"); // Append wildcard to path

    hFind = FindFirstFileA(path, &fileData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                fileList.push_back(fileData.cFileName);
            }
        } while (FindNextFileA(hFind, &fileData));
        FindClose(hFind);
    }
    return fileList;
}




#endif

*/