#pragma once

#include "Remotery.h"
#include <iostream>

#define PROGRAM_TIME_BLOCK(blockname) rmt_ScopedCPUSample(blockname, 0);

struct ProgramTimerBackendToBeInstantiatedAtBeginningOfProgram {
    ProgramTimerBackendToBeInstantiatedAtBeginningOfProgram()
    {
        std::cout << "Creating remotery instance" << std::endl;
        const auto error = rmt_CreateGlobalInstance(&m_rmt);

        if (error != RMT_ERROR_NONE) {
            throw std::runtime_error(std::string("Remotery gave error code: " + std::to_string(error)));
        }
    }

    ~ProgramTimerBackendToBeInstantiatedAtBeginningOfProgram()
    {
        std::cout << "Destroying remotery instance" << std::endl;
        rmt_CreateGlobalInstance(&m_rmt);
    }

    Remotery* m_rmt; // TODO: unique_ptr
};
