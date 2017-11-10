# BLAPP [![Build Status](https://travis-ci.org/ISCDtoolbox/BLAPP.svg?branch=master)](https://travis-ci.org/ISCDtoolbox/BLAPP)
Benchmarking Linear Algebra Parallelization Performance

## Compilation
To compile, create and navigate to an (out of source) build directory, and run the cmake command:
```
mkdir build
cd build
cmake ..
make
```

## Running
To run the "elastic" executable on a demo file, run from BLAPP main directory the command:
```
./build/elastic demos/biel3d.mesh
```
The program will solve the linear elasticity on the file biel3d.mesh, according to the parameters specified in the file biel3d.elas. A file biel3d.sol should have been created in the **demos** directory, which can be opened in medit to display the results:
```
medit demos/biel3d.mesh
```
![screenshot from 2017-11-10 15-53-42](https://user-images.githubusercontent.com/11873158/32664037-47cf8718-c630-11e7-80b6-a161c3bca6ab.png)
