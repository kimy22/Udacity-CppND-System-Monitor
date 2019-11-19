#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// Implementation: Added a constructor that initializes private variable pid_
Process::Process(int pid) : pid_(pid){}

// TODO: Return this process's ID
// Implementation: Return private variable pid_
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
// Implementation: Pass through a newly created function CpuUtilization(int pid) in LinuxParser namespace
float Process::CpuUtilization() { return LinuxParser::CpuUtilization(pid_); }

// TODO: Return the command that generated this process
// Implementation: Pass through LinuxParser namespace function Command(int pid) 
string Process::Command() { return LinuxParser::Command(pid_); }

// TODO: Return this process's memory utilization
// Implementation: Pass through LinuxParser namespace function Ram(int pid)
string Process::Ram() { return LinuxParser::Ram(pid_); }

// TODO: Return the user (name) that generated this process
// Implementation: Pass through LinuxParser namespace function User(int pid)
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
// Implementation: Pass through LinuxParser namespace function UpTime(int pid)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
// Implementation: No need for modification for this project
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }