#include "process.h"
#include "system.h"
#include "linux_parser.h"

System::System() : cpu(files) { // cpu (Processor class) constructor needs a reference to the files.
    files.ReadSystemFiles();
    UpdateListOfPIDs();
    GenerateProcesses();
}

vector<Process> &System::getSystemProcesses() { return processes; }

void System::Running() {
    files.ReadSystemFiles();
    cpu.Running();
    UpdateListOfPIDs();
    UpdateAliveProcesses();
    AddNewProcesses();
}

long int System::getUpTime() { return LinuxParser::UpTimeTotal(files.getUptimeFile()); }

void System::UpdateListOfPIDs() {
    previous_cycle_pids = current_pids;
    current_pids = LinuxParser::Pids();

    new_pids = current_pids;
    new_pids.erase(
            std::remove_if(new_pids.begin(), new_pids.end(),
                           [&](int value) {
                return std::find(previous_cycle_pids.begin(), previous_cycle_pids.end(),
                                 value) != previous_cycle_pids.end();
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
    number_of_updated_process = 0;
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
}


void System::AddNewProcesses() {
    number_of_added_process = 0;
    if (!new_pids.empty()) {
        for (int pid : new_pids) {
            string user = LinuxParser::User(pid, files.getPasswordFileParsed());
            string command = LinuxParser::Command(pid);
            Process new_process(pid, user, command, getSystemCPU());
            processes.push_back(new_process);
            number_of_added_process++;
        }
    }
}

bool System::ProcessIsAlive(Process& input_process) {
    auto pid_found_in = std::ranges::find(current_pids, input_process.getPid());
    if (pid_found_in != current_pids.end() && !files.getStatFile().empty() && !files.getStatusFile().empty() && !files.getCmdLineFile().empty()){
        return true;
    }
    else {
        return false;
    }
}
