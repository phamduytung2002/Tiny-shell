#include <bits/stdc++.h>
#include <dirent.h>
#include <tlhelp32.h>
#include <windows.h>
#include <processthreadsapi.h>
using namespace std;

int listprocess(string input) {
    set<string> processList;
    processList.insert("ourShell.exe");
    processList.insert("checkmodule.exe");
    processList.insert("checkthread.exe");
    processList.insert("checkprocess.exe");
    processList.insert("killprocess.exe");
    processList.insert("help.exe");
    processList.insert("Calculator.exe");
    processList.insert("clrscr.exe");
    processList.insert("clock.exe");

    HANDLE hSnapShot = INVALID_HANDLE_VALUE;
    PROCESSENTRY32 ProcessInfo = {0};
    ProcessInfo.dwSize = sizeof(PROCESSENTRY32);
    int count = 0;
    hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    cout<<"listing...\n";
    if (INVALID_HANDLE_VALUE == hSnapShot) {
        cout << "CreatToolhelp32SnapShot Function Failed" << endl;
        cout << "Error No - " << GetLastError() << endl;
    }
    DWORD exitCode = 0;
    while (Process32Next(hSnapShot, &ProcessInfo) != FALSE) {
        if (processList.find(ProcessInfo.szExeFile) == processList.end()) continue;
        cout << "---------------------------------------" << endl;
        cout << "\t PROCESS NO - " << ++count << endl;
        cout << "---------------------------------------" << endl;
        cout << "NO. OF THREAD - " << ProcessInfo.cntThreads << endl;
        cout << "SIZE - " << ProcessInfo.dwSize << endl;
        cout << "BASE PRIORITY - " << ProcessInfo.pcPriClassBase << endl;
        wcout << "EXECUTABLE FILE - " << ProcessInfo.szExeFile << endl;
        cout << "PPID - " << ProcessInfo.th32ParentProcessID << endl;
        cout << "PPID - " << ProcessInfo.th32ProcessID << endl;
    }
    CloseHandle(hSnapShot);
    return 0;
}
string listprocessDoc = "Display running process informations.";

int dir(string input) {
    string path = filesystem::current_path().string();
    DIR* dir;
    dirent* pdir;
    vector<string> files;
    dir = opendir(path.c_str());
    while (pdir = readdir(dir)) {
        files.push_back(pdir->d_name);
    }
    for (int i = 0; i < files.size(); ++i) {
        cout << files[i] << '\n';
    }
    return 0;
}
string dirDoc = "List all directory.";