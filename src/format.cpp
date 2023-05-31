#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    const int seconds_in_hour = 3600;
    const int seconds_in_minutes = 60;
    int hours_elapsed = int(seconds) / seconds_in_hour;
    int minutes_elapsed = (int(seconds) - seconds_in_hour * hours_elapsed)


}