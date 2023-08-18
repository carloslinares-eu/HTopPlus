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


System::System() : CPU(Files) {
    Files.ReadSystemFiles();
}

Processor& System::getSystemCPU() { return CPU; }
vector<Process>& System::getSystemProcesses() { return Processes; }

void System::Running() {
    Files.ReadSystemFiles();
}


string System::Kernel() { return LinuxParser::Kernel(Files.getVersionFile()); }

float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(Files.getMemInfoFile());}

std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(Files.getOSFileParsed()); }

int System::RunningProcesses() { return LinuxParser::RunningProcesses(Files.getCpuStatFile()); }

int System::TotalProcesses() { return LinuxParser::TotalProcesses(Files.getCpuStatFile()); }

long int System::UpTime() { return LinuxParser::UpTimeTotal(Files.getUptimeFile()); }
