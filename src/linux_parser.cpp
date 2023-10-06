#include "linux_parser.h"

namespace LP = LinuxParser;

string LinuxParser::OperatingSystem(const LP::TextFile &kOSFileRefParsed) {
    for (vector<string> line: kOSFileRefParsed) {
        string key = line[0];
        if (key == "PRETTY_NAME") {
            string value = line[1];
            std::replace(value.begin(), value.end(), '_', ' ');
            return value;
        }
    }
}

string LinuxParser::Kernel(const LP::TextFile &kVersionFileRef) {
    return kVersionFileRef[0][2];
}

vector<int> LinuxParser::Pids() {
    vector<int> pids;
    auto proc_dir_iterator = fs::directory_iterator(kProcDirectory);

    for (const auto& current_directory : proc_dir_iterator) {
        string current_folder = lastFolderInPath(current_directory.path());
        if (current_folder.length() < 4) {
            continue;
        }
        try {
            int current_pid = std::stoi(current_folder);
            pids.push_back(current_pid);
        }
        catch (const std::invalid_argument& error) {
            continue;
        }
        catch (const std::out_of_range& error) {
            continue;
        }
    }

    return pids;
}

int LinuxParser::TotalMemory(const LP::TextFile &kMemInfoFile) {
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

float LinuxParser::MemoryUtilization(const LP::TextFile &kMemInfoFile) {
    int available_memory = LinuxParser::AvailableMemory(kMemInfoFile);
    int total_memory = LinuxParser::TotalMemory(kMemInfoFile);
    float memory_utilization = 1.0f - static_cast<float>(available_memory) / static_cast<float>(total_memory);
    return memory_utilization;
}

long int LinuxParser::UpTimeTotal(const LP::TextFile &kUptimeFile) {
    long int uptime_total;
    string uptime_total_s = kUptimeFile[0][0];
    std::from_chars(uptime_total_s.data(), uptime_total_s.data() + uptime_total_s.size(), uptime_total);
    return uptime_total;
}


[[maybe_unused]] long LinuxParser::Jiffies(const LP::TextFile &kStatFile) {
    long system_jiffies;
    string user = kStatFile[0][1];
    system_jiffies = std::stol(user);
    return system_jiffies;
}


std::vector<long int> LinuxParser::getAggregatedCPUInfo(const LP::TextFile &kStatFile) {
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

long LinuxParser::ActiveJiffiesProcess(const LP::TextFile &kStatFile) {
    long int user_time = std::stoi(kStatFile[0][13]);
    long int kernel_time = std::stoi(kStatFile[0][14]);
    long int user_children_time = std::stoi(kStatFile[0][15]);
    long int kernel_children_time = std::stoi(kStatFile[0][16]);
    return (user_time + kernel_time + user_children_time + kernel_children_time);
}

int LinuxParser::TotalProcesses(const LP::TextFile &kStatFile) {
    for (vector<string> line: kStatFile) {
        string key = line[0];
        if (key == "processes") {
            string value = line[1];
            int total_processes = std::stoi(value);
            return total_processes;
        }
    }
}

int LinuxParser::RunningProcesses(const LP::TextFile& kStatFile) {
    for (vector<string> line: kStatFile) {
        string key = line[0];
        if (key == "procs_running") {
            string value = line[1];
            int running_processes = std::stoi(value);
            return running_processes;
        }
    }
}

string LinuxParser::Command(int pid) {
    string cmd_line_file_path = kProcDirectory + "/" + std::to_string(pid) + kCmdlineFilename;
    LP::TextFile cmd_line_file = ReadTextFile(cmd_line_file_path);
    if (cmd_line_file.empty()) {
        return "Unknown";
    }
    else {
        return cmd_line_file[0][0];
    }
}

unsigned long LinuxParser::ProcessUsedRam(const LP::TextFile & kStatusFile) {
    long unsigned int process_ram_usage_kb = 0, process_ram_usage_mb;
    unsigned int const kb_in_mb = 1024;
    for (vector<string> line: kStatusFile) {
        string key = line[0];
        if (key != "VmSize:") {
            continue;
        } else {
            process_ram_usage_kb = std::stol(line[1]);
            break;
        }
    }
    process_ram_usage_mb = process_ram_usage_kb / kb_in_mb;
    return process_ram_usage_mb;
}


string LinuxParser::Uid(int pid) {
    string status_file_path = kProcDirectory + "/" + std::to_string(pid) + kStatusFilename;
    LP::TextFile pid_status_file = ReadTextFile (status_file_path);
    return pid_status_file[8][1];
}

string LinuxParser::User(int pid, const LP::TextFile& kPasswordFileParsed) {
    string user_id = Uid(pid);
    for (vector<string> user_information : kPasswordFileParsed) {
        string name = user_information[0];
        string id = user_information[2];
        if (id == user_id) {
            return name;
        }
        else {
            continue;
        }
    }
    return "unknown";
}


long LinuxParser::UpTime(const LP::TextFile & kPdiStatFile) {
    long int active_jiffies = std::stoi(kPdiStatFile[0][21]);
    long int active_time_seconds = active_jiffies / sysconf(_SC_CLK_TCK);
    return active_time_seconds;
}


// Generic functions to follow the DRY principle
LP::TextFile LinuxParser::ReadTextFile(const string &file_path) {
    LP::TextFile read_file;
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

LP::TextFile LinuxParser::ParseOSFile(const LP::TextFile &kOSFileRefRaw) {
    LP::TextFile parsed_os_file;

    for (const vector<string> &line: kOSFileRefRaw) {
        // kOSFile is expected to have only one element in the vector representing the line.
        // Thus taking only the first element.
        vector<string> parsed_os_line;
        string line_string;
        for (const string &word: line) { // This is done to merge all the words in a single
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

LP::TextFile LinuxParser::ParsePasswordFile(const LP::TextFile &kPasswordFileRefRaw) {
    LP::TextFile parsed_pass_file;

    for (const vector<string> &line: kPasswordFileRefRaw) {
        // kPassFile is expected to have only one element in the vector representing the line.
        // Thus taking only the first element.
        vector<string> parsed_os_line;
        string line_string;
        for (const string &word: line) { // This is done to merge all the words in a single
            line_string += word + " ";
        }
        std::replace(line_string.begin(), line_string.end(), ' ', '_');
        std::replace(line_string.begin(), line_string.end(), ':', ' ');

        std::istringstream line_stream(line_string);
        string word;

        while (line_stream >> word) {
            parsed_os_line.push_back(word);
        }
        parsed_pass_file.push_back(parsed_os_line);
    }
    return parsed_pass_file;
}

bool LinuxParser::isInteger(const std::string &input_string) {
    try {
        size_t pos;
        return pos == input_string.size();
    } catch (const std::invalid_argument&) {
        return false;
    } catch (const std::out_of_range&) {
        return false;
    }
}

string LinuxParser::lastFolderInPath(const fs::path &input_path) {
    string last_folder_read;
    for (auto& current_folder_in_path : input_path) {
        last_folder_read = current_folder_in_path.string();
    }
    return last_folder_read;
}