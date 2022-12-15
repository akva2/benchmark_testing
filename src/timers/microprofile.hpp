#pragma once
#include <microprofile.h>
#define PROGRAM_TIME_BLOCK(blockname) MICROPROFILE_SCOPEI("simulator", #blockname, MP_YELLOW)

#if PROGRAM_HAVE_MPI
#include <mpi.h>
#endif
#include <string>

struct ProgramTimerBackendToBeInstantiatedAtBeginningOfProgram {
    ProgramTimerBackendToBeInstantiatedAtBeginningOfProgram()
    {

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
        const auto profile_filename_base
            = std::string("opm-profiling-output_") + std::to_string(rank);
        MicroProfileDumpFileImmediately((profile_filename_base + ".html").c_str(),
                                        (profile_filename_base + ".csv").c_str(),
                                        nullptr);
    }
};
