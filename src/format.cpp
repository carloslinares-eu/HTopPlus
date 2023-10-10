#include <string>

#include "format.h"

using std::string;

string Format::ElapsedTime(long seconds) {
    long seconds_left_to_divide = seconds;
    string formatted_time;
    const int seconds_in_hour = 3600;
    const int seconds_in_minutes = 60;

    int hours_elapsed = int(seconds_left_to_divide) / seconds_in_hour;
    seconds_left_to_divide = int(seconds_left_to_divide) % seconds_in_hour;
    if (std::to_string(hours_elapsed).length() < 2) {
        formatted_time += "0";
    }
    formatted_time += std::to_string(hours_elapsed) + ":";

    int minutes_elapsed = int(seconds_left_to_divide) / seconds_in_minutes;
    seconds_left_to_divide = int(seconds_left_to_divide) % seconds_in_minutes;
    if (std::to_string(minutes_elapsed).length() < 2) {
        formatted_time += "0";
    }
    formatted_time += std::to_string(minutes_elapsed) + ":";

    int seconds_elapsed = int(seconds_left_to_divide);
    if (std::to_string(seconds_elapsed).length() < 2) {
        formatted_time += "0";
    }
    formatted_time += std::to_string(seconds_elapsed);

    return formatted_time;
}