#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <charconv>
#include <iostream>
#include "system.h"

using std::vector;
using std::string;
using std::ifstream;
using std::istringstream;



namespace LinuxParser {
// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuInfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMemInfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};

// System
float MemoryUtilization(vector<vector<string>>& system);
long UpTime(vector<vector<string>>& system);
std::vector<int> Pids();
int TotalProcesses(vector<vector<string>>& system);
int RunningProcesses(vector<vector<string>>& system);
std::string Opera

// CPU
enum CPUStates {
  kUser_ = 0,
  kNice_,
  kSystem_,
  kIdle_,
  kIOwait_,
  kIRQ_,
  kSoftIRQ_,
  kSteal_,
  kGuest_,
  kGuestNice_
};
std::vector<std::string> CpuUtilization();
long Jiffies();
long ActiveJiffies();
long ActiveJiffies(int pid);
long IdleJiffies();

// General functions
vector<vector<string>> ReadTextFile(const string& file_path);
vector<string> ReadLine(const string& line);


// Processes
std::string Command(int pid);
std::string Ram(int pid);
std::string Uid(int pid);
std::string User(int pid);
long int UpTime(int pid);
};  // namespace LinuxParser

#endif