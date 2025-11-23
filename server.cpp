#include "server.h"

server::server(const std::string& file_path, asio::io_context& io_cntx) :
    io_cntx_(io_cntx),
    acceptor(io_cntx_, tcp::endpoint{addr, port})
{

}

void server::start(){
    start_accept();
}

void server::start_accept(){
    std::cout << "start accceptor " << std::endl;
    auto socket = std::make_shared<tcp::socket>(io_cntx_);
    acceptor.async_accept(*socket,
                          [socket, this](boost::system::error_code er){
                              if(!er){
                                  std::chrono::time_point now = std::chrono::system_clock::now() + std::chrono::hours{3};
                                  std::ostringstream ss;
                                  ++counter;
                                  ss << "[" << std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count()  << "] - " << counter <<": ";
                                  const std::string fileName = ss.str();
                                  std::cout << "CONGRATULATION SUCCSESSFULL SAVE TO FILE WITH NAME: " << fileName << std::endl;
                                  auto filer = std::make_shared<FileReciver>(std::move(*socket), fileName);
                                  filer->start();
                              }else{
                                  std::cerr << "read error: " << er.message() <<'\n';
                              }

                              start_accept();
                          });
}

void server::do_socket(){

}
