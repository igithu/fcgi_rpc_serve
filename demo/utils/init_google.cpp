/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file init_google.cpp
 * @author aishuyu(com@baidu.com)
 * @date 2014/11/03 13:11:06
 * @brief 
 *  
 **/


#include "init_google.h"


void FailureWriter(const char* data, int size) {
    write(STDERR_FILENO, data, size);

    google::base::GetLogger(google::FATAL)->Write(
            false, time(NULL), data, size);
}

void InitGoogle(int* argc, char*** argv) {
    google::ParseCommandLineFlags(argc, argv, true);
    google::InitGoogleLogging((*argv)[0]);
    google::InstallFailureSignalHandler();
    google::InstallFailureWriter(&FailureWriter);
}














/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
