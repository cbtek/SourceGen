/*
    $CLASS_NAME.h
    $COPYRIGHT
*/

#ifndef $HEADER_GUARD
#define $HEADER_GUARD
#include <$QT_WIDGET>
$INCLUDES_H
class Ui_$CLASS_NAME;

$BEGIN_NAMESPACE

class $CLASS_NAME : public $QT_WIDGET
{
    Q_OBJECT

public:
	//! Constructor for $CLASS_NAME
	/*!
		Detailed description for $CLASS_NAME
        @param      parent points to embedding super widget. Defaults to null.
	*/
    explicit $CLASS_NAME(QWidget *parent = 0);
    $CLASS_SETTERS_H
    $CLASS_GETTERS_H
    //! Destructor for $CLASS_NAME
    ~$CLASS_NAME();
private:
    /** 
    * MOC generated ui class for this widget
    */
     Ui_$CLASS_NAME *m_ui;
    $CLASS_MEMBERS_H
};

$END_NAMESPACE
#endif // $HEADER_GUARD
