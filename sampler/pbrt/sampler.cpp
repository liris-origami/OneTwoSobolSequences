
#incude "sampler.h"


std::string OneTwoSampler::ToString() const 
{
    return StringPrintf("[ OneTwoSampler spp: %d seed: %d ]", nspp, seed); 
}

Sampler OneTwoSampler::Clone( Allocator alloc ) 
{
    return alloc.new_object<OneTwoSampler>(*this); 
}

OneTwoSampler *OneTwoSampler::Create( const ParameterDictionary &parameters, const FileLoc *loc, Allocator alloc ) 
{
    int n= parameters.GetOneInt("pixelsamples", 4);
    if(Options->pixelSamples) n= *Options->pixelSamples;
    
    unsigned seed = parameters.GetOneInt("seed", Options->seed);
    return alloc.new_object<OneTwoSampler>(n, seed);
}


// Sampler Method Definitions
Sampler Sampler::Create( const std::string &name, const ParameterDictionary &parameters, Point2i fullRes, const FileLoc *loc, Allocator alloc )
{
    Sampler sampler = nullptr;
    if (name == "zsobol")
        sampler = ZSobolSampler::Create(parameters, fullRes, loc, alloc);
    else if (name == "paddedsobol")
        sampler = PaddedSobolSampler::Create(parameters, loc, alloc);
    else if (name == "halton")
        sampler = HaltonSampler::Create(parameters, fullRes, loc, alloc);
    else if (name == "sobol")
        sampler = SobolSampler::Create(parameters, fullRes, loc, alloc);
    else if (name == "pmj02bn")
        sampler = PMJ02BNSampler::Create(parameters, loc, alloc);
    else if (name == "independent")
        sampler = IndependentSampler::Create(parameters, loc, alloc);
    
    // test ccode
    else if (name == "onetwo")
        sampler = OneTwoSampler::Create(parameters, loc, alloc);
    
    
    else if (name == "stratified")
        sampler = StratifiedSampler::Create(parameters, loc, alloc);
    
    else
        ErrorExit(loc, "'%s': sampler type unknown.", name);
    
    if (!sampler)
        ErrorExit(loc, "'%s': unable to create sampler.", name);
    
    parameters.ReportUnused();
    return sampler;
}
