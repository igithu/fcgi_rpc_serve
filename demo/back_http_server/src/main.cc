/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file main.cc
 * @author aishuyu(com@baidu.com)
 * @date 2014/10/30 16:35:48
 * @brief 
 *  
 **/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <signal.h>
#include <fcntl.h>
#include <string.h>

#include <google/gflags.h>
#include "../../utils/init_google.h"
#include "backend_rpc_server.h"

using namespace backend_rpc_server;

DEFINE_bool(daemon, false, "True if run as a daemon process.");


inline void InitSignal() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    if (-1 == sigaction(SIGPIPE, &sa, NULL)) {
        exit(1);
    }
}


inline void Daemonize() {

    if (0 != fork()) {
        exit(0);
    }
    setsid();
    int fd = open("/dev/null", O_RDWR, 0);
    if (-1 != fd) {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        if (fd > STDERR_FILENO) {
            close(fd);
        }
    }                     
}

int main(int argc, char* argv[]) {

    InitSignal();
//    google::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]); 
    FLAGS_log_dir="/home/users/aishuyu/tmp1/glog";
    LOG(ERROR) << "init test";

    if (FLAGS_daemon) {
        Daemonize();
    }


    ThriftRpcServer& global_server = ThriftRpcServer::GetInstance();
    global_server.Start();
    global_server.Wait();
    global_server.Stop();

    return 0;
}






/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
