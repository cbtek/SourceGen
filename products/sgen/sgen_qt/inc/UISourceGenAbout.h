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
#ifndef _SIG_CBTEK_SOURCEGEN_UISOURCEGENABOUT_H
#define _SIG_CBTEK_SOURCEGEN_UISOURCEGENABOUT_H
#include <QDialog>
#include <QMovie>

class Ui_UISourceGenAbout;

namespace cbtek{
namespace products{
namespace sourcegen {

class UISourceGenAbout : public QDialog
{
    Q_OBJECT

public:
	//! Constructor for UISourceGenAbout
	/*!
		Detailed description for UISourceGenAbout
        @param      parent points to embedding super widget. Defaults to null.
	*/
    explicit UISourceGenAbout(bool drawBackground, QWidget *parent);
    
    
	//! Descructor for UISourceGenAbout
    ~UISourceGenAbout();
private:
    /** 
    * MOC generated ui class for this widget
    */
    QMovie m_movie;
    Ui_UISourceGenAbout *m_ui;
    QImage m_currentImage;
    bool m_drawBackground;
protected:
    void paintEvent(QPaintEvent *);
protected slots:

    void onFrameUpdated(int frame);

};

}}}//end namespace

#endif // _SIG_CBTEK_SOURCEGEN_UISOURCEGENABOUT_H
