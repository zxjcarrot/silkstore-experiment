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

bool RunMixed(const size_t thread_id, ZipfDistribution &zipf, FastRandom &rng) {
    leveldb::Status statue;
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
            statue = user_table->Put(std::to_string(tuple.key), tuple.ToString());
        } else {
            /////////////////////////////////////////////////////////
            // PERFORM READ
            /////////////////////////////////////////////////////////

            auto lookup_key = zipf.GetNextNumber();
            std::string value;
            statue = user_table->Get(std::to_string(lookup_key), value);
        }
        /////////////////////////////////////////////////////////
        // PERFORM SCAN
        /////////////////////////////////////////////////////////
        // TODO I'm not sure the range size of scan and the times to perform scan. 
        // how about add scan ratio ?
        auto start_key =  zipf.GetNextNumber();
        int num = zipf.GenerateInteger(0, state.operation_count);
        //printf("scan num %d \n", num);
        std::vector<std::string> scan_results;
        statue = user_table->Scan(std::to_string(start_key), num, scan_results);
        
        if (!statue.ok()) return false;
    }
    

    return true;
}
}
}
}
