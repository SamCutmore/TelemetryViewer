#include <stdint.h>

class ITransportService {
public:
    virtual ~ITransportService() = default;
    virtual size_t read(uint8_t* buffer, size_t max_length) = 0;
};
