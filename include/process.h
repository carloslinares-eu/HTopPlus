#ifndef PROCESS_H
#define PROCESS_H

#include <string>

#include "os_files.h"
#include "linux_parser.h"

using std::string;

class Process {
public:
    explicit Process(OSFiles &input_files_ref, int input_pid, string input_user, string input_command);    // Process needs a reference to OSFiles for accessing psw file.

    int getPid();                               // TODO: See src/process.cpp
    std::string getUser();                      // TODO: See src/process.cpp
    std::string getCommand();                   // TODO: See src/process.cpp
    float getCpuUtilization();                  // TODO: See src/process.cpp
    std::string getRamUtilization();                       // TODO: See src/process.cpp
    long int getUpTime();                       // TODO: See src/process.cpp
    bool operator<(Process const &a) const;  // TODO: See src/process.cpp

    void setPid();
    void setUser();
    void setCommand();

    void updateCpuUtilization();
    void updateRamUtilization();
    void updateUptime();

private:
    const OSFiles& files_ref;
    const int pid;
    const std::string user;
    const std::string command;

    float cpu_utilization;
    string ram_utilization;
    long int uptime;

};

#endif