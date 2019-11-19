#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"
#include <unistd.h>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
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

// TODO: Read and return the system memory utilization
// Implementation: read /proc/meminfo and parse to get memtotal and memfree then calculate percent memory usage
float LinuxParser::MemoryUtilization() { 
  float mem_total, mem_free;
  string key, value, line;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "MemTotal:") {
          mem_total = stof(value);
      } else if (key == "MemFree:") {
          mem_free = stof(value);
      }
    }
  }
  return (mem_total-mem_free)/mem_total; 
}

// TODO: Read and return the system uptime
// Implementation: read /proc/uptime and return the first number
long LinuxParser::UpTime() {
  string uptime, idletime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime >> idletime;
  }
  return stol(uptime);
}

// TODO: Read and return the number of jiffies for the system
// Implementation: No need for modification for this project
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
// Implementation: No need for modification for this project
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
// Implementation: No need for modification for this project
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
// Implementation: No need for modification for this project
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
// Implementation: read /proc/stat then return all strings as a vector
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> cpu_data;
  string line;
  string key;
  string cpu_key;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "cpu") {
        while (linestream >> cpu_key) {
          cpu_data.push_back(cpu_key);
        }
      }
    }
  }
  return cpu_data; 
}

// TODO: Read and return the total number of processes
// Implementation: read /proc/meminfo line by line; if key == "processes" return its value
int LinuxParser::TotalProcesses() { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "processes") {
          return stoi(value);
      }
    }
  }
  return stoi(value);
}

// TODO: Read and return the number of running processes
// Implementation: read /proc/meminfo line by line; if key == "procs_running" return its value
int LinuxParser::RunningProcesses() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "procs_running") {
        return stoi(value);
      }
    }
  }
  return stoi(value);
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
// Implementation: read /proc/[pid]/cmdline and return the entire line
string LinuxParser::Command(int pid) {
  string line, value;
  string cmdline = "";
  std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::replace(line.begin(), line.end(), '\0', ' ');
    std::istringstream linestream(line);
    while (linestream >> value) {
      cmdline += value;
    }
    return cmdline;
  }
  return cmdline;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
// Implementation: read /proc/[pid]/status line by line; if key == "VmSize:" return its value
string LinuxParser::Ram(int pid) { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize:") {
          return to_string(stol(value)/1000);
        }
      }
    }
  }
  return value;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
// Implementation: read /proc/[pid]/status line by line; if key == "Uid:" return its value
string LinuxParser::Uid(int pid) { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:") {
          return value;
        }
      }
    }
  }
  return value;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
// Implementation: read /etc/passwd line by line; replace ":" with " "; if value == uid then return its user
string LinuxParser::User(int pid) { 
  string line;
  string user;
  string skip;
  int uid = stoi(LinuxParser::Uid(pid));
  int value;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> user >> skip >> value;
        if (value == uid) {
          return user;
        }

    }
  }
  return user;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
// Implementation: read /proc/[pid]/stat then get start time of the process; get system up time then calculate process up time
long LinuxParser::UpTime(int pid) { 
  string line, value;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (int i = 1; i <= 22; i++) {
      linestream >> value;
    }
  }
  return LinuxParser::UpTime() - stol(value)/sysconf(_SC_CLK_TCK);
}

// NEW FUNCTION
// Implementation: read /proc/[pid]/stat then calculate process' cpu utilization
float LinuxParser::CpuUtilization(int pid) {
  long uptime = LinuxParser::UpTime();
  long utime, stime, cutime, cstime, starttime;
  string line, value;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (int i = 1; i <= 22; i++) {
      linestream >> value;
      if (i == 14) {
        utime = stol(value)/sysconf(_SC_CLK_TCK);
      } else if (i == 15) {
        stime = stol(value)/sysconf(_SC_CLK_TCK);
      } else if (i == 16) {
        cutime = stol(value)/sysconf(_SC_CLK_TCK);
      } else if (i == 17) {
        cstime = stol(value)/sysconf(_SC_CLK_TCK);
      } else if (i == 22) {
        starttime = stol(value)/sysconf(_SC_CLK_TCK);
      }
    }
  }
  return (float)(utime+stime+cutime+cstime)/(uptime-starttime);
}