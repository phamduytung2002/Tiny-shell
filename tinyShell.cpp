#include "commands/master.hpp"

int run(string input) {
    string command = takeFirstArgAndRemove(input);
    if (command == "") return 0;

    if (funcmap.find(command) == funcmap.end()) {
        if (command.find('.') != string::npos && (command.substr(command.find('.')) == ".exe" || command.substr(command.find('.')) == ".bat"))
            return runBatExe(command + " " + input);  // No command, run file .exe or .bat
        else {
            char val[1024];
            DWORD res = GetEnvironmentVariable(takeFirstArgAndRemove(command).c_str(), val, 1024);
            if (res != 0) {
                return runBatExe(string(val) + " " + input);
            } else
                cout << command << " is not recognized as an internal or external command, operable program or batch file.\n";
        }
        return 0;
    } else
        return funcmap[command].func(input);
}

bool processRunResult(int res) {
    switch (res) {
        case 0:
            break;
        case 1:
            return true;
        case 2:
            cout << "Not found.\n";
            break;
        default:
            cout << "Error!\n";
    }
    return false;
}

int main() {
    buildCommand();
    string input;
    while (true) {
        signal(SIGINT, [](int signum) {
            if (foreProc.processStatus != 200) {
                TerminateProcess(foreProc.pi.hProcess, 0);
                foreProc.processStatus = 200;
            } else
                exit(0);
        });  // CTRC C to terminate foreground process if there is any
        input = "";
        cout << filesystem::current_path().string() << ">";

        getline(cin, input);
        int res = run(input);
        if (processRunResult(res)) break;
    }
}