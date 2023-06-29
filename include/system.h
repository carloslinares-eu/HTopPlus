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
  Processor& Cpu();                             // TODO: See src/system.cpp
  vector<Process>& Processes();            // TODO: See src/system.cpp
  static float MemoryUtilization();             // TODO: See src/system.cpp
  static long UpTime();                         // TODO: See src/system.cpp
  static int TotalProcesses();                  // TODO: See src/system.cpp
  static int RunningProcesses();                // TODO: See src/system.cpp
  static string Kernel();                  // TODO: See src/system.cpp
  static string OperatingSystem();         // TODO: See src/system.cpp

  void ReadSystemFiles();

  vector<vector<string>> getKCmdlineFile(){return kCmdlineFile;}
  vector<vector<string>> getKCpuInfoFile(){return kCpuInfoFile;};
  vector<vector<string>> getKStatusFile(){return kStatusFile;}
  vector<vector<string>> getKStatFile(){return kStatFile;}
  vector<vector<string>> getKUptimeFile(){return kUptimeFile;}
  vector<vector<string>> getKMemInfoFile(){return kMemInfoFile;}
  vector<vector<string>> getKVersionFile(){return kVersionFile;}
  vector<vector<string>> getKOSFile(){return kOSFile;}
  vector<vector<string>> getKPasswordFile(){return kPasswordFile;}

 private:
  Processor cpu_ = {};
  vector<Process> processes_ = {};

  vector<vector<string>> kCmdlineFile;
  vector<vector<string>> kCpuInfoFile;
  vector<vector<string>> kStatusFile;
  vector<vector<string>> kStatFile;
  vector<vector<string>> kUptimeFile;
  vector<vector<string>> kMemInfoFile;
  static vector<vector<string>> kVersionFile;
  vector<vector<string>> kOSFile;
  vector<vector<string>> kPasswordFile;

};

#endif