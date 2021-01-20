# 3DsMIN

3DsMIN is simple 3D modeling software.  
Features:
* Create objects (cube, pyramid).
* Change object positions, rotation, scale and color.
* Dymanic light.
* Add texture to object (not with UI yet).
* Change and drag application's sub windows.
* Free camera (press 'M' button and use WASD to manipulate)
* Loader meshes, stl ascii and binary (not with UI yet, will be added) 

![alt text](https://raw.githubusercontent.com/IgorPritula/3DsMIN/master/Screenshot.png)

Future features:
* Multiple lights calculation.
* Create lights objects with gui.
* Export/import scene in lua or yaml.
* Fixed camera, switching between cameras.



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
