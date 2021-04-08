#include "ringbuffer.h"

CRingBuffer::CRingBuffer()
    : m_mask(SIZE_RING_BUFFER - 1)
    , m_read(0)
    , m_write(0)
    , m_array{ 0 }
{
}

CRingBuffer::~CRingBuffer()
{
}

void CRingBuffer::Write(const uint8_t* array, const int& size)
{
    for(int i = 0; i < size; i++)
        m_array[m_write++ & m_mask] = array[i];
}

uint8_t* CRingBuffer::Read()
{
    return &m_array[m_read & m_mask];
}

void CRingBuffer::Flush(int count)
{
    m_read += count;
}