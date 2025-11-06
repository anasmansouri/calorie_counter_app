#!/bin/bash
#rm json_data_base.json
cd build
#rm -r *
cmake .. 
make 
#./bin/cc_app
gdb ./bin/cc_app
