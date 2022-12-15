#pragma once
#include <tracy/Tracy.hpp>
#define PROGRAM_TIME_BLOCK(blockname) ZoneNamedN(blockname, #blockname, true)

struct ProgramTimerBackendToBeInstantiateAtBeginningOfProgram {
    ProgramTimerBackendToBeInstantiateAtBeginningOfProgram() {
        // Does nothing
    }

    ~ProgramTimerBackendToBeInstantiateAtBeginningOfProgram() {
        // Does nothing
    }
};
