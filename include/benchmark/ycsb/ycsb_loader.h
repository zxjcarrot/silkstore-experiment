//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// ycsb_loader.h
//
// Identification: src/include/benchmark/ycsb/ycsb_loader.h
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//


#pragma once

#include "util/sync.h"
#include "kv/store.h"
#include "benchmark/ycsb/ycsb_configuration.h"

namespace silkstore {
namespace benchmark {
namespace ycsb {

typedef KeyValueStore YCSBTable;

extern configuration state;

extern YCSBTable *user_table;

extern ThreadPool the_tp;

void CreateYCSBDatabase();

void LoadYCSBDatabase();

void LoadYCSBRows(const int begin_rowid, const int end_rowid);

void DestroyYCSBDatabase();
}  // namespace ycsb
}  // namespace benchmark
}  // namespace peloton
