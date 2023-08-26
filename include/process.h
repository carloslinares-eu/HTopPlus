#ifndef PROCESS_H
#define PROCESS_H

#include <string>

#include "pid_files.h"
#include "os_files.h"
#include "linux_parser.h"
#include "format.h"
#include "processor.h"

using std::string;

class Process {
public:
    explicit Process(int input_pid, string input_user, string input_command, Processor &system_cpu);
    // Process needs a reference to OSFiles for accessing psw file.

    [[nodiscard]] int getPid() const {return pid;}
    string getUser() {return user;};
    string getCommand() {return command;}
    [[nodiscard]] float getCpuUtilization() const {return cpu_utilization;};
    std::string getRamUtilization();
    [[nodiscard]] long int getUpTime() const;

    bool operator<(Process const &a) const;  // TODO: See src/process.cpp

    void updateDynamicInformation();

private:
    const int pid;
    const std::string user;
    const std::string command;

    Processor& cpu;

    PIDFiles files;

    float cpu_utilization;
    string ram_utilization;
    long int uptime;

    long int sum_current_process_jiffies;
    long int sum_previous_process_jiffies;

    void updateCpuUtilization();
    void updateRamUtilization();
    void updateUptime();
    void updateJiffies();
    void saveJiffiesForNextCycle();

};

#endif