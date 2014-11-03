/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file params_parser.h
 * @author aishuyu(com@baidu.com)
 * @date 2014/10/27 15:25:28
 * @brief 
 *  
 **/




#ifndef  __PARAMS_PARSER_H_
#define  __PARAMS_PARSER_H_

#include <string>

#include "../../proto/proto_cpp/commun.pb.h"

namespace fcgi_http_server {

    using namespace fcgi_commu;
    using std::string;

    class ParamsParser {
        public:
            static bool ParseRequestParams(const string& query_str, FcgiHttpRequest &request_ptr);
            static string ParseResultFmt(const string& query_str);
    };

}  // end of namespace fcgi_http_server



#endif  //__PARAMS_PARSER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
