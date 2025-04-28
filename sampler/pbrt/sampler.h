
#include "onetwo_matrices.h"


class OneTwoSampler
{
public:
    OneTwoSampler( int n, unsigned s= 123451 ) : nspp(n), seed(s) {}
    
    static OneTwoSampler *
    Create( const ParameterDictionary &parameters, const FileLoc *loc, Allocator alloc );
    
    PBRT_CPU_GPU
    static constexpr const char *Name( ) { return "OneTwoSampler"; }
    
    PBRT_CPU_GPU
    int SamplesPerPixel( ) const { return nspp; }
    
    PBRT_CPU_GPU
    void StartPixelSample( Point2i p, int n, int d )
    {
        pixel= p;
        dimension= 0;
        dimension1= 0;
        dimension12= 0;
        
        index= n; // pixel sampler
        
        sample_pixel.x= sample12(index, dimension12++); 
        sample_pixel.y= sample12(index, dimension12++); 
        
        sample_lens.x= sample12(index, dimension12++); 
        sample_lens.y= sample12(index, dimension12++); 
        
        sample_time= sample12(index, dimension12++); dimension12++; // 1 pair
    }
    
    PBRT_CPU_GPU
    Float Get1D( ) 
    {
        dimension++;
        if(dimension == 3)
            return sample_time;
            
        if((dimension1 % 2) == 0)
        {
            sample_cache[0]= sample12(index, dimension12++);
            sample_cache[1]= sample12(index, dimension12++);
        }
        
        Float sample= sample_cache[dimension1 % 2]; dimension1++;
        return sample;
    }
    
    PBRT_CPU_GPU
    Point2f Get2D( ) 
    { 
        dimension++;
        dimension++;
        if(dimension == 4)
            return sample_lens;
        
        Float x= sample12(index, dimension12++); 
        Float y= sample12(index, dimension12++); 
        return { x, y }; 
    }

    PBRT_CPU_GPU
    Point2f GetPixel2D( )
    {
        dimension++;
        dimension++;
        assert(dimension == 2);
        return sample_pixel;
    }
    
    PBRT_CPU_GPU
    int GetDimension( ) { return dimension; }
    
    Sampler Clone( Allocator alloc );
    std::string ToString( ) const;
    
private:
    Float sample12( const uint64_t index, const int dim ) const 
    {
        auto owen_seed= Hash(pixel, seed, dim);      // per-pixel scrambling
        auto scramble= OwenScrambler(owen_seed);
        return std::min( scramble( onetwo_sample(dim, index) ) * 0x1p-32f, FloatOneMinusEpsilon );
    }
    
    Point2i pixel;
    // sample cache
    Point2f sample_pixel;
    Float sample_time;
    Point2f sample_lens;
    // last pair
    Float sample_cache[2];
    
    int nspp;
    unsigned scale;
    unsigned seed;
    unsigned index;
    
    unsigned dimension;
    unsigned dimension1;
    unsigned dimension12;
};
