# SourceGen
Tool for generating C++ skeleton code. 

[![SourceGen Demo](http://img.youtube.com/vi/MD3Moce921M/0.jpg)](https://www.youtube.com/watch?v=MD3Moce921M "SourceGen Demo")

# Description 
Generates CMake project templates for Qt / C++ 

**The Command Line Version**    
sgen - The command line version of the application does not require Qt to build.  

**Qt Version**  

sgen_qt - This version provides a GUI that can be integerated with IDEs as an external tool.  Pass "-DENABLE_SGEN_QT="TRUE" to the command line when building with cmake to compile the Qt version. 

#Building 

1) git clone https://github.com/cbtek/SourceGen.git  
2) cd SourceGen  
3) mkdir build  
4) cd build  

**For Linux (GCC)**  
5) cmake ..  or cmake -DENABLE_SGEN_QT="TRUE"    
6) make 
7) sudo make install

**For Windows (MinGW)**  
5) cmake -G "MinGW Makefiles" ..   
6) mingw32-make  
7) cd ../bin/SourceGen/release
8) Build artifacts will be located here

# SourceGen Help


```------------------------------------
SourceGen Help
------------------------------------
--class-name       [-n]   <name of class>    (required)
--class-type       [-t]   <class type>
--class-includes   [-inc] <list of includes>
--class-inherits   [-inh] <list of inherits>
--class-namespace  [-p]   <namespace>
--class-attributes [-a]   <attribute list>
--copyright-file   [-c]   <copyright file>
--output-folder    [-o]   <output folder>
--header-subfolder [-hs]  <header sub-folder>
--source-subfolder [-ss]  <source sub-folder>
--ui-subfolder     [-us]  <ui sub-folder>
--help             [-h]   (displays this help message)
------------------------------------
Valid class-types:
        1) NORMAL
        2) STATIC
        3) SINGLETON
        4) VIRTUAL
        5) QWIDGET
        6) QDIALOG
        7) QMAINWINDOW
------------------------------------
Example:
sgen
--class-name "MyClass"
--class-type "NORMAL"
--class-namespace "MyCompany.Package.MyClass"
--class-includes "<iostream>,<fstream>,*MyInclude.h*"
--class-inherits "public MyInclude, public MyOtherInclude"
--class-attributes "id:int,x:float,y:float,z:float,name:std::string"
--output-folder "C:/"
------------------------------------```
