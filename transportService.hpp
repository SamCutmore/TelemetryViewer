#include <stdint.h>
#include "eventQueue.hpp"

class ITransportService {
public:
    virtual ~ITransportService() = default;
    virtual size_t read(uint8_t* buffer, size_t max_length) = 0;
    void start(EventQueue& queue);

private:
    int fd_;
    void stop();
};
