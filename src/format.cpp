#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
    long hour, minute, second;
    string value;
    hour = seconds/3600;
    minute = (seconds % 3600)/60;
    second = (seconds % 3600) % 60;
    if (second < 10) {
        value = std::to_string(hour)+":"+std::to_string(minute)+":0"+std::to_string(second);
    } else {
        value = std::to_string(hour)+":"+std::to_string(minute)+":"+std::to_string(second);
    }
    return value;
}