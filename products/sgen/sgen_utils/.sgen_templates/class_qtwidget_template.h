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
    explicit $CLASS_NAME(QWidget *parent = nullptr);
    $CLASS_SETTERS_H
    $CLASS_GETTERS_H
   /**
     * @brief Destructor for this class     
	 */
    ~$CLASS_NAME();
private:
    /** 
      * Qt meta object compiler (moc) generated user interface.
      * Objects created in designer will appear in m_ui object
      */
     Ui_$CLASS_NAME *m_ui;
    $CLASS_MEMBERS_H
};
$END_NAMESPACE