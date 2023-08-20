#include <unistd.h>
#include <cctype>
#include <sstream>
#include <utility>
#include <vector>

#include "process.h"

using std::to_string;
using std::vector;

Process::Process(OSFiles &input_files_ref, int input_pid, string input_user, string input_command) :
files_ref(input_files_ref), pid(input_pid), user(std::move(input_user)), command(std::move(input_command)) {
    cpu_utilization = 0;
    ram_utilization = "0";
    uptime = 0;
}

// TODO: Return this process's ID
int Process::getPid() { return pid; }

// TODO: Return the user (name) that generated this process
string Process::getUser() { return user; }

// TODO: Return the command that generated this process
string Process::getCommand() { return command; }

// TODO: Return this process's cpu utilization
float Process::getCpuUtilization() { return cpu_utilization; }

// TODO: Return this process's memory utilization
string Process::getRamUtilization() { return ram_utilization; }

// TODO: Return the age of this process (in seconds)
long int Process::getUpTime() { return uptime; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const &a[[maybe_unused]]) const { return true; }

