# 3DsMIN

### Build steps

Clone repo with dependecies:

`git clone --recursive https://github.com/IgorPritula/3DsMIN.git`

Process CMake build:  
#### For MacOs. 
`cd 3DsMIN`  
`mkdir build`  
`cd build`  
`cmake ../`  
`make `  

#### For Windows.  
Run cmake in Visual Studio Command Prompt to be able to invoke `cl` compiler and `nmake`.  
`cd 3DsMIN`  
`mkdir build`  
`cd build`  
`cmake -G "CodeBlocks - NMake Makefiles" ../`  
`cmake --build ./`  
