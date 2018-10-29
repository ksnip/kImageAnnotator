# kImageAnnotator [![Build Status](https://travis-ci.org/DamirPorobic/kImageAnnotator.svg?branch=master)](https://travis-ci.org/DamirPorobic/kImageAnnotator)
Tool for annotating images

Version 0.0.1


![kImageAnnotator](https://imgur.com/y9CT0Ia.png "kImageAnnotator")

### Dependencies

kImageAnnotator depends on [kColoPicker](https://github.com/DamirPorobic/kColorPicker) which needs
to be installed before building kImageAnnotator. Install instructions can be found on the github page.

### Building from source

1. Get latest release from GitHub by cloning the repo:  
    `$ git clone https://github.com/DamirPorobic/kImageAnnotator`
2. Change to repo directory:  
    `$ cd kImageAnnotator`  
3. Make new build directory and enter it:  
    `$ mkdir build && cd build`  
4. Create the makefile and build the project:  
    `$ cmake .. && make`  
5. Install shared library (not required when only using the example):  
    `$ sudo make install`
6. Run the example application:  
    `$ ./example/kImageAnnotator-example`

### Shared vs Static

You can either build the project as shared library by providing the flag `-DBUILD_SHARED_LIBS=ON`
to cmake or `-DBUILD_SHARED_LIBS=OFF` to build as static library. When no flag is provided a 
static library is build.

### Integrate library

1. Let cmake find the shared library, optionally with version  
    `set(KIMAGEANNOTATOR_MIN_VERSION "0.x.x")`  
    `find_package(kImageAnnotator ${KIMAGEANNOTATOR_MIN_VERSION} REQUIRED)`  

2. Link the library with your application  
    `target_link_libraries(myApp kImageAnnotator)`  