#include "essential.hpp"

int stop(string input) {
    string processIdStr = takeFirstArgAndRemove(input);
    DWORD processId = stringToDWORD(processIdStr);

    for (auto proc = backProcList.begin(); proc != backProcList.end(); ++proc) {
        if (proc->pi.dwProcessId == processId) {
            if (proc->processStatus == 0) {
                SuspendThread(proc->pi.hThread);
                proc->processStatus = 300;  // Suspend
                return 0;
            } else
                return 2;
        }
    }
    return 2;
}
string stopDoc = "Stop a background process.\n\t\t  Usage: stop <process ID>.";

int resume(string input) {
    string processIdStr = takeFirstArgAndRemove(input);
    DWORD processId = stringToDWORD(processIdStr);

    for (auto proc = backProcList.begin(); proc != backProcList.end(); ++proc) {
        if (proc->pi.dwProcessId == processId) {
            if (proc->processStatus == 300) {
                ResumeThread(proc->pi.hThread);
                proc->processStatus = 0;  // running
                return 0;
            } else
                return 2;
        }
    }
    return 2;
}
string resumeDoc = "Resume a stopped background process.\n\t\t  Usage: 'resume <process ID>'.";

int kill(string c) {
    // input = dau vao - "kill"
    // kill mot background process

    string arg1, arg2;
    parse(c, arg1, arg2);
    // chuyen tu string sang so
    if (arg1 == ".") {
        while (!backProcList.empty()) {
            TerminateProcess(backProcList.begin()->pi.hProcess, 0);
            backProcList.pop_front();
        }
        return 0;
    } else {
        DWORD processId = stringToDWORD(arg1);
        for (auto proc = backProcList.begin(); proc != backProcList.end(); ++proc) {
            if (proc->pi.dwProcessId == processId) {
                TerminateProcess(proc->pi.hProcess, 0);
                backProcList.erase(proc);
                return 0;
            }
        }
        return 2;  // cant found process
    }
}
string killDoc = "Kill (a) process(es).\n\t\t  Usage: 'kill <process ID>' or 'kill .' for kill all";

int listprocess(string input) {
    printf("Process ID\tStatus\t\tFile address\n");
    for (auto proc = backProcList.begin(); proc != backProcList.end(); ++proc) {
        HANDLE hProcess = proc->pi.hProcess;
        string this_status;
        DWORD exitcode;
        GetExitCodeProcess(proc->pi.hProcess, &exitcode);
        if (proc->processStatus == 0 && exitcode == STILL_ACTIVE)
            this_status = "running";
        else if (proc->processStatus == 300)
            this_status = "suspend";
        else continue;
        CHAR name[1024];
        DWORD a = GetModuleFileNameEx(hProcess, NULL, name, 1024);
        cout << proc->pi.dwProcessId << "\t\t" << this_status << "\t\t" << name << "\n";
    }
    return 0;
}
string listprocessDoc = "Display running process informations.\n\t\t  Usage: 'listprocess'";

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
        if (inputs == "foreground") {
            foreProc = newProc;
            foreProc.processStatus = 0;
            for (auto proc = backProcList.begin(); proc != backProcList.end(); ++proc) {
                if (proc->processStatus == 0)
                    SuspendThread(proc->pi.hThread);
            }
            WaitForSingleObject(newProc.pi.hProcess, INFINITE);
            foreProc.processStatus = 200;
            for (auto proc = backProcList.begin(); proc != backProcList.end(); ++proc) {
                if (proc->processStatus == 0)
                    ResumeThread(proc->pi.hThread);
            }
        } else
            backProcList.push_back(newProc);
        return 0;
    }
}
string runBatExeDoc = "Run a .exe or .bat file\n\t\t  Usage: 'run <.bat or .exe file> [foreground]'";

int toForeground(string input) {
    string idstring = takeFirstArgAndRemove(input);
    DWORD ID = stringToDWORD(idstring);
    for (auto proc = backProcList.begin(); proc != backProcList.end(); ++proc) {
        if (proc->pi.dwProcessId == ID && proc->processStatus == 0) {
            foreProc = *proc;
            foreProc.processStatus = 0;
            backProcList.erase(proc);
            for (auto pproc = backProcList.begin(); pproc != backProcList.end(); ++pproc) {
                if (pproc->processStatus == 0)
                    SuspendThread(pproc->pi.hThread);
            }
            WaitForSingleObject(proc->pi.hProcess, INFINITE);
            foreProc.processStatus = 200;
            for (auto pproc = backProcList.begin(); pproc != backProcList.end(); ++pproc) {
                if (pproc->processStatus == 0)
                    ResumeThread(pproc->pi.hThread);
            }
            return 0;
        }
    }
    return 2;
}
string toForegroundDoc = "Change a running background process to foreground\n\t\t  Usage: 'toForeground <procesID>'.";
