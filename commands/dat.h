#include <winbase.h>

#include "../utils.h"
#include "processList.h"

int runBat(string input) {
    if (num_process == maxprocess) return 2;
    string file = takeFirstArgAndRemove(input);
    cout << file << endl;
    input = takeFirstArgAndRemove(input);
    ZeroMemory(&si[num_process], sizeof(si[num_process]));
    si[num_process].cb = sizeof(si[num_process]);
    if (!CreateProcess(file.c_str(), NULL, NULL, NULL, FALSE,
                       CREATE_NEW_CONSOLE, NULL, NULL, &si[num_process], &pi[num_process]))
        return 2;
    else {
        ++num_process;
        return 0;
    }
}
string runBatDoc = "Run a .bat file, can omit 'runbat' (draft).";