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

#include "leveldb/status.h"

namespace silkstore {
namespace benchmark {
namespace ycsb {


// perform point read
bool PointRead(ZipfDistribution &zipf) {
    leveldb::Status statue;
    auto lookup_key = zipf.GetNextNumber();
    std::string value;
    statue = user_table->Get(std::to_string(lookup_key), value);
    return statue.ok();
}

// perform scan read
bool RangeRead(ZipfDistribution &zipf) {
    leveldb::Status statue;
    auto start_key =  zipf.GetNextNumber();
    int num = state.range_size;
    std::vector<std::string> scan_results;
    statue = user_table->Scan(std::to_string(start_key), num, scan_results);
    return statue.ok();
}

// perform update
bool Update(ZipfDistribution &zipf, FastRandom &rng) {
    leveldb::Status statue;
    auto lookup_key = zipf.GetNextNumber();
    YCSBTuple tuple;
    tuple.key = lookup_key;
    for (int c = 0; c < COLUMN_COUNT; ++c) {
        tuple.cols[c] = rng.NextUniform();
    }
    statue = user_table->Put(std::to_string(tuple.key), tuple.ToString());
    return statue.ok();
}

bool RunMixed(const size_t thread_id, ZipfDistribution &zipf, FastRandom &rng) {
    bool is_ok = true;

    for (int i = 0; i < state.operation_count && is_ok; i++) {
        auto rng_val = rng.NextUniform();
        if (rng_val < state.update_ratio) {
            is_ok = Update(zipf, rng);
        } else {
            is_ok = state.scan_read ? RangeRead(zipf) : PointRead(zipf);
        }
    }
    
    return is_ok;
}

}
}
}
