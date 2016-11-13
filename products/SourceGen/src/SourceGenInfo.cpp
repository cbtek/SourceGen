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
#include "SourceGenInfo.h"

namespace cbtek {
namespace products {
namespace sourcegen {


SourceGenInfo::SourceGenInfo()
{
    m_canOverwrite=false;
    m_disableAnim=false;
    m_showUI=false;
}

SourceGenInfo::~SourceGenInfo()
{

}

void SourceGenInfo::setOutputFolder(const std::string & value)
{
    m_outputFolder=value;
}

void SourceGenInfo::setIncSubFolder(const std::string & value)
{
    m_incSubFolder=value;
}

void SourceGenInfo::setSrcSubFolder(const std::string & value)
{
    m_srcSubFolder=value;
}

void SourceGenInfo::setUiSubFolder(const std::string & value)
{
    m_uiSubFolder=value;
}

void SourceGenInfo::setClassType(const std::string & value)
{
    m_classType=value;
}

void SourceGenInfo::setNamespace(const std::string & value)
{
    m_namespace=value;
}

void SourceGenInfo::setIncludes(const std::string & value)
{
    m_includes=value;
}

void SourceGenInfo::setBaseClasses(const std::string & value)
{
    m_baseClass=value;
}

void SourceGenInfo::setClassName(const std::string & value)
{
    m_className=value;
}

void SourceGenInfo::setGetsSets(const std::string & value)
{
    m_getsSets=value;
}

void SourceGenInfo::setCopyrightFile(const std::string & value)
{
    m_copyrightFile=value;
}

void SourceGenInfo::setCanOverwrite(bool value)
{
    m_canOverwrite=value;
}

const std::string &SourceGenInfo::getOutputFolder() const
{
    return m_outputFolder;
}

const std::string &SourceGenInfo::getIncSubFolder() const
{
    return m_incSubFolder;
}

const std::string &SourceGenInfo::getSrcSubFolder() const
{
    return m_srcSubFolder;
}

const std::string &SourceGenInfo::getUiSubFolder() const
{
    return m_uiSubFolder;
}

const std::string &SourceGenInfo::getClassType() const
{
    return m_classType;
}

const std::string &SourceGenInfo::getNamespace() const
{
    return m_namespace;
}

const std::string &SourceGenInfo::getIncludes() const
{
    return m_includes;
}

const std::string &SourceGenInfo::getBaseClasses() const
{
    return m_baseClass;
}

const std::string &SourceGenInfo::getClassName() const
{
    return m_className;
}

const std::string &SourceGenInfo::getGetsSets() const
{
    return m_getsSets;
}

const std::string &SourceGenInfo::getCopyrightFile() const
{
    return m_copyrightFile;
}

bool SourceGenInfo::getCanOverwrite() const
{
    return m_canOverwrite;
}

void SourceGenInfo::setShowUI(bool flag)
{
    m_showUI=flag;
}

bool SourceGenInfo::getShowUI() const
{
    return m_showUI;
}

void SourceGenInfo::setDisableAnimations(bool flag)
{
    m_disableAnim=flag;
}

bool SourceGenInfo::getDisableAnimations() const
{
    return m_disableAnim;
}

}}}//end namespace


