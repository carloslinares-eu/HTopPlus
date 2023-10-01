#include "process.h"


Process::Process(int pid) : pid(pid) {}

void Process::updateDynamicInformation() {
    if (process_is_active) {
        updateCpuUtilization();
        updateRamUtilization();
        updateUptime();
    }
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


void Process::updateCpuUtilization() {
    long int current_jiffies_increment;
    long int latest_cpu_increment = input_info.current_usage_increment;

    updateJiffies();
    current_jiffies_increment = sum_current_process_jiffies - sum_previous_process_jiffies;

    if (latest_cpu_increment == 0) {
        cpu_utilization = 0.0;
    }
    else {
        cpu_utilization = static_cast<float>(current_jiffies_increment)/static_cast<float>(latest_cpu_increment);
    }

    saveJiffiesForNextCycle();
}

void Process::updateRamUtilization() {
    LP::TextFile StatusFile = input_info.current_process_files.kPidStatusFile;
    ram_utilization = LP::ProcessUsedRam(StatusFile);
}

void Process::updateUptime() {
    LP::TextFile StatFile = input_info.current_process_files.kPidStatFile;
    uptime = LP::UpTime(StatFile);
}

void Process::updateJiffies() {
    LP::TextFile StatFile = input_info.current_process_files.kPidStatFile;
    sum_current_process_jiffies = LP::ActiveJiffiesProcess(StatFile);
}

void Process::saveJiffiesForNextCycle() {
    sum_previous_process_jiffies = sum_current_process_jiffies;
}
