#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>

struct Chunk
{
    void init(std::size_t block_size, std::uint8_t count_blocks);
    void* allocate(std::size_t block_size);
    void deallocate(void* pointer, std::size_t block_size);
    void release();

    std::uint8_t* m_data;
    std::uint8_t  m_first_available_block;
    std::uint8_t  m_count_available_blocks;
};

class FixedAllocator
{
private:
    std::size_t        m_block_size;
    std::uint8_t       m_count_available_blocks;
    std::vector<Chunk> m_chunks;
    Chunk*             m_allocated_chunk;
    Chunk*             m_deallocated_chunk;
};
