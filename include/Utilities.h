#pragma once

#include <stdio.h>
#include <time.h>


namespace ProdCon {
    /**
     * Interface for provided functions Trans and Sleep. These functions are provided by the course.
     * No modification is made.
     *
     */
    class Utilities {
        /**
         * Simulate a long processing routine
         *
         * @param n
         */
        static void Trans(int n);

        /**
         * Simulating sleep.
         *
         * @param n Wait time in hundreds of nanosecond.
         */
        static void Sleep(int n);
    };
}


