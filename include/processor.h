#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Processor {
 public:
   float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
    void GetSystemJiffies(const vector<vector<string>>& kStatFile);
    long system_jiffies;
};

#endif