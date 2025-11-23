#include "filereciver.h"

FileReciver::FileReciver(tcp::socket&& socket, const std::string& file_path):
    socket_(std::move(socket)),
    file(file_path, std::ios::binary),
    fileName(file_path)
{
    buffer.resize(4096);
}

void FileReciver::start(){
    do_recive();
}

void FileReciver::do_recive(){
    auto self = shared_from_this();
    socket_.async_read_some(
        boost::asio::buffer(buffer),
        [this, self] (boost::system::error_code er, std::size_t bytes){
            if(!er){
                file.write(buffer.data(), bytes);
                do_recive();
            }else{
                std::cerr<< "error file: "  << er.message() << '\n';
                file.close();
                socket_.close();
            }
        });
}
