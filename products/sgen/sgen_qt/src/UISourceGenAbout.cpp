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
#include "UISourceGenAbout.h"
#include "ui_UISourceGenAbout.h"

#include "utility/inc/Random.h"

#include <QPainter>

#include <ctime>

namespace cbtek {
namespace products {
namespace sourcegen {

UISourceGenAbout::UISourceGenAbout(bool drawBackground,QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui_UISourceGenAbout)
{
    m_ui->setupUi(this);    
    m_drawBackground=drawBackground;
    if (drawBackground)
    {
        this->setStyleSheet(parent->styleSheet());
        common::utility::Random rnd;
        rnd.reseed(time(NULL));
        if (rnd.next(1000) > 500)
        {
            m_movie.setFileName(":/resx/movPlasma.gif");
        }
        else
        {
            m_movie.setFileName(":/resx/movCircuit.gif");
        }
        m_movie.start();
        connect(&m_movie,SIGNAL(frameChanged(int)),this,SLOT(onFrameUpdated(int)));
    }
    else
    {
        this->setStyleSheet("");
    }
    connect(m_ui->m_btnClose,SIGNAL(clicked(bool)),this,SLOT(close()));
    resize(320,200);
}


UISourceGenAbout::~UISourceGenAbout()
{
    delete m_ui;
}

void UISourceGenAbout::paintEvent(QPaintEvent *)
{
    if (m_drawBackground)
    {
        QPainter g(this);
        g.drawImage(QRect(0,0,this->width(),this->height()),m_currentImage);
        g.fillRect(0,0,this->width(),this->height(),QColor(0,0,0,150));
    }
}

void UISourceGenAbout::onFrameUpdated(int frame)
{
    m_currentImage=m_movie.currentImage();
    update();
}

}}}//end namespace

