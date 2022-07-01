#include <bits/stdc++.h>
#include <dirent.h>
#include <processthreadsapi.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <unistd.h>
#include <windows.h>
using namespace std;
#include "utils.h"

#pragma once

///////////  process data structure

const int maxprocess = 10;
int num_process = 0;

STARTUPINFO si[maxprocess];
PROCESS_INFORMATION pi[maxprocess];
int processStatus[maxprocess];

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