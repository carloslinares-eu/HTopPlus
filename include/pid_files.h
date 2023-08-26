#ifndef MONITOR_PID_FILES_H
#define MONITOR_PID_FILES_H

#include <string>
#include <vector>


#include "linux_parser.h"

using std::string;
using std::vector;

namespace LP = LinuxParser;

class PIDFiles {
public:
    explicit PIDFiles(int& pid);

    vector<vector<string>>& getkStatFile() {return KStatFile;}

    void ReadPIDFiles();

private:
    const string pid_folder_path_in_proc;

    vector<vector<string>> kCmdLineFile;
    vector<vector<string>> KStatFile;
    vector<vector<string>> kStatusFile;
};


#endif //MONITOR_PID_FILES_H
