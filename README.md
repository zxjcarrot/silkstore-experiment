# ycsb-experiment
```
./targets/leveldb_ycsb -I "leveldb" -k 100 -D "/tmp/testleveldb"
./targets/leveldb_ycsb -I "leveldb" -k 100 -s -r 500 -D "/tmp/testleveldb"

./targets/pebblesdb_ycsb -I "pebblesdb" -k 100 -D "/tmp/testpebblesdb"
./targets/pebblesdb_ycsb -I "pebblesdb" -k 100 -s -r 500 -D "/tmp/testpebblesdb"

./targets/silkstore_ycsb -I "silkstore" -k 100 -D "/tmp/testsilkstore"
./targets/silkstore_ycsb -I "silkstore" -k 100 -s -r 500 -D "/tmp/testsilkstore"

./targets/wisckey_ycsb -I "wisckey" -k 100 -D "/tmp/testwisckey"
./targets/wisckey_ycsb -I "wisckey" -k 100 -s -r 500 -D "/tmp/testwisckey"
```