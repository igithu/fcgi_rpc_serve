/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file http_server_handler.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2014/10/31 15:14:01
 * @brief 
 *  
 **/

#include <glog/logging.h>

#include "../../proto/proto_cpp/commun.pb.h"

#include "http_server_handler.h"

namespace backend_rpc_server {
    
    using namespace fcgi_commu;

    HttpServerHandler::HttpServerHandler() {
    }

    HttpServerHandler::~HttpServerHandler() {
    }

    void HttpServerHandler::add(std::string& _return, 
                                const std::string& request_str) {
        FcgiHttpRequest h_request;
        if (!h_request.ParseFromString(request_str)) {
            return;
        }

        int ret = h_request.param_one() + h_request.param_two();

        FcgiHttpResponse h_reponse;
        h_reponse.set_result(ret);
        h_reponse.SerializeToString(&_return);

    }

    void HttpServerHandler::sub(std::string& _return,
                                const std::string& request_str) {
        FcgiHttpRequest h_request;
        if (!h_request.ParseFromString(request_str)) {
            return;
        }

        int ret = h_request.param_one() - h_request.param_two();

        FcgiHttpResponse h_reponse;
        h_reponse.set_result(ret);
        h_reponse.SerializeToString(&_return);

    }

    boost::shared_ptr<TProcessor> THttpServerProcessorFactory::getProcessor(
            const TConnectionInfo& connInfo) {
        boost::shared_ptr<HttpServerIf> service(new HttpServerHandler());
        return boost::shared_ptr<TProcessor>(new HttpServerProcessor(service));
    }

}  // end of namespace backend_rpc_server






/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
