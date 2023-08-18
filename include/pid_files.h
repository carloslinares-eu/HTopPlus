#ifndef MONITOR_PID_FILES_H
#define MONITOR_PID_FILES_H

#include <string>
#include <vector>

using std::string;
using std::vector;

#include "linux_parser.h"


class PIDFiles {
public:
    PIDFiles();

    void ReadPIDFiles();

private:
    vector<vector<string>> kCmdLineFile;
    vector<vector<string>> KStatFile;
    vector<vector<string>> kStatusFile;
};


#endif //MONITOR_PID_FILES_H
