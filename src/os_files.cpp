#include "os_files.h"


void OSFiles::Running() {
    ReadSystemFiles();
    ParseSystemFiles();
}

void OSFiles::ReadSystemFiles() {
    kCpuStatFile = LP::ReadTextFile(LP::kProcDirectory + LP::kStatFilename);
    kUptimeFile = LP::ReadTextFile(LP::kProcDirectory + LP::kUptimeFilename);
    kMemInfoFile = LP::ReadTextFile(LP::kProcDirectory + LP::kMemInfoFilename);
    kVersionFile = LP::ReadTextFile(LP::kProcDirectory + LP::kVersionFilename);
    kPasswordFileRaw = LP::ReadTextFile(LP::kPasswordPath);
    kOSFileRaw = LP::ReadTextFile(LP::kOSPath);
}

void OSFiles::ParseSystemFiles() {
    kOSFileParsed = LP::ParseOSFile(kOSFileRaw);
    kPasswordFileParsed = LP::ParsePasswordFile(kPasswordFileRaw);
}


