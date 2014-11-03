/***************************************************************************
 * 
 * Copyright (c) 2014 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file result_format.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2014/10/28 15:19:44
 * @brief 
 *  
 **/


#include <gflags/gflags.h>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>

// #include "../../proto/proto_cpp/commun.pb.h"
#include "result_format.h"

namespace fcgi_http_server {

    using namespace rapidjson;

    DEFINE_string(cur_version, "version: demo", "demo");
    DEFINE_string(succ_status, "succ", "run succ");
    DEFINE_string(fail_status, "fail", "run failed");


    bool FormatDataResponse(const FcgiHttpRequest& request,
                            const FcgiHttpResponse& response,
                            Document::AllocatorType& allocator,
                            Value& data_obj) {

        data_obj.AddMember("result", response.result(), allocator);
        //data_obj.AddMember("yourIP", request.ip().c_str(), allocator);
        return true;
    }

    bool ResultFormatter::FormatResponse(const FcgiHttpRequest& request,
                                         const FcgiHttpResponse& response,
                                         string& output_str) {
        //response.set_ip(request.ip());
        if (request.fmt() == "pb") {
            response.SerializeToString(&output_str);
        } else {
            Document doc;
            doc.SetObject();

            Document::AllocatorType& allocator = doc.GetAllocator();
            Value data_obj(kObjectType);
            data_obj.AddMember("status", "succ", allocator);
            doc.AddMember("arribute", data_obj, allocator);

            Value data_obj_ret(kObjectType);
            FormatDataResponse(request, response, allocator, data_obj_ret);
            doc.AddMember("result_data", data_obj_ret, allocator);

            StringBuffer buffer;
            Writer<StringBuffer> writer(buffer);
            doc.Accept(writer);
            output_str = buffer.GetString();
        }
        
        return true;
    }

    bool ResultFormatter::FormatErrorResponse(const FcgiHttpRequest& request,
                                              //const FcgiHttpReponse& response,
                                              string& output_str) {

        if  (request.fmt() == "pb") {
            // TODO, for now error output_str is empty
        } else {
            Document doc;
            doc.SetObject();
            
            Document::AllocatorType& allocator = doc.GetAllocator();
            Value data_obj(kObjectType);
            data_obj.AddMember("status", "failed", allocator);
            doc.AddMember("arribute", data_obj, allocator);

            StringBuffer buffer;
            Writer<StringBuffer> writer(buffer);
            doc.Accept(writer);
            output_str = buffer.GetString();
        }
        return true;

    }

}















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
