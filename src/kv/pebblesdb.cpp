//
// Created by zxjcarrot on 2020-03-02.
//

#include "kv/store.h"
#include "pebblesdb/db.h"

// Include your pebblesdb-related header files

// ./pebblesdb_ycsb -I "pebbles" -k 100 -D "/tmp/testpebblesdb"

namespace silkstore {

static leveldb::DB* db;

leveldb::Status PebblesDB::Init(const std::string & db_path) {
    // TODO: implement this
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status s = leveldb::DB::Open(options, db_path, &db);
    return s;
}

leveldb::Status PebblesDB::Get(const std::string &key, std::string &value) {
    // TODO: implement this
    leveldb::Status s = db->Get(leveldb::ReadOptions(), key, &value);
    return s;
}

leveldb::Status PebblesDB::Put(const std::string &key, const std::string &value) {
    // TODO: implement this
    leveldb::Status s = db->Put(leveldb::WriteOptions(), key, value);
    return s;
}

leveldb::Status PebblesDB::Scan(const std::string &start_key, int num, std::vector <std::string> &values) {
    // TODO: implement this
}

}