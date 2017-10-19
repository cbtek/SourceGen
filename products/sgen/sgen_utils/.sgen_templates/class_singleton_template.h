/*
    $CLASS_NAME.h
    $COPYRIGHT
*/
#pragma once
$INCLUDES_H
$BEGIN_NAMESPACE
class $CLASS_NAME $PARENT_CLASSES
{
public:
    /**
     * @brief $CLASS_NAME     
     */
	$CLASS_NAME();
    $CLASS_SETTERS_H
    $CLASS_GETTERS_H		
	/**	
     * @brief Static instance method for this singleton     
     */	
    static $CLASS_NAME & inst();

	/**
     * Destructor for this class     
     */
	~$CLASS_NAME();	
private:
    static $CLASS_NAME m_instance;
    $CLASS_MEMBERS_H
};
$END_NAMESPACE