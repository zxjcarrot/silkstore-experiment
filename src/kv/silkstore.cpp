//
// Created by zxjcarrot on 2020-03-02.
//

#include<memory>

#include "kv/store.h"
#include "leveldb/db.h"

// Include your silkstore-related header files
// ./targets/silkstore_ycsb -I "silkstore" -k 100 -D "/tmp/testsilkstore"

namespace silkstore {

static leveldb::DB* db;

leveldb::Status SilkStore::Init(const std::string & db_path) {
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status s = leveldb::DB::OpenSilkStore(options, db_path, &db);
    return s;
}

leveldb::Status SilkStore::Get(const std::string &key, std::string &value) {
    leveldb::Status s = db->Get(leveldb::ReadOptions(), key, &value);
    return s;
}

leveldb::Status SilkStore::Put(const std::string &key, const std::string &value) {
    leveldb::Status s = db->Put(leveldb::WriteOptions(), key, value);
    return s;
}

leveldb::Status SilkStore::Scan(const std::string &start_key, int num, std::vector <std::string> &values) {
    std::shared_ptr<leveldb::Iterator> it(db->NewIterator(leveldb::ReadOptions()));

    it->Seek(start_key);
    while ( (num--) && it->Valid() ) {
        values.push_back(it->value().ToString());
        it->Next();
    }

    // If an error has occurred, return it.  Else return an ok status.
    // when "it" seek to last but num still > 0, but no error occur, return ok.
    return it->status();
}

}