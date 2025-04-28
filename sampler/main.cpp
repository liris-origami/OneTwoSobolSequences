
#include <cstdlib>
#include <cstdio>

#include "onetwo_matrices.h"


void usage( const char *argv0 )
{
    printf("usage: %s N D\n", argv0);
    exit(1);
}

int main( int argc, char *argv[] )
{
    unsigned N= 16;
    if(argc > 1)
        if(sscanf(argv[1], "%d", &N) != 1)
            usage(argv[0]);
            
    unsigned D= 4;
    if(argc > 2)
        if(sscanf(argv[2], "%d", &D) != 1)
            usage(argv[0]);
    
    printf("generating %d %dD points...\n", N, D);
    for(unsigned i= 0; i < N; i++)
    {
        for(unsigned d= 0; d < D; d++)
        {
            double x= onetwo_sample_double(d, i);
            printf("%f", x);
            if(d+1 < D)
                printf(" ");
        }
        printf("\n");
    }
    
    return 0;
}
