//
// Created by zxjcarrot on 2020-03-02.
//

#include "kv/store.h"

// Include your wisckey-related header files


namespace silkstore {

Status WiscKey::Init(const std::string & db_path) {
    // TODO: implement this
}

Status WiscKey::Get(const std::string &key, std::string &value) {
    // TODO: implement this
}

Status WiscKey::Put(const std::string &key, const std::string &value) {
    // TODO: implement this
}

Status WiscKey::Scan(const std::string &start_key, int num, std::vector <std::string> &values) {
    // TODO: implement this
}

}