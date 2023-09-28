#include "process.h"
#include <utility>


Process::Process(LP::ProcessInputInformation  process_constructor_input) :
input_info(std::move(process_constructor_input)){
    pid = input_info.current_process_files.Pid;
    process_is_active = input_info.current_process_files.all_files_present;

}

void Process::updateDynamicInformation() {
    if (process_is_active) {
        updateCpuUtilization();
        updateRamUtilization();
        updateUptime();
    }
}

void Process::updateCpuUtilization() {
    long int current_jiffies_increment;
    long int latest_cpu_increment = input_info.current_usage_increment;

    updateJiffies();
    current_jiffies_increment = sum_current_process_jiffies - sum_previous_process_jiffies;

    if (latest_cpu_increment == 0) {
        cpu_utilization = 0.0;
    }
    else {
        cpu_utilization = static_cast<float>(current_jiffies_increment)/static_cast<float>(latest_cpu_increment);
    }

    saveJiffiesForNextCycle();
}

void Process::updateRamUtilization() {
    LP::TextFile StatusFile = input_info.current_process_files.kPidStatusFile;
    ram_utilization = LP::ProcessUsedRam(StatusFile);
}

void Process::updateUptime() {
    LP::TextFile StatFile = input_info.current_process_files.kPidStatFile;
    uptime = LP::UpTime(StatFile);
}

void Process::updateJiffies() {
    LP::TextFile StatFile = input_info.current_process_files.kPidStatFile;
    sum_current_process_jiffies = LP::ActiveJiffiesProcess(StatFile);
}

void Process::saveJiffiesForNextCycle() {
    sum_previous_process_jiffies = sum_current_process_jiffies;
}
