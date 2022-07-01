#pragma once

string trim(string s) {
    // remove the spaces at the start and end of string
    s.erase(s.find_last_not_of(" \n\r\t") + 1);
    s.erase(0, s.find_first_not_of(' '));
    return s;
}

void parse(string input, string &command, string &argument) {
    // split input string by " "
    // input = "  A  B...    " -> command = "A", argument = "B..."
    input = trim(input);
    size_t found = input.find(" ");
    if (found == string::npos) {
        command = input;
        argument = "";
    } else {
        command = input.substr(0, found);
        argument = input.substr(found + 1, input.size());
    }
    command = trim(command);
    argument = trim(argument);
}

string takeFirstArgAndRemove(string &input) {
    // input = "    A       B.......     "
    // -> return A, input := B
    string A;
    parse(input, A, input);
    return A;
}

unsigned stringToDWORD(string input) {
    stringstream ss(input);
    unsigned num = 0;
    ss >> num;
    return num;
}