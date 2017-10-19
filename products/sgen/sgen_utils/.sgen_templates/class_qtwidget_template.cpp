/*
    $CLASS_NAME.cpp
    $COPYRIGHT
*/
//$TIMESTAMP

#include "$CLASS_NAME.h"
#include "ui_$CLASS_NAME.h"

$BEGIN_NAMESPACE

$CLASS_NAME::$CLASS_NAME(QWidget *parent) :
    $QT_WIDGET(parent),
    m_ui(new Ui_$CLASS_NAME)
{
    m_ui->setupUi(this);
}
$CLASS_SETTERS_CPP

$CLASS_GETTERS_CPP

$CLASS_NAME::~$CLASS_NAME()
{
    delete m_ui;
}
$END_NAMESPACE