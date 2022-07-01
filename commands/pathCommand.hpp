#include "essential.hpp"

int addpath(string input) {
    string a = takeFirstArgAndRemove(input);
    string b = takeFirstArgAndRemove(input);
    putenv((a + "=" + b).c_str());
    return 0;
}
string addpathDoc = "Add/change an environment variable\n\t\t  Usage: 'addpath <variable> <value>'.";

int path(string input) {
    cout << getenv(takeFirstArgAndRemove(input).c_str()) << "\n";
    return 0;
}
string pathDoc = "Display an environment variable\n\t\t  Usage: 'path <variable>'.";

int listpath(string input) {
    function<void(LPTCH)> free = [](LPTCH p) {
        FreeEnvironmentStrings(p);
    };
    unique_ptr<TCHAR, decltype(free)> env_block = unique_ptr<TCHAR, decltype(free)>{
        GetEnvironmentStrings(), free};
    for (LPTCH i = env_block.get(); *i != '\0'; ++i) {
        string key, value;
        for (; *i != '='; ++i) key += *i;
        if (key == "") continue;
        ++i;
        for (; *i != '\0'; ++i) value += *i;

        cout << key;
        for (int i = 0; i < 4 - key.size() / 8; ++i) cout << "\t";
        cout << value << "\n";
    }
    return 0;
}
string listpathDoc = "Display all environment variable\n\t\t  Usage: 'listpath'.";

int delpath(string input) {
    input = takeFirstArgAndRemove(input);
    SetEnvironmentVariable(input.c_str(), NULL);
    return 0;
}
string delpathDoc = "Delete an environment variable\n\t\t  Usage: 'delpath <variable>'.";