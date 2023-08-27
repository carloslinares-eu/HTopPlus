#include <sstream>
#include <utility>
#include <vector>

#include "process.h"

using std::to_string;
using std::vector;

Process::Process(int input_pid, string input_user, string input_command, Processor &system_cpu) :
pid(input_pid),
user(std::move(input_user)),
command(std::move(input_command)),
cpu(system_cpu),
files(input_pid) {
    cpu_utilization = 0;
    ram_utilization = "0";
    uptime = 0;
    sum_current_process_jiffies = LinuxParser::ActiveJiffiesProcess(files.getStatFile());
    sum_previous_process_jiffies = sum_current_process_jiffies;
    updateDynamicInformation();
}

// TODO: Return this process's memory utilization
string Process::getRamUtilization() { return ram_utilization; }

long int Process::getUpTime() const {
    return uptime;
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const &a[[maybe_unused]]) const { return true; }


void Process::updateDynamicInformation() {
    files.ReadPIDFiles();
    updateCpuUtilization();
    updateRamUtilization();
    updateUptime();
}

void Process::updateCpuUtilization() {
    long int current_jiffies_increment;
    long int latest_cpu_increment = cpu.getUsageIncrement();

    updateJiffies();
    current_jiffies_increment = sum_current_process_jiffies - sum_previous_process_jiffies;

    cpu_utilization = static_cast<float>(current_jiffies_increment)/static_cast<float>(latest_cpu_increment);

    saveJiffiesForNextCycle();
}

void Process::updateRamUtilization() {

}

void Process::updateUptime() {
    uptime = LP::UpTime(files.getStatFile());
}

void Process::updateJiffies() {
    sum_current_process_jiffies = LinuxParser::ActiveJiffiesProcess(files.getStatFile());
}


void Process::saveJiffiesForNextCycle() {
    sum_previous_process_jiffies = sum_current_process_jiffies;
}









