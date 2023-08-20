#include <unistd.h>
#include <cctype>
#include <sstream>
#include <utility>
#include <vector>

#include "process.h"

using std::to_string;
using std::vector;

Process::Process(OSFiles &input_files_ref, int input_pid, string input_user, string input_command) :
os_files_ref(input_files_ref),
pid(input_pid),
user(std::move(input_user)),
command(std::move(input_command)),
files(input_pid) {
    cpu_utilization = 0;
    ram_utilization = "0";
    uptime = 0;
}

int Process::getPid() { return pid; }

string Process::getUser() { return user; }

// TODO: Return the command that generated this process
string Process::getCommand() { return command; }

// TODO: Return this process's cpu utilization
float Process::getCpuUtilization() { return cpu_utilization; }

// TODO: Return this process's memory utilization
string Process::getRamUtilization() { return ram_utilization; }

long int Process::getUpTime() {
    return LP::UpTime(files.getkStatFile());
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

}

void Process::updateRamUtilization() {

}

void Process::updateUptime() {

}










