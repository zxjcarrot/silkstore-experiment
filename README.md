# ycsb-experiment


shuang@shuang-X555LD:/media/shuang/Workspace/cpp-workspace/silkstore-experiment-master/build$ ./ycsb -I "leveldb" -k 100 -D "/tmp/testdb"
2020-03-02 21:49:10 [:69:ValidateScaleFactor] INFO  - scale_factor : 100
2020-03-02 21:49:10 [:78:ValidateDuration] INFO  - duration : 30.000000
2020-03-02 21:49:10 [:87:ValidateProfileDuration] INFO  - profile_duration : 1.000000
2020-03-02 21:49:10 [:96:ValidateBackendCount] INFO  - backend_count : 1
2020-03-02 21:49:10 [:106:ValidateOperationCount] INFO  - operation_count : 10
2020-03-02 21:49:10 [:115:ValidateUpdateRatio] INFO  - update_ratio : 0.500000
2020-03-02 21:49:10 [:124:ValidateZipfTheta] INFO  - zipf_theta : 0.000000
2020-03-02 21:49:10 [:133:ValidateIndexType] INFO  - index_type : leveldb
2020-03-02 21:49:10 [:217:ParseArguments] INFO  - Run exponential backoff : 0
2020-03-02 21:49:10 [:218:ParseArguments] INFO  - Run string mode : 0
2020-03-02 21:49:11 [:103:LoadYCSBDatabase] INFO  - database table loading time = 408.000000 ms
2020-03-02 21:49:11 [:106:LoadYCSBDatabase] INFO  - user count = 100000
2020-03-02 21:49:41 [:230:WriteOutput] INFO  - ----------------------------------------------------------
2020-03-02 21:49:41 [:239:WriteOutput] INFO  - 100 1 10 0.500000 0.000000 :: 19184.266667 0.000000 0

shuang@shuang-X555LD:/media/shuang/Workspace/cpp-workspace/silkstore-experiment-master/build$ ./ycsb -I "pebblesdb" -k 100 -D "/tmp/testdb"
2020-03-02 21:53:25 [:69:ValidateScaleFactor] INFO  - scale_factor : 100
2020-03-02 21:53:25 [:78:ValidateDuration] INFO  - duration : 30.000000
2020-03-02 21:53:25 [:87:ValidateProfileDuration] INFO  - profile_duration : 1.000000
2020-03-02 21:53:25 [:96:ValidateBackendCount] INFO  - backend_count : 1
2020-03-02 21:53:25 [:106:ValidateOperationCount] INFO  - operation_count : 10
2020-03-02 21:53:25 [:115:ValidateUpdateRatio] INFO  - update_ratio : 0.500000
2020-03-02 21:53:25 [:124:ValidateZipfTheta] INFO  - zipf_theta : 0.000000
2020-03-02 21:53:25 [:133:ValidateIndexType] INFO  - index_type : pebblesdb
2020-03-02 21:53:25 [:217:ParseArguments] INFO  - Run exponential backoff : 0
2020-03-02 21:53:25 [:218:ParseArguments] INFO  - Run string mode : 0
2020-03-02 21:53:25 [:103:LoadYCSBDatabase] INFO  - database table loading time = 500.000000 ms
2020-03-02 21:53:25 [:106:LoadYCSBDatabase] INFO  - user count = 100000
2020-03-02 21:53:55 [:230:WriteOutput] INFO  - ----------------------------------------------------------
2020-03-02 21:53:55 [:239:WriteOutput] INFO  - 100 1 10 0.500000 0.000000 :: 14440.766667 0.000000 0
