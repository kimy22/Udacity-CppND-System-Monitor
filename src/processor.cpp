#include "processor.h"

#include "linux_parser.h"

#include <vector>
#include <string>

using std::string;
using std::vector;
using std::stof;

// TODO: Return the aggregate CPU utilization
// Implementation: Get data from LinuxParser namespace function CpuUtilization() and calculate total CPU percentage
float Processor::Utilization() { 
    vector<string> cpu_data = LinuxParser::CpuUtilization();
    float user_ = stof(cpu_data[0]);
    float nice_ = stof(cpu_data[1]);
    float system_ = stof(cpu_data[2]);
    float idle_ = stof(cpu_data[3]);
    float iowait_ = stof(cpu_data[4]);
    float irq_ = stof(cpu_data[5]);
    float softirq_ = stof(cpu_data[6]);
    float steal_ = stof(cpu_data[7]);
    float total_cpu = user_ + nice_ + system_ + idle_ + iowait_ + irq_ + softirq_ + steal_;
    float total_idle = idle_ + iowait_;
    return (total_cpu-total_idle)/total_cpu; 
}