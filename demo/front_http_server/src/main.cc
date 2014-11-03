/***************************************************************************
 * 
 * Copyright (c) 2014 , Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file main.cc
 * @author 
 * @date 2014/10/27 15:18:24
 * @brief 
 *  
 **/


#include <string>

#include "fcgiapp.h"
//#include "fcgi_stdio.h"

#include "result_format.h"
#include "params_parser.h"
#include "thrift_rpc_client.h"
#include "../../utils/init_google.h"

using namespace fcgi_http_server;
using std::string;

inline void send_response(FCGX_Request& request, const string& resp_str, const string& result_fmt) {
    if ("pb" == result_fmt) {
        FCGX_FPrintF(request.out, "Content-type: application/octet-stream\r\n\r\n");
        FCGX_PutStr(resp_str.c_str(), resp_str.size(), request.out);
    } else {
        FCGX_FPrintF(request.out, "Content-type: text/html;charset=utf-8\r\n\r\n");
        FCGX_FPrintF(request.out, "%s", resp_str.c_str());
    }
    FCGX_Finish_r(&request);
}


int main(int argc, char* argv[]) {

    //InitGoogle(&argc, &argv);

    google::InitGoogleLogging(argv[0]); 
    FLAGS_log_dir="/home/users/aishuyu/tmp1/glog";

    FCGX_Init();
    FCGX_Request request;
    FCGX_InitRequest(&request, 0, 0);

    boost::shared_ptr<HttpServerRpcClient> http_rpc_client_ptr(new HttpServerRpcClient());
    while (FCGX_Accept_r(&request) >= 0) {
        string query_str = FCGX_GetParam("QUERY_STRING", request.envp);
        const string result_fmt = ParamsParser::ParseResultFmt(query_str);
        
        FcgiHttpRequest fcgi_http_request;
        string format_response_str;
        ResultFormatter::FormatErrorResponse(fcgi_http_request, format_response_str);
        try {
            if (!ParamsParser::ParseRequestParams(query_str, fcgi_http_request)) {
                LOG(ERROR) << "parse request params failed!";
                send_response(request, format_response_str, result_fmt);
                continue;
            }

            const char *client_ip_str = FCGX_GetParam("HTTP_X_REAL_IP",request.envp);
            if (NULL == client_ip_str) {
                client_ip_str = FCGX_GetParam("REMOTE_ADDR", request.envp);
            }

            if (NULL == client_ip_str) {
                client_ip_str = "";
            }

            string http_server_request_str;
            fcgi_http_request.SerializeToString(&http_server_request_str);

            string http_server_response_str;
            bool status = false; 
            if (fcgi_http_request.op() == "+") {
                status = http_rpc_client_ptr->Add(http_server_request_str, http_server_response_str);
            } else if (fcgi_http_request.op() == "-") {
                status = http_rpc_client_ptr->Sub(http_server_request_str, http_server_response_str);
            }

            if (!status) {
                send_response(request, format_response_str, result_fmt);
                continue;
            }

            FcgiHttpResponse fcgi_http_response;
            fcgi_http_response.set_ip(client_ip_str);
            if (!fcgi_http_response.ParseFromString(http_server_response_str)) {
                send_response(request, format_response_str, result_fmt);
                continue;
            }

            ResultFormatter::FormatResponse(
                    fcgi_http_request, fcgi_http_response, format_response_str);

            send_response(request, format_response_str, result_fmt);

        } catch (std::exception&) {
            send_response(request, format_response_str, result_fmt);
        }
    }

    return 0;
}







/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
