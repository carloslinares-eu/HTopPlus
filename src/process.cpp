#include <unistd.h>
#include <cctype>
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
    current_process_jiffies = 0;
    previous_process_jiffies = 0;
}

int Process::getPid() { return pid; }

string Process::getUser() { return user; }

// TODO: Return the command that generated this process
string Process::getCommand() { return command; }

// TODO: Return this process's cpu utilization
float Process::getCpuUtilization() const { return cpu_utilization; }

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
    calculateCpuUtilization();
    updateRamUtilization();
    updateUptime();
}

void Process::calculateCpuUtilization() {
    bool is_first_cycle;
    current_process_jiffies = LinuxParser::ActiveJiffiesProcess(files.getkStatFile());
    long int latest_cpu_increment = cpu.getUsageIncrement();

    is_first_cycle = previous_process_jiffies == 0;

    if (is_first_cycle) {
        cpu_utilization = 0.0;
    }


}

void Process::updateRamUtilization() {

}

void Process::updateUptime() {
    uptime = LP::UpTime(files.getkStatFile());
}










