#pragma once
#define PL_IMPLEMENTATION 1
#include "palanteer.h"
#include <iostream>
#include <string>

#define PROGRAM_TIME_BLOCK(blockname) plScope(#blockname)

struct ProgramTimerBackendToBeInstantiatedAtBeginningOfProgram {
    ProgramTimerBackendToBeInstantiatedAtBeginningOfProgram()
    {
        std::cout << "Creating palanteer instance" << std::endl;
        plInitAndStart("simulator"); // Start the instrumentation, for the program named "example"
        plDeclareThread(
            "Main"); // Declare the current thread as "Main" so that it can be identified more easily in the script
    }

    ~ProgramTimerBackendToBeInstantiatedAtBeginningOfProgram()
    {
        std::cout << "Destroying palanteer instance" << std::endl;
        plStopAndUninit();
    }
};
