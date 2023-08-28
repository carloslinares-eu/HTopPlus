#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <utility>
#include <sstream>


#include "pid_files.h"
#include "os_files.h"
#include "linux_parser.h"
#include "format.h"
#include "processor.h"

using std::string;
using std::vector;

class Process {
public:
    Process(int input_pid, string input_user, string input_command, Processor* system_cpu);

    [[nodiscard]] int getPid() const {return pid;}
    string getUser() {return user;};
    string getCommand() {return command;}
    [[nodiscard]] float getCpuUtilization() const {return cpu_utilization;}
    std::string getRamUtilization() {return ram_utilization;}
    [[nodiscard]] long int getUpTime() const {return uptime;}

    PIDFiles& getFiles() {return files;}

    bool operator<(Process const &process2) const  {return getCpuUtilization() < process2.getCpuUtilization();}

    void updateDynamicInformation();

private:
    int pid;
    std::string user;
    std::string command;

    Processor* cpu;

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