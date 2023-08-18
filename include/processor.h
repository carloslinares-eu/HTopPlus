#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>
#include <iostream>
#include <ctime>

#include "osfiles.h"
#include "linux_parser.h"

using std::string;
using std::vector;

class Processor {
 public:
    explicit Processor(OSFiles& FilesRef);

    void Running();
    float Utilization();

 private:

    void getAggregatedCPUInfo();

    OSFiles& files_ref;

    std::vector<long int> current_cpus_jiffies;

};

#endif