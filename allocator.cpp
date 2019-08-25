#include "allocator.hpp"

#include <cassert>

void Chunk::init(const std::size_t block_size, const std::uint8_t count_blocks)
{
    m_data = new std::uint8_t[block_size * count_blocks];
    m_first_available_block = 0u;
    m_count_available_blocks = count_blocks;
    
    std::uint8_t index = 0u;
    std::uint8_t* iterator = m_data;
    for (; index < count_blocks; iterator += block_size)
    {
        *iterator = ++index;
    }
}

void* Chunk::allocate(const std::size_t block_size)
{
    if (m_count_available_blocks == 0)
    {
        return nullptr;
    }

    std::uint8_t* dest_address = m_data + (m_first_available_block * block_size);
    m_first_available_block = *dest_address;
    --m_count_available_blocks;
    return dest_address;
}

void Chunk::deallocate(void* pointer, const std::size_t block_size)
{
    assert(pointer >= m_data);
    const auto dest_address = static_cast<std::uint8_t*>(pointer);
    assert((dest_address - m_data) % block_size == 0);
    *dest_address = m_first_available_block;
    m_first_available_block = static_cast<std::uint8_t>((dest_address - m_data) / block_size);
    assert(m_first_available_block == (dest_address - m_data) / block_size);
    ++m_count_available_blocks;
}

void Chunk::release()
{
    delete m_data;
    m_first_available_block = 0u;
    m_count_available_blocks = 0u;
}
