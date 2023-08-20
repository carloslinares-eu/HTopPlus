#ifndef PROCESS_H
#define PROCESS_H

#include <string>

#include "pid_files.h"
#include "os_files.h"
#include "linux_parser.h"

using std::string;

class Process {
public:
    explicit Process(OSFiles &input_files_ref, int input_pid, string input_user, string input_command);
    // Process needs a reference to OSFiles for accessing psw file.

    int getPid();
    std::string getUser();
    std::string getCommand();
    float getCpuUtilization();                  // TODO: See src/process.cpp
    std::string getRamUtilization();            // TODO: See src/process.cpp
    long int getUpTime() const;

    bool operator<(Process const &a) const;  // TODO: See src/process.cpp

    void updateDynamicInformation();

private:
    const OSFiles& os_files_ref;
    const int pid;
    const std::string user;
    const std::string command;

    PIDFiles files;

    float cpu_utilization;
    string ram_utilization;
    long int uptime;

    void updateCpuUtilization();
    void updateRamUtilization();
    void updateUptime();

};

#endif