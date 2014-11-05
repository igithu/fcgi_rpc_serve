/***************************************************************************
 * 
 * Copyright (c) 2014 aishuyu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file http_server_handler.h
 * @author aishuyu(asy5178@163.com)
 * @date 2014/10/31 14:58:02
 * @brief 
 *  
 **/




#ifndef  __HTTP_SERVER_HANDLER_H_
#define  __HTTP_SERVER_HANDLER_H_

#include <boost/shared_ptr.hpp>

#include "../../proto/http_server/gen-cpp/HttpServer.h"

namespace backend_rpc_server {

    using apache::thrift::TProcessor;
    using apache::thrift::TProcessorFactory;
    using apache::thrift::TConnectionInfo;

    class HttpServerHandler : public HttpServerIf {
        public:
            HttpServerHandler();
            ~HttpServerHandler();

            virtual void add(std::string& _return, const std::string& request_str);
            virtual void sub(std::string& _return, const std::string& request_str);
    };


    class THttpServerProcessorFactory : public TProcessorFactory {
        public:
            THttpServerProcessorFactory() {}
            boost::shared_ptr<TProcessor> getProcessor(const TConnectionInfo& connInfo);
    };
}  // end of namespace backend_rpc_server




#endif  //__HTTP_SERVER_HANDLER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
