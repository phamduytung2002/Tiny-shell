#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

#pragma once

const int maxprocess = 10;

STARTUPINFO si[maxprocess];
PROCESS_INFORMATION pi[maxprocess];

int num_process = 0;

int mode = 1;  // mode = 0 <=> mode = foregroundMode ; mode = 1 <=> mode = backgroundMode
int pi_run[maxprocess];
// int num_process_run = 0;