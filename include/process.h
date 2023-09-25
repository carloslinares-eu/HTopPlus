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
    explicit Process(LP::ProcessInputInformation  process_constructor_input);

    [[nodiscard]] int getPid() const {return pid;}
    string getUser() {return user;};
    string getCommand() {return command;}
    [[nodiscard]] float getCpuUtilization() const {return cpu_utilization;}
    std::string getRamUtilization() {return ram_utilization;}
    [[nodiscard]] long int getUpTime() const {return uptime;}

    bool operator<(const Process& process2) const  {return this->getCpuUtilization() < process2.getCpuUtilization();}
    void updateDynamicInformation();

private:
    int pid;

    LP::ProcessInputInformation input_info;

    bool process_is_active{};

    std::string user;
    std::string command;

    float cpu_utilization{};
    string ram_utilization;
    long int uptime{};

    long int sum_current_process_jiffies{};
    long int sum_previous_process_jiffies{};

    void updateCpuUtilization();
    void updateRamUtilization();
    void updateUptime();
    void updateJiffies();
    void saveJiffiesForNextCycle();
};

#endif