#include "process.h"

#include <utility>


Process::Process(int pid, string user) : pid(pid), user(std::move(user)) {
    setConstantInformation();
}

void Process::setConstantInformation() {
    setPidPath();
    setFilesPaths();
    command = LP::Command(pid);
}

void Process::setPidPath() {
    pid_path = LP::kProcDirectory + "/" + std::to_string(pid);
}

void Process::updateDynamicInformation(const long int & cpu_current_usage_increment) {
    readFiles();
    updateCpuUtilization(cpu_current_usage_increment);
    updateRamUtilization();
    updateUptime();
}

void Process::readFiles() {
    files[cmdline] = LP::ReadTextFile(files_paths[cmdline]);
    files[stat] = LP::ReadTextFile(files_paths[stat]);
    files[status] = LP::ReadTextFile(files_paths[status]);
}

void Process::setFilesPaths() {
    files_paths[cmdline] = pid_path + LP::kCmdlineFilename;
    files_paths[stat] = pid_path + LP::kStatFilename;
    files_paths[status] = pid_path + LP::kStatusFilename;
}

//bool Process::allFilesArePresent() {
//    bool all_files_exist = std::ranges::all_of(files_paths, [](string& file_path)
//    {return FS::exists(file_path);});
//    return all_files_exist;
//}


void Process::updateCpuUtilization(const long int & cpu_current_usage_increment) {
    long int current_jiffies_increment;
    long int latest_cpu_increment = cpu_current_usage_increment;

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
    ram_utilization = LP::ProcessUsedRam(files[status]);
}

void Process::updateUptime() {
    uptime = LP::UpTime(files[stat]);
}

void Process::updateJiffies() {
    sum_current_process_jiffies = LP::ActiveJiffiesProcess(files[stat]);
}

void Process::saveJiffiesForNextCycle() {
    sum_previous_process_jiffies = sum_current_process_jiffies;
}
