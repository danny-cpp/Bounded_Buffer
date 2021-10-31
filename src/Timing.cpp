#include "Timing.h"


Shell379::Utilities::totalTiming::totalTiming(std::shared_ptr<double> return_time) {
    reference_duration = std::move(return_time);
    start = std::chrono::high_resolution_clock::now();
}


Shell379::Utilities::totalTiming::~totalTiming() {
    end = std::chrono::high_resolution_clock::now();
    *reference_duration = std::chrono::duration<double, std::micro>(end - start).count();
}


double Shell379::Utilities::totalTiming::getElapsedTime() {
    auto stamp = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::micro>(stamp - start).count();
}

double Shell379::Utilities::totalTiming::stamp(std::chrono::time_point<std::chrono::system_clock> previous_stamp) {
    auto stamp = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::micro>(stamp - previous_stamp).count();
}
