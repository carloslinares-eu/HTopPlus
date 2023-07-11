#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;


void System::ReadSystemFiles(){
    kCmdlineFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kCmdlineFilename);
    kCpuInfoFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kCpuInfoFilename);
    kStatusFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kStatusFilename);
    kStatFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
    kUptimeFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kUptimeFilename);
    kMemInfoFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kMemInfoFilename);
    kVersionFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kVersionFilename);
    kOSFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kOSPath);
    kPasswordFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kPasswordPath);
}

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

string System::Kernel() { return LinuxParser::Kernel(kVersionFile); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization();}

std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(kOSFile); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }

// TODO: Create system constructor to initialize variables defined by value
System::System() {
    ReadSystemFiles();
}

