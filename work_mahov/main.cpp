#include "server.h"
#include "thread"
#include "tcpheader.h"

int main(int argc, char *argv[])
{
    try {
        asio::io_context ioc;

        auto serv = std::make_shared<server>("fily", ioc);
        serv->start();

        unsigned int threads = std::max(1u, std::thread::hardware_concurrency());
        std::cout << "running io contxt with " << threads << "threads" << std::endl;
        std::vector<std::thread> pool;
        pool.reserve(threads);

        for(int i = 0; i < threads; ++i){
            pool.emplace_back([&ioc](){
                try{
                    ioc.run();
                }catch(std::exception& ex){
                    std::cerr << "io context exception: " << ex.what() << '\n';
                }
            });
        }

        for(auto& t : pool){ t.join(); }

    } catch (std::exception& ex) {
        std::cerr << "main exception: " << ex.what() << '\n';
    }

}
