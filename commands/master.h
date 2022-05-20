#include <bits/stdc++.h>
#include "bien.h"
#include "tung.h"
#include "dat.h"
using namespace std;
/*
    >> How to add a command:
    Create a function take a string as argument and return an int as an error code
        0: no error, continue to run
        1: exit shell
        2, 3, ...
    Create instruction/doc (string)
    Add to funcmap in buildCommand() below.
    See echo command (in tung.h) for example.
*/

void buildCommand() {
    funcmap["echo"] = funcAndInstruction(echo, echoDoc);
    funcmap["help"] = funcAndInstruction(help, helpDoc);
    funcmap["exitShell"] = funcAndInstruction(exitShell, exitShellDoc);
    funcmap["runexe"] = funcAndInstruction(runExe, runExeDoc);
    funcmap["datetime"] = funcAndInstruction(datetime, datetimeDoc);
    funcmap["time"] = funcAndInstruction(timee, timeDoc);
    funcmap["date"] = funcAndInstruction(date, dateDoc);
    funcmap["stop"] = funcAndInstruction(stop, stopDoc);
    funcmap["listprocess"] = funcAndInstruction(listprocess, listprocessDoc);
    funcmap["resume"] = funcAndInstruction(resume, resumeDoc);
    funcmap["addpath"] = funcAndInstruction(addpath, addpathDoc);
    funcmap["path"] = funcAndInstruction(path, pathDoc);
    funcmap["listpath"] = funcAndInstruction(listpath, listpathDoc);
    funcmap["delpath"] = funcAndInstruction(delpath, delpathDoc);
    funcmap["kill"] = funcAndInstruction(kill, killDoc);
    funcmap["foregroundMode"] = funcAndInstruction(foregroundMode, foregroundModeDoc);
    funcmap["backgroundMode"] = funcAndInstruction(backgroundMode, backgroundModeDoc);
    funcmap["runbat"] = funcAndInstruction(runBat, runBatDoc);
    //funcmap["exit"] = funcAndInstruction(exit, exitDoc);
}