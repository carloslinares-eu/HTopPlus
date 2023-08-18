#ifndef MONITOR_OSFILES_H
#define MONITOR_OSFILES_H

#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::vector;

class OSFiles {
public:
    OSFiles();

    void ReadSystemFiles();
    void Running();

    vector<vector<string>> &getCmdlineFile() {return kCmdlineFile;}
    vector<vector<string>> &getCpuInfoFile() {return kCpuInfoFile;}
    vector<vector<string>> &getStatusFile() {return kStatusFile;}
    vector<vector<string>> &getCpuStatFile() {return kCpuStatFile;}
    vector<vector<string>> &getUptimeFile() {return kUptimeFile;}
    vector<vector<string>> &getMemInfoFile() {return kMemInfoFile;}
    vector<vector<string>> &getVersionFile() {return kVersionFile;}
    vector<vector<string>> &getOSFileRaw() {return kOSFileRaw;}
    vector<vector<string>> &getOSFileParsed() {return kOSFileParsed;}
    vector<vector<string>> &getPasswordFile() {return kPasswordFile;}

private:
    vector<vector<string>> kCmdlineFile;
    vector<vector<string>> kCpuInfoFile;
    vector<vector<string>> kStatusFile;
    vector<vector<string>> kCpuStatFile;
    vector<vector<string>> kUptimeFile;
    vector<vector<string>> kMemInfoFile;
    vector<vector<string>> kVersionFile;
    vector<vector<string>> kOSFileRaw;
    vector<vector<string>> kOSFileParsed;
    vector<vector<string>> kPasswordFile;
};


#endif //MONITOR_OSFILES_H
