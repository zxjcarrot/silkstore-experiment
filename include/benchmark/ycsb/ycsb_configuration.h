//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// ycsb_configuration.h
//
// Identification: src/include/benchmark/ycsb/ycsb_configuration.h
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//


#pragma once

#include <string>
#include <cstring>
#include <getopt.h>
#include <vector>
#include <sys/time.h>
#include <iostream>
#include <sstream>

namespace silkstore {
namespace benchmark {
namespace ycsb {

#define COLUMN_COUNT 10

struct YCSBTuple {
    uint64_t key;
    uint64_t cols[COLUMN_COUNT];
    uint64_t Key() const {
        return key;
    }
    std::string ToString() {
        std::ostringstream buffer;

        for (int i = 0; i < COLUMN_COUNT; ++i)
            buffer << cols[i];
        return buffer.str();
    }
};

class configuration {
public:
    // size of the table
    int scale_factor;

    // execution duration (in s)
    double duration;

    // profile duration (in s)
    double profile_duration;

    // number of backends
    int backend_count;

    // operation count in a transaction
    int operation_count;

    // update ratio
    double update_ratio;

    // contention level
    double zipf_theta;

    // exponential backoff
    bool exp_backoff;

    // store strings
    bool string_mode;

    // number of loaders
    int loader_count;

    // throughput
    double throughput = 0;

    // abort rate
    double abort_rate = 0;

    std::vector<double> profile_throughput;

    std::vector<double> profile_abort_rate;

    std::vector<int> profile_memory;

    std::string db_path;
    std::string index_type;
};

extern configuration state;

void Usage(FILE *out);

void ParseArguments(int argc, char *argv[], configuration &state);

void ValidateScaleFactor(const configuration &state);

void ValidateDuration(const configuration &state);

void ValidateProfileDuration(const configuration &state);

void ValidateBackendCount(const configuration &state);

void ValidateOperationCount(const configuration &state);

void ValidateUpdateRatio(const configuration &state);

void ValidateZipfTheta(const configuration &state);

void ValidateIndexType(const configuration & state);

void WriteOutput();

}  // namespace ycsb
}  // namespace benchmark
}  // namespace peloton
