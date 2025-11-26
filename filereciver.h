#ifndef FILERECIVER_H
#define FILERECIVER_H
#include "asio.h"
#include "tcpheader.h"

class FileReciver : public std::enable_shared_from_this<FileReciver>
{
    tcp::socket socket_;
    std::string fileName = "";
    std::ofstream file;
    uint64_t file_byte_size;
    tcpHeader header{};
    float file_KiB_size;
    float accepted_KiB;
    std::vector<char> buffer;
    std::chrono::time_point<std::chrono::steady_clock> now;
    std::chrono::time_point<std::chrono::steady_clock> later;


    void do_recive();

    void set_settings();

    static void print_byte_bits(uint8_t b);

    void print_bits(const void* data, size_t len);
public:
    FileReciver(tcp::socket&& socket);
    void start();
};

#endif // FILERECIVER_H
