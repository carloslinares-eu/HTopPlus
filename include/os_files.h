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
    explicit OSFiles(vector<int> &updated_pids) : system_pids(updated_pids){};

    void ReadSystemFiles();
    void ParseSystemFiles();
    void ReadPidsFiles();

    void Running();

    LP::TextFile& getCpuStatFile() {return kCpuStatFile;}
    LP::TextFile& getUptimeFile() {return kUptimeFile;}
    LP::TextFile& getMemInfoFile() {return kMemInfoFile;}
    LP::TextFile& getVersionFile() {return kVersionFile;}
    LP::TextFile& getOSFileParsed() {return kOSFileParsed;}
    LP::TextFile& getPasswordFileParsed() {return kPasswordFileParsed;}

private:
    vector<int>& system_pids;

    LP::TextFile kCpuStatFile;
    LP::TextFile kUptimeFile;
    LP::TextFile kMemInfoFile;
    LP::TextFile kVersionFile;
    LP::TextFile kOSFileRaw;
    LP::TextFile kPasswordFileRaw;

    LP::TextFile kOSFileParsed;
    LP::TextFile kPasswordFileParsed;



    void getPidPath();
    void getFilesPathInPid();
    void checkIfPdiHasAllFilesNeeded();
};


#endif //MONITOR_OS_FILES_H
