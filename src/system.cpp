#include "system.h"

System::System() : files(current_pids), cpu(files) { // cpu (Processor class) constructor needs a reference to the files.
    files.ReadSystemFiles();
    UpdateListOfCurrentPIDs();
    GenerateNewProcesses();
}

void System::Running() {
    files.ReadSystemFiles();
    cpu.Running();
    UpdateListOfCurrentPIDs();
    UpdateListOfNewPids();
    UpdateListOfDeadPids();
    files.getUpdatedListOfPIDs(current_pids);
    files.Running();
    GenerateNewProcesses();
    RemoveDeadProcesses();
    UpdateAliveProcesses();
    OrderProcesses();
}

void System::UpdateListOfCurrentPIDs() {
    previous_cycle_pids = current_pids;
    current_pids.clear();
    current_pids = LinuxParser::Pids();
    // TODO: Maybe the processes should be the owner of their own files.
    // This would lead to cleaner architecture (less inputs for process creation and less update of os_files.
}

void System::UpdateListOfNewPids() {
    new_pids.clear();
    for (int pid : current_pids) {
        auto pcpids = previous_cycle_pids;
        if (std::find(pcpids.begin(), pcpids.end(), pid) == pcpids.end()){
            new_pids.push_back(pid);
        }
    }
}

void System::UpdateListOfDeadPids() {
    dead_pids.clear();
    for (int pid : previous_cycle_pids) {
        auto cpids = current_pids;
        if (std::find(cpids.begin(), cpids.end(), pid) == cpids.end()){
            dead_pids.push_back(pid);
        }
    }
}

void System::RemoveDeadProcesses() {

}

void System::GenerateNewProcesses() {
    for (auto pid : new_pids) {
        string user = LP::User(pid, files.getPasswordFileParsed());
        auto ptr_new_process = new Process(pid, user);
        processes.push_back(ptr_new_process);
    }
}

void System::UpdateAliveProcesses() {

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

