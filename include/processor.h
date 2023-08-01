#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Processor {
 public:
   float Utilization();

  // TODO: Declare any necessary private members
 private:

    void GetSystemJiffies(const vector<vector<string>>& kStatFile);
    long int system_jiffies;
    long int previous_cycle_utilization;
    long int current_cycle_utilization;
};

#endif