#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { return 0.0; }

void Processor::GetSystemJiffies(const vector<vector<string>>& kStatFile)  {
    system_jiffies = LinuxParser::Jiffies(kStatFile);
}

