#include "process.h"


Process::Process(int input_pid, string input_user, string input_command, Processor* system_cpu) :
pid(input_pid),
user(std::move(input_user)),
command(std::move(input_command)),
cpu(system_cpu),
files(input_pid) {
    cpu_utilization = 0;
    uptime = 0;
    sum_current_process_jiffies = LinuxParser::ActiveJiffiesProcess(files.getStatFile());
    sum_previous_process_jiffies = sum_current_process_jiffies;
    updateDynamicInformation();
}

void Process::updateDynamicInformation() {
    files.ReadPIDFiles();
    if (!files.getStatFile().empty() && !files.getStatusFile().empty() && !files.getCmdLineFile().empty()) {
        updateCpuUtilization();
        updateRamUtilization();
        updateUptime();
    }
}

void Process::updateCpuUtilization() {
    long int current_jiffies_increment;
    long int latest_cpu_increment = cpu->getUsageIncrement();

    updateJiffies();
    current_jiffies_increment = sum_current_process_jiffies - sum_previous_process_jiffies;

    cpu_utilization = static_cast<float>(current_jiffies_increment)/static_cast<float>(latest_cpu_increment);

    saveJiffiesForNextCycle();
}

void Process::updateRamUtilization() {
    ram_utilization = LP::ProcessUsedRam(files.getStatusFile());
}

void Process::updateUptime() {
    uptime = LP::UpTime(files.getStatFile());
}

void Process::updateJiffies() {
    sum_current_process_jiffies = LP::ActiveJiffiesProcess(files.getStatFile());
}

void Process::saveJiffiesForNextCycle() {
    sum_previous_process_jiffies = sum_current_process_jiffies;
}
