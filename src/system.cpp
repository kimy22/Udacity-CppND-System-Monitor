#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
// Implementation: No need for modification for this project
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
// Implementation: Get process ids from LinuxParser function and create vector of process objects
vector<Process>& System::Processes() { 
    vector<int> pid = LinuxParser::Pids();
    for (int p:pid){
        processes_.push_back(Process(p));
    }
    return processes_; 
}

// TODO: Return the system's kernel identifier (string)
// Implementation: Pass through LinuxParser namespace function Kernel()
std::string System::Kernel() { return LinuxParser::Kernel(); }

// TODO: Return the system's memory utilization
// Implementation: Pass through LinuxParser namespace function MemoryUtilization()
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
// Implementation: Pass through LinuxParser namespace function OperatingSystem()
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
// Implementation: Pass through LinuxParser namespace function RunningProcesses()
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
// Implementation: Pass through LinuxParser namespace function TotalProcesses()
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
// Implementation: Pass through LinuxParser namespace function UpTime()
long int System::UpTime() { return LinuxParser::UpTime(); }