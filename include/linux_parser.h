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
    typedef  vector<vector<string>> TextFile;
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
    int TotalMemory(const TextFile& kMemInfoFile);
    int AvailableMemory(const TextFile& kMemInfoFile);
    float MemoryUtilization(const TextFile& kMemInfoFile);
    long UpTimeTotal(const TextFile& kUptimeFile);
    std::vector<long int> getAggregatedCPUInfo(const TextFile& kStatFile);
    
        [[maybe_unused]] long UpTimeEffective(const TextFile& kUptimeFile);
    std::vector<int> Pids();
    int TotalProcesses(const TextFile& kStatFile);
    int RunningProcesses(const TextFile& kStatFile);
    string Kernel(const TextFile& kVersionFileRef);
    TextFile ParseOSFile(const TextFile& kOSFileRef);
    TextFile ParsePasswordFile(const TextFile& kPasswordFileRefRaw);
    string OperatingSystem(const TextFile& kOSFileRef);
    
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
    
        [[maybe_unused]] [[maybe_unused]] long Jiffies(const TextFile& kStatFile);
    long ActiveJiffiesProcess(const TextFile& kStatFile);
    long ActiveJiffies(const TextFile& kStatFile);
    long IdleJiffies(const TextFile& kStatFile);
    
    
    
    // General functions
    TextFile ReadTextFile(const string& file_path);
    vector<string> ReadLine(const string& line);
    TextFile ReplaceAllInstancesInFile (const TextFile& input_file,
                                                      const string& to_find,
                                                      const string& to_replace_with);
    bool isInteger(const string& input_string);
    
    // getSystemProcesses
    string Command(int pid);
    string ProcessUsedRam(const TextFile& kStatusFile);
    string Uid(int pid);
    string User(int pid, const TextFile& kPasswordFile);
    long int UpTime(TextFile& kPdiStatFile);
    
    struct PidFiles {
        int Pid;
        bool all_files_present;
        TextFile kPidCmdLineFile;
        TextFile kPidStatFile;
        TextFile kPidStatusFile;
        };
    
    
    struct ProcessInputInformation {
        PidFiles current_process_files;
        TextFile password_file_parsed;
        long int current_usage_increment;
        };

};  // namespace LinuxParser



#endif