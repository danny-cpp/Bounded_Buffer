#pragma once

#include <PCH.h>
#include <chrono>
#include <utility>


namespace Shell379 {
    namespace Utilities {
        /**
         * Scope timer object. Initiate at the beginning of the scope to measure time passed in that scope.
         */
        class totalTiming {
        public:

            /**
             * Initiate at the beginning of the scope to measure time of the scope.
             *
             * @param return_time reference to be written for the total_time of the scope. Time in microsecond
             */
            explicit totalTiming(std::shared_ptr<double> return_elapsed_time);


            /**
             * Immediately return time elapsed from the creating of the timer object.
             *
             * @return return time in microsecond
             */
            double getElapsedTime();

            ~totalTiming();

        private:
            std::chrono::time_point<std::chrono::system_clock> start, end;
            std::shared_ptr<double> reference_duration;
        };

    }
}

