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

    OSFiles &getOSFiles();
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
    Processor CPU = {};
    vector<Process> Processes = {};

    // TODO: To be included in the system files.
    vector<vector<string>> kCmdlineFile;
    vector<vector<string>> kCpuInfoFile;
    vector<vector<string>> kStatusFile;
    vector<vector<string>> kCpuStatFile;
    vector<vector<string>> kUptimeFile;
    vector<vector<string>> kMemInfoFile;
    vector<vector<string>> kVersionFile;
    vector<vector<string>> kOSFileRaw;
    vector<vector<string>> kOSFileParsed;
    vector<vector<string>> kPasswordFile;

    void UpdateTiming();

    void ReadSystemFiles();

    static const int update_time_seconds = 5;

    long int previous_to_update_system_uptime;
    long int current_system_uptime;
    int time_elapsed_since_update;

};

#endif