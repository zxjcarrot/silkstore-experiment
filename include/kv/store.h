//
// Created by zxjcarrot on 2020-03-02.
//

#ifndef SILKSTORE_EXPERIMENT_STORE_H
#define SILKSTORE_EXPERIMENT_STORE_H


#include "leveldb/status.h"
#include <algorithm>
#include <string>


namespace silkstore {

class KeyValueStore {
public:
    virtual leveldb::Status Init(const std::string & db_path) = 0;

    virtual leveldb::Status Put(const std::string &key, const std::string &value) = 0;

    virtual leveldb::Status Get(const std::string &key, std::string &value) = 0;

    virtual leveldb::Status Scan(const std::string &start_key, int num, std::vector <std::string> &values) = 0;


    virtual ~KeyValueStore() {}
};


class LevelDB: public KeyValueStore {
public:
    virtual leveldb::Status Init(const std::string & db_path);

    virtual leveldb::Status Put(const std::string &key, const std::string &value);

    virtual leveldb::Status Get(const std::string &key, std::string &value);

    virtual leveldb::Status Scan(const std::string &start_key, int num, std::vector <std::string> &values);

};



class SilkStore: public KeyValueStore {
public:
    virtual leveldb::Status Init(const std::string & db_path);

    virtual leveldb::Status Put(const std::string &key, const std::string &value);

    virtual leveldb::Status Get(const std::string &key, std::string &value);

    virtual leveldb::Status Scan(const std::string &start_key, int num, std::vector <std::string> &values);

};

class PebblesDB: public KeyValueStore {
public:
    virtual leveldb::Status Init(const std::string & db_path);

    virtual leveldb::Status Put(const std::string &key, const std::string &value);

    virtual leveldb::Status Get(const std::string &key, std::string &value);

    virtual leveldb::Status Scan(const std::string &start_key, int num, std::vector <std::string> &values);
};


class WiscKey: public KeyValueStore {
public:
    virtual leveldb::Status Init(const std::string & db_path);

    virtual leveldb::Status Put(const std::string &key, const std::string &value);

    virtual leveldb::Status Get(const std::string &key, std::string &value);

    virtual leveldb::Status Scan(const std::string &start_key, int num, std::vector <std::string> &values);
};

}
#endif //SILKSTORE_EXPERIMENT_STORE_H
