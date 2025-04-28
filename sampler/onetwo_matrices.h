
#pragma once

#include <cassert>
#include <cstdint>
#include <array>

inline
unsigned onetwo_sample( const std::array<unsigned, 52>& m, uint64_t n )
{
    unsigned x= 0;
    for(unsigned i= 0; i < 52; i++)
        x ^= ((n >> i) & 1) * m[i];
    
    return x;
}

constexpr unsigned onetwo_matrices_size= 692;
extern std::array<unsigned, 52> onetwo_matrices[onetwo_matrices_size];

inline
unsigned onetwo_sample( const unsigned d, const unsigned index )
{
    assert(d < onetwo_matrices_size);
    return onetwo_sample(onetwo_matrices[d], index);
}

inline
float onetwo_sample_float( const unsigned d, const unsigned index )
{
    assert(d < onetwo_matrices_size);
    return float(onetwo_sample(d, index)) / float(uint64_t(1) << 32);
}

inline
double onetwo_sample_double( const unsigned d, const unsigned index )
{
    assert(d < onetwo_matrices_size);
    return double(onetwo_sample(d, index)) / double(uint64_t(1) << 32);
}

