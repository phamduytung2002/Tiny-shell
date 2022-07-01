#include "esstential.h"

int stop(string input) {
    string processIdStr = takeFirstArgAndRemove(input);
    DWORD processId = stringToDWORD(processIdStr);

    for (int i = 0; i < num_process; ++i) {
        if (pi[i].dwProcessId == processId) {
            SuspendThread(pi[i].hThread);
            processStatus[i] = 300;  // Suspend
            break;
        }
    }
    return 0;
}
string stopDoc = "Stop a background process.";

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
                if (processStatus[i] == 200) return 2;  // process is terminated
                TerminateProcess(pi[i].hProcess, 0);
                processStatus[i] = 200;
                return 0;
            }
        }
        return 2;  // cant found process
    }
}
string killDoc = "kill a process with its ID; kill . for kill all.";

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
            signal(SIGINT, [](int signum) {
                HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, pi[num_process - 1].dwProcessId);
                TerminateProcess(hProc, 0);
                CloseHandle(hProc);
            });

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
string runBatExeDoc = "Run a .exe or .bat file in background or foreground mode, can omit 'run'.\n\t\t  To run in foreground mode use '* foreground'.";
