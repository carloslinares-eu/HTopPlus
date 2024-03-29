#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>
#include <ranges>
#include <algorithm>
#include <set>
#include <iostream>

#include "os_files.h"
#include "processor.h"
#include "process.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

class System {
public:
    System();

    Processor& getSystemCPU() {return cpu;}
    vector<Process>& getSystemProcesses() {return processes;};

    float getMemoryUtilization() {return LinuxParser::MemoryUtilization(files.getMemInfoFile());}
    long getUpTime(){return LinuxParser::UpTimeTotal(files.getUptimeFile());}
    int getTotalProcesses() {return LinuxParser::TotalProcesses(files.getCpuStatFile());}
    int getRunningProcesses() {return LinuxParser::RunningProcesses(files.getCpuStatFile());}

    string getKernel() {return LinuxParser::Kernel(files.getVersionFile());}
    string getOperatingSystem() {return LinuxParser::OperatingSystem(files.getOSFileParsed());}

    void Running();

private:
    OSFiles files;
    Processor cpu;
    vector<Process> processes = {};

    vector<int> current_pids;
    vector<int> previous_cycle_pids;
    vector<int> new_pids;
    vector<int> dead_pids;

    void UpdateListsOfPids();
    void UpdateListOfCurrentPIDs();
    void UpdateListOfNewPids();
    void UpdateListOfDeadPids();

    void InitProcesses();
    void UpdateProcesses();
    void RemoveDeadProcesses();
    void UpdateAliveProcesses();
    void GenerateNewProcesses();
    void OrderProcesses();

};

#endif