/*
    $CLASS_NAME.h
    $COPYRIGHT
*/

#ifndef $HEADER_GUARD
#define $HEADER_GUARD

$INCLUDES_H
$BEGIN_NAMESPACE

class $CLASS_NAME $PARENT_CLASSES
{

public:
	//! Constructor for $CLASS_NAME
	/*!
		Detailed description for $CLASS_NAME
	*/
	$CLASS_NAME();
    $CLASS_SETTERS_H
    $CLASS_GETTERS_H

	//! Static instance method for this singleton
    static $CLASS_NAME & inst();

	//! Destructor
	~$CLASS_NAME();	

private:
    static $CLASS_NAME m_instance;
    $CLASS_MEMBERS_H
};
$END_NAMESPACE
#endif

