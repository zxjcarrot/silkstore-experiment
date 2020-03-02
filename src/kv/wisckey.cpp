//
// Created by zxjcarrot on 2020-03-02.
//
#include "leveldb/db.h"
#include "kv/store.h"

// Include your wisckey-related header files

// ./wisckey_ycsb -I "wisckey" -k 100 -D "/tmp/testwisckeydb"

namespace silkstore {

static leveldb::DB* db;

leveldb::Status WiscKey::Init(const std::string & db_path) {
    // TODO: implement this
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status s = leveldb::DB::Open(options, db_path, &db);
    return s;
}

leveldb::Status WiscKey::Get(const std::string &key, std::string &value) {
    // TODO: implement this
    leveldb::Status s = db->Get(leveldb::ReadOptions(), key, &value);
    return s;
}

leveldb::Status WiscKey::Put(const std::string &key, const std::string &value) {
    // TODO: implement this
    leveldb::Status s = db->Put(leveldb::WriteOptions(), key, value);
    return s;
}

leveldb::Status WiscKey::Scan(const std::string &start_key, int num, std::vector <std::string> &values) {
    // TODO: implement this
}

}