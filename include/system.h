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
    OSFiles files = {};
    Processor cpu;
    vector<Process> processes = {};

    vector<int> current_pids;
    vector<int> previous_cycle_pids;
    vector<int> new_pids;

    unsigned int number_of_updated_process{};
    unsigned int number_of_added_process{};

    void UpdateListOfPIDs();
    void GenerateProcesses();
    void UpdateAliveProcesses();
    void AddNewProcesses();
    void OrderProcesses();

    bool ProcessIsAlive(Process& input_process);
};

#endif