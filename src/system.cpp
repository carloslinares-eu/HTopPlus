#include "system.h"

System::System() : cpu(files) { // cpu (Processor class) constructor needs a reference to the files.
    files.Running();
    UpdateListOfCurrentPIDs();
    UpdateListOfNewPids();
    InitProcesses();
}

void System::Running() {
    files.ReadSystemFiles();
    cpu.Running();
    UpdateListsOfPids();
    UpdateProcesses();
}

void System::UpdateListsOfPids() {
    UpdateListOfCurrentPIDs();
    UpdateListOfNewPids();
    UpdateListOfDeadPids();
}

void System::InitProcesses() {
    GenerateNewProcesses();
    UpdateAliveProcesses();
    OrderProcesses();
}

void System::UpdateProcesses() {
    GenerateNewProcesses();
    RemoveDeadProcesses();
    UpdateAliveProcesses();
    OrderProcesses();
}

void System::UpdateListOfCurrentPIDs() {
    previous_cycle_pids = current_pids;
    current_pids.clear();
    current_pids = LinuxParser::Pids();
}

void System::UpdateListOfNewPids() {
    new_pids.clear();
    for (int pid : current_pids) {
        if (std::find(previous_cycle_pids.begin(), previous_cycle_pids.end(),
                      pid) == previous_cycle_pids.end()){
            new_pids.push_back(pid);
        }
    }
}

void System::UpdateListOfDeadPids() {
    dead_pids.clear();
    for (int pid : previous_cycle_pids) {
        if (std::find(current_pids.begin(), current_pids.end(), pid) == current_pids.end()){
            dead_pids.push_back(pid);
        }
    }
}

void System::RemoveDeadProcesses() {
    vector<Process> processes_after_clearing;
    for (const auto & process : processes) {
        if (std::find(dead_pids.begin(), dead_pids.end(), process.getPid()) == dead_pids.end()) {
            processes_after_clearing.push_back(process);
            continue;
        } else {
            continue;
        }
    }
    processes.clear();
    processes = processes_after_clearing;
}

void System::GenerateNewProcesses() {
    for (const auto & pid : new_pids) {
        string user_of_pid = LP::User(pid, files.getPasswordFileParsed());
        Process new_process = Process(pid, user_of_pid);
        processes.push_back(new_process);
    }
}

void System::UpdateAliveProcesses() {
    vector<Process> processes_after_updating;
    for (Process & current_process : processes) {
        current_process.updateDynamicInformation(cpu.getUsageIncrement());
        processes_after_updating.push_back(current_process);
    }
}

void System::OrderProcesses() {
    uint number_of_processes = processes.size();
    for (size_t i = 0; i < number_of_processes - 1; ++i) {
        for (size_t j = 0; j < number_of_processes - i - 1; ++j) {
            if (processes[j] < processes[j + 1]) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

