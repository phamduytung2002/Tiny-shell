#include <bits/stdc++.h>

#include "../utils.h"
#include "processList.h"

using namespace std;
#pragma once

int kill(string c) {
    // input = dau vao - "kill"
    // kill mot background process

    string arg1, arg2;
    parse(c, arg1, arg2);
    // chuyen tu string sang so
    if (arg1 == ".") {
        for (int i = 0; i < maxprocess; i++) {
            TerminateProcess(pi[i].hProcess, 0);
            processStatus[i] = 200;  // killed
        }
        return 0;
    } else {
        DWORD processId = stringToDWORD(arg1);
        for (int i = 0; i < num_process; ++i) {
            if (pi[i].dwProcessId == processId) {
                if (processStatus[i] == 200) return 2; //process is terminated
                TerminateProcess(pi[i].hProcess, 0);
                processStatus[i] = 200;
                return 0;
            }
        }
        return 2; // cant found process
    }
}
string killDoc = "kill a process with its ID; kill . for kill all.";

// int foregroundMode(string c) {
//     // Shell phải đợi tiến trình kết thúc
//     if (mode = 1) {
//         for (int i = 0; i < maxprocess; i++) {
//             DWORD id = pi[i].dwProcessId;
//             HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, id);
//             TerminateProcess(hProc, 0);
//         }
//     }
//     mode = 0;
//     return 0;
// }
// string foregroundModeDoc = "foregroundMode.";

// int backgroundMode(string c) {
//     // Shell và tiến trình thực hiện song song
//     mode = 1;
//     return 0;
// }
// string backgroundModeDoc = "backgroundMode.";

// DWORD isProcessRunning(HANDLE hProcess) {
//     DWORD dwExitCode = 0;
//     GetExitCodeProcess(hProcess, &dwExitCode);
//     return dwExitCode;
// }

// int numProcessRunning() {
//     int num = 0;
//     for (int i = 0; i < maxprocess; i++) {
//         HANDLE hProc = pi[i].hProcess;
//         DWORD a = isProcessRunning(hProc);
//         if (a == 259) {
//             num++;
//         }
//     }
//     return num;
// }