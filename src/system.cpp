#include "system.h"

System::System() : files(current_pids), cpu(files) { // cpu (Processor class) constructor needs a reference to the files.
    files.ReadSystemFiles();
    UpdateListOfPIDs();
    GenerateProcesses();
}

void System::Running() {
    files.ReadSystemFiles();
    cpu.Running();
    // TODO: Not getting the list of PIDs. Fix this issue.
    UpdateListOfPIDs();
    files.getUpdatedListOfPIDs(current_pids);
    files.Running();
    GenerateProcesses();
    OrderProcesses();
}

void System::UpdateListOfPIDs() {
    previous_cycle_pids = current_pids;
    current_pids = LinuxParser::Pids();
    files.getUpdatedListOfPIDs(current_pids);
}

void System::GenerateProcesses() {
    for (const LP::PidFiles& current_pid_files : files.getAllPidsFiles()) {
        LP::ProcessInputInformation current_process_input_information{
                current_pid_files,
                files.getPasswordFileParsed(),
                cpu.getUsageIncrement()
        };
        Process new_process(current_process_input_information);
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

