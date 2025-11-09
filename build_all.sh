#!/bin/bash
#rm json_data_base.json
cd build
#rm -r *
#cmake .. 
#make 
cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON ..
cmake --build . -j
ctest --output-on-failure
./bin/cc_app
#gdb ./bin/cc_app
