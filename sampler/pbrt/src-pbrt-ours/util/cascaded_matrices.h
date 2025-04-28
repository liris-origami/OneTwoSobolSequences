
#ifndef _CASCADED_MATRICES_H
#define _CASCADED_MATRICES_H

#include <cassert>
#include <array>


inline
unsigned cascaded_sample( const std::array<unsigned, 32>& m, unsigned n )
{
    unsigned x= 0;
    for(unsigned i= 0; i < 32; i++)
    {
	if((n >> i) & 1)
            x ^= m[i];
    }
    
    return x;
}


constexpr unsigned cascaded_matrices_size= 100;
extern std::array<unsigned, 32> cascaded_matrices[cascaded_matrices_size];

inline
unsigned cascaded_sample( const unsigned dim, const unsigned index )
{
    assert(dim < cascaded_matrices_size);
    return cascaded_sample(cascaded_matrices[dim], index);
}

#endif
