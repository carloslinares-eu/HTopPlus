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
#include <format>
#include <algorithm>
#include <map>
#include <array>
#include <filesystem>

using std::vector;
using std::string;
using std::ifstream;
using std::istringstream;
using std::stof;
using std::to_string;

namespace fs = std::filesystem;


namespace LinuxParser {
// Paths
const string kProcDirectory{"/proc"};
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
int TotalMemory(const vector<vector<string>>& kMemInfoFile);
int AvailableMemory(const vector<vector<string>>& kMemInfoFile);
float MemoryUtilization(const vector<vector<string>>& kMemInfoFile);
long UpTimeTotal(const vector<vector<string>>& kUptimeFile);
std::vector<long int> getAggregatedCPUInfo(const vector<vector<string>>& kStatFile);

    [[maybe_unused]] long UpTimeEffective(const vector<vector<string>>& kUptimeFile);
std::vector<int> Pids();
int TotalProcesses(const vector<vector<string>>& kStatFile);
int RunningProcesses(const vector<vector<string>>& kStatFile);
string Kernel(const vector<vector<string>>& kVersionFileRef);
vector<vector<string>> ParseOSFile(const vector<vector<string>>& kOSFileRef);
string OperatingSystem(const vector<vector<string>>& kOSFileRef);

// cpu. To be used as index of vector current_cpus_jiffies
enum CPUStates {
  kUser_ = 0,
  kNice_ = 1,
  kSystem_ = 2,
  kIdle_ = 3,
  kIOwait_ = 4,
  kIRQ_ = 5,
  kSoftIRQ_ = 6,
  kSteal_ = 7,
  kGuest_ = 8,
  kGuestNice_ = 9
};

// processes
std::vector<string> CpuUtilization();
long Jiffies(const vector<vector<string>>& kStatFile);
long ActiveJiffies(int pid[[maybe_unused]]);
long ActiveJiffies(const vector<vector<string>>& kStatFile);
long IdleJiffies(const vector<vector<string>>& kStatFile);



// General functions
vector<vector<string>> ReadTextFile(const string& file_path);
vector<string> ReadLine(const string& line);
vector<vector<string>> ReplaceAllInstancesInFile (const vector<vector<string>>& input_file,
                                                  const string& to_find,
                                                  const string& to_replace_with);
bool isInteger(const string& input_string);

// getSystemProcesses
string Command(int pid);
string Ram(int pid);
string Uid(int pid);
string User(int pid);
long int UpTime(int pid);
};  // namespace LinuxParser

#endif