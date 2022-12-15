#pragma once
// We add this to make sure we do not get warnings
// about uncessary semicolons.
#define PROGRAM_TIME_BLOCK(blockname)                                          \
do {                                                                         \
} while (false)


    struct ProgramTimerBackendToBeInstantiateAtBeginningOfProgram {
    ProgramTimerBackendToBeInstantiateAtBeginningOfProgram() {
        // Does nothing
    }

    ~ProgramTimerBackendToBeInstantiateAtBeginningOfProgram() {
        // Does nothing
    }
};
