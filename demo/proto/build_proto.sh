# /bin/sh

PROTOC=./protoc
CPPIN=./
#CPPOUT=../front_http_server/src/proto_cpp
CPPOUT=./proto_cpp

if [ ! -d "$CPPIN" ]; then 
    echo $CPPIN "is not exist! program exit!"
    exit 0
fi

if [ ! -f "$PROTOC" ]; then 
    echo $PROTOC"is not exist! program exit!"
    exit 0
fi

if [ ! -d "$CPPOUT" ]; then 
    mkdir $CPPOUT
fi

$PROTOC -I=$CPPIN --cpp_out=$CPPOUT $CPPIN/*.proto

if [ $? != 0 ]; then
	echo "generated pb ccp failed!"
	exit 1
fi

echo "generated pb ccp is completed!"
