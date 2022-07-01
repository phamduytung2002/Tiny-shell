#include <bits/stdc++.h>
#include <tlhelp32.h>
#include <unistd.h>
#include <winbase.h>

#include <cstdlib>

#include "../utils.h"
#include "commandList.h"
#include "processList.h"
using namespace std;

// example
int echo(string c) {
    cout << c << endl;
    return 0;
}
string echoDoc = "Just print the argument.";

int exitShell(string c) {
    for (int i = 0; i < maxprocess; i++) {
        DWORD id = pi[i].dwProcessId;
        HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, id);
        TerminateProcess(hProc, 0);
    }
    return 1;
}
string exitShellDoc = "Exit shell.";

int help(string c) {
    cout << "Command list: \n";
    for (auto i = funcmap.begin(); i != funcmap.end(); ++i) {
        string command = i->first;
        string space = command.size() < 8 ? "\t\t" : "\t";
        cout << command << space << i->second.instruction << "\n";
    }
    return 0;
}
string helpDoc = "List all available command.";

int date(string input) {
    time_t t = time(0);  // get time now
    tm* now = localtime(&t);
    cout << now->tm_mday << "/" << now->tm_mon + 1 << "/" << now->tm_year + 1900 << '\n';
    return 0;
}
string dateDoc = "Display today date.";

int timee(string input) {
    time_t t = time(0);  // get time now
    tm* now = localtime(&t);
    cout << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << '\n';
    return 0;
}
string timeDoc = "Display current time.";

int datetime(string input) {
    time_t t = time(0);  // get time now
    tm* now = localtime(&t);
    cout << now->tm_mday << "/" << (now->tm_mon + 1) << "/" << (now->tm_year + 1900) << "  ";
    cout << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "\n";
    return 0;
}
string datetimeDoc = "Display current date and time.";

int resume(string input) {
    string processIdStr = takeFirstArgAndRemove(input);
    DWORD processId = stringToDWORD(processIdStr);

    for (int i = 0; i < maxprocess; ++i) {
        if (pi[i].dwProcessId == processId) {
            ResumeThread(pi[i].hThread);
            processStatus[i] = 0;  // running
            break;
        }
    }
    return 0;
}
string resumeDoc = "Resume a stopped background process.";

int addpath(string input) {
    string a = takeFirstArgAndRemove(input);
    string b = takeFirstArgAndRemove(input);
    putenv((a + "=" + b).c_str());
    return 0;
}
string addpathDoc = "Add/change an environment variable";

int path(string input) {
    cout << getenv(takeFirstArgAndRemove(input).c_str()) << "\n";
    return 0;
}
string pathDoc = "Display an environment variable";

int listpath(string input) {
    function<void(LPTCH)> free = [](LPTCH p) {
        FreeEnvironmentStrings(p);
    };
    unique_ptr<TCHAR, decltype(free)> env_block = unique_ptr<TCHAR, decltype(free)>{
        GetEnvironmentStrings(), free};
    for (LPTCH i = env_block.get(); *i != '\0'; ++i) {
        string key, value;
        for (; *i != '='; ++i) key += *i;
        if (key == "") continue;
        ++i;
        for (; *i != '\0'; ++i) value += *i;

        cout << key;
        for (int i = 0; i < 4 - key.size() / 8; ++i) cout << "\t";
        cout << value << "\n";
    }
    return 0;
}
string listpathDoc = "Display all environment variable";

int delpath(string input) {
    input = takeFirstArgAndRemove(input);
    SetEnvironmentVariable(input.c_str(), NULL);
    return 0;
}
string delpathDoc = "Delete an environment variable";

int cd(string input) {
    chdir(input.c_str());
    return 0;
}
string cdDoc = "Change dir";