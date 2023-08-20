#include "os_files.h"

OSFiles::OSFiles() {
    ReadSystemFiles();
}

void OSFiles::ReadSystemFiles() {
    kCpuStatFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
    kUptimeFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kUptimeFilename);
    kMemInfoFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kMemInfoFilename);
    kVersionFile = LinuxParser::ReadTextFile(LinuxParser::kProcDirectory + LinuxParser::kVersionFilename);
    kPasswordFileRaw = LinuxParser::ReadTextFile(LinuxParser::kPasswordPath);
    kOSFileRaw = LinuxParser::ReadTextFile(LinuxParser::kOSPath);
    ParseSystemFiles();
}

void OSFiles::ParseSystemFiles() {
    kOSFileParsed = LinuxParser::ParseOSFile(kOSFileRaw);
    kPasswordFileParsed = LinuxParser::ParsePasswordFile(kPasswordFileRaw);
}
