#include "commands/master.hpp"

int run(string input) {
    string command = takeFirstArgAndRemove(input);
    if (command == "") return 0;

    if (funcmap.find(command) == funcmap.end()) {
        if (command.find('.') != string::npos && (command.substr(command.find('.')) == ".exe" || command.substr(command.find('.')) == ".bat"))
            return runBatExe(command + " " + input);  // No command, run file .exe or .bat
        else
            cout << command << " is not recognized as an internal or external command, operable program or batch file.\n";
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
            cout << "Command fails.\n";
            break;
        default:
            cout << "Error!\n";
    }
    return false;
}

int main() {
    buildCommand();
    string input;
    signal(SIGINT, [](int signum) {
        TerminateProcess(foreProc.pi.hProcess, 0);
    });  // CTRC C to stop foreground process if there is any
    while (true) {
        input = "";
        cout << filesystem::current_path().string() << ">";
        getline(cin, input);
        int res = run(input);
        if (processRunResult(res)) break;
    }
}