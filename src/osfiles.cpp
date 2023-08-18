#include "osfiles.h"

OSFiles::OSFiles() {
    ReadSystemFiles();
}

void OSFiles::ReadSystemFiles() {
    kCmdlineFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kCmdlineFilename);
    kCpuInfoFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kCpuInfoFilename);
    kStatusFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kStatusFilename);
    kCpuStatFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
    kUptimeFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kUptimeFilename);
    kMemInfoFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kMemInfoFilename);
    kVersionFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kVersionFilename);
    kPasswordFile = LinuxParser::ReadTextFile(LinuxParser::kPasswordPath);
    kOSFileRaw = LinuxParser::ReadTextFile(LinuxParser::kOSPath);
    kOSFileParsed = LinuxParser::ParseOSFile(kOSFileRaw);
}

void OSFiles::Running() {
    ReadSystemFiles();
}
