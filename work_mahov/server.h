#ifndef SERVER_H
#define SERVER_H
#include "asio.h"
#include "filereciver.h"





class server : public std::enable_shared_from_this<server>
{

    asio::io_context& io_cntx_;
    ip::address addr = ip::make_address_v4(IP);
    unsigned short port = PORT;
    tcp::acceptor acceptor;
    std::atomic<int> counter = 0;



    void do_socket();
public:
    server(const std::string& file_path, asio::io_context& io_cntx);

    void start_accept();
    void start();
};

#endif // SERVER_H
