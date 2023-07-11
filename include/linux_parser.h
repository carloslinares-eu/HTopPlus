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
using std::stof;
using std::to_string;


namespace LinuxParser {
// Paths
const string kProcDirectory{"/proc/"};
const string kCmdlineFilename{"/cmdline"};
const string kCpuInfoFilename{"/cpuinfo"};
const string kStatusFilename{"/status"};
const string kStatFilename{"/stat"};
const string kUptimeFilename{"/uptime"};
const string kMemInfoFilename{"/meminfo"};
const string kVersionFilename{"/version"};
const string kOSPath{"/etc/os-release"};
const string kPasswordPath{"/etc/passwd"};

// System
float MemoryUtilization(vector<vector<string>>& system);
long UpTime(vector<vector<string>>& system);
std::vector<int> Pids();
int TotalProcesses(vector<vector<string>>& system);
int RunningProcesses(vector<vector<string>>& system);
string Kernel(const vector<vector<string>>& kVersionFileRef);
string OperatingSystem(const vector<vector<string>>& kOSFileRef);

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
std::vector<string> CpuUtilization();
long Jiffies();
long ActiveJiffies();
long ActiveJiffies(int pid);
long IdleJiffies();

// General functions
vector<vector<string>> ReadTextFile(const string& file_path);
vector<string> ReadLine(const string& line);


// Processes
string Command(int pid);
string Ram(int pid);
string Uid(int pid);
string User(int pid);
long int UpTime(int pid);
};  // namespace LinuxParser

#endif