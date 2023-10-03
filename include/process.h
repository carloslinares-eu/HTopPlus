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
    explicit Process(int pid, string user);

    [[nodiscard]] int getPid() const {return pid;}
    string getUser() {return user;};
    string getCommand() {return command;}
    [[nodiscard]] float getCpuUtilization() const {return cpu_utilization;}
    string getRamUtilization() {return ram_utilization;}
    [[nodiscard]] long int getUpTime() const {return uptime;}

    void setUser(string input_user){user = std::move(input_user);}
    void setCommand(string input_command){command = std::move(input_command);}
    void setCpuUtilization(float const &input_cpu_utilization){cpu_utilization = input_cpu_utilization;}
    void setRamUtilization(string input_ram_utilization){ram_utilization = std::move(input_ram_utilization);}
    void setUpTime(long int const &input_uptime){uptime = input_uptime;}

    bool operator<(const Process& process2) const  {return this->getCpuUtilization() < process2.getCpuUtilization();}

    void updateDynamicInformation();

private:
    int pid;

    LP::TextFile cmdline_file;
    LP::TextFile stat_file;
    LP::TextFile status_file;

    bool process_is_active{};

    string user;
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

    void getConstantInformation();


};

#endif