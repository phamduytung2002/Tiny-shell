#include <winbase.h>

#include "../utils.h"
#include "processList.h"

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
string stopDoc = "Stop a background process.";

void signalHandler(int signum) {
    HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, pi[num_process - 1].dwProcessId);
    TerminateProcess(hProc, 0);
    CloseHandle(hProc);
}

int runBatExe(string input) {
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

        if (inputs == "foreground") {
            signal(SIGINT, signalHandler);

            for (int i = 0; i < num_process - 1; i++) {
                DWORD id = pi[i].dwProcessId;
                string ids = to_string(id);
                stop(ids);
            }
            WaitForSingleObject(pi[num_process - 1].hProcess, INFINITE);
            for (int i = 0; i < maxprocess; i++) {
                DWORD id = pi[i].dwProcessId;
                string idss = to_string(id);
                resume(idss);
            }
        }
        return 0;
    }
}
string runBatExeDoc = "Run a .exe file, can omit 'runexe' (draft).";