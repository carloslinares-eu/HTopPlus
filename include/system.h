#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

using std::string;
using std::vector;

class System {
 public:
    System();
    Processor& Cpu();
    vector<Process>& Processes();
    float MemoryUtilization();
    long UpTime();
    int TotalProcesses();
    int RunningProcesses();
    string Kernel();
    string OperatingSystem();
    void ReadSystemFiles();

 private:
  Processor cpu_ = {};
  vector<Process> processes_ = {};

   vector<vector<string>> kCmdlineFile;
   vector<vector<string>> kCpuInfoFile;
   vector<vector<string>> kStatusFile;
   vector<vector<string>> kStatFile;
   vector<vector<string>> kUptimeFile;
   vector<vector<string>> kMemInfoFile;
   vector<vector<string>> kVersionFile;
   vector<vector<string>> kOSFileRaw;
   vector<vector<string>> kOSFileParsed;
   vector<vector<string>> kPasswordFile;

};

#endif