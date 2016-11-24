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
#ifndef TXWI_UISOURCEGEN_EVKW
#define TXWI_UISOURCEGEN_EVKW

#include <QDialog>
#include <QImage>
#include <QPainter>

#include "utility/inc/ObjectList.hpp"
#include "utility/inc/Random.h"
#include "utility/inc/StringList.h"
#include "utility/inc/ObjectList.hpp"

#include "sgen_utils/inc/SourceGen.h"

class Ui_UISourceGen;

namespace cbtek {
namespace products {
namespace sourcegen {

class UISourceGen : public QDialog
{
    Q_OBJECT

public:
    ///
    /// \brief Constructor UISourceGen
    /// \param parent
    ///
    explicit UISourceGen(bool closeOnSave,const SourceGenInfo & info,QWidget *parent = NULL);


    ///
    /// \brief UISourceGen
    /// \param clone
    /// \param parent
    ///
    explicit UISourceGen(UISourceGen * clone,QWidget * parent=NULL);

    ~UISourceGen();

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);
    Ui_UISourceGen *m_ui;
    int m_timerId;
    struct Particle
    {
        int x,y,speed,size,direction;
        bool active;
        int level;
        int angle;
    };

    common::utility::ObjectList<Particle> m_particles;
    common::utility::Random m_rnd;
    QImage m_background;
    QImage m_overlay;
    QString m_styleSheet;    
    bool m_init;
    bool m_drawBackground;
    bool m_closeOnSave;
    int m_whiteOut;
    SourceGenInfo m_info;
    common::utility::StringList m_log;

    void checkForSubDirs(const QString & dir);
private slots:
    void onSaveToSubfolderToggled(bool toggle);
    void onAbout();
    void onClear();
    void onExit();
    void onClone();
    void onSave();
    void onBrowse();
    void onClassTypeChanged(QString text);    
    void onToggleGraphics(bool flag);
    void updateParticle(Particle & p);
    void onNameChanged(QString text);
    void onInit();
    void onViewLog();
    void onBrowseForCopyrightFile();
};

}}}//end namespace

#endif // CLASS_NAME_H
