/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file thrift_rpc_client.h
 * @author aishuyu(asy5178@163.com)
 * @date 2014/10/27 18:07:12
 * @brief 
 *  
 **/




#ifndef  __THRIFT_RPC_CLIENT_H_
#define  __THRIFT_RPC_CLIENT_H_

#include <string>

#include <boost/shared_ptr.hpp>

#include "thrift_client.h"
#include "../../proto/http_server/gen-cpp/HttpServer.h"

//template<class T>
//class ThriftClient;

namespace fcgi_http_server {

    using std::string;
    
    ///class HttpServerClient;

    class HttpServerRpcClient {
        public:
            HttpServerRpcClient(); 
            virtual ~HttpServerRpcClient();

            bool Add(const string& requesr_str, string &response_str_ptr);
            bool Sub(const string& requesr_str, string &response_str_ptr);
    
        private:
            boost::shared_ptr<ThriftClient<HttpServerClient> > client_;
    };


}  // end of namespace fcgi_http_server


#endif  //__THRIFT_RPC_CLIENT_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
