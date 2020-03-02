//
// Created by zxjcarrot on 2020-03-02.
//

#include "kv/store.h"

// Include your silkstore-related header files


namespace silkstore {

leveldb::Status SilkStore::Init(const std::string & db_path) {
    // TODO: implement this
}

leveldb::Status SilkStore::Get(const std::string &key, std::string &value) {
    // TODO: implement this
}

leveldb::Status SilkStore::Put(const std::string &key, const std::string &value) {
    // TODO: implement this
}

leveldb::Status SilkStore::Scan(const std::string &start_key, int num, std::vector <std::string> &values) {
    // TODO: implement this
}

}