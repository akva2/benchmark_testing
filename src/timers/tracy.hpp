#pragma once
#include <tracy/Tracy.hpp>
#define PROGRAM_TIME_BLOCK(blockname) ZoneNamedN(blockname, #blockname, true)

struct ProgramTimerBackendToBeInstantiatedAtBeginningOfProgram {
    ProgramTimerBackendToBeInstantiatedAtBeginningOfProgram() {
        // Does nothing
    }

    ~ProgramTimerBackendToBeInstantiatedAtBeginningOfProgram() {
        // Does nothing
    }
};
