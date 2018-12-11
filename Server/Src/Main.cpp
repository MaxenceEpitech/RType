#include "UDPServer.hpp"

int main(int argc, char **argv) {
    try {
        boost::asio::io_service io_service;

        auto UDPPort =
                (argc >= 2) ? static_cast<unsigned short>(std::stoul(argv[1])) : 1234;
        std::cout << "Using UDP Port: " << UDPPort << std::endl;
        /// Used for network send and receive
        UDPServer UDPserver(UDPPort, io_service);

        io_service.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
