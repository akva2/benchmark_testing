#include "timers.hpp"
#include <array>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

int
main()
{
    ProgramTimerBackendToBeInstantiateAtBeginningOfProgram timer_backend;
    size_t N = 1024 * 1024;
    std::array<int*, 1000> pointers;
    {
        std::cout << "sleeping for 10 seconds" << std::endl;
        PROGRAM_TIME_BLOCK(TenSeconds);
        sleep(10);
    }
    {
        PROGRAM_TIME_BLOCK(ThirtySeconds);
        std::cout << "sleeping for 30 seconds" << std::endl;
        sleep(30);
        for (auto& pointer : pointers) {
            pointer = (int*)malloc(N * sizeof(int));
        }
    }

    {
        PROGRAM_TIME_BLOCK(SixSeconds);
        for (auto& pointer : pointers) {
            for (size_t i = 0; i < N; ++i) {
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
