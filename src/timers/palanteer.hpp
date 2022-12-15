#pragma once
#define PL_IMPLEMENTATION 1
#include "palanteer.h"
#include <iostream>
#include <string>

// struct PalanteerTimer {
//     PalanteerTimer(const std::string& blockname)
//         : m_blockname(blockname)
//     {
//         plBegin(blockname.c_str());
//     }

//    ~PalanteerTimer()
//    {
//        plEnd(m_blockname.c_str()); // Technically not needed to give the name, but better safe than sorry.
//    }

// private:
//     const std::string m_blockname;
// };

#define PROGRAM_TIME_BLOCK(blockname) plScope(#blockname)

struct ProgramTimerBackendToBeInstantiateAtBeginningOfProgram {
    ProgramTimerBackendToBeInstantiateAtBeginningOfProgram()
    {
        std::cout << "Creating palanteer instance" << std::endl;
        plInitAndStart("simulator"); // Start the instrumentation, for the program named "example"
        plDeclareThread(
            "Main"); // Declare the current thread as "Main" so that it can be identified more easily in the script
    }

    ~ProgramTimerBackendToBeInstantiateAtBeginningOfProgram()
    {
        std::cout << "Destroying palanteer instance" << std::endl;
        plStopAndUninit();
    }
};
