/***************************************************************************
 * 
 * Copyright (c) 2014 aishuyu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file common_log.h
 * @author aishuyu(asy5178@163.com)
 * @date 2014/11/01 17:54:47
 * @brief 
 *  
 **/




#ifndef  __COMMON_LOG_H_
#define  __COMMON_LOG_H_

#include <glog/logging.h>

#define FATAL    1 
#define ERROR    2
#define WARNING  3 
#define INFO     4
#define DEBUG    5

#define WRITE_LOG(_loglevel_, _fmt_, args...) \
    do { \ 
        if (_loglevel_ > )
        fprintf(stderr, "[%s|%s@%s,%d] " _fmt_ "/n", \
                _loglevel_, __func__, __FILE__, __LINE__, ##__VA_ARGS__ ); \
    } while (0)  

#define LOG_FATAL(_fmt_, args...) \
    do { \ 
        if (_loglevel_ <= FATAL )
        fprintf(stderr, "[%s|%s@%s,%d] " _fmt_ "/n", \
                _loglevel_, __func__, __FILE__, __LINE__, ##__VA_ARGS__ ); \
    } while (0)

#define LOG_WARNING(_fmt_, args...) 








#endif  //__COMMON_LOG_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
