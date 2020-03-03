//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// ycsb.cpp
//
// Identification: src/main/ycsb/ycsb.cpp
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//w

#include <iostream>
#include <fstream>
#include <iomanip>

#include "util/logger.h"
#include "benchmark/ycsb/ycsb_configuration.h"
#include "benchmark/ycsb/ycsb_loader.h"
#include "benchmark/ycsb/ycsb_workload.h"


namespace silkstore {
namespace benchmark {
namespace ycsb {

configuration state;

// Main Entry Point
void RunBenchmark() {
    // Create the database
    CreateYCSBDatabase();

    // Load the databases
    LoadYCSBDatabase();

    // Run the workload
    RunWorkload();

    // Emit throughput
    WriteOutput();

    DestroyYCSBDatabase();
}

}  // namespace ycsb
}  // namespace benchmark
}  // namespace silkstore

int main(int argc, char **argv) {
    silkstore::benchmark::ycsb::ParseArguments(argc, argv,
                                               silkstore::benchmark::ycsb::state);

    silkstore::benchmark::ycsb::RunBenchmark();

    return 0;
}
