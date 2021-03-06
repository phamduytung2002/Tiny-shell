#include <bits/stdc++.h>
#include <windows.h>
#include <dirent.h>
#include <psapi.h>
using namespace std;
#include "utils.hpp"

#pragma once

///////////  process data structure

struct procInfo {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    int processStatus;

    procInfo() {
        this->processStatus = 200;  // not exist
    }
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