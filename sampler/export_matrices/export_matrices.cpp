
#include <string>

#include "sobol_fast.h"


bool export_sobol_matrices( const std::vector<sobol_matrix>& matrices, const char *prefix, const unsigned count= 0 )
{
    unsigned n= matrices.size();
    if(count) 
        n= std::min(count, unsigned(matrices.size()));
    
    // export matrices
    std::string cppfile= std::string(prefix) + "_matrices.cpp";
    {
        printf("export cpp '%s'\n", cppfile.c_str());
        FILE *out= fopen(cppfile.c_str(), "wt");
        if(!out) 
            return false;
        
        fprintf(out, "\n#include <array>\n\n");
        fprintf(out, "std::array<unsigned, 52> %s_matrices[%d] {\n", prefix, n);
        for(unsigned i= 0; i < n; i++)
        {
            fprintf(out, "    { ");
            for(unsigned k= 0; k < 52; k++)
            {
                fprintf(out, "0x%08x", matrices[i].m[k]);
                if(k+1 < 52)
                    fprintf(out, ", ");
            }
            fprintf(out, " }");
            
            if(i+1 < n)
                fprintf(out, ",\n");
            else
                fprintf(out, "\n");
        }
        
        fprintf(out, "};\n");
        fclose(out);
    }
    
    // export header
    std::string hppfile= std::string(prefix) + "_matrices.h";
    {
        printf("export hpp '%s'\n", hppfile.c_str());
        FILE *out= fopen(hppfile.c_str(), "wt");
        if(!out) 
            return false;
        
        // verbatim string literal
        const char *header= R"(
#pragma once

#include <cassert>
#include <cstdint>
#include <array>

inline
unsigned %s_sample( const std::array<unsigned, 52>& m, uint64_t n )
{
    unsigned x= 0;
    for(unsigned i= 0; i < 52; i++)
        x ^= ((n >> i) & 1) * m[i];
    
    return x;
}

constexpr unsigned %s_matrices_size= %d;
extern std::array<unsigned, 52> %s_matrices[%s_matrices_size];

inline
unsigned %s_sample( const unsigned d, const unsigned index )
{
    assert(d < %s_matrices_size);
    return %s_sample(%s_matrices[d], index);
}

inline
float %s_sample_float( const unsigned d, const unsigned index )
{
    assert(d < %s_matrices_size);
    return float(%s_sample(d, index)) / float(uint64_t(1) << 32);
}

inline
double %s_sample_double( const unsigned d, const unsigned index )
{
    assert(d < %s_matrices_size);
    return double(%s_sample(d, index)) / double(uint64_t(1) << 32);
}

)";
        
        fprintf(out, header, 
            prefix, 
            prefix, n, 
            prefix, prefix, 
            prefix, 
            prefix, 
            prefix, prefix, 
            prefix, 
            prefix, 
            prefix, 
            prefix, 
            prefix, 
            prefix);
        fclose(out);
    }
    
    return true;
}


int main( int argc, char *argv[] )
{
    const char *sobol_init_tab= "sobol_init_tab.dat";
    if(argc > 1)
        sobol_init_tab= argv[1];
        
    const char *export_tab= "matrices";
    if(argc > 2)
        export_tab= argv[2];
    
    printf("reading '%s'...\n", sobol_init_tab);
    std::vector<sobol_matrix> sobols= read_sobols(sobol_init_tab);
    
    printf("%d matrices...\n", int(sobols.size()));
    export_sobol_matrices(sobols, export_tab, 1024);
    
    return 0;
}
