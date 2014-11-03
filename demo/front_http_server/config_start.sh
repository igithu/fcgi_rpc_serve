#! /bin/bash

#export CPLUS_INCLUDE_PATH=/home/users/aishuyu/open_src/tair/tb_common_utils/tb_libs/include/libeasy
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/users/aishuyu/open_src/tb_common_utils/tb_libs/lib

#export LIBRARY_PATH=/home/users/aishuyu/open_src/tb_common_utils/tb_libs/glibc-2.4/lib

./configure CPPFLAGS="-I/home/users/aishuyu/.jumbo/opt/gcc46/include -I/home/users/aishuyu/.jumbo/include" LDFLAGS="-L/home/users/aishuyu/.jumbo/lib -L/home/users/aishuyu/.jumbo/opt/gcc46/lib64 -L/home/users/aishuyu/.jumbo/opt/gcc46/lib/" CC=/home/users/aishuyu/.jumbo/opt/gcc46/bin/gcc CXX=/home/users/aishuyu/.jumbo/opt/gcc46/bin/g++ 
#CFLAGS="-march=i686" 
