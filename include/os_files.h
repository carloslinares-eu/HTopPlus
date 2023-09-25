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

    vector<vector<string>>& getCpuStatFile() {return kCpuStatFile;}
    vector<vector<string>>& getUptimeFile() {return kUptimeFile;}
    vector<vector<string>>& getMemInfoFile() {return kMemInfoFile;}
    vector<vector<string>>& getVersionFile() {return kVersionFile;}
    vector<vector<string>>& getOSFileParsed() {return kOSFileParsed;}
    vector<vector<string>>& getPasswordFileParsed() {return kPasswordFileParsed;}

    vector<LP::PidFiles> getAllPidsFiles() {return all_pids_files;}

    void getUpdatedListOfPIDs(vector<int>& updated_pids) {system_pids = updated_pids;}

private:
    vector<int>& system_pids;

    vector<vector<string>> kCpuStatFile;
    vector<vector<string>> kUptimeFile;
    vector<vector<string>> kMemInfoFile;
    vector<vector<string>> kVersionFile;
    vector<vector<string>> kOSFileRaw;
    vector<vector<string>> kPasswordFileRaw;

    vector<vector<string>> kOSFileParsed;
    vector<vector<string>> kPasswordFileParsed;

    int current_pid{};
    string current_pid_path;
    vector<string> files_paths_in_current_pid;
    bool pid_has_all_files{};

    vector<vector<string>> current_pid_cmdline_file;
    vector<vector<string>> current_pid_stat_file;
    vector<vector<string>> current_pid_status_file;

    vector<LP::PidFiles> all_pids_files;

    enum needed_files_in_pid {cmdline = 0,
            stat = 1,
            status = 2};

    void getPidPath();
    void getFilesPathInPid();
    void checkIfPdiHasAllFilesNeeded();
};


#endif //MONITOR_OS_FILES_H
