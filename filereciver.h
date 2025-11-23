#ifndef FILERECIVER_H
#define FILERECIVER_H
#include "asio.h"

class FileReciver : public std::enable_shared_from_this<FileReciver>
{
    tcp::socket socket_;
    std::string fileName = "";
    std::ofstream file;
    std::vector<char> buffer;


    void do_recive();
public:
    FileReciver(tcp::socket&& socket, const std::string& file_path);
    void start();
};

#endif // FILERECIVER_H
