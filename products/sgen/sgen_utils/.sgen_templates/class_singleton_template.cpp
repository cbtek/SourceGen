/*
    $CLASS_NAME.cpp
    $COPYRIGHT
*/
//----------------------------------------
//$TIMESTAMP
//----------------------------------------

#include "$CLASS_NAME.h"

$BEGIN_NAMESPACE
$CLASS_NAME $CLASS_NAME::m_instance = $CLASS_NAME();
$CLASS_NAME & $CLASS_NAME::inst()
{
    return m_instance;
}
$CLASS_NAME::$CLASS_NAME()
{

}
$CLASS_NAME::~$CLASS_NAME()
{

}
$CLASS_SETTERS_CPP
$CLASS_GETTERS_CPP
$END_NAMESPACE