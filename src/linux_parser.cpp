#include "linux_parser.h"


string LinuxParser::OperatingSystem(const vector<vector<string>>& kOSFileRef) {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream line_stream(line);
      while (line_stream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

string LinuxParser::Kernel(const vector<vector<string>>& kVersionFileRef) {
    return kVersionFileRef[0][2];
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

float LinuxParser::MemoryUtilization() {
    std::ifstream file_stream (kProcDirectory + kMemInfoFilename);
    int total_memory = 0;
    int available_memory = 0;
    float memory_utilization = 0.0;
    if (file_stream.is_open()) {
        string line;
        while (std::getline(file_stream, line)) {
            string key;
            string value;
            string unit;
            std::istringstream line_stream(line);
            line_stream >> key >> value >> unit;
            if (key == "MemTotal:") {
                total_memory = std::stoi(value);
                continue;
            }
            if (key == "MemAvailable:") {
                available_memory = std::stoi(value);
                break;
            }

        }
    }
    try {
        memory_utilization = 1.0f - static_cast<float>(available_memory) / static_cast<float>(total_memory);
    } catch (const std::runtime_error& runtime_error) {
        std::cout << "Error in Memory Utilization: " << runtime_error.what() << std::endl;
        memory_utilization = 0.0f;
    }

    return memory_utilization;
}

long int LinuxParser::UpTime() {
    long int uptime_effective;
    long int uptime_total;
    std::ifstream stream (kProcDirectory + kUptimeFilename);
    if (stream.is_open()) {
        string line;
        std::getline(stream, line);
        std::istringstream line_stream (line);
        std::vector<std::string> words_in_line;
        std::string word;

        while (line_stream >> word){
            words_in_line.push_back(word);
        }
        std::from_chars(words_in_line[0].data(), words_in_line[0].data() + words_in_line[0].size(), uptime_total);
        std::from_chars(words_in_line[1].data(), words_in_line[1].data() + words_in_line[1].size(), uptime_effective);
    }
    return uptime_total;
}

long LinuxParser::Jiffies() {
    int system_jiffies;
    std::ifstream file_stream (kProcDirectory + kStatFilename);
    if (file_stream.is_open()) {
        string line;
        std::getline(file_stream, line);
        std::istringstream line_stream(line);
        std::string line_heading, user, nice, system, idle, io_wait, irq, soft_irq, steal, guest, guest_nice;
        line_stream >> line_heading >> user >> nice >> system >> idle >> io_wait >> irq >> soft_irq >> steal >> guest >> guest_nice;
        system_jiffies = std::stoi(user);
    }
    return system_jiffies;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

int LinuxParser::TotalProcesses() {
    int total_processes;
    std::ifstream file_stream (kProcDirectory + kStatFilename);
    if (file_stream.is_open()){
        string line;
        while (std::getline(file_stream, line)) {
            std::istringstream line_stream (line);
            std::string first_word_in_line;
            line_stream >> first_word_in_line;
            if (first_word_in_line == "processes") {
                std::string value;
                line_stream >> value;
                total_processes = std::stoi(value);
                break;
            }
            else {
                continue;
            }
        }
    }
    return total_processes;
}

int LinuxParser::RunningProcesses() {
    int running_processes;
    std::ifstream file_stream (kProcDirectory + kStatFilename);
    if (file_stream.is_open()){
        string line;
        while (std::getline(file_stream, line)) {
            std::istringstream line_stream (line);
            std::string first_word_in_line;
            line_stream >> first_word_in_line;
            if (first_word_in_line == "procs_running") {
                std::string value;
                line_stream >> value;
                running_processes = std::stoi(value);
                break;
            }
            else {
                continue;
            }
        }
    }
    return running_processes;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }


// Generic functions to avoid reading the same files multiple times during runtime
vector<vector<string>> LinuxParser::ReadTextFile(const string &file_path) {
    vector<vector<string>> read_file;
    ifstream file_stream (file_path);
    if (file_stream.is_open()){
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
    istringstream line_stream (line);
    string current_word;
    while (line_stream >> current_word) {
        read_line.push_back(current_word);
    }
    return read_line;
}