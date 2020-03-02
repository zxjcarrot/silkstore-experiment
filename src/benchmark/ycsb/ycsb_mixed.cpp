//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// ycsb_mixed.cpp
//
// Identification: src/main/ycsb/ycsb_mixed.cpp
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <ctime>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "benchmark/ycsb/ycsb_configuration.h"
#include "benchmark/ycsb/ycsb_loader.h"
#include "benchmark/ycsb/ycsb_workload.h"


namespace silkstore {
namespace benchmark {
namespace ycsb {

bool RunMixed(const size_t thread_id, ZipfDistribution &zipf, FastRandom &rng) {
    for (int i = 0; i < state.operation_count; i++) {
        auto rng_val = rng.NextUniform();
        if (rng_val < state.update_ratio) {
            /////////////////////////////////////////////////////////
            // PERFORM UPDATE
            /////////////////////////////////////////////////////////

            auto lookup_key = zipf.GetNextNumber();
            YCSBTuple tuple;
            tuple.key = lookup_key;
            for (int c = 0; c < COLUMN_COUNT; ++c) {
                tuple.cols[c] = rng.NextUniform();
            }
            user_table->Put(std::to_string(tuple.key), tuple.ToString());
        } else {
            /////////////////////////////////////////////////////////
            // PERFORM READ
            /////////////////////////////////////////////////////////

            auto lookup_key = zipf.GetNextNumber();
            std::string value;
            user_table->Get(std::to_string(lookup_key), value);
        }
    }
    // TODO for jinshuang : Add scan as well
    return true;
}
}
}
}
