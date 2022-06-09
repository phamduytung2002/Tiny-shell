#include <bits/stdc++.h>
#include <tlhelp32.h>
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
    // Need to kill all process
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


int stop(string input) {
    string processIdStr = takeFirstArgAndRemove(input);
    DWORD processId = stringToDWORD(processIdStr);

    HANDLE hThreadSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    THREADENTRY32 threadEntry;
    threadEntry.dwSize = sizeof(THREADENTRY32);
    Thread32First(hThreadSnapshot, &threadEntry);
    do {
        if (threadEntry.th32OwnerProcessID == processId) {
            HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, threadEntry.th32ThreadID);
            SuspendThread(hThread);
            CloseHandle(hThread);
        }
    } while (Thread32Next(hThreadSnapshot, &threadEntry));

    CloseHandle(hThreadSnapshot);
    return 0;
}
string stopDoc = "Stop a background process (draft).";

int listprocess(string input) {
    for (int i = 0; i < num_process; ++i) {
        cout << pi[i].dwProcessId << " " << pi[i].dwThreadId << endl;
    }
    return 0;
}
string listprocessDoc = "All running process information.";

int resume(string input) {
    string processIdStr = takeFirstArgAndRemove(input);
    DWORD processId = stringToDWORD(processIdStr);

    for (int i = 0; i < maxprocess; ++i) {
        if (pi[i].dwProcessId == processId) {
            ResumeThread(pi[i].hThread);
            break;
        }
    }
    return 0;
}
string resumeDoc = "Resume a stopped background process.";
/*
int addpath(string input) {
    string a = takeFirstArgAndRemove(input);
    string b = takeFirstArgAndRemove(input);
    putenv((a + "=" + b).c_str());
    return 0;
}
string addpathDoc = "Add/change an environment variable";
*/
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


int runExe(string input) {
    if (num_process == maxprocess) return 2;
    string file = takeFirstArgAndRemove(input);
    string inputs = takeFirstArgAndRemove(input);
    
    
    ZeroMemory(&si[num_process], sizeof(si[num_process]));
    si[num_process].cb = sizeof(si[num_process]);
    if (!CreateProcess(file.c_str(), NULL, NULL, NULL, FALSE,
                       CREATE_NEW_CONSOLE, NULL, NULL, &si[num_process], &pi[num_process]))
        return 2;
    else {
        ++num_process;
        
        if ( inputs == "foreground"){
            for (int i = 0; i < num_process-1 ; i++) {
                    DWORD id = pi[i].dwProcessId;
                    string ids = to_string(id);
                    stop(ids);
                }
            WaitForSingleObject(pi[num_process-1].hProcess,INFINITE);
            for (int i = 0; i < maxprocess; i++) {
                DWORD id = pi[i].dwProcessId;
                string idss = to_string(id);
                resume(idss);
                }
            }




        //     DWORD a = isProcessRunning(pi[num_process-1].hProcess);
        //     if (a == STILL_ACTIVE){
        //         for (int i = 0; i < num_process-1 ; i++) {
        //             DWORD id = pi[i].dwProcessId;
        //             string ids = to_string(id);
        //             stop(ids);
        //         }
        //         /*
        //         DWORD id_system =  GetCurrentProcessId();
        //         string ids = to_string(id_system);
        //         stop(ids);
        //         */
        //     }
            
        //     else{
        //         //WaitForSingleObject(pi[num_process-1], INT_MAX);
        //         for (int i = 0; i < maxprocess; i++) {
        //             DWORD id = pi[i].dwProcessId;
        //             string idss = to_string(id);
        //             resume(idss);
        //         }

        //         //DWORD id_system =  GetCurrentProcessId();
        //         //string ids = to_string(id_system);
        //         //resume(ids);
        //     }
            
        // }           
                    
            /*
            while(a == STILL_ACTIVE);
             
            */
        return 0;
    }
}

string runExeDoc = "Run a .exe file, can omit 'runexe' (draft).";