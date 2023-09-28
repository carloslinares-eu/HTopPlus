#include "os_files.h"


void OSFiles::Running() {
    ClearPidsFiles();
    ReadSystemFiles();
    ParseSystemFiles();
    ReadPidsFiles();
}

void OSFiles::ClearPidsFiles() {
    all_pids_files.clear();
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

void OSFiles::ReadPidsFiles() {
    for (int pid : system_pids) {
        current_pid = pid;

        current_pid_cmdline_file.clear();
        current_pid_stat_file.clear();
        current_pid_status_file.clear();

        getPidPath();
        getFilesPathInPid();
        checkIfPdiHasAllFilesNeeded();

        if (pid_has_all_files) {
            string path_of_current_pid_cmdline_file = files_paths_in_current_pid[needed_files_in_pid::cmdline];
            string path_of_current_pid_stat_file = files_paths_in_current_pid[needed_files_in_pid::stat];
            string path_of_current_pid_status_file = files_paths_in_current_pid[needed_files_in_pid::status];

            current_pid_cmdline_file = LP::ReadTextFile(path_of_current_pid_cmdline_file);
            current_pid_stat_file = LP::ReadTextFile(path_of_current_pid_stat_file);
            current_pid_status_file = LP::ReadTextFile(path_of_current_pid_status_file);

        }

        LP::PidFiles current_pid_files {current_pid,  pid_has_all_files,
                                    current_pid_cmdline_file,
                                    current_pid_stat_file,
                                    current_pid_status_file};

        all_pids_files.push_back(current_pid_files);
    }
}

void OSFiles::getPidPath() {
    current_pid_path = LP::kProcDirectory + "/" + std::to_string(current_pid);
}

void OSFiles::getFilesPathInPid() {
    files_paths_in_current_pid.clear();
    files_paths_in_current_pid.push_back(current_pid_path + LP::kCmdlineFilename);
    files_paths_in_current_pid.push_back(current_pid_path + LP::kStatFilename);
    files_paths_in_current_pid.push_back(current_pid_path + LP::kStatusFilename);
}

void OSFiles::checkIfPdiHasAllFilesNeeded() {
    pid_has_all_files = std::ranges::all_of(files_paths_in_current_pid, [](string& file_path)
    {return FS::exists(file_path);});
}
