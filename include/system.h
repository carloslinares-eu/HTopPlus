#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>
#include <ranges>
#include <algorithm>

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
    vector<int> current_pids;
    vector<int> previous_cycle_pids;
    vector<int> new_pids;


    void UpdateListOfPIDs();
    void GenerateProcesses();
    void UpdateAliveProcesses();
    void AddNewProcesses();

    bool ProcessIsAlive(Process& input_process);
};

#endif