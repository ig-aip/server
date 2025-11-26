#include "filereciver.h"
#include <iostream>
#include <cstring>
#include <chrono>

FileReciver::FileReciver(tcp::socket&& socket):
    socket_(std::move(socket)) {
    buffer.resize(131072);
}

void FileReciver::start(){
    set_settings();

}

void FileReciver::set_settings(){
    auto self = shared_from_this();
    asio::async_read(socket_,
        boost::asio::buffer(&header, sizeof(header)),
        [this, self](boost::system::error_code er, std::size_t bytes){
            if(!er){
                std::cout << "bytes: " << bytes<< std::endl;
                fileName = header.name_;
                file_byte_size = header.size_byte;
                file_KiB_size = float(file_byte_size) / 1024.0f;
                file.open(fileName, std::ios::binary);
                if(file){
                    std::cout << "file open with name: " << fileName << std::endl;
                    now = std::chrono::steady_clock::now();
                    do_recive();
                }else{
                    std::cout << "file not open"<< std::endl;
                }

            }else{
                std::cerr<< "error header of file: "  << er.message() << '\n';
            }

        });
}

void FileReciver::do_recive(){
    auto self = shared_from_this();
    socket_.async_read_some(
        boost::asio::buffer(buffer),
        [this, self] (boost::system::error_code er, std::size_t bytes){
            if(!er){
                file.write(buffer.data(), bytes);
                accepted_KiB += float(bytes) / 1024.0f;
                //std::cout << "accepted Kib [" << accepted_KiB <<" / " << file_KiB_size <<"] file: " << fileName << std::endl;
                do_recive();
            }
            else if(er.message() == "End of file"){
                later = std::chrono::steady_clock::now();
                std::cout << "file has been all writed" << std::endl;
                std::cout<<"time: " << std::chrono::duration_cast<std::chrono::seconds>(later - now).count() << " seconds"
                          <<"\n and " << std::chrono::duration_cast<std::chrono::milliseconds>(later - now).count() << "miliseconds" <<std::endl;
            }
            else{
                later = std::chrono::steady_clock::now();
                std::cout<<"time: " << std::chrono::duration_cast<std::chrono::seconds>(later - now).count() << " seconds"
                          <<"\n and " << std::chrono::duration_cast<std::chrono::milliseconds>(later - now).count() << "miliseconds" <<std::endl;

                std::cerr<< "error file: "  << er.message() << '\n';
                file.close();
                socket_.close();
            }

        });
}






