
#SUBDIRS=src
#DIST_SUBDIRS=src

bin_PROGRAMS = fcgi_http_server

fcgi_http_server_SOURCES = \
		      src/main.cc \
		      src/params_parser.cpp \
		      src/params_parser.h \
		      src/result_format.cpp \
		      src/result_format.h \
		      src/thrift_rpc_client.cpp \
		      src/thrift_rpc_client.h \
		      ../proto/proto_cpp/commun.pb.cc \
		      ../proto/proto_cpp/commun.pb.h \
		      ../proto/http_server/gen-cpp/HttpServer.h \
		      ../proto/http_server/gen-cpp/HttpServer.cpp \
		      ../utils/init_google.h \
		      ../utils/init_google.cpp 

#INCLUDES = -I../third-64/libevent/include/
#CXXFLAGS = -std=c++11 -Wall -g -fPIC
fcgi_http_server_CPPFLAGS = -I../../third-64/fcgi/include/ \
     			    -I../../third-64/thrift/include/ \
     			    -I../../third-64/json-cpp/include/ \
			    -I../../third-64/boost/include/ \
			    -I../../third-64/protobuf/include/ \
			    -I../../third-64/gflags/include/ \
			    -I../../third-64/rapidjson/include \
			    -I../../third-64/glog/include/ \
		            -I../utils/include/

fcgi_http_server_LDFLAGS = -DHAVE_NETINET_IN_H -fpermissive 
fcgi_http_server_LDADD = -lpthread -lz -ldl -lrt  \
		       	 ../../third-64/fcgi/lib/*.a  \
     			 ../../third-64/thrift/lib/*.a  \
			 ../../third-64/json-cpp/lib/*.a  \
			 ../../third-64/boost/lib/*.a  \
			 ../../third-64/protobuf/lib/*.a \
			 ../../third-64/gflags/lib/*.a \
			 ../../third-64/glog/lib/*.a 
#http_server_a_LDADD = ../third-64/libevent/lib/*.a
