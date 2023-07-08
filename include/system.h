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

  static vector<vector<string>> kCmdlineFile;
  static vector<vector<string>> kCpuInfoFile;
  static vector<vector<string>> kStatusFile;
  static vector<vector<string>> kStatFile;
  static vector<vector<string>> kUptimeFile;
  static vector<vector<string>> kMemInfoFile;
  static vector<vector<string>> kVersionFile;
  static vector<vector<string>> kOSFile;
  static vector<vector<string>> kPasswordFile;

};

#endif