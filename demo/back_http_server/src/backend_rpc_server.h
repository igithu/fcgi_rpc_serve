/***************************************************************************
 * 
 * Copyright (c) 2014 aishuyu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file backend_rpc_server.h
 * @author aishuyu(asy5178@163.com)
 * @date 2014/10/30 16:43:33
 * @brief 
 *  
 **/




#ifndef  __BACKEND_RPC_SERVER_H_
#define  __BACKEND_RPC_SERVER_H_

#include <boost/shared_ptr.hpp>

#include <thrift/server/TThreadPoolServer.h>

#include "thread.h"
#include "disallow_copy_and_assign.h"

namespace backend_rpc_server {

    using apache::thrift::server::TThreadPoolServer;

    class ThriftRpcServer : public Thread {
        public:
            static ThriftRpcServer& GetInstance();
            ~ThriftRpcServer();
            virtual void Run();

        private:
            ThriftRpcServer();
            ThriftRpcServer(const ThriftRpcServer&);
            void operator=(const ThriftRpcServer&);

        private:
            boost::shared_ptr<TThreadPoolServer> thread_pool_server_;
            // boost::shared_ptr<Thread> thread_ptr_;
        private:
            //DISALLOW_COPY_AND_ASSIGN(ThriftRpcServer);
    };
}  // end of namespace














#endif  //__BACKEND_RPC_SERVER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
