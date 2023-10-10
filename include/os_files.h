#ifndef MONITOR_OS_FILES_H
#define MONITOR_OS_FILES_H

#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::vector;

namespace LP = LinuxParser;
namespace FS = std::filesystem;

class OSFiles {
public:
    OSFiles() = default;

    void ReadSystemFiles();
    void ParseSystemFiles();

    void Running();

    LP::TextFile& getCpuStatFile() {return kCpuStatFile;}
    LP::TextFile& getUptimeFile() {return kUptimeFile;}
    LP::TextFile& getMemInfoFile() {return kMemInfoFile;}
    LP::TextFile& getVersionFile() {return kVersionFile;}
    LP::TextFile& getOSFileParsed() {return kOSFileParsed;}
    LP::TextFile& getPasswordFileParsed() {return kPasswordFileParsed;}

private:
    LP::TextFile kCpuStatFile;
    LP::TextFile kUptimeFile;
    LP::TextFile kMemInfoFile;
    LP::TextFile kVersionFile;
    LP::TextFile kOSFileRaw;
    LP::TextFile kPasswordFileRaw;

    LP::TextFile kOSFileParsed;
    LP::TextFile kPasswordFileParsed;

};

#endif
