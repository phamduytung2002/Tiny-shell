#include "pathCommand.hpp"
#include "processCommand.hpp"
#include "specialCommand.hpp"

/*
    >> How to add a command:
    Create a function take a string as argument and return an int as an error code
        0: no error, continue to run
        1: exit shell
        2: cant execute a command
        3, 4 ...
    Create instruction/doc (string)
    Add to funcmap in buildCommand() below.
    See echo command (in specialCommand.h) for example.
*/

void buildCommand() {
    funcmap["echo"] = funcAndInstruction(echo, echoDoc);
    funcmap["help"] = funcAndInstruction(help, helpDoc);
    funcmap["exitshell"] = funcAndInstruction(exitshell, exitshellDoc);
    funcmap["run"] = funcAndInstruction(runBatExe, runBatExeDoc);
    funcmap["datetime"] = funcAndInstruction(datetime, datetimeDoc);
    funcmap["time"] = funcAndInstruction(timee, timeDoc);
    funcmap["date"] = funcAndInstruction(date, dateDoc);
    funcmap["stop"] = funcAndInstruction(stop, stopDoc);
    funcmap["resume"] = funcAndInstruction(resume, resumeDoc);
    funcmap["addpath"] = funcAndInstruction(addpath, addpathDoc);
    funcmap["path"] = funcAndInstruction(path, pathDoc);
    funcmap["listpath"] = funcAndInstruction(listpath, listpathDoc);
    funcmap["delpath"] = funcAndInstruction(delpath, delpathDoc);
    funcmap["kill"] = funcAndInstruction(kill, killDoc);
    funcmap["listprocess"] = funcAndInstruction(listprocess, listprocessDoc);
    funcmap["dir"] = funcAndInstruction(dir, dirDoc);
    funcmap["cd"] = funcAndInstruction(cd, cdDoc);
    funcmap["clear"] = funcAndInstruction(clear, clearDoc);
    funcmap["toForeground"] = funcAndInstruction(toForeground, toForegroundDoc);
}