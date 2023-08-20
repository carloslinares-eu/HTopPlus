#include "pid_files.h"

PIDFiles::PIDFiles(int &pid) : pid_folder_path_in_proc(LP::kProcDirectory + "/" + std::to_string(pid)) {}

void PIDFiles::ReadPIDFiles() {
    kCmdLineFile = LinuxParser::ReadTextFile(pid_folder_path_in_proc + LP::kCmdlineFilename);
    KStatFile = LinuxParser::ReadTextFile(pid_folder_path_in_proc + LP::kStatFilename);
    kStatusFile = LinuxParser::ReadTextFile(pid_folder_path_in_proc + LP::kStatusFilename);
}
