# PBRT plugin

# Build instructions

Our code relies on the pbrt-v4 repository and its dependencies.

In this `pbrt` folder:
* clone pbrt-v4: `git clone --recursive https://github.com/mmp/pbrt-v4.git`
* update the source code:

```
mv pbrt-v4/src/pbrt pbrt-v4/src/pbrt-old
mv src-pbrt-ours pbrt-v4/src/pbrt
```
Then proceed with the pbrt-v4 build (https://github.com/mmp/pbrt-v4#building-the-code):

```
cd pbrt-v4
mkdir build
cd build
cmake ..
make
```

# Render the cornell-box

In the `pbrt-v4` build folder:

```
./pbrt ../../cornell-box/scene-v4.pbrt
```



# Sampler usage

If you want to use our sampler in your scene, you would need to update the description file:
```
    Sampler "onetwo"
        "integer pixelsamples" [ 16 ]

    Integrator "path"
        "integer maxdepth" [ 2 ]
```

# Main files
- sampler.h: code fragment of the actual pbrt v4 sampler,
- sampler.cpp: support code such as object creation and configuration,
- onetwo_matrices.h: point generation functions,
- onetwo_matrices.cpp: pre-compiled matrices.

Please note that these files do not compile outside `pbvrt-v4`
