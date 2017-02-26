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
#include <QFileDialog>
#include <QMessageBox>

#include <ctime>

#include "UISourceGen.h"
#include "UISourceGenAbout.h"

#include "sgen_utils/inc/SourceGen.h"

#include "utility/inc/StringList.h"
#include "utility/inc/SystemUtils.hpp"
#include "utility/inc/FileUtils.hpp"
#include "utility/inc/ColorUtils.hpp"


#include "ui_UISourceGen.h"

using namespace cbtek::common::utility;

namespace cbtek {
namespace products {
namespace sourcegen {


UISourceGen::UISourceGen(bool closeOnSave, const SourceGenInfo &info, QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui_UISourceGen)
{        
    m_closeOnSave = closeOnSave;
    m_ui->setupUi(this);
    m_info=info;
    QString output = QString::fromStdString(info.getOutputFolder());
    output = output.remove("\"");
    m_ui->m_txtOutputDir->setText(output);
    m_ui->m_txtClass->setText(QString::fromStdString(info.getClassName()));
    m_ui->m_txtCopyright->setText(QString::fromStdString(info.getCopyrightFile()));
    m_ui->m_txtGetSet->setPlainText(QString::fromStdString(info.getGetsSets()));
    m_ui->m_txtIncludes->setText(QString::fromStdString(info.getIncludes()));
    m_ui->m_txtInherits->setText(QString::fromStdString(info.getBaseClasses()));
    m_ui->m_txtNamespace->setText(QString::fromStdString(info.getNamespace()));

    if (m_ui->m_txtOutputDir->text().size())
    {
        checkForSubDirs((m_ui->m_txtOutputDir->text()));
    }

    m_styleSheet = styleSheet();
    m_drawBackground=true;
    m_ui->m_chkDisableGraphics->setChecked(true);
    onToggleGraphics(!m_info.getDisableAnimations());
    onInit();
    m_whiteOut = 0;

}


UISourceGen::UISourceGen(UISourceGen *clone,
                         QWidget * parent) :
                       QDialog(parent),
                       m_ui(new Ui_UISourceGen)
{
    m_ui->setupUi(this);
    m_ui->m_txtNamespace->setText(clone->m_ui->m_txtNamespace->text());
    m_ui->m_txtOutputDir->setText(clone->m_ui->m_txtOutputDir->text());    

    if (m_ui->m_txtOutputDir->text().size())
    {
        checkForSubDirs((m_ui->m_txtOutputDir->text()));
    }

    int hIndex = clone->m_ui->m_cmbHeaderFolder->currentIndex();
    int sIndex = clone->m_ui->m_cmbSourceFolder->currentIndex();
    int uIndex = clone->m_ui->m_cmbUIFolder->currentIndex();

    if (hIndex<m_ui->m_cmbHeaderFolder->count())
    {
        m_ui->m_cmbHeaderFolder->setCurrentIndex(hIndex);
    }
    if (sIndex<m_ui->m_cmbSourceFolder->count())
    {
        m_ui->m_cmbSourceFolder->setCurrentIndex(sIndex);
    }
    if (uIndex<m_ui->m_cmbUIFolder->count())
    {
        m_ui->m_cmbUIFolder->setCurrentIndex(uIndex);
    }
    m_ui->m_txtCopyright->setText(clone->m_ui->m_txtCopyright->text());
    m_styleSheet = styleSheet();
    m_drawBackground=clone->m_drawBackground;
    m_ui->m_chkDisableGraphics->setChecked(clone->m_ui->m_chkDisableGraphics->isChecked());
    onToggleGraphics(m_drawBackground);
    onInit();
}

UISourceGen::~UISourceGen()
{
    delete m_ui;
}

void UISourceGen::onAbout()
{
    UISourceGenAbout(m_drawBackground,this).exec();
}

void UISourceGen::onClear()
{
    m_ui->m_txtClass->clear();
    m_ui->m_txtGetSet->clear();
    m_ui->m_txtIncludes->clear();
    m_ui->m_txtInherits->clear();
    m_ui->m_txtNamespace->clear();    
    m_ui->m_txtOutputDir->clear();
    m_ui->m_txtClass->setFocus();    
}

void UISourceGen::onExit()
{
    this->close();
}

void UISourceGen::onClone()
{    
    UISourceGen * sg = new UISourceGen(this);
    sg->show();
}

void UISourceGen::onSave()
{

    if (m_ui->m_txtClass->text().isEmpty())
    {
        QMessageBox::critical(this,"Empty field!","The class name field can not be empty!");
        return;
    }

    if (m_ui->m_txtClass->text().contains(" "))
    {
        QMessageBox::critical(this,"Space detected!","The class name field can not contain spaces!");
        return;
    }

    if (m_ui->m_lstTypes->currentItem()==0)
    {
        QMessageBox::critical(this,"No Type!","You must select a class type!");
        return;
    }
    try
    {
        common::utility::StringMap fileDataMap = SourceGen::getValidFileList();
        SourceGenInfo info;
        info.setClassName(m_ui->m_txtClass->text().toStdString());
        info.setGetsSets(m_ui->m_txtGetSet->toPlainText().toStdString());
        info.setIncludes(m_ui->m_txtIncludes->text().toStdString());
        info.setBaseClasses(m_ui->m_txtInherits->text().toStdString());
        info.setNamespace(m_ui->m_txtNamespace->text().toStdString());
        info.setClassType(m_ui->m_lstTypes->currentItem()->text().toStdString());
        info.setOutputFolder(m_ui->m_txtOutputDir->text().toStdString());
        info.setCanOverwrite(m_ui->m_chkOverwrite->isChecked());
        info.setCopyrightFile(m_ui->m_txtCopyright->text().toStdString());

        if (m_ui->m_chkSaveToSubfolder->isChecked() && m_ui->m_cmbHeaderFolder->currentIndex()>=0)
        {
            info.setIncSubFolder(m_ui->m_cmbHeaderFolder->currentText().toStdString());
        }

        if (m_ui->m_chkSaveToSubfolder->isChecked() && m_ui->m_cmbSourceFolder->currentIndex()>=0)
        {
            info.setSrcSubFolder(m_ui->m_cmbSourceFolder->currentText().toStdString());
        }

        if (m_ui->m_chkSaveToSubfolder->isChecked() && m_ui->m_cmbUIFolder->currentIndex()>=0)
        {
            info.setUiSubFolder(m_ui->m_cmbUIFolder->currentText().toStdString());
        }
        common::utility::StringList log;

        if (SourceGen::save(info,log,fileDataMap))
        {
            m_whiteOut= 127;
        }
        m_log << log;
        if (m_closeOnSave)
        {
            this->close();
        }
    }
    catch(const std::exception& e)
    {
        QMessageBox::critical(this,"Exception Occured!",QString(e.what()));
    }
}

void UISourceGen::onBrowse()
{
    QString dir = QFileDialog::getExistingDirectory(this,"Select Output Folder",m_ui->m_txtOutputDir->text());
    if (dir.size()==0)return;
    m_ui->m_txtOutputDir->setText(dir);
    checkForSubDirs(dir);

}

void UISourceGen::onClassTypeChanged(QString text)
{
    bool isNormal = text.toUpper().trimmed()=="NORMAL";
    bool isSingleton = text.toUpper().trimmed()=="SINGLETON";
    bool isVirtual = text.toUpper().trimmed()=="VIRTUAL";
    bool isStatic = text.toUpper().trimmed()=="STATIC";
    bool isTemplate = text.toUpper().trimmed()=="TEMPLATE";
    bool isQt = text.toUpper().startsWith("QT");

    if (isNormal || isSingleton || isQt)
    {
        m_ui->m_txtGetSet->setEnabled(true);
    }
    else m_ui->m_txtGetSet->setEnabled(false);

    if (isQt)
    {
        m_ui->m_cmbUIFolder->setEnabled(true);
    }
    else
    {
        m_ui->m_cmbUIFolder->setEnabled(false);
    }

}


void UISourceGen::onToggleGraphics(bool flag)
{
    m_drawBackground=flag;
    if (flag)
    {
        setStyleSheet(m_styleSheet);
    }
    else
    {
        setStyleSheet("");
    }
    update();
}

void UISourceGen::updateParticle(UISourceGen::Particle &p)
{
    p.direction = m_rnd.next(0,4);
    p.size = m_rnd.next(2,9);
    p.speed = m_rnd.next(2,15);
    p.active=true;
    p.angle = m_rnd.next(0,360);
    float offset = m_rnd.next(p.speed*2,p.speed*8);
    p.x = (this->width()/2)+std::cos(p.angle*0.01745329251) * offset;
    p.y = (this->height()/2)+std::sin(p.angle*0.01745329251) * offset;
    p.level = m_rnd.next(32,200);
}

void UISourceGen::onNameChanged(QString text)
{
    this->setWindowTitle(text.size()?text+" - "+"SourceGen Alpha (11/12/2016)":"SourceGen Alpha (11/12/2016)");
}

void UISourceGen::onInit()
{
    if (!m_ui->m_txtOutputDir->text().size())
    {
        m_ui->m_txtOutputDir->setText(QApplication::applicationDirPath());
    }
    m_ui->m_chkSaveToSubfolder->setChecked(false);
    m_ui->m_cmbHeaderFolder->setEnabled(false);
    m_ui->m_cmbSourceFolder->setEnabled(false);
    m_ui->m_cmbUIFolder->setEnabled(false);
    connect(m_ui->m_btnBrowseCopyright,SIGNAL(clicked(bool)),this,SLOT(onBrowseForCopyrightFile()));
    connect(m_ui->m_btnOutputLog,SIGNAL(clicked(bool)),this,SLOT(onViewLog()));
    connect(m_ui->m_chkSaveToSubfolder,SIGNAL(toggled(bool)),this,SLOT(onSaveToSubfolderToggled(bool)));
    connect(m_ui->m_btnBrowse,SIGNAL(clicked()),this,SLOT(onBrowse()));
    connect(m_ui->m_btnSave,SIGNAL(clicked()),this,SLOT(onSave())) ;
    connect(m_ui->m_btnClone,SIGNAL(clicked()),this,SLOT(onClone()))  ;
    connect(m_ui->m_btnExit,SIGNAL(clicked()),this,SLOT(onExit()))   ;
    connect(m_ui->m_lstTypes,SIGNAL(currentTextChanged(QString)),this,SLOT(onClassTypeChanged(QString)));
    connect(m_ui->m_txtClass,SIGNAL(textChanged(QString)),this,SLOT(onNameChanged(QString)));
    connect(m_ui->m_btnClear,SIGNAL(clicked()),this,SLOT(onClear()));
    connect(m_ui->m_btnAbout,SIGNAL(clicked()),this,SLOT(onAbout()));
    connect(m_ui->m_btnHelp,SIGNAL(clicked()),this,SLOT(onHelp()));
    connect(m_ui->m_chkDisableGraphics,SIGNAL(toggled(bool)),this,SLOT(onToggleGraphics(bool)));
    m_init=false;
    m_timerId=startTimer(60);
}

void UISourceGen::onViewLog()
{

    QPlainTextEdit * edit = new QPlainTextEdit(this);
    edit->setPlainText(QString::fromStdString(m_log.toString("\n")));
    edit->resize(320,240);
    edit->show();

    QDialog dialog;
    dialog.setLayout(new QVBoxLayout());
    dialog.layout()->addWidget(edit);
    dialog.exec();
}

void UISourceGen::onBrowseForCopyrightFile()
{

    QString file = QFileDialog::getOpenFileName(this,tr("Select Copyright File"),m_ui->m_txtOutputDir->text(),tr("Text Files (*.txt)"));
    if (file.size()==0)return;
    m_ui->m_txtCopyright->setText(file);
}

void UISourceGen::onHelp()
{
    QPlainTextEdit * helpText = new QPlainTextEdit;
    helpText->resize(800,600);

QString data=
    "------------------------------------\n"
    "SourceGen Help\n"
    "------------------------------------\n"
    "--class-name       [-n]   <name of class>    (required)\n"
    "--class-type       [-t]   <class type>\n"
    "--class-includes   [-inc] <list of includes>\n"
    "--class-inherits   [-inh] <list of inherits>\n"
    "--class-namespace  [-p]   <namespace>\n"
    "--class-attributes [-a]   <attribute list>\n"
    "--copyright-file   [-c]   <copyright file>\n"
    "--output-folder    [-o]   <output folder>\n"
    "--header-subfolder [-hs]  <header sub-folder>\n"
    "--source-subfolder [-ss]  <source sub-folder>\n"
    "--ui-subfolder     [-us]  <ui sub-folder>\n"
    "--help             [-h]   (displays this help message)\n"
    "------------------------------------\n"
    "Valid class-types:\n"
    "       1) NORMAL\n"
    "        2) STATIC\n"
    "        3) SINGLETON\n"
    "        4) VIRTUAL\n"
    "        5) QWIDGET\n"
    "        6) QDIALOG\n"
    "        7) QMAINWINDOW\n"
    "------------------------------------\n"
    "Example:\n"
    "sgen\n"
    "--class-name \"MyClass\"\n"
    "--class-type \"NORMAL\"\n"
    "--class-namespace \"MyCompany.Package.MyClass\"\n"
    "--class-includes \"<iostream>,<fstream>,*MyInclude.h*\"\n"
    "--class-inherits \"public MyInclude, public MyOtherInclude\"\n"
    "--class-attributes \"id:int,x:float,y:float,z:float,name:std::string\"\n"
    "--output-folder \"C:/\"\n"
    "------------------------------------\n";
    helpText->setPlainText(data);
    helpText->setReadOnly(false);
    QFont fixedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    fixedFont.setPointSize(14);
    helpText->setFont(fixedFont);
    helpText->setReadOnly(true);
    helpText->show();
}

void UISourceGen::paintEvent(QPaintEvent *)
{
    if (m_drawBackground)
    {
        QPainter g(this);
        QRectF viewRect = QRectF(0,0,this->width(),this->height());
        g.drawImage(viewRect,m_background);
        g.drawImage(viewRect,m_overlay);
        if (m_whiteOut > 0)
        {
            common::utility::Color c = common::utility::ColorFactory::create("eefaab");
            g.fillRect(viewRect,QColor(c.getRed(),c.getGreen(),c.getBlue(),m_whiteOut));
            m_whiteOut -= 10;
            if (m_whiteOut < 0)
            {
                m_whiteOut = 0;
            }
        }
    }
}

void UISourceGen::timerEvent(QTimerEvent *)
{
    if (!m_init)
    {
        m_rnd.reseed(time(NULL));

        for (size_t a1 = 0;a1<150;++a1)
        {
            Particle p;
            m_particles.push_back(p);
            updateParticle(m_particles.back());
            p.x=m_rnd.next(0,this->width());
            p.y=m_rnd.next(0,this->height());
        }
        m_init=true;
    }

    m_overlay = QImage(this->size(),QImage::Format_ARGB32);
    m_overlay.fill(Qt::transparent);
    QPainter g(&m_overlay);
    for(int a1 = 0;a1<m_particles.size();++a1)
    {
        Particle & p = m_particles[a1];
        QPen pen;
        pen.setColor(QColor(p.level,p.level,p.level));
         g.setPen(pen);
        if (p.active)
        {
            p.x += std::cos(p.angle*0.01745329251) * p.speed;
            p.y += std::sin(p.angle*0.01745329251) * p.speed;

            if (p.y >this->height()+p.size || p.y<-p.size || p.x>this->width()+p.size||p.x< -p.size)
            {
                updateParticle(p);
            }
            g.drawRect(p.x,p.y,2,2);
        }

    }
    update();
}

void UISourceGen::checkForSubDirs(const QString &dir)
{
    m_ui->m_cmbHeaderFolder->clear();
    m_ui->m_cmbSourceFolder->clear();
    m_ui->m_cmbUIFolder->clear();
    QStringList dirs = QDir(dir).entryList(QDir::AllDirs);
    dirs.removeAll("");
    dirs.removeAll(" ");
    dirs.removeAll(".");
    dirs.removeAll("..");
    dirs.removeAll("./");
    dirs.removeAll("../");
    if (dirs.size() > 0)
    {
        m_ui->m_cmbHeaderFolder->addItems(dirs);
        m_ui->m_cmbSourceFolder->addItems(dirs);
        m_ui->m_cmbUIFolder->addItems(dirs);
    }
}

void UISourceGen::onSaveToSubfolderToggled(bool toggle)
{
    m_ui->m_cmbHeaderFolder->setEnabled(toggle);
    m_ui->m_cmbSourceFolder->setEnabled(toggle);
    m_ui->m_cmbUIFolder->setEnabled(toggle);
}

}}}//end namespace
