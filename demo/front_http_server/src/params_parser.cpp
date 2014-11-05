/***************************************************************************
 * 
 * Copyright (c) 2014 aishuyu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file params_parser.cpp
 * @author aishuyu(asy5178@163.com)
 * @date 2014/10/27 15:31:06
 * @brief 
 *  
 **/

#include <vector>
#include <iostream>

#include <glog/logging.h>
#include <google/gflags.h>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "params_parser.h"


DEFINE_string(req_param_one, "param_one", "first param");
DEFINE_string(req_param_two, "param_two", "first param");
DEFINE_string(req_op, "op", "add or sub");
DEFINE_string(req_result_format, "pb", "fmt");

namespace fcgi_http_server {

    using std::vector;

    bool UrlDecode(const string& in, string& out) {
         out.clear();
         out.reserve(in.size());

         for (size_t i = 0; i < in.size(); ++i) {
             if (in[i] == '%') {
                 if (i + 3 <= in.size()) {
                     int value = 0;
                     std::istringstream is(in.substr(i + 1, 2));
                     if (is >> std::hex >> value) {
                         out += static_cast<char>(value);
                         i += 2;
                     } else {
                         return false;
                     }
                 } else {
                     return false;
                 }
             } else if (in[i] == '+') {
                 out += ' ';
             } else {
                 out += in[i];
             }
         }
         return true;
    }


    bool ParamsParser::ParseRequestParams(const string& query_str, FcgiHttpRequest &fcgi_request) {
        //if (NULL == fcgi_request) {
        //    return false;
        //}
        vector<string> query_vec;
        boost::split(query_vec, query_str, boost::is_any_of("&"));

        try {
            vector<string> key_value;
            for (vector<string>::const_iterator itr = query_vec.begin();
                 itr != query_vec.end();
                 ++itr) {
                key_value.clear();
                boost::split(key_value, *itr, boost::is_any_of("="));
                if (key_value.size() != 2) {
                    continue;
                }

                string& key_str = key_value[0];
                boost::trim(key_str);
                string val_str;
                UrlDecode(key_value[1], val_str);

                if (0 == key_str.compare(FLAGS_req_param_one) && !val_str.empty()) {
                    int32_t param_one;
                    try {
                        param_one = boost::lexical_cast<int32_t>(val_str);
                    } catch (std::exception&) {
                        LOG(ERROR) << "parse the param" + val_str + " failed!";
                        return false;
                    }
                    fcgi_request.set_param_one(param_one); 
                } else if (0 == key_str.compare(FLAGS_req_param_two) && !val_str.empty()) {
                    int32_t param_two;
                    try {
                        param_two = boost::lexical_cast<int32_t>(val_str);
                    } catch (std::exception&) {
                        LOG(ERROR) << "parse the param" + val_str + " failed!";
                        return false;
                    }
                    fcgi_request.set_param_two(param_two); 
                } else if (0 == key_str.compare(FLAGS_req_op) && !val_str.empty()) {
                    fcgi_request.set_op(val_str); 
                }

            }
        } catch (std::exception&) {
            LOG(ERROR) << "parse params exception!";
            return false;
        }

        return true;
    }

    string ParamsParser::ParseResultFmt(const string& query_str) {
        vector<string> query_pairs;
        boost::split(query_pairs, query_str, boost::is_any_of("&"));
        vector<string> key_value;

        for (vector<string>::const_iterator itr = query_pairs.begin();
             itr != query_pairs.end();
             ++itr) {
            key_value.clear();
            boost::split(key_value, *itr, boost::is_any_of("="));
            if (key_value.size() == 2) {
                string key_str = key_value[0];
                boost::trim(key_str);
                string val_str;
                UrlDecode(key_value[1], val_str);
                boost::trim(val_str);
                if (0 == key_str.compare(FLAGS_req_result_format) && !val_str.empty()) {
                    if (val_str == "pb") {
                        return "pb";
                    }
                }
            }
        }

        return "json";
    }
}  // end of namespace fcgi_http_server








/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
