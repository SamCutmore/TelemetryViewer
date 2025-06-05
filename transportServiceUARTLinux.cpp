#include <fcntl.h>
#include <termios.h>
#include <stdint.h>
#include <stdexcept>
#include <iostream>    // std::cout, std::endl
#include <thread>      // std::thread
#include <cctype>      // std::isprint
#include <unistd.h>    // close(), read()
#include "transportService.hpp"
#include "eventQueue.hpp"

class TransportServiceUART : public ITransportService {
    int fd_;
    std::thread worker_;

public:
    TransportServiceUART(const char* device, int baudrate) {
        fd_ = open(device, O_RDWR | O_NOCTTY | O_SYNC);
        if (fd_ < 0) throw std::runtime_error("Failed to open UART device");

        struct termios tty;
        if (tcgetattr(fd_, &tty) != 0)
            throw std::runtime_error("tcgetattr failed");

        cfsetospeed(&tty, baudrate);
        cfsetispeed(&tty, baudrate);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
        tty.c_cflag &= ~PARENB;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;
        tty.c_cflag |= CREAD | CLOCAL;
        tty.c_lflag = 0;
        tty.c_iflag &= ~(IXON | IXOFF | IXANY);
        tty.c_oflag = 0;
        tty.c_cc[VMIN] = 1;
        tty.c_cc[VTIME] = 0;

        if (tcsetattr(fd_, TCSANOW, &tty) != 0)
            throw std::runtime_error("tcsetattr failed");
    }

    ~TransportServiceUART() override {
        if (fd_ >= 0) close(fd_);
    }

    size_t read(uint8_t* buffer, size_t max_length) override {
        ssize_t n = ::read(fd_, buffer, max_length);
        if (n < 0) throw std::runtime_error("UART read error");
        return static_cast<size_t>(n);
    }

    void start(EventQueue& queue) {
        std::thread([this, &queue]() {
            uint8_t buffer[1024];
            while (true) {
                size_t bytes = this->read(buffer, sizeof(buffer));
                if (bytes > 0) {
                    std::cout << " | ASCII: ";
                    for (size_t i = 0; i < bytes; ++i) {
                        char c = static_cast<char>(buffer[i]);
                        std::cout << (std::isprint(c) ? c : '.');
                    }
                    std::cout << std::endl;
                }
            }
        }).detach();
    }


private: 
    void stop() {

    }
};
