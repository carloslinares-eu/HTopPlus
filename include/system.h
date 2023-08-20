#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "os_files.h"
#include "processor.h"
#include "process.h"


using std::string;
using std::vector;

class System {
public:
    System();

    Processor &getSystemCPU();
    vector<Process> &getSystemProcesses();

    float getMemoryUtilization();
    long getUpTime();
    int getTotalProcesses();
    int getRunningProcesses();
    string getKernel();
    string getOperatingSystem();

    void Running();

private:
    OSFiles files = {};
    Processor cpu;
    vector<Process> processes = {};
    vector<int> pids;

    void UpdateListOfPIDs();
};

#endif