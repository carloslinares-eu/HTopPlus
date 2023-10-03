#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <utility>
#include <sstream>

#include "os_files.h"
#include "linux_parser.h"
#include "format.h"
#include "processor.h"

using std::string;
using std::vector;

namespace LP = LinuxParser;

class Process {
public:
    Process(int pid, string user);

    [[nodiscard]] int getPid() const {return pid;}
    string getUser() {return user;};
    string getCommand() {return command;}
    [[nodiscard]] float getCpuUtilization() const {return cpu_utilization;}
    [[nodiscard]] unsigned long getRamUtilization() const {return ram_utilization;}
    [[nodiscard]] long int getUpTime() const {return uptime;}

    bool operator<(const Process& process2) const  {return this->getCpuUtilization() < process2.getCpuUtilization();}

    void updateDynamicInformation(const long int & cpu_current_usage_increment);

private:
    int pid;

    string pid_path;

    string files_paths[3];
    LP::TextFile files[3];

    string user;
    std::string command;

    float cpu_utilization{};
    unsigned long ram_utilization = 999;
    long int uptime{};

    long int sum_current_process_jiffies{};
    long int sum_previous_process_jiffies{};

    void setPidPath();

    void readFiles();
    void setFilesPaths();

    void updateCpuUtilization(const long int & current_usage_increment);
    void updateRamUtilization();
    void updateUptime();
    void updateJiffies();
    void saveJiffiesForNextCycle();

    void setConstantInformation();

    enum needed_files_in_pid {
        cmdline = 0,
        stat = 1,
        status = 2
    };
};

#endif