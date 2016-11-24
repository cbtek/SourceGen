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

#ifndef _PRODUCTS_SOURCEGEN_SOURCEGENINFO_H
#define _PRODUCTS_SOURCEGEN_SOURCEGENINFO_H
#include <string>

namespace cbtek{
namespace products{
namespace sourcegen {


class SourceGenInfo 
{
	public:
	//! Constructor for SourceGenInfo
	/*!
		Detailed description for SourceGenInfo
	*/
	SourceGenInfo();

    /*
    * @brief Setter for m_outputFolder
    * @param Value to replace m_outputFolder
    */
    void setOutputFolder(const std::string & value);

    /*
    * @brief Getter for m_outputFolder
    * @return Return copy of m_outputFolder
    /*
    * @brief Setter for m_incSubFolder
    * @param Value to replace m_incSubFolder
    */
    void setIncSubFolder(const std::string & value);

    /*
    * @brief Getter for m_incSubFolder
    * @return Return copy of m_incSubFolder
    /*
    * @brief Setter for m_srcSubFolder
    * @param Value to replace m_srcSubFolder
    */
    void setSrcSubFolder(const std::string & value);

    /*
    * @brief Getter for m_srcSubFolder
    * @return Return copy of m_srcSubFolder
    /*
    * @brief Setter for m_uiSubFolder
    * @param Value to replace m_uiSubFolder
    */
    void setUiSubFolder(const std::string & value);

    /*
    * @brief Getter for m_uiSubFolder
    * @return Return copy of m_uiSubFolder
    /*
    * @brief Setter for m_classType
    * @param Value to replace m_classType
    */
    void setClassType(const std::string & value);

    /*
    * @brief Getter for m_classType
    * @return Return copy of m_classType
    /*
    * @brief Setter for m_namespace
    * @param Value to replace m_namespace
    */
    void setNamespace(const std::string & value);

    /*
    * @brief Getter for m_namespace
    * @return Return copy of m_namespace
    /*
    * @brief Setter for m_includes
    * @param Value to replace m_includes
    */
    void setIncludes(const std::string & value);

    /*
    * @brief Getter for m_includes
    * @return Return copy of m_includes
    /*
    * @brief Setter for m_baseClass
    * @param Value to replace m_baseClass
    */
    void setBaseClasses(const std::string & value);

    /*
    * @brief Getter for m_baseClass
    * @return Return copy of m_baseClass
    /*
    * @brief Setter for m_className
    * @param Value to replace m_className
    */
    void setClassName(const std::string & value);

    /*
    * @brief Getter for m_className
    * @return Return copy of m_className
    /*
    * @brief Setter for m_getsSets
    * @param Value to replace m_getsSets
    */
    void setGetsSets(const std::string & value);

    /*
    * @brief Getter for m_getsSets
    * @return Return copy of m_getsSets
    /*
    * @brief Setter for m_copyrightFile
    * @param Value to replace m_copyrightFile
    */
    void setCopyrightFile(const std::string & value);

    /*
    * @brief Getter for m_copyrightFile
    * @return Return copy of m_copyrightFile
    /*
    * @brief Setter for m_canOverwrite
    * @param Value to replace m_canOverwrite
    */
    void setCanOverwrite(bool value);

    /*
    * @brief Getter for m_canOverwrite
    * @return Return copy of m_canOverwrite

    */
    const std::string & getOutputFolder() const;

    const std::string & getIncSubFolder() const;

    const std::string & getSrcSubFolder() const;

    const std::string & getUiSubFolder() const;

    const std::string & getClassType() const;

    const std::string & getNamespace() const;

    const std::string & getIncludes() const;

    const std::string & getBaseClasses() const;

    const std::string & getClassName() const;

    const std::string & getGetsSets() const;

    const std::string & getCopyrightFile() const;

    bool getCanOverwrite() const;

    void setShowUI(bool flag);

    bool getShowUI() const;

    void setDisableAnimations(bool flag);

    bool getDisableAnimations() const;


	//! Destructor
	~SourceGenInfo();	

    private:
    std::string m_outputFolder;
    std::string m_incSubFolder;
    std::string m_srcSubFolder;
    std::string m_uiSubFolder;
    std::string m_classType;
    std::string m_namespace;
    std::string m_includes;
    std::string m_baseClass;
    std::string m_className;
    std::string m_getsSets;
    std::string m_copyrightFile;
    bool m_canOverwrite;
    bool m_disableAnim;
    bool m_showUI;

};
}}}//end namespace

#endif // _PRODUCTS_SOURCEGEN_SOURCEGENINFO_H

