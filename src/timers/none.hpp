#pragma once
// We add this to make sure we do not get warnings
// about uncessary semicolons.
#define PROGRAM_TIME_BLOCK(blockname)                                          \
do {                                                                         \
} while (false)


    struct ProgramTimerBackendToBeInstantiatedAtBeginningOfProgram {
    ProgramTimerBackendToBeInstantiatedAtBeginningOfProgram() {
        // Does nothing
    }

    ~ProgramTimerBackendToBeInstantiatedAtBeginningOfProgram() {
        // Does nothing
    }
};
