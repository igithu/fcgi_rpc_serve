#/bin/bash

/home/users/aishuyu/.jumbo/others/nginx/sbin/spawn-fcgi -a 127.0.0.1 -p 9000  -F 1 -- /home/users/aishuyu/open_src/my_src/fcgi_server/fcgi_http_serve/demo/front_http_server/fcgi_http_server -log_dir=/home/users/aishuyu/tmp1/glog
