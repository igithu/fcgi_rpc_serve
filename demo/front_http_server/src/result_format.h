/***************************************************************************
 * 
 * Copyright (c) 2014 aishuyu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file result_format.h
 * @author aishuyu(asy5178@163.com)
 * @date 2014/10/28 15:12:58
 * @brief 
 *  
 **/




#ifndef  __RESULT_FORMAT_H_
#define  __RESULT_FORMAT_H_

#include <string>

#include "../../proto/proto_cpp/commun.pb.h"

namespace fcgi_http_server {

    using namespace fcgi_commu;
    using std::string;

    class ResultFormatter {
        public:
            static bool FormatResponse(const FcgiHttpRequest& request,
                                       const FcgiHttpResponse& reponse,
                                       string& result);
            static bool FormatErrorResponse(const FcgiHttpRequest& request,
                                            // const FcgiHttpReponse& reponse,
                                            string& result);
            // static bool FormatDefaultErrorResponse(const FcgiHttpRequest& request,
            //                                        const FcgiHttpReponse& reponse,
            //                                        string& result);
            //static bool FormatResponse(const FcgiHttpRequest& request,
            //                           const FcgiHttpReponse* reponse,
            //                           string& result);
    };

}  // end of namespace fcgi_http_server











#endif  //__RESULT_FORMAT_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
