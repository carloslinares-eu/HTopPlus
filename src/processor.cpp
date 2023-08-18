#include "processor.h"

Processor::Processor(OSFiles &FilesRef) : files_ref(FilesRef) {
    getAggregatedCPUInfo();
}

void Processor::getAggregatedCPUInfo() {
    current_cpus_jiffies = LinuxParser::getAggregatedCPUInfo(files_ref.getCpuStatFile());
}

float Processor::Utilization() {
    bool is_first_cycle;

    long int previous_idle, current_idle;
    long int previous_non_idle, current_non_idle;
    long int previous_total, current_total;
    long int idle_increment, total_increment;

    float cpu_utilization;

    // Saves previous values before updating.
    std::vector<long int> previous_cpus_jiffies = current_cpus_jiffies;

    // Updates current cpus jiffies with latest information available.
    getAggregatedCPUInfo();

    previous_idle = previous_cpus_jiffies[LinuxParser::CPUStates::kIdle_] +
                    previous_cpus_jiffies[LinuxParser::CPUStates::kIOwait_];
    current_idle = current_cpus_jiffies[LinuxParser::CPUStates::kIdle_] +
                   current_cpus_jiffies[LinuxParser::CPUStates::kIOwait_];

    previous_non_idle = previous_cpus_jiffies[LinuxParser::CPUStates::kUser_] +
                        previous_cpus_jiffies[LinuxParser::CPUStates::kNice_] +
                        previous_cpus_jiffies[LinuxParser::CPUStates::kSystem_] +
                        previous_cpus_jiffies[LinuxParser::CPUStates::kIRQ_] +
                        previous_cpus_jiffies[LinuxParser::CPUStates::kSoftIRQ_] +
                        previous_cpus_jiffies[LinuxParser::CPUStates::kSteal_];
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

    if (is_first_cycle) {
        cpu_utilization = 0.0;
    } else {
        cpu_utilization = static_cast<float>(total_increment - idle_increment) / static_cast<float>(total_increment);

    }

    return cpu_utilization;
}

