#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "osfiles.h"
#include "processor.h"
#include "process.h"


using std::string;
using std::vector;

class System {
public:
    System();

    Processor &getSystemCPU();
    vector<Process> &getSystemProcesses();

    float MemoryUtilization();
    long UpTime();
    int TotalProcesses();
    int RunningProcesses();
    string Kernel();
    string OperatingSystem();

    void Running();

private:
    OSFiles Files = {};
    Processor CPU;
    vector<Process> Processes = {};
};

#endif