/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file backend_rpc_server.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2014/10/31 14:28:30
 * @brief 
 *  
 **/



#include <google/gflags.h>
#include <thrift/concurrency/PlatformThreadFactory.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSSLServerSocket.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "http_server_handler.h"
#include "backend_rpc_server.h"

DEFINE_int32(rpc_server_port, 9090, "The port of the rpc server.");
DEFINE_int32(rpc_thread_pool_size, 100,
        "The size of the rpc thread pool. Because of long connection, "\
        "this size should a little larger than fcgi process number.");

namespace backend_rpc_server {

    using apache::thrift::concurrency::PlatformThreadFactory;
    using apache::thrift::protocol::TProtocolFactory;
    using apache::thrift::TProcessorFactory;
    using apache::thrift::protocol::TBinaryProtocolFactoryT;
    using apache::thrift::transport::TBufferBase;
    using apache::thrift::transport::TBufferedTransportFactory;
    using apache::thrift::transport::TServerSocket;
    using apache::thrift::transport::TTransportFactory;
    using apache::thrift::server::ThreadManager;


    ThriftRpcServer& ThriftRpcServer::GetInstance() {
        static ThriftRpcServer instance;
        return instance;
    }

    ThriftRpcServer::ThriftRpcServer () {
    }


    ThriftRpcServer::~ThriftRpcServer () {
        fprintf(stderr, "end ThriftRpcServer");
    }

    void ThriftRpcServer::Run() {
         boost::shared_ptr<TProtocolFactory> protocolFactory(
                 new TBinaryProtocolFactoryT<TBufferBase>());

         // THttpServerProcessorFactory: hold the HttpServerHandler
         boost::shared_ptr<TProcessorFactory> processorFactory(
                 new THttpServerProcessorFactory());

         boost::shared_ptr<TServerSocket> serverSocketPtr(
                 new TServerSocket(FLAGS_rpc_server_port));

         boost::shared_ptr<TTransportFactory> transportFactory(
                 new TBufferedTransportFactory());

         boost::shared_ptr<ThreadManager> threadManagerPtr =
             ThreadManager::newSimpleThreadManager(FLAGS_rpc_thread_pool_size);

         boost::shared_ptr<PlatformThreadFactory> threadFactory =
             boost::shared_ptr<PlatformThreadFactory>(new PlatformThreadFactory());

         threadManagerPtr->threadFactory(threadFactory);
         threadManagerPtr->start();
         thread_pool_server_.reset(new TThreadPoolServer(processorFactory,
                                                         serverSocketPtr,
                                                         transportFactory,
                                                         protocolFactory,
                                                         threadManagerPtr));
         thread_pool_server_->serve();
    }

}  // end of namespace backend_rpc_server 





















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
