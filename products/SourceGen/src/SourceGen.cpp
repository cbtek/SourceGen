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

#include "SourceGen.h"

#include "utility/inc/StringUtils.hpp"
#include "utility/inc/FileUtils.hpp"
#include "utility/inc/SystemUtils.hpp"
#include "utility/inc/TimeUtils.hpp"
#include "utility/inc/DateUtils.hpp"
#include "utility/inc/StringList.h"

using namespace cbtek::common::utility;

namespace cbtek{
namespace products{
namespace sourcegen {

////////////////////////////////////////////////////////////////////////
/// \brief SourceGen::save
/// \param info
/// \param log
/// \param fileDataMap
/// \return
////////////////////////////////////////////////////////////////////////
bool SourceGen::save(const SourceGenInfo &info,
                     StringList &log,
                     const common::utility::StringMap &fileDataMap)
{    

    std::string className           = info.getClassName();
    std::string gettersSetters      = info.getGetsSets();
    std::string includes            = info.getIncludes();
    std::string inherits            = info.getBaseClasses();
    std::string namespaces          = info.getNamespace();
    std::string type                = info.getClassType();
    std::string outputdir           = info.getOutputFolder();
    std::string copyrightData       = FileUtils::getFileContents(info.getCopyrightFile());
    std::string srcSubFolder        = info.getSrcSubFolder();
    std::string uiSubFolder         = info.getUiSubFolder();
    std::string incSubFolder        = info.getIncSubFolder();

    bool overwrite                  = info.getCanOverwrite();
    std::string hData,cppData;

    std::vector<std::string> namespaceList        = StringUtils::split(namespaces,".");
    StringUtils::clean(namespaceList);
    std::string beginNamespace,endNamespace;

    if (namespaceList.size())
    {
        beginNamespace          = StringList(namespaceList).toString("namespace "," {\n");
        StringUtils::repeat("}",endNamespace,namespaceList.size());
        endNamespace            += "//end namespace\n";
    }

    std::string headerguard     = StringUtils::toUpperTrimmed("_"+StringList(namespaceList).toString("_")+"_"+className+"_H");
    std::string timestamp       = className+".cpp generated by "+ SystemUtils::getUserName()+" on "+ DateUtils::toShortDateString(DateUtils::getCurrentDate()) +" at "+TimeUtils::to12HourTimeString(TimeUtils::getCurrentTime());
    std::string cppFileOut      = FileUtils::buildFilePath(FileUtils::buildFilePath(outputdir,srcSubFolder),className+".cpp");
    std::string hFileOut        = FileUtils::buildFilePath(FileUtils::buildFilePath(outputdir,incSubFolder),className+".h");
    std::string classtype       = StringUtils::toUpperTrimmed(type);

    ///
    //Start constructing class output for each class type
    ///
    if (classtype=="NORMAL")
    {
        hData                   = fileDataMap.getValue("class_normal_template.h");
        cppData                 = fileDataMap.getValue("class_normal_template.cpp");
    }

    else if (classtype=="SINGLETON")
    {
        hData           = fileDataMap.getValue("class_singleton_template.h");
        cppData         = fileDataMap.getValue("class_singleton_template.cpp");
    }

    else if (classtype=="STATIC")
    {
        hData           = fileDataMap.getValue("class_static_template.h");
        cppData         = fileDataMap.getValue("class_static_template.cpp");
    }

    else if (classtype=="VIRTUAL")
    {
        hData           = fileDataMap.getValue("class_virtual_template.h");
        cppFileOut      = "";
    }

    else if (classtype=="QMAINWINDOW" ||
             classtype=="QWIDGET" ||
             classtype=="QDIALOG")
    {
        std::string qtwidget;
        if (classtype=="QMAINWINDOW")
        {
            qtwidget    ="QMainWindow";
        }
        else if (classtype=="QDIALOG")
        {
            qtwidget    = "QDialog";
        }
        else
        {
            qtwidget="QWidget";
        }

        hData                   = fileDataMap.getValue("class_qtwidget_template.h");
        cppData                 = fileDataMap.getValue("class_qtwidget_template.cpp");
        std::string uiData      = fileDataMap.getValue("class_qtwidget_template.ui");
        std::string uiFileOut   = FileUtils::buildFilePath(FileUtils::buildFilePath(outputdir,uiSubFolder),className+".ui");
        uiData                  = StringUtils::replace(uiData,"$CLASS_NAME",className,true);
        hData                   = StringUtils::replace(hData,"$QT_WIDGET",qtwidget,true);
        cppData                 = StringUtils::replace(cppData,"$QT_WIDGET",qtwidget,true);
        uiData                  = StringUtils::replace(uiData,"$QT_WIDGET",qtwidget,true);

        if (classtype=="QMAINWINDOW")
        {
            uiData              = StringUtils::replace(uiData,"$QT_MAIN_WINDOW_CHILD","<widget class=\"QWidget\" name=\"centralwidget\">\n</widget>\n");
        }
        else
        {
            uiData              = StringUtils::replace(uiData,"$QT_MAIN_WINDOW_CHILD","\n");
        }

        SourceGen::saveGettersSetters(gettersSetters,className,hData,cppData);

        if (!overwrite && FileUtils::fileExists(uiFileOut))
        {
            log.push_back("Can not overwrite file at '");
            log.push_back(uiFileOut);
            log.push_back("'\n");
            return false;
        }
        else
        {
            log.push_back("Successfully generated UI file at '");
            log.push_back(uiFileOut);
            log.push_back("'\n");
            FileUtils::writeFileContents(uiFileOut,uiData);
        }
    }

    if (StringUtils::trimmed(inherits).size())
    {
        hData                   = StringUtils::replace(hData,"$PARENT_CLASSES",":"+inherits,true);
    }
    else
    {
        hData                   = StringUtils::replace(hData,"$PARENT_CLASSES","",true);
    }

    //fix for cmdline version
    std::string includesFixed = StringUtils::replace(includes,"*","\"",true);

    StringList includeList = StringUtils::split(includesFixed,",");
    includeList.trimmed();
    includeList.remove("");
    std::string yearStr = StringUtils::toString(DateUtils::getCurrentDate().getYear());
    hData  = StringUtils::replace(hData,"$INCLUDES_H",(includeList.size()?(includeList).toString("#include ","\n"):""));
    hData   = StringUtils::replace(hData,"$CLASS_NAME",className,true);
    cppData = StringUtils::replace(cppData,"$CLASS_NAME",className,true);
    hData   = StringUtils::replace(hData,"$BEGIN_NAMESPACE",beginNamespace,true);
    cppData = StringUtils::replace(cppData,"$BEGIN_NAMESPACE",beginNamespace,true);
    hData   = StringUtils::replace(hData,"$END_NAMESPACE",endNamespace,true);
    cppData = StringUtils::replace(cppData,"$END_NAMESPACE",endNamespace,true);
    hData   = StringUtils::replace(hData,"$HEADER_GUARD",headerguard,true);
    cppData = StringUtils::replace(cppData,"$TIMESTAMP",timestamp,true);
    hData   = StringUtils::replace(hData,"$YEAR",yearStr,true);
    cppData = StringUtils::replace(cppData,"$YEAR",yearStr,true);
    cppData = StringUtils::replace(cppData,"$COPYRIGHT","\n"+copyrightData,true);
    hData   = StringUtils::replace(hData,"$COPYRIGHT","\n"+copyrightData,true);

    SourceGen::saveGettersSetters(gettersSetters,className,hData,cppData);

    if (!overwrite && FileUtils::fileExists(hFileOut))
    {
        log << "Can not overwrite file at '"<<hFileOut<<"'!\n";
        return false;
    }
    else
    {
        if (cppFileOut.size()==0)
        {
            hFileOut = hFileOut+"pp";
            log << "Successfully generated .hpp file at "<<hFileOut<<"\n";
            FileUtils::writeFileContents(hFileOut,hData);
        }
        else
        {
            log << "Successfully generated .h file at "<<hFileOut<<"\n";
            FileUtils::writeFileContents(hFileOut,hData);
        }
    }

    if (!overwrite && FileUtils::fileExists(cppFileOut))
    {
        log << "Can not overwrite file at '"<<cppFileOut<<"'!\n";
        return false;
    }
    else
    {
        if (cppFileOut.size())
        {
            log << "Successfully generated .cpp file at "<<cppFileOut<<"\n";
            FileUtils::writeFileContents(cppFileOut,cppData);
        }
    }
    return true;
}

////////////////////////////////////////////////////////////////////////
/// \brief SourceGen::saveGettersSetters
/// \param gettersSetters
/// \param classname
/// \param hData
/// \param cppData
////////////////////////////////////////////////////////////////////////
void SourceGen::saveGettersSetters(const std::string &gettersSetters, const std::string &classname, std::string &hData, std::string &cppData)
{
    std::string headerMembers,headerGetters,headerSetters;
    std::string sourceGetters,sourceSetters;
    std::vector<std::string> getsSets = StringUtils::split(gettersSetters,"\n");
    for(int a1 = 0;a1<getsSets.size();++a1)
    {
        StringList items = StringUtils::split(getsSets[a1],":");
        items.trimmed();
        items.remove("");

        if (items.size()>1)
        {
            std::string variable = items[0];
            std::string type = items[1];
            if (items.size()>2)
            {
                for (size_t a2=2;a2<items.size();++a2)
                {
                    type+="::"+items[a2];
                }
            }
            std::string func = variable;
            if (StringUtils::startsWith(func,"m_"))
            {
                func = func.substr(2,func.size()-2);
            }
            else if (StringUtils::startsWith(func,"_"))
            {
                func = func.substr(1,func.size()-1);
            }
            if (func.size())
            {
                func[0]=std::toupper(func[0]);
            }
            bool useConstCorrectness=true;
            if (StringUtils::toLower(type)=="int" ||
                StringUtils::toLower(type)=="long" ||
                StringUtils::toLower(type)=="long int" ||
                StringUtils::toLower(type)=="long long" ||
                StringUtils::toLower(type)=="unsigned long int" ||
                StringUtils::toLower(type)=="unsigned long long" ||
                StringUtils::toLower(type)=="double" ||
                StringUtils::toLower(type)=="float" ||
                StringUtils::toLower(type)=="char" ||
                StringUtils::toLower(type)=="size_t" ||
                StringUtils::toLower(type)=="unsigned char" ||
                StringUtils::toLower(type)=="unsigned int" ||
                StringUtils::toLower(type)=="bool" ||
                StringUtils::toLower(type)=="unsigned long" ||
                StringUtils::toLower(type)=="boost::uint8_t" ||
                StringUtils::toLower(type)=="boost::uint16_t" ||
                StringUtils::toLower(type)=="boost::uint32_t" ||
                StringUtils::toLower(type)=="boost::uint64_t" ||
                StringUtils::toLower(type)=="boost::int8_t" ||
                StringUtils::toLower(type)=="boost::int16_t" ||
                StringUtils::toLower(type)=="boost::int32_t" ||
                StringUtils::toLower(type)=="boost::int64_t" ||
                StringUtils::toLower(type)=="std::uint8_t" ||
                StringUtils::toLower(type)=="std::uint16_t" ||
                StringUtils::toLower(type)=="std::uint32_t" ||
                StringUtils::toLower(type)=="std::uint64_t" ||
                StringUtils::toLower(type)=="std::int8_t" ||
                StringUtils::toLower(type)=="std::int16_t" ||
                StringUtils::toLower(type)=="std::int32_t" ||
                StringUtils::toLower(type)=="std::int64_t" ||
                StringUtils::toLower(type)=="uint8_t" ||
                StringUtils::toLower(type)=="uint16_t" ||
                StringUtils::toLower(type)=="uint32_t" ||
                StringUtils::toLower(type)=="uint64_t" ||
                StringUtils::toLower(type)=="int8_t" ||
                StringUtils::toLower(type)=="int16_t" ||
                StringUtils::toLower(type)=="int32_t" ||
                StringUtils::toLower(type)=="int64_t")
                {
                    useConstCorrectness=false;
                }           
            headerMembers+="    "+type+" "+variable+";\n";

            headerSetters+="    /**\n";
            headerSetters+="    * @brief Setter for "+variable+"\n";
            headerSetters+="    * @param Value to replace "+variable+"\n";
            headerSetters+="    */\n";
            headerSetters+="    void set"+func+"("+ (useConstCorrectness?"const "+type+" & value": type+" value") +");\n\n";            

            headerGetters+="    /**\n";
            headerGetters+="    * @brief Getter for "+variable+"\n";
            headerGetters+="    * @return Return copy of "+variable+"\n";
            headerGetters+="    */\n";
            headerGetters+="    "+(useConstCorrectness?"const "+type+" &": type)+" get"+func+"() const;\n\n";            

            sourceSetters+="void "+classname+"::set"+func+"("+ (useConstCorrectness?"const "+type+" & value": type+" value") +")\n{\n    "+variable+"=value;\n}\n\n";
            sourceGetters+=""+(useConstCorrectness?"const "+type+" &": type+" ")+classname+"::get"+func+"() const\n{\n    return "+variable+";\n}\n\n";

        }
    }

    hData   = StringUtils::replace(hData,"$CLASS_MEMBERS_H",headerMembers);
    hData   = StringUtils::replace(hData,"$CLASS_GETTERS_H",headerGetters);
    hData   = StringUtils::replace(hData,"$CLASS_SETTERS_H",headerSetters);
    cppData = StringUtils::replace(cppData,"$CLASS_GETTERS_CPP",sourceGetters);
    cppData = StringUtils::replace(cppData,"$CLASS_SETTERS_CPP",sourceSetters);
}
}}}//namespace
