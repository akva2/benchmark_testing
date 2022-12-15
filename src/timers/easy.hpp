#pragma once
#include <easy/profiler.h>
#define PROGRAM_TIME_BLOCK(blockname) EASY_BLOCK(#blockname)

#if PROGRAM_HAVE_MPI
#include <mpi.h>
#endif
#include <string>

struct ProgramTimerBackendToBeInstantiatedAtBeginningOfProgram {
    ProgramTimerBackendToBeInstantiatedAtBeginningOfProgram()
    {
        EASY_PROFILER_ENABLE;
    }

    ~ProgramTimerBackendToBeInstantiatedAtBeginningOfProgram()
    {
#if PROGRAM_HAVE_MPI
        // Here we set the filename based on the MPI process
        // Note that we really do want to to use the global one
        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
#else
        int rank = 0;
#endif
        EASY_PROFILER_ENABLE;

        const auto profile_filename
            = std::string("opm-profiling-output_") + std::to_string(rank) + std::string(".prof");
        profiler::dumpBlocksToFile(profile_filename.c_str());
    }
};
