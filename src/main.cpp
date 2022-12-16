#include "timers.hpp"
#include <array>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <unistd.h>

int
main()
{
    ProgramTimerBackendToBeInstantiatedAtBeginningOfProgram timer_backend;
    const size_t memory_to_allocate = 1024 * 1024;
    std::array<int*, 1000> pointers;
    PROGRAM_TIME_BLOCK(WholeProgram);
    {
        std::cout << "sleeping for 10 seconds" << std::endl;
        PROGRAM_TIME_BLOCK(TenSeconds);
//        sleep(10);
    }
    {
        PROGRAM_TIME_BLOCK(ThirtySeconds);
        std::cout << "sleeping for 30 seconds" << std::endl;
  //      sleep(30);
        for (auto& pointer : pointers) {
            pointer = (int*)malloc(memory_to_allocate * sizeof(int));
        }
    }

    {
        PROGRAM_TIME_BLOCK(HeavyComputation);
        std::cout << "calculating e" << std::endl;
        using int_type = long;
        const int_type N = 1l << 38;

        // Compute e with insane precision that will anyway be lost
        // due to rounding
        double e = 0.0;

#pragma omp parallel for schedule(static) reduction(+:e)
        for (int_type i = 1u; i < N; ++i) {
            e += 1.0 / (double(i)*double(i));
        }

        std::cout << "e = " << e << std::endl;
    }
    {
        PROGRAM_TIME_BLOCK(SixSeconds);
        for (auto& pointer : pointers) {
            for (size_t i = 0; i < memory_to_allocate; ++i) {
                pointer[i] = 43.4 + i;
            }
        }
        std::cout << "sleeping for 6 seconds" << std::endl;
        sleep(6);
        for (auto& pointer : pointers) {
            free(pointer);
        }
    }

    std::cout << "Yaaawn, is it time to get up?" << std::endl;
    return 0;
}
