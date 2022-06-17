#include <bits/stdc++.h>
#include <dirent.h>
#include <processthreadsapi.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <windows.h>
using namespace std;

int listprocess(string input) {
    printf("Process ID\tStatus\tFile name\n");
    for (int i = 0; i < num_process; ++i) {
        HANDLE hProcess = pi[i].hProcess;
        string this_status;
        if (processStatus[i] == 0)
            this_status = "running";
        else if (processStatus[i] == 300)
            this_status = "suspend";
        else if (processStatus[i] == 200)
            continue;
        CHAR name[1024];
        DWORD a = GetModuleFileNameEx(hProcess, NULL, name, 1024);
        cout << pi[i].dwProcessId << "\t" << this_status << "\t" << name << "\n";
    }
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