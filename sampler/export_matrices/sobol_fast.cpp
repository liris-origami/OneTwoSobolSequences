
#include <iostream>
#include <fstream>
#include <sstream>

#include "sobol_fast.h"


std::vector<sobol_matrix> read_sobols( const char *filename )
{
    std::ifstream in(filename);
    if(!in.is_open())
    {
        std::cerr << "[error] reading '" << filename << "'...\n";
        exit(1);
    }
    
    std::vector<sobol_matrix> matrices;
    
    // insert first dimension, van der Corput
    sobol_polynomial p(0, 0, 0, {});
    matrices.push_back( sobol_matrix(p) );
    
    std::string line;
    while(getline(in, line))
    {
        unsigned d, s, a;
        std::istringstream stream(line);
        if(!(stream >> d >> s >> a))
            // skip comments
            continue;
        
        if(s == 0)
            // skip van der Corput polynomial
            continue;
        
        // read coefficients
        unsigned mi;
        std::vector<unsigned> coefficients;
        while(stream >> mi)
            coefficients.push_back(mi);
        
        // generate sobol' matrix from polynomial
        sobol_polynomial p(d, s, a, coefficients);
        matrices.push_back( sobol_matrix(p) );
    }
    
    in.close();
    return matrices;
}
