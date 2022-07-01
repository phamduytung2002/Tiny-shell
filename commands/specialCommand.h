#include "esstential.h"

// example
int echo(string c) {
    cout << c << endl;
    return 0;
}
string echoDoc = "Just print the argument.";

int exitShell(string c) {
    while(!procList.empty()){
        TerminateProcess(procList.begin()->pi.hProcess, 0);
        procList.pop_front();
    }
    return 1;
}
string exitShellDoc = "Exit shell.";

int help(string c) {
    cout << "Command list: \n";
    for (auto i = funcmap.begin(); i != funcmap.end(); ++i) {
        string command = i->first;
        string space = command.size() < 8 ? "\t\t" : "\t";
        cout << command << space << i->second.instruction << "\n";
    }
    return 0;
}
string helpDoc = "List all available command.";

int date(string input) {
    time_t t = time(0);  // get time now
    tm* now = localtime(&t);
    cout << now->tm_mday << "/" << now->tm_mon + 1 << "/" << now->tm_year + 1900 << '\n';
    return 0;
}
string dateDoc = "Display today date.";

int timee(string input) {
    time_t t = time(0);  // get time now
    tm* now = localtime(&t);
    cout << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << '\n';
    return 0;
}
string timeDoc = "Display current time.";

int datetime(string input) {
    time_t t = time(0);  // get time now
    tm* now = localtime(&t);
    cout << now->tm_mday << "/" << (now->tm_mon + 1) << "/" << (now->tm_year + 1900) << "  ";
    cout << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "\n";
    return 0;
}
string datetimeDoc = "Display current date and time.";

int dir(string input) {
    string path = filesystem::current_path().string();
    DIR* dir;
    dirent* pdir;
    vector<string> files;
    dir = opendir(path.c_str());
    while (pdir = readdir(dir)) {
        files.push_back(pdir->d_name);
    }
    for (int i = 0; i < files.size(); ++i) {
        cout << files[i] << '\n';
    }
    return 0;
}
string dirDoc = "List all directory.";

int cd(string input) {
    chdir(input.c_str());
    return 0;
}
string cdDoc = "Change dir";