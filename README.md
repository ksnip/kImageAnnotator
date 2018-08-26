# kImageAnnotator
Tool for annotating images

Version v0.0.1 - alpha

The tool is currently work in Progress

![kImageAnnotator](https://i.imgur.com/MlzhHkb.png "kImageAnnotator")


### Building from source
1. Get latest release from GitHub by cloning the repo:  
    `$ git clone https://github.com/DamirPorobic/kImageAnnotator`
2. Change to repo directory:  
    `$ cd kImageAnnotator`    
3. Make new build directory and enter it:  
    `$ mkdir build`  
    `$ cd build`  
4. Create the makefile and build the project:  
    `$ cmake ..`  
    `$ make`
5. Install shared library (not required when only using the example):  
    `$ sudo make install`
6. Run the example application:  
    `$ ./example/kImageAnnotator-example`
