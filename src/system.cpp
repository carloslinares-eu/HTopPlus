#include "system.h"

System::System() : cpu(files) { // cpu (Processor class) constructor needs a reference to the files.
    files.ReadSystemFiles();
    UpdateListOfPIDs();
    GenerateProcesses();
}

void System::Running() {
    files.ReadSystemFiles();
    cpu.Running();
    UpdateListOfPIDs();
    OrderProcesses();
}

void System::UpdateListOfPIDs() {
    previous_cycle_pids = current_pids;
    current_pids = LinuxParser::Pids();
    files.getUpdatedListOfPIDs(current_pids);
}

void System::GenerateProcesses() {
    for (int pid : current_pids) {
        string user = LinuxParser::User(pid, files.getPasswordFileParsed());
        string command = LinuxParser::Command(pid);
        Process new_process(pid, user, command, getSystemCPU());
        processes.push_back(new_process);
    }
}

void System::OrderProcesses() {
    unsigned int vector_size = processes.size();
    if (vector_size != 0) {
        for (size_t i = 0; i < vector_size - 1; ++i) {
            for (size_t j = 0; j < vector_size - i - 1; ++j) {
                if (processes[j + 1] < processes[j]) {
                    Process temp = processes[j];
                    processes[j] = processes[j + 1];
                }
            }
        }
    }
}


bool System::ProcessIsAlive(Process& input_process) {
    auto pid_found_in = std::ranges::find(current_pids, input_process.getPid());
    bool folder_in_proc_dir = pid_found_in != current_pids.end();
    bool stat_file_is_not_empty = !input_process.getFiles().getStatFile().empty();
    bool status_file_is_not_empty = !input_process.getFiles().getStatusFile().empty();
    bool cmdline_file_is_not_empty = !input_process.getFiles().getCmdLineFile().empty();

    if (folder_in_proc_dir && stat_file_is_not_empty && status_file_is_not_empty && cmdline_file_is_not_empty){
        return true;
    }
    else {
        return false;
    }
}
