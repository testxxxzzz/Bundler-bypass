#include <iostream>
#include <windows.h>
#pragma comment( linker, "/subsystem:windows /entry:mainCRTStartup" )

using namespace std;

static int num = 0;

void EnumTypesFunc(HMODULE hModule, LPTSTR lpType, LPTSTR lParam) {
    num++;
    char* a = new char[10];
    WideCharToMultiByte(CP_OEMCP, NULL, lpType, -1, a, 6, NULL, FALSE);
    string fileType = string(a);

    CHAR PathFileName[MAX_PATH] = { 0 };
    CHAR FileName[MAX_PATH] = { 0 };

    HRSRC Resource = FindResourceA(NULL, MAKEINTRESOURCEA(100 + num), fileType.c_str());
    HGLOBAL ResourceGlobal = LoadResource(NULL, Resource);
    DWORD FileSize = SizeofResource(NULL, Resource);
    LPVOID PFILE = LockResource(ResourceGlobal);
    GetModuleFileNameA(NULL, PathFileName, MAX_PATH);

    strcpy_s(FileName, strrchr(PathFileName, '\\') + 1);
    string FileNameFinal = FileName;
    FileNameFinal.replace(FileNameFinal.rfind('.'), 4, "." + fileType);

    CHAR czTempPath[MAX_PATH] = { 0 };
    GetTempPathA(MAX_PATH, czTempPath);
    FileNameFinal = czTempPath + FileNameFinal;

    strcpy_s(FileName, FileNameFinal.c_str());

    HANDLE FILE = CreateFileA(FileName, FILE_ALL_ACCESS, 0, NULL, CREATE_ALWAYS, 0, NULL);
    DWORD dwSize;
    WriteFile(FILE, PFILE, FileSize, &dwSize, NULL);
    CloseHandle(FILE);


    Sleep(100);
    SHELLEXECUTEINFOA shellexecute = { 0 };
    shellexecute.cbSize = sizeof(shellexecute);
    shellexecute.lpFile = FileName;
    shellexecute.nShow = SW_SHOW;
    ShellExecuteExA(&shellexecute);
}


int main(int argc, char* argv[])
{
    EnumResourceTypes(NULL,
        (ENUMRESTYPEPROC)EnumTypesFunc,
        0);                             
}
