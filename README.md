# kImageAnnotator [![Build Status](https://travis-ci.org/DamirPorobic/kImageAnnotator.svg?branch=master)](https://travis-ci.org/DamirPorobic/kImageAnnotator)
Tool for annotating images

Version 0.0.1

The tool is currently work in Progress

![kImageAnnotator](https://i.imgur.com/MlzhHkb.png "kImageAnnotator")


### Building from source

1. Get latest release from GitHub by cloning the repo:  
    `$ git clone https://github.com/DamirPorobic/kImageAnnotator`
2. Change to repo directory:  
    `$ cd kImageAnnotator`  
3. Resolve dependencies by fetching git submodules:  
    `$ git submodule update --init --recursive`  
4. Make new build directory and enter it:  
    `$ mkdir build && cd build`  
5. Create the makefile and build the project:  
    `$ cmake .. && make`  
6. Install shared library (not required when only using the example):  
    `$ sudo make install`
7. Run the example application:  
    `$ ./example/kImageAnnotator-example`
