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

#include "XMLUtils.h"
#include "StringUtils.hpp"

namespace cbtek {
namespace common {
namespace utility {


std::string XMLUtils::getEncodedString(const std::string &rawString)
{
    std::string retStr;
    retStr=StringUtils::replace(rawString,"&","&amp;",true);
    retStr=StringUtils::replace(retStr,"\"","&quot;",true);
    retStr=StringUtils::replace(retStr,"<","&lt;",true);
    retStr=StringUtils::replace(retStr,">","&gt;",true);
    retStr=StringUtils::replace(retStr,"\n","&nl;",true);
    retStr=StringUtils::replace(retStr,"\t","&tab;",true);
    return retStr;
}

std::string XMLUtils::getDecodedString(const std::string &xmlString)
{
    std::string retStr;
    retStr=StringUtils::replace(xmlString,"&amp;","&",true);
    retStr=StringUtils::replace(retStr,"&quot;","\"",true);
    retStr=StringUtils::replace(retStr,"&lt;","<",true);
    retStr=StringUtils::replace(retStr,"&gt;",">",true);
    retStr=StringUtils::replace(retStr,"&nl;","\n",true);
    retStr=StringUtils::replace(retStr,"&tab;","\n",true);
    return retStr;
}
}}}//namespace
