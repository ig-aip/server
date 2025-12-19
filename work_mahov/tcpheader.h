#ifndef TCPHEADER_H
#define TCPHEADER_H
#include <boost/asio.hpp>


#pragma pack(push, 1)
struct tcpHeader
{
    //1 - sent 0 - accept
    bool isSent;
    boost::asio::ip::address adr;
    uint16_t port;
    char name_[225];
    uint64_t size_byte;
};

#pragma pack(pop)
#endif // TCPHEADER_H
