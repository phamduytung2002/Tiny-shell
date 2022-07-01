#include "esstential.h"

int stop(string input) {
    string processIdStr = takeFirstArgAndRemove(input);
    DWORD processId = stringToDWORD(processIdStr);

    for (auto proc = procList.begin(); proc != procList.end(); ++proc) {
        if (proc->pi.dwProcessId == processId) {
            SuspendThread(proc->pi.hThread);
            proc->processStatus = 300;  // Suspend
            break;
        }
    }
    return 0;
}
string stopDoc = "Stop a background process.";

int resume(string input) {
    string processIdStr = takeFirstArgAndRemove(input);
    DWORD processId = stringToDWORD(processIdStr);

    for (auto proc = procList.begin(); proc != procList.end(); ++proc) {
        if (proc->pi.dwProcessId == processId) {
            ResumeThread(proc->pi.hThread);
            proc->processStatus = 0;  // running
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
        while (!procList.empty()) {
            TerminateProcess(procList.begin()->pi.hProcess, 0);
            procList.pop_front();
        }
        return 0;
    } else {
        DWORD processId = stringToDWORD(arg1);
        for (auto proc = procList.begin(); proc != procList.end(); ++proc) {
            if (proc->pi.dwProcessId == processId) {
                if (proc->processStatus == 200) return 2;  // process is terminated
                TerminateProcess(proc->pi.hProcess, 0);
                procList.erase(proc);
                return 0;
            }
        }
        return 2;  // cant found process
    }
}
string killDoc = "kill a process with its ID; kill . for kill all.";

int listprocess(string input) {
    printf("Process ID\tStatus\t\tFile name\n");
    for (auto proc = procList.begin(); proc != procList.end(); ++proc) {
        HANDLE hProcess = proc->pi.hProcess;
        string this_status;
        if (proc->processStatus == 0)
            this_status = "running";
        else if (proc->processStatus == 300)
            this_status = "suspend";
        CHAR name[1024];
        DWORD a = GetModuleFileNameEx(hProcess, NULL, name, 1024);
        cout << proc->pi.dwProcessId << "\t\t" << this_status << "\t\t" << name << "\n";
    }
    return 0;
}
string listprocessDoc = "Display running process informations.";

int runBatExe(string input) {
    string file = takeFirstArgAndRemove(input);
    string inputs = takeFirstArgAndRemove(input);

    procInfo newProc;
    newProc.processStatus = 0;
    ZeroMemory(&(newProc.si), sizeof(newProc.si));
    newProc.si.cb = sizeof(newProc.si);
    if (!CreateProcess(file.c_str(), NULL, NULL, NULL, FALSE,
                       CREATE_NEW_CONSOLE, NULL, NULL, &(newProc.si), &(newProc.pi)))
        return 2;
    else {
        procList.push_back(newProc);
        if (inputs == "foreground") {
            signal(SIGINT, [](int signum) {
                HANDLE hProc = OpenProcess(PROCESS_TERMINATE, FALSE, procList.end()->pi.dwProcessId);
                TerminateProcess(hProc, 0);
                CloseHandle(hProc);
                procList.pop_back();
            });  // CTRC C to stop this foreground process

            for (auto proc = procList.begin(); proc != procList.end(); ++proc) {
                DWORD id = proc->pi.dwProcessId;
                string ids = to_string(id);
                stop(ids);
            }
            WaitForSingleObject(newProc.pi.hProcess, INFINITE);
            for (auto proc = procList.begin(); proc != procList.end(); ++proc) {
                DWORD id = proc->pi.dwProcessId;
                string idss = to_string(id);
                resume(idss);
            }
        }
        return 0;
    }
}
string runBatExeDoc = "Run a .exe or .bat file in background or foreground mode, can omit 'run'.\n\t\t  To run in foreground mode use '* foreground'.";
