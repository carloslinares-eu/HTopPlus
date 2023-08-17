#include "processor.h"
#include "linux_parser.h"

float Processor::Utilization() {
    return 0.0;
}

// TODO: Add pointer to system in the constructor.
void Processor::GetSystemJiffies(const vector<vector<string>>& kStatFile)  {
    system_jiffies = LinuxParser::Jiffies(kStatFile);
}
