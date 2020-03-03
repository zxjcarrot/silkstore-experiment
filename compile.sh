#!/bin/bash

if [  -d "build" ];then
rm -r build
fi

if [ -d "targets" ];then
rm -r targets
fi

mkdir targets
mkdir build

cd build

cmake -DMAKE_LEVELDB=ON ..
cmake ..
make
make install
cmake -DMAKE_LEVELDB=OFF ..

cmake -DMAKE_PEBBLESDB=ON ..
cmake ..
make
make install
cmake -DMAKE_PEBBLESDB=OFF ..

cmake -DMAKE_SILKSTORE=ON ..
cmake ..
make
make install
cmake -DMAKE_SILKSTORE=OFF ..

cmake -DMAKE_WISCKEY=ON ..
cmake ..
make
make install
cmake -DMAKE_WISCKEY=OFF ..


