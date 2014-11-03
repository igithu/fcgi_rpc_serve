/*
 * @file thrift_client.h
 * @brief thrift rpc cleint  tool
 * @author kenwell
 * @date 2012.10.17
 */

#ifndef UTIL_THRIFT_CLIENT_H
#define UTIL_THRIFT_CLIENT_H

#include <string>

#include <thrift/Thrift.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include <boost/shared_ptr.hpp>
#include <gflags/gflags.h>
#include <glog/logging.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace boost;

template <class T>
class ThriftClient {
public:
    ThriftClient(const std::string& ip, int port, int timeout_in_ms);
    ThriftClient();
    ~ThriftClient();

    boost::shared_ptr<T> GetClient();

    void Init(const std::string&ip, int port);

    bool Start();
    bool Stop();
    bool Open();

    bool GetStatus();
    void SetStatus(bool status);

private:
    void InitClient();

    std::string m_ip;
    int m_port;
    int m_timeout_in_ms;
    boost::shared_ptr<T>  m_clientPtr;
    shared_ptr<TTransport> m_transportPtr;
    bool status_;
};

template<class T>
ThriftClient<T>::ThriftClient()
    : m_ip(""),
      m_port(-1),
      m_timeout_in_ms(500),
      status_(false) {
}

template<class T>
ThriftClient<T>::ThriftClient(const std::string& ip, int port, int timeout_in_ms)
    : m_ip(ip),
      m_port(port),
      m_timeout_in_ms(timeout_in_ms),
      status_(false) {
    InitClient();
}

template<class T>
void ThriftClient<T>::Init(const std::string&ip, int port) {
    m_ip = ip;
    m_port = port;
    InitClient();
}

template<class T>
ThriftClient<T>::~ThriftClient() {
    if (m_transportPtr) {
        m_transportPtr->close();
    }
}

template<class T>
boost::shared_ptr<T> ThriftClient<T>::GetClient() {
    return m_clientPtr;
}

template<class T>
bool ThriftClient<T>::Start() {
    return Open();
}

template<class T>
bool ThriftClient<T>::Stop() {
    if (m_transportPtr) {
        m_transportPtr->close();
    }
    return true;
}


template<class T>
void ThriftClient<T>::InitClient() {
    shared_ptr<TSocket> socket(new TSocket(m_ip, m_port));
    socket->setConnTimeout(m_timeout_in_ms);
    socket->setSendTimeout(m_timeout_in_ms);
    socket->setRecvTimeout(m_timeout_in_ms);
    m_transportPtr.reset(new TBufferedTransport(socket));
    shared_ptr<TProtocol> protocol(new TBinaryProtocol(m_transportPtr));
    m_clientPtr.reset(new T(protocol));
}

template<class T>
bool ThriftClient<T>::Open() {
    if (!m_transportPtr) {
        LOG(ERROR) << "ThriftClient::transport null";
        return false;
    }

    if (m_transportPtr) {
        m_transportPtr->close();
    }

    bool open_status = true;
    try {
        m_transportPtr->open();
    } catch (TException &tx) {
        open_status = false;;
        LOG(ERROR) << "ThriftClient open thriftclient failed, ip:" << m_ip
                   << ", port:" << m_port;
    }

    status_ = open_status;
    return open_status;
}

template<class T>
bool ThriftClient<T>::GetStatus() {
    return status_;
}

template<class T>
void ThriftClient<T>::SetStatus(bool status) {
    status_ = status;
}

#endif
