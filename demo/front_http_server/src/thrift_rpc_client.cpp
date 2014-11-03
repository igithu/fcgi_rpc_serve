/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file thrift_rpc_client.cpp
 * @author aishuyu(com@baidu.com)
 * @date 2014/10/28 13:28:42
 * @brief 
 *  
 **/

#include <google/gflags.h>

#include "thrift_rpc_client.h"

namespace fcgi_http_server {

    using namespace apache::thrift;
    using namespace apache::thrift::protocol;
    using namespace apache::thrift::transport;

    DEFINE_string(rpc_server_host, "localhost", "The host of the server.");
    DEFINE_int32(rpc_server_port, 9090, "The port of the server.");
    DEFINE_int32(rpc_client_timeout_in_ms, 900, "The timeout of rpc client.");

    HttpServerRpcClient::HttpServerRpcClient() {
        client_.reset(new ThriftClient<HttpServerClient>(
                    FLAGS_rpc_server_host,
                    FLAGS_rpc_server_port,
                    FLAGS_rpc_client_timeout_in_ms));
        client_->Start();
    }

    HttpServerRpcClient::~HttpServerRpcClient() {
    }

    bool HttpServerRpcClient::Add(const string& requesr_str, string& response_str_ptr) {
        int max_try_count = 2;

        while (max_try_count-- > 0) {
            if (!client_->GetStatus()) {
                client_->Open();
            }

            boost::shared_ptr<HttpServerClient> rpc_client = client_->GetClient();

            try {
                rpc_client->add(response_str_ptr, requesr_str);
                return true;
            } catch (TException& tx) {
                if (max_try_count > 0) {
                    continue;
                }
                client_->SetStatus(false);
            }
        }

        return false;
    }

    bool HttpServerRpcClient::Sub(const string& requesr_str, string& response_str_ptr) {
        int max_try_count = 2;

        while (max_try_count-- > 0) {
            if (!client_->GetStatus()) {
                client_->Open();
            }

            boost::shared_ptr<HttpServerClient> rpc_client = client_->GetClient();

            try {
                rpc_client->sub(response_str_ptr, requesr_str);
                return true;
            } catch (TException& tx) {
                if (max_try_count > 0) {
                    continue;
                }
                client_->SetStatus(false);
            }
        }

        return false;
    }





}  // end of namespace fcgi_http_server





/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
