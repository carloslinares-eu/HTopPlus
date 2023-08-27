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
    GenerateProcesses();
}

Processor &System::getSystemCPU() { return cpu; }

vector<Process> &System::getSystemProcesses() { return processes; }

void System::Running() {
    files.ReadSystemFiles();
    cpu.Running();
    UpdateListOfPIDs();
    UpdateAliveProcesses();
    AddNewProcesses();
}


string System::getKernel() { return LinuxParser::Kernel(files.getVersionFile()); }

float System::getMemoryUtilization() { return LinuxParser::MemoryUtilization(files.getMemInfoFile()); }

std::string System::getOperatingSystem() { return LinuxParser::OperatingSystem(files.getOSFileParsed()); }

int System::getRunningProcesses() { return LinuxParser::RunningProcesses(files.getCpuStatFile()); }

int System::getTotalProcesses() { return LinuxParser::TotalProcesses(files.getCpuStatFile()); }

long int System::getUpTime() { return LinuxParser::UpTimeTotal(files.getUptimeFile()); }

void System::UpdateListOfPIDs() {
    previous_cycle_pids = current_pids;
    current_pids = LinuxParser::Pids();

    new_pids = current_pids;
    new_pids.erase(std::remove_if(new_pids.begin(), new_pids.end(),
                                      [&](int value) {
                                          return std::find(previous_cycle_pids.begin(), previous_cycle_pids.end(), value) != previous_cycle_pids.end();
                                      }),
                       new_pids.end());
}

void System::GenerateProcesses() {
    processes.clear();  // Wiping out all the information of processes before populating it again.
    for (int pid : current_pids) {
        string user = LinuxParser::User(pid, files.getPasswordFileParsed());
        string command = LinuxParser::Command(pid);
        Process new_process(pid, user, command, getSystemCPU());
        processes.push_back(new_process);
    }
}

void System::UpdateAliveProcesses() {
    unsigned int number_of_updated_process = 0;
    vector<Process> tmp_cp_processes = processes;
    processes.clear();

    unsigned int const number_of_registered_processes = tmp_cp_processes.size();
    for (size_t vector_index = 0; vector_index != number_of_registered_processes; ++vector_index) {
        Process current_process = tmp_cp_processes[vector_index];
        if (ProcessIsAlive(current_process)) {
            current_process.updateDynamicInformation();
            processes.push_back(current_process);
            number_of_updated_process++;
        } else {
            continue;
        }
    }

    std::cout << "Updated " << number_of_updated_process << " processes.";
    std::cout << "Removed " << number_of_registered_processes - number_of_updated_process << "processes.";
}


void System::AddNewProcesses() {
    unsigned int number_of_added_process = 0;

    for (int pid : new_pids) {
        string user = LinuxParser::User(pid, files.getPasswordFileParsed());
        string command = LinuxParser::Command(pid);
        Process new_process(pid, user, command, getSystemCPU());
        processes.push_back(new_process);
        number_of_added_process++;
    }
    std::cout << "Added  " << number_of_added_process << "processes.";

}

bool System::ProcessIsAlive(Process& input_process) {
    auto pid_found_in = std::ranges::find(current_pids, input_process.getPid());
    if (pid_found_in != current_pids.end()){
        return true;
    }
    else {
        return false;
    }
}


