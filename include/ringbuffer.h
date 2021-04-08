#ifndef CRINGBUFFER_H
#define CRINGBUFFER_H

#include <stdint.h>

#define SIZE_RING_BUFFER 256

class CRingBuffer
{
private:
    const int m_mask;

    int m_read;
    int m_write;

    uint8_t m_array[SIZE_RING_BUFFER];

public:
    CRingBuffer();
    ~CRingBuffer();

    void Write(const uint8_t* array, const int& size);
    uint8_t* Read();

    void Flush(int count);
};

#endif // CRINGBUFFER_H
