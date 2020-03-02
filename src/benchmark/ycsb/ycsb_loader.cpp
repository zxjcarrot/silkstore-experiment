//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// ycsb_loader.cpp
//
// Identification: src/main/ycsb/ycsb_loader.cpp
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <iostream>
#include <ctime>

#include "util/logger.h"
#include "util/sync.h"
#include "benchmark/ycsb/ycsb_loader.h"
#include "benchmark/ycsb/ycsb_configuration.h"

namespace silkstore {
namespace benchmark {
namespace ycsb {

#define THREAD_POOL_SIZE 10
ThreadPool the_tp(THREAD_POOL_SIZE);

YCSBTable *user_table = nullptr;

void CreateYCSBDatabase() {
    if (state.index_type == "leveldb") {
        user_table = new LevelDB;
    } else if (state.index_type == "silsktore") {
        user_table = new SilkStore;
    } else if (state.index_type == "wisckey") {
        user_table = new WiscKey;
    } else {
        user_table = new PebblesDB;
    }
    Status s = user_table->Init(state.db_path);
    if (!s.ok()) {
        exit(EXIT_FAILURE);
    }
}

void DestroyYCSBDatabase() {
    delete user_table;
    user_table = nullptr;
}

void LoadYCSBRows(const int begin_rowid, const int end_rowid) {
    /////////////////////////////////////////////////////////
    // Load in the data
    /////////////////////////////////////////////////////////

    // Insert tuples into the data table.
    for (int rowid = begin_rowid; rowid < end_rowid; rowid++) {
        YCSBTuple tuple;
        tuple.key = rowid;
        for (int i = 0; i < COLUMN_COUNT; ++i)
            tuple.cols[i] = rowid;

        user_table->Put(std::to_string(rowid), tuple.ToString());
    }
}

void LoadYCSBDatabase() {

    std::chrono::steady_clock::time_point start_time;
    start_time = std::chrono::steady_clock::now();

    const int tuple_count = state.scale_factor * 1000;
    int row_per_thread = tuple_count / state.loader_count;

    CountDownLatch latch(state.loader_count);

    for (int thread_id = 0; thread_id < state.loader_count - 1; ++thread_id) {
        int begin_rowid = row_per_thread * thread_id;
        int end_rowid = row_per_thread * (thread_id + 1);
        the_tp.enqueue([&latch, begin_rowid, end_rowid]() {
            LoadYCSBRows(begin_rowid, end_rowid);
            latch.CountDown();
        });
    }

    int thread_id = state.loader_count - 1;
    int begin_rowid = row_per_thread * thread_id;
    int end_rowid = tuple_count;
    the_tp.enqueue([&latch, begin_rowid, end_rowid]() {
        LoadYCSBRows(begin_rowid, end_rowid);
        latch.CountDown();
    });

    latch.Await();

    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
    double diff = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    LOG_INFO("database table loading time = %lf ms", diff);

    //LOG_INFO("%sTABLE SIZES%s", peloton::GETINFO_HALF_THICK_LINE.c_str(), peloton::GETINFO_HALF_THICK_LINE.c_str());
    LOG_INFO("user count = %lu", tuple_count);

}

}  // namespace ycsb
}  // namespace benchmark
}  // namespace peloton
