------------------------------------
SourceGen Readme
------------------------------------
This tool was originally developed to generate C++ skeleton 
code (.h, .cpp) with correctly formated namespaces and headerguards for
a variety of class types. It has been slightly updated to match 
the formatting from SIG's coding standard. 

------------------------------------
GUI Operation:
------------------------------------
See the "Example.png" file
The "Example - MyClass.h" and "Example - MyClass.cpp" files show what gets 
generated from the "Example.png" example. 


------------------------------------
CMDLine Operation:
------------------------------------

SourceGen Help 
--class-name       <name of class>                    (no spaces, REQUIRED)
--class-type       <class type>                       (see class types below, REQUIRED)
--class-includes   <list of includes>                 (seperated by commas, substitute '*' for double quotes)
--class-inherits   <list of inherits>                 (seperated by commas)
--class-namespace  <namespace>                        (dot notation)
--class-attributes <attributes for getters/setters>   (name1:type1,name2:type2,etc)
--output-folder    <output folder>                    (defaults to current dir)
--help                                                (displays this help message)
Valid class-types:
	1) NORMAL
	2) STATIC
	3) SINGLETON
	4) VIRTUAL
	5) QWIDGET
	6) QDIALOG
	7) QMAINWINDOW
Example:
sourcegen
--class-name "MyClass" 
--class-type "NORMAL" 
--class-namespace "SIG.Package.MyClass" 
--class-includes "<iostream>,<fstream>,*MyInclude.h*" 
--class-inherits "public MyInclude, public MyOtherInclude" 
--class-attributes "id:int,x:float,y:float,z:float,name:std::string" 
--output-folder "C:/" 

Notes: 
1) In Command Line Mode for the class-includes argument the * character will be replaced with double quotes 
2) This app is cross platform and its source uses CMAke which can be included if desired



