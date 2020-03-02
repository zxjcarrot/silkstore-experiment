//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// ycsb_workload.h
//
// Identification: src/include/benchmark/ycsb/ycsb_workload.h
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//


#pragma once

#include "benchmark/benchmark_common.h"
#include "benchmark/ycsb/ycsb_configuration.h"

namespace silkstore {
namespace benchmark {
namespace ycsb {

extern configuration state;

void RunWorkload();

bool RunMixed(const size_t thread_id, ZipfDistribution &zipf, FastRandom &rng);

/////////////////////////////////////////////////////////

void PinToCore(size_t core);

}  // namespace ycsb
}  // namespace benchmark
}  // namespace peloton
