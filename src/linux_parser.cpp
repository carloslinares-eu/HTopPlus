#include "linux_parser.h"


string LinuxParser::OperatingSystem(const vector<vector<string>> &kOSFileRefParsed) {
    for (vector<string> line: kOSFileRefParsed) {
        string key = line[0];
        if (key == "PRETTY_NAME") {
            string value = line[1];
            std::replace(value.begin(), value.end(), '_', ' ');
            return value;
        }
    }
}

string LinuxParser::Kernel(const vector<vector<string>> &kVersionFileRef) {
    return kVersionFileRef[0][2];
}

vector<int> LinuxParser::Pids() {
    vector<int> pids;
    vector<string> folderNames;

    if (!fs::is_directory(kProcDirectory)) {
        std::cerr << "Error: '" << kProcDirectory << "' is not a valid directory." << std::endl;
        return pids;
    }

    for (const auto& entry : fs::directory_iterator(kProcDirectory)) {
        if (fs::is_directory(entry)) {
            folderNames.push_back(entry.path().filename());
        }
    }

    return pids;
}

int LinuxParser::TotalMemory(const vector<vector<string>> &kMemInfoFile) {
    for (vector<string> line: kMemInfoFile) {
        string key = line[0];
        if (key == "MemTotal:") {
            string total_memory = line[1];
            return std::stoi(total_memory);
        }
    }
}

int LinuxParser::AvailableMemory(const vector<vector<std::string>> &kMemInfoFile) {
    for (vector<string> line: kMemInfoFile) {
        string key = line[0];
        if (key == "MemAvailable:") {
            string available_memory = line[1];
            return std::stoi(available_memory);
        }
    }
}

float LinuxParser::MemoryUtilization(const vector<vector<string>> &kMemInfoFile) {
    int available_memory = LinuxParser::AvailableMemory(kMemInfoFile);
    int total_memory = LinuxParser::TotalMemory(kMemInfoFile);
    float memory_utilization = 1.0f - static_cast<float>(available_memory) / static_cast<float>(total_memory);
    return memory_utilization;
}

long int LinuxParser::UpTimeTotal(const vector<vector<string>> &kUptimeFile) {
    long int uptime_total;
    string uptime_total_s = kUptimeFile[0][0];
    std::from_chars(uptime_total_s.data(), uptime_total_s.data() + uptime_total_s.size(), uptime_total);
    return uptime_total;
}

[[maybe_unused]] long int LinuxParser::UpTimeEffective(const vector<vector<string>> &kUptimeFile) {
    long int uptime_effective;
    string uptime_effective_s = kUptimeFile[0][1];
    std::from_chars(uptime_effective_s.data(), uptime_effective_s.data() + uptime_effective_s.size(), uptime_effective);
    return uptime_effective;
}

long LinuxParser::Jiffies(const vector<vector<string>> &kStatFile) {
    long system_jiffies;
    string user = kStatFile[0][1];
    system_jiffies = std::stol(user);
    return system_jiffies;
}


std::vector<long int> LinuxParser::getAggregatedCPUInfo(const vector<vector<string>> &kStatFile) {
    std::vector<long int> all_cpus_jiffies;
    for (const string &jiffies_value: kStatFile[0]) {
        if (jiffies_value == "cpu") {
            continue;
        }
        long int jiffies_numeric = std::stol(jiffies_value);
        all_cpus_jiffies.push_back(jiffies_numeric);
    }
    return all_cpus_jiffies;
}


// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies(const vector<vector<string>> &kStatFile) { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies(const vector<vector<string>> &kStatFile) { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

int LinuxParser::TotalProcesses(const vector<vector<string>> &kStatFile) {
    for (vector<string> line: kStatFile) {
        string key = line[0];
        if (key == "processes") {
            string value = line[1];
            int total_processes = std::stoi(value);
            return total_processes;
        }
    }
}

int LinuxParser::RunningProcesses(const vector<vector<string>> &kStatFile) {
    for (vector<string> line: kStatFile) {
        string key = line[0];
        if (key == "procs_running") {
            string value = line[1];
            int running_processes = std::stoi(value);
            return running_processes;
        }
    }
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return {}; }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return {}; }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return {}; }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return {}; }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }


// Generic functions to follow the DRY principle
vector<vector<string>> LinuxParser::ReadTextFile(const string &file_path) {
    vector<vector<string>> read_file;
    ifstream file_stream(file_path);
    if (file_stream.is_open()) {
        string current_line;
        while (std::getline(file_stream, current_line)) {
            vector<string> read_line;
            read_line = ReadLine(current_line);
            read_file.push_back(read_line);
        }
    }
    return read_file;
}

vector<string> LinuxParser::ReadLine(const std::string &line) {
    vector<string> read_line;
    istringstream line_stream(line);
    string current_word;
    while (line_stream >> current_word) {
        read_line.push_back(current_word);
    }
    return read_line;
}

vector<vector<string>> LinuxParser::ParseOSFile(const vector<vector<string>> &kOSFileRefRaw) {
    vector<vector<string>> parsed_os_file;

    for (const vector<string> &line: kOSFileRefRaw) {
        // kOSFile is expected to have only one element in the vector representing the line.
        // Thus taking only the first element.
        vector<string> parsed_os_line;
        string line_string;
        for (const string &word: line) {
            line_string += word + " ";
        }
        std::replace(line_string.begin(), line_string.end(), ' ', '_');
        std::replace(line_string.begin(), line_string.end(), '=', ' ');
        std::replace(line_string.begin(), line_string.end(), '"', ' ');

        std::istringstream line_stream(line_string);
        string word;

        while (line_stream >> word) {
            parsed_os_line.push_back(word);
        }
        parsed_os_file.push_back(parsed_os_line);
    }
    return parsed_os_file;
}

bool LinuxParser::isInteger(const std::string &input_string) {
    try {
        size_t pos;
        int result = std::stoi(input_string, &pos);
        return pos == input_string.size(); // Check if entire string was converted
    } catch (const std::invalid_argument&) {
        return false; // Conversion failed
    } catch (const std::out_of_range&) {
        return false; // Conversion out of range
    }
}