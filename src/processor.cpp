#include "processor.h"

Processor::Processor(OSFiles &FilesRef) : files_ref(FilesRef) {
    updateAggregatedCpuInfo();
}

void Processor::Running() {
    calculateCpuUtilization();
}

void Processor::updateAggregatedCpuInfo() {
    current_cpus_jiffies = LinuxParser::getAggregatedCPUInfo(files_ref.getCpuStatFile());
}

void Processor::calculateCpuUtilization() {
    bool is_first_cycle;

    long int previous_idle, current_idle;
    long int previous_non_idle, current_non_idle;
    long int previous_total, current_total;
    long int idle_increment, total_increment;

    // Saves previous values before updating.
    previous_cycle_cpus_jiffies = current_cpus_jiffies;

    // Updates current cpus jiffies with latest information available.
    updateAggregatedCpuInfo();

    previous_idle = previous_cycle_cpus_jiffies[LinuxParser::CPUStates::kIdle_] +
                    previous_cycle_cpus_jiffies[LinuxParser::CPUStates::kIOwait_];
    current_idle = current_cpus_jiffies[LinuxParser::CPUStates::kIdle_] +
                   current_cpus_jiffies[LinuxParser::CPUStates::kIOwait_];

    previous_non_idle = previous_cycle_cpus_jiffies[LinuxParser::CPUStates::kUser_] +
                        previous_cycle_cpus_jiffies[LinuxParser::CPUStates::kNice_] +
                        previous_cycle_cpus_jiffies[LinuxParser::CPUStates::kSystem_] +
                        previous_cycle_cpus_jiffies[LinuxParser::CPUStates::kIRQ_] +
                        previous_cycle_cpus_jiffies[LinuxParser::CPUStates::kSoftIRQ_] +
                        previous_cycle_cpus_jiffies[LinuxParser::CPUStates::kSteal_];
    current_non_idle = current_cpus_jiffies[LinuxParser::CPUStates::kUser_] +
                       current_cpus_jiffies[LinuxParser::CPUStates::kNice_] +
                       current_cpus_jiffies[LinuxParser::CPUStates::kSystem_] +
                       current_cpus_jiffies[LinuxParser::CPUStates::kIRQ_] +
                       current_cpus_jiffies[LinuxParser::CPUStates::kSoftIRQ_] +
                       current_cpus_jiffies[LinuxParser::CPUStates::kSteal_];

    previous_total = previous_idle + previous_non_idle;
    current_total = current_idle + current_non_idle;

    total_increment = current_total - previous_total;
    idle_increment = current_idle - previous_idle;

    is_first_cycle = previous_total == 0;

    current_usage_increment = total_increment-idle_increment;

    if (is_first_cycle) {
        utilization = 0.0;
    } else {
        utilization = static_cast<float>(total_increment - idle_increment) / static_cast<float>(total_increment);
    }
}