#pragma once

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
struct Options
{
    Options();
    ~Options();

    // --------------------------------------------------------------------------------------------
    bool BenchmarkMode;
    std::string InitialProblem;
    std::string InitialSolution;


    static const char* DefaultInitialProblem;
    static const char* DefaultInitialSolution;
};

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
Options ProcessCommandLine(int argc, char* argv[]);
