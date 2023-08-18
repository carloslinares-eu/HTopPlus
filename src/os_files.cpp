#include "os_files.h"

OSFiles::OSFiles() {
    ReadSystemFiles();
}

void OSFiles::ReadSystemFiles() {
    kCpuStatFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
    kUptimeFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kUptimeFilename);
    kMemInfoFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kMemInfoFilename);
    kVersionFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kVersionFilename);
    kOSFileRaw = LinuxParser::ReadTextFile(LinuxParser::kOSPath);
    kOSFileParsed = LinuxParser::ParseOSFile(kOSFileRaw);
}
