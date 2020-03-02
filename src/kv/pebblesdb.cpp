//
// Created by zxjcarrot on 2020-03-02.
//

#include "kv/store.h"

// Include your pebblesdb-related header files


namespace silkstore {

Status PebblesDB::Init(const std::string & db_path) {
    // TODO: implement this
}

Status PebblesDB::Get(const std::string &key, std::string &value) {
    // TODO: implement this
}

Status PebblesDB::Put(const std::string &key, const std::string &value) {
    // TODO: implement this
}

Status PebblesDB::Scan(const std::string &start_key, int num, std::vector <std::string> &values) {
    // TODO: implement this
}

}