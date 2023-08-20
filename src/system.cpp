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


System::System() : cpu(files) { // cpu (Processor class) constructor needs a reference to the files.
    files.ReadSystemFiles();
    UpdateListOfPIDs();
}

Processor &System::getSystemCPU() { return cpu; }

vector<Process> &System::getSystemProcesses() { return processes; }

void System::Running() {
    files.ReadSystemFiles();
    UpdateListOfPIDs();
    GenerateProcesses();
}


string System::getKernel() { return LinuxParser::Kernel(files.getVersionFile()); }

float System::getMemoryUtilization() { return LinuxParser::MemoryUtilization(files.getMemInfoFile()); }

std::string System::getOperatingSystem() { return LinuxParser::OperatingSystem(files.getOSFileParsed()); }

int System::getRunningProcesses() { return LinuxParser::RunningProcesses(files.getCpuStatFile()); }

int System::getTotalProcesses() { return LinuxParser::TotalProcesses(files.getCpuStatFile()); }

long int System::getUpTime() { return LinuxParser::UpTimeTotal(files.getUptimeFile()); }

void System::UpdateListOfPIDs() {
    pids = LinuxParser::Pids();
}

void System::GenerateProcesses() {
    processes.clear();
    for (int pid : pids) {
        string user = LinuxParser::User(pid);
        string command = LinuxParser::Command(pid);
        Process new_process(files, pid, user, command);
        processes.push_back(new_process);
    }
}
