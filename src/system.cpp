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


System::System()  {
    ReadSystemFiles();
    previous_to_update_system_uptime = this->UpTime();
    current_system_uptime = previous_to_update_system_uptime;
    time_elapsed_since_update = 0;
}

void System::Running() {
    ReadSystemFiles();
    UpdateTiming();
    Cpu().Running();
}

void System::ReadSystemFiles(){
    kCmdlineFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kCmdlineFilename);
    kCpuInfoFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kCpuInfoFilename);
    kStatusFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kStatusFilename);
    kCpuStatFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
    kUptimeFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kUptimeFilename);
    kMemInfoFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kMemInfoFilename);
    kVersionFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kVersionFilename);
    kPasswordFile = LinuxParser::ReadTextFile(LinuxParser::kPasswordPath);
    kOSFileRaw = LinuxParser::ReadTextFile(LinuxParser::kOSPath);

    kOSFileParsed = LinuxParser::ParseOSFile(kOSFileRaw);
}

Processor& System::Cpu() { return cpu_; }

vector<Process>& System::Processes() { return processes_; }

string System::Kernel() { return LinuxParser::Kernel(kVersionFile); }

float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(kMemInfoFile);}

std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(kOSFileParsed); }

int System::RunningProcesses() { return LinuxParser::RunningProcesses(kCpuStatFile); }

int System::TotalProcesses() { return LinuxParser::TotalProcesses(kCpuStatFile); }

long int System::UpTime() { return LinuxParser::UpTimeTotal(kUptimeFile); }

void System::UpdateTiming(){
    current_system_uptime = this->UpTime();
    time_elapsed_since_update = static_cast<int>(current_system_uptime - previous_to_update_system_uptime);
    if (time_elapsed_since_update >= update_time_seconds) {
        previous_to_update_system_uptime = current_system_uptime;
    }
}