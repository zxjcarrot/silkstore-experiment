//
// Created by zxjcarrot on 2020-03-02.
//

#ifndef SILKSTORE_EXPERIMENT_STORE_H
#define SILKSTORE_EXPERIMENT_STORE_H

#include "util/status.h"

namespace silkstore {

class KeyValueStore {
public:
    virtual Status Init(const std::string & db_path) = 0;

    virtual Status Put(const std::string &key, const std::string &value) = 0;

    virtual Status Get(const std::string &key, std::string &value) = 0;

    virtual Status Scan(const std::string &start_key, int num, std::vector <std::string> &values) = 0;

    virtual ~KeyValueStore() {}
};

class LevelDB: public KeyValueStore {
public:
    virtual Status Init(const std::string & db_path);

    virtual Status Put(const std::string &key, const std::string &value);

    virtual Status Get(const std::string &key, std::string &value);

    virtual Status Scan(const std::string &start_key, int num, std::vector <std::string> &values);
};

class SilkStore: public KeyValueStore {
public:
    virtual Status Init(const std::string & db_path);

    virtual Status Put(const std::string &key, const std::string &value);

    virtual Status Get(const std::string &key, std::string &value);

    virtual Status Scan(const std::string &start_key, int num, std::vector <std::string> &values);
};

class PebblesDB: public KeyValueStore {
public:
    virtual Status Init(const std::string & db_path);

    virtual Status Put(const std::string &key, const std::string &value);

    virtual Status Get(const std::string &key, std::string &value);

    virtual Status Scan(const std::string &start_key, int num, std::vector <std::string> &values);
};


class WiscKey: public KeyValueStore {
public:
    virtual Status Init(const std::string & db_path);

    virtual Status Put(const std::string &key, const std::string &value);

    virtual Status Get(const std::string &key, std::string &value);

    virtual Status Scan(const std::string &start_key, int num, std::vector <std::string> &values);
};

}
#endif //SILKSTORE_EXPERIMENT_STORE_H
