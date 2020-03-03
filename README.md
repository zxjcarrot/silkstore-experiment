# ycsb-experiment

./targets/leveldb_ycsb -I "leveldb" -k 100 -D "/tmp/testleveldb"
2020-03-04 03:56:26 [:69:ValidateScaleFactor] INFO  - scale_factor : 100
2020-03-04 03:56:26 [:78:ValidateDuration] INFO  - duration : 30.000000
2020-03-04 03:56:26 [:87:ValidateProfileDuration] INFO  - profile_duration : 1.000000
2020-03-04 03:56:26 [:96:ValidateBackendCount] INFO  - backend_count : 1
2020-03-04 03:56:26 [:106:ValidateOperationCount] INFO  - operation_count : 10
2020-03-04 03:56:26 [:115:ValidateUpdateRatio] INFO  - update_ratio : 0.500000
2020-03-04 03:56:26 [:124:ValidateZipfTheta] INFO  - zipf_theta : 0.000000
2020-03-04 03:56:26 [:133:ValidateIndexType] INFO  - index_type : leveldb
2020-03-04 03:56:26 [:217:ParseArguments] INFO  - Run exponential backoff : 0
2020-03-04 03:56:26 [:218:ParseArguments] INFO  - Run string mode : 0
2020-03-04 03:56:26 [:111:LoadYCSBDatabase] INFO  - database table loading time = 417.000000 ms
2020-03-04 03:56:26 [:114:LoadYCSBDatabase] INFO  - user count = 100000
2020-03-04 03:56:56 [:230:WriteOutput] INFO  - ----------------------------------------------------------
2020-03-04 03:56:56 [:239:WriteOutput] INFO  - 100 1 10 0.500000 0.000000 :: 7835.533333 0.000000 0

./targets/pebblesdb_ycsb -I "pebblesdb" -k 100 -D "/tmp/testpebblesdb"
2020-03-04 03:57:31 [:69:ValidateScaleFactor] INFO  - scale_factor : 100
2020-03-04 03:57:31 [:78:ValidateDuration] INFO  - duration : 30.000000
2020-03-04 03:57:31 [:87:ValidateProfileDuration] INFO  - profile_duration : 1.000000
2020-03-04 03:57:31 [:96:ValidateBackendCount] INFO  - backend_count : 1
2020-03-04 03:57:31 [:106:ValidateOperationCount] INFO  - operation_count : 10
2020-03-04 03:57:31 [:115:ValidateUpdateRatio] INFO  - update_ratio : 0.500000
2020-03-04 03:57:31 [:124:ValidateZipfTheta] INFO  - zipf_theta : 0.000000
2020-03-04 03:57:31 [:133:ValidateIndexType] INFO  - index_type : pebblesdb
2020-03-04 03:57:31 [:217:ParseArguments] INFO  - Run exponential backoff : 0
2020-03-04 03:57:31 [:218:ParseArguments] INFO  - Run string mode : 0
2020-03-04 03:57:32 [:111:LoadYCSBDatabase] INFO  - database table loading time = 497.000000 ms
2020-03-04 03:57:32 [:114:LoadYCSBDatabase] INFO  - user count = 100000
2020-03-04 03:58:02 [:230:WriteOutput] INFO  - ----------------------------------------------------------
2020-03-04 03:58:02 [:239:WriteOutput] INFO  - 100 1 10 0.500000 0.000000 :: 2503.033333 0.000000 0

 ./targets/silkstore_ycsb -I "silkstore" -k 100 -D "/tmp/testsilkstore"
2020-03-04 03:59:07 [:69:ValidateScaleFactor] INFO  - scale_factor : 100
2020-03-04 03:59:07 [:78:ValidateDuration] INFO  - duration : 30.000000
2020-03-04 03:59:07 [:87:ValidateProfileDuration] INFO  - profile_duration : 1.000000
2020-03-04 03:59:07 [:96:ValidateBackendCount] INFO  - backend_count : 1
2020-03-04 03:59:07 [:106:ValidateOperationCount] INFO  - operation_count : 10
2020-03-04 03:59:07 [:115:ValidateUpdateRatio] INFO  - update_ratio : 0.500000
2020-03-04 03:59:07 [:124:ValidateZipfTheta] INFO  - zipf_theta : 0.000000
2020-03-04 03:59:07 [:133:ValidateIndexType] INFO  - index_type : silkstore
2020-03-04 03:59:07 [:217:ParseArguments] INFO  - Run exponential backoff : 0
2020-03-04 03:59:07 [:218:ParseArguments] INFO  - Run string mode : 0
2020-03-04 03:59:08 [:111:LoadYCSBDatabase] INFO  - database table loading time = 766.000000 ms
2020-03-04 03:59:08 [:114:LoadYCSBDatabase] INFO  - user count = 100000
2020-03-04 03:59:38 [:230:WriteOutput] INFO  - ----------------------------------------------------------
2020-03-04 03:59:38 [:239:WriteOutput] INFO  - 100 1 10 0.500000 0.000000 :: 1860.400000 0.000896 0

./targets/wisckey_ycsb -I "wisckey" -k 100 -D "/tmp/testwisckey"
2020-03-04 04:00:01 [:69:ValidateScaleFactor] INFO  - scale_factor : 100
2020-03-04 04:00:01 [:78:ValidateDuration] INFO  - duration : 30.000000
2020-03-04 04:00:01 [:87:ValidateProfileDuration] INFO  - profile_duration : 1.000000
2020-03-04 04:00:01 [:96:ValidateBackendCount] INFO  - backend_count : 1
2020-03-04 04:00:01 [:106:ValidateOperationCount] INFO  - operation_count : 10
2020-03-04 04:00:01 [:115:ValidateUpdateRatio] INFO  - update_ratio : 0.500000
2020-03-04 04:00:01 [:124:ValidateZipfTheta] INFO  - zipf_theta : 0.000000
2020-03-04 04:00:01 [:133:ValidateIndexType] INFO  - index_type : wisckey
2020-03-04 04:00:01 [:217:ParseArguments] INFO  - Run exponential backoff : 0
2020-03-04 04:00:01 [:218:ParseArguments] INFO  - Run string mode : 0
2020-03-04 04:00:03 [:111:LoadYCSBDatabase] INFO  - database table loading time = 2244.000000 ms
2020-03-04 04:00:03 [:114:LoadYCSBDatabase] INFO  - user count = 100000
2020-03-04 04:00:33 [:230:WriteOutput] INFO  - ----------------------------------------------------------
2020-03-04 04:00:33 [:239:WriteOutput] INFO  - 100 1 10 0.500000 0.000000 :: 8184.866667 0.000000 0