#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

#pragma once

const int maxprocess = 10;
int num_process = 0;

STARTUPINFO si[maxprocess];
PROCESS_INFORMATION pi[maxprocess];
int processStatus[maxprocess];
