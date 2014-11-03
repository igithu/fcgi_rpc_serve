#!/bin/bash

THRIFT_PATH=../../third-64/thrift/bin

if [ ! -d http_server ]; then
        mkdir http_server
fi
$THRIFT_PATH/thrift --gen cpp -o http_server http_server.thrift
