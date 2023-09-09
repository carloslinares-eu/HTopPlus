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

    vector<vector<string>>& getStatFile() {return KStatFile;}
    vector<vector<string>>& getStatusFile() {return kStatusFile;}
    vector<vector<string>>& getCmdLineFile() {return kCmdLineFile;}

    void ReadPIDFiles();

private:
    string pid_folder_path_in_proc;

    // System wide files
    vector<vector<string>> kCmdLineFile;
    vector<vector<string>> KStatFile;
    vector<vector<string>> kStatusFile;

    // Processes files
};


#endif //MONITOR_PID_FILES_H
