#include <bits/stdc++.h>
#include <dirent.h>
#include <processthreadsapi.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <unistd.h>
#include <windows.h>
using namespace std;
#include "utils.hpp"

#pragma once

///////////  process data structure

struct procInfo {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    int processStatus;
};
list<procInfo> backProcList;
procInfo foreProc;

///////////  command data structure

struct funcAndInstruction {
    function<int(string)> func;
    string instruction;

    funcAndInstruction() {
        func = [](string c) { return 0; };
        instruction = "default command";
    }

    funcAndInstruction(function<int(string)> funcc, string instructionn) : func(funcc), instruction(instructionn) {}
};
map<string, funcAndInstruction> funcmap;