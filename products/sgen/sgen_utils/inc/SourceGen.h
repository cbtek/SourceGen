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
#pragma once


#include <string>

#include "utility/inc/ObjectMap.hpp"
#include "utility/inc/StringList.h"

#include "SourceGenInfo.h"

namespace cbtek{
namespace products{
namespace sourcegen {

class SourceGen
{
    public:

    /**
     * @brief save
     * @param info
     * @param log
     * @param fileDataMap
     * @return
     */
    static bool save(const SourceGenInfo & info,
                     common::utility::StringList &log,
                     const common::utility::StringMap &fileDataMap);

    static common::utility::StringMap getValidFileList();

    private:

    ///
    /// \brief saveGettersSetters
    /// \param gettersSetters
    /// \param classname
    /// \param hData
    /// \param cppData
    ///
        static void saveGettersSetters(const std::string & gettersSetters,
                           const std::string & classname,
                             std::string & hData,
                             std::string & cppData);
        ~SourceGen(){}
        SourceGen(){}
};
}}}//namespace
