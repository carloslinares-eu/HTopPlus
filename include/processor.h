#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>
#include <iostream>
#include <ctime>

#include "os_files.h"
#include "linux_parser.h"

using std::string;
using std::vector;

class Processor {
 public:
    explicit Processor(OSFiles& FilesRef);
    [[nodiscard]] float getUtilization() const {return utilization;}
    std::vector<long int>& getCurrentAggregatedCPUInfo() {return current_cpus_jiffies;}
    long int& getUsageIncrement() {return current_usage_increment;}

    void Running();

 private:
    void updateAggregatedCpuInfo();
    void calculateCpuUtilization();

    OSFiles& files_ref;

    std::vector<long int> current_cpus_jiffies;
    std::vector<long int> previous_cycle_cpus_jiffies;

    long int current_usage_increment{};
    float utilization{};
};

#endif