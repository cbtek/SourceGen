/**
MIT License

Copyright (c) 2016 cbtek

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include <QApplication>
#include <QFile>
#include <iostream>

#include "utility/inc/StringUtils.hpp"
#include "utility/inc/FileUtils.hpp"

#include "SourceGen.h"
#include "UISourceGen.h"

using namespace cbtek::common::utility;
using namespace cbtek::products::sourcegen;

int main(int argc , char ** argv)
{       

    QApplication a(argc, argv);   
    std::string classType       = StringUtils::toUpperTrimmed(StringUtils::getCommandLineArg(argc,argv,"--class-type"));
    std::string className       = StringUtils::getCommandLineArg(argc,argv,"--class-name");
    std::string classInherits   = StringUtils::getCommandLineArg(argc,argv,"--class-inherits");
    std::string classIncludes   = StringUtils::getCommandLineArg(argc,argv,"--class-includes");
    std::string classNamespace  = StringUtils::getCommandLineArg(argc,argv,"--class-namespace");
    std::string classAttributes = StringUtils::getCommandLineArg(argc,argv,"--class-attributes");
    std::string outputFolder    = StringUtils::getCommandLineArg(argc,argv,"--output-folder");
    std::string copyrightFile   = StringUtils::getCommandLineArg(argc,argv,"--copyright-file");
    std::string headerSubfolder = StringUtils::getCommandLineArg(argc,argv,"--header-subfolder");
    std::string sourceSubfolder = StringUtils::getCommandLineArg(argc,argv,"--source-subfolder");
    std::string uiSubfolder     = StringUtils::getCommandLineArg(argc,argv,"--ui-subfolder");

    bool closeOnSave = StringUtils::commandLineArgExists(argc,argv,"--close-on-save");
    bool showHelp  = StringUtils::commandLineArgExists(argc,argv,"--help");
    bool showUI  = StringUtils::commandLineArgExists(argc,argv,"--populate-ui");
    bool disableAnimations  = StringUtils::commandLineArgExists(argc,argv,"--disable-animations");
//For debugging:
//    std::cerr << "        Class Type: ["<<classType<<"]"<<std::endl;
//    std::cerr << "        Class Name: ["<<className<<"]"<<std::endl;
//    std::cerr << "    Class Inherits: ["<<classInherits<<"]"<<std::endl;
//    std::cerr << "    Class Includes: ["<<classIncludes<<"]"<<std::endl;
//    std::cerr << "   Class Namespace: ["<<classNamespace<<"]"<<std::endl;
//    std::cerr << "  Class Attributes: ["<<classAttributes<<"]"<<std::endl;
//    std::cerr << "     Output Folder: ["<<outputFolder<<"]"<<std::endl;
//    std::cerr << "    Copyright File: ["<<copyrightFile<<"]"<<std::endl;
//    std::cerr << " Header Sub-Folder: [" << headerSubfolder<<"]"<<std::endl;
//    std::cerr << " Source Sub-Folder: [" << sourceSubfolder<<"]"<<std::endl;
//    std::cerr << "     UI Sub-Folder: [" << uiSubfolder <<"]"<< std::endl;
//    std::cerr << "     Close on Save: "<<(closeOnSave?"true":"false")<<std::endl;
//    std::cerr << "         Show Help: "<<(showHelp?"true":"false")<<std::endl;
//    std::cerr << "Disable Animations: "<<(disableAnimations?"true":"false")<<std::endl;
//    std::cerr << "           Show UI: "<<(showUI?"true":"false")<<std::endl;

    classAttributes = StringUtils::replace(classAttributes,",","\n",true);
    cbtek::products::sourcegen::SourceGenInfo info;
    info.setClassName(className);
    info.setGetsSets(classAttributes);
    info.setIncludes(classIncludes);
    info.setBaseClasses(classInherits);
    info.setNamespace(classNamespace);
    info.setClassType(classType);
    info.setOutputFolder(outputFolder.size()?outputFolder:FileUtils::getCurrentPath());
    info.setCanOverwrite(true);
    info.setCopyrightFile(copyrightFile);
    info.setSrcSubFolder(sourceSubfolder);
    info.setIncSubFolder(headerSubfolder);
    info.setUiSubFolder(uiSubfolder);
    info.setShowUI(showUI);
    info.setDisableAnimations(disableAnimations);

    if (showHelp)
    {
        std::cout << "------------------------------------\n";
        std::cout << "SourceGen Help \n";
        std::cout << "------------------------------------\n";
        std::cout << "--class-name       <name of class>    (no spaces, REQ)\n";\
        std::cout << "--class-type       <class type>       (see class types below, REQ)\n";
        std::cout << "--class-includes   <list of includes> (seperated by commas, substitute '*' for double quotes)\n";
        std::cout << "--class-inherits   <list of inherits> (seperated by commas)\n";
        std::cout << "--class-namespace  <namespace>        (dot notation)\n";
        std::cout << "--class-attributes <attribute list>   (name1:type1,name2:type2,etc)\n";
        std::cout << "--copyright-file   <copyright file>   (Location of simple text file for copyright header)\n";
        std::cout << "--output-folder    <output folder>    (defaults to current dir)\n";
        std::cout << "--header-subfolder <header sub-folder>    (wrt output-folder)\n";
        std::cout << "--source-subfolder <source sub-folder>    (wrt output-folder)\n";
        std::cout << "--ui-subfolder     <ui sub-folder>    (wrt output-folder)\n";
        std::cout << "--help             (displays this help message)\n";
        std::cout << "--populate-ui      (displays UI with populated fields)\n";
        std::cout << "--disable-animations(disables theme and animation by default)\n";
        std::cout << "------------------------------------\n";
        std::cout << "Valid class-types:\n";
        std::cout << "\t1) NORMAL\n";
        std::cout << "\t2) STATIC\n";
        std::cout << "\t3) SINGLETON\n";
        std::cout << "\t4) VIRTUAL\n";
        std::cout << "\t5) QWIDGET\n";
        std::cout << "\t6) QDIALOG\n";
        std::cout << "\t7) QMAINWINDOW\n";
        std::cout << "------------------------------------\n";
        std::cout << "Example:\n";
        std::cout << "sourcegen\n";
        std::cout << "--class-name \"MyClass\" \n";
        std::cout << "--class-type \"NORMAL\" \n";
        std::cout << "--class-namespace \"MyCompany.Package.MyClass\" \n";
        std::cout << "--class-includes \"<iostream>,<fstream>,*MyInclude.h*\" \n";
        std::cout << "--class-inherits \"public MyInclude, public MyOtherInclude\" \n";
        std::cout << "--class-attributes \"id:int,x:float,y:float,z:float,name:std::string\" \n";
        std::cout << "--output-folder \"C:/\" \n";
        std::cout << "------------------------------------"<<std::endl;
        return 0;
    }

    if (!showUI && classType.size() && className.size())
    {
        StringMap fileDataMap;
        QStringList files = QStringList()
        <<"class_normal_template.cpp"
        <<"class_normal_template.h"
        <<"class_qtwidget_template.cpp"
        <<"class_qtwidget_template.h"
        <<"class_qtwidget_template.ui"
        <<"class_singleton_template.cpp"
        <<"class_singleton_template.h"
        <<"class_static_template.cpp"
        <<"class_static_template.h"
        <<"class_virtual_template.h";

        foreach(QString file,files)
        {
            QFile f("templates/"+file);
            if (f.open(QFile::ReadOnly))
            {
                QString fileData(f.readAll());
                fileDataMap[file.toStdString()] = fileData.toStdString();
            }
        }

        StringList emptyLog;
        SourceGen::save(info,emptyLog,fileDataMap);
        return 0;
    }
    else
    {
        UISourceGen sgUI(closeOnSave,info);
        sgUI.show();
        return a.exec();
    }
}

