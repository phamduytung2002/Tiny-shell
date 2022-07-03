#include "essential.hpp"

// example
int echo(string c) {
    cout << c << endl;
    return 0;
}
string echoDoc = "Just print the argument.\n\t\t  Usage: 'echo <anything>'.";

int exitshell(string c) {
    while (!backProcList.empty()) {
        TerminateProcess(backProcList.begin()->pi.hProcess, 0);
        backProcList.pop_front();
    }
    return 1;
}
string exitshellDoc = "Exit shell.\n\t\t  Usage: 'exitShell'.";

int help(string c) {
    cout << "Command list: \n";
    for (auto i = funcmap.begin(); i != funcmap.end(); ++i) {
        string command = i->first;
        string space = command.size() < 8 ? "\t\t" : "\t";
        cout << command << space << i->second.instruction << "\n";
    }
    return 0;
}
string helpDoc = "List all available command.\n\t\t  Usage: 'help'.";

int date(string input) {
    time_t t = time(0);  // get time now
    tm* now = localtime(&t);
    cout << now->tm_mday << "/" << now->tm_mon + 1 << "/" << now->tm_year + 1900 << '\n';
    return 0;
}
string dateDoc = "Display today date.\n\t\t  Usage: 'date'.";

int timee(string input) {
    time_t t = time(0);  // get time now
    tm* now = localtime(&t);
    cout << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << '\n';
    return 0;
}
string timeDoc = "Display current time.\n\t\t  Usage: 'time'.";

int datetime(string input) {
    time_t t = time(0);  // get time now
    tm* now = localtime(&t);
    cout << now->tm_mday << "/" << (now->tm_mon + 1) << "/" << (now->tm_year + 1900) << "  ";
    cout << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "\n";
    return 0;
}
string datetimeDoc = "Display current date and time.\n\t\t  Usage: 'datetime'.";

int dir(string input) {
    string path = filesystem::current_path().string();
    DIR* dir;
    dirent* pdir;
    dir = opendir(path.c_str());
    while (pdir = readdir(dir)) {
        cout << pdir->d_name << endl;
    }
    return 0;
}
string dirDoc = "List all directory.\n\t\t  Usage: 'dir'.";

int cd(string input) {
    chdir(input.c_str());
    return 0;
}
string cdDoc = "Change dir.\n\t\t  Usage: 'cd <subdirectory>' or 'cd ..' to change to the parents directory.";

int clear(string input){
    system("cls");
    return 0;
}
string clearDoc = "Clear screen.\n\t\t  Usage: 'clear'.";