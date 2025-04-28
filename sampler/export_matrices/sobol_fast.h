
#ifndef SOBOL_FAST_H
#define SOBOL_FAST_H

#include <cassert>
#include <cstring>
#include <cstdint>
#include <cstdio>

#include <vector>
#include <array>


struct sobol_polynomial
{
    // dimension of Sobol polynomial
    unsigned d;
    unsigned s;

    // binary Sobol polynomial
    unsigned a;
    std::vector<unsigned> m;
    
    sobol_polynomial( const unsigned _d, const unsigned _s, const unsigned _a, const std::vector<unsigned>& _m ) : 
        d(_d), s(_s), a(_a), m(_m) 
    {
        assert(s == m.size());
    }
};


struct sobol_matrix
{
    // Sobol matrix
    std::array<unsigned, 52> m;
    
    sobol_matrix() : m() {}
    sobol_matrix( const sobol_polynomial& p ) : m() { generate_matrix(p); }
    sobol_matrix( const std::array<unsigned, 52>& matrix ) : m(matrix) {}
   
    void generate_matrix( const sobol_polynomial& p )
    {
        std::array<uint64_t, 52> mm;
        
        if(p.s == 0) 
        {	
            // dimension 0, van der Corput
            for(unsigned k= 0; k < m.size(); ++k)
                mm[k]= 1;
        }
        else 
        {
            for(unsigned k= 0; k < p.s; ++k)
                mm[k]= p.m[k];
            
            for(unsigned k= p.s; k < m.size(); ++k)
            {
                mm[k]= 0;
                for(unsigned i= 1; i < p.s; ++i) 
                {
                    // `akj` stores aj_k, note that the polynomial rep is reversed
                    unsigned ai = (p.a >> (p.s - 1 - i)) & 1;
                    mm[k] ^= ai * mm[k - i] << i;
                }
                
                mm[k] ^= mm[k - p.s] << p.s;
                mm[k] ^= mm[k - p.s];
            }
        }
        
        for(unsigned i= 0; i < 52; i++)
            mm[i] <<= 51 - i;
        
        for(unsigned i= 0; i < 52; i++)
            m[i] = mm[i] >> 20;
    }
    
    void print( ) const
    {
        for(unsigned i= 0; i < 32; i++)
        {
            for(unsigned k= 0; k < 52; k++)
            {
                unsigned x= (m[k] >> (31-i)) & 1;
                printf("%c ", x ? '1' : '.');
            }
            
            printf("\n");
        }
    }
    
    unsigned sample( const uint64_t n ) const
    {
        unsigned x= 0;
        for(unsigned i= 0; i < 52; i++)
            x ^= ((n >> i) & 1) * m[i];
        
        return x;
    }
    
    float sample_float( unsigned n ) const
    {
        unsigned x= sample(n);
        return float(x) / float(uint64_t(1) << 32);
    }
    
    double sample_double( unsigned n ) const
    {
        unsigned x= sample(n);
        return double(x) / double(uint64_t(1) << 32);
    }
};


std::vector<sobol_matrix> read_sobols( const char *filename );

#endif
