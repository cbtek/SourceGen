/*
    $CLASS_NAME.h
    $COPYRIGHT
*/
#pragma once
#include <$QT_WIDGET>
$INCLUDES_H
class Ui_$CLASS_NAME;
$BEGIN_NAMESPACE
class $CLASS_NAME : public $QT_WIDGET
{
    Q_OBJECT
public:
   /**
    * @brief $CLASS_NAME
    * @param parent Pointer to parent widget. Defaults to null.
	*/		
    explicit $CLASS_NAME(QWidget *parent = 0);
    $CLASS_SETTERS_H
    $CLASS_GETTERS_H
   /**
    * @brief $CLASS_NAME
    *
	*/
    ~$CLASS_NAME();
private:
    /** 
    * MOC generated ui class for this widget
    */
     Ui_$CLASS_NAME *m_ui;
    $CLASS_MEMBERS_H
};
$END_NAMESPACE