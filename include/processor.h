#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>
#include <iostream>
#include <ctime>

using std::string;
using std::vector;

class Processor {
 public:
    Processor();

    void Running();
    float Utilization();



 private:

    void getAggregatedCPUInfo();
    void ReadSystemFiles();

    vector<vector<string>> kCpuStatFile;
    std::vector<long int> current_cpus_jiffies;

};

#endif