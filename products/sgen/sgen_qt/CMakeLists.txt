#==============================================================================
# CMakeLists file for sourcegen/qt
#==============================================================================
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CURR_TARGET sgen_qt)

include(${CMAKE_MODULE_PATH}/flags.cmake)
include(${CMAKE_MODULE_PATH}/build.cmake)

set(CURR_TARGET_SOURCES "${CURR_TARGET}_SOURCES")
set(CURR_TARGET_FORMS "${CURR_TARGET}_FORMS")
set(CURR_TARGET_HEADERS "${CURR_TARGET}_HEADERS")
set(CURR_TARGET_HEADERS_NO_MOC "${CURR_TARGET}_HEADERS_NO_MOC")

include_directories(src)
include_directories(inc)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

#==============================================================================
# Include Source Files
#==============================================================================
file(GLOB CURR_TARGET_SOURCES "src/*.cpp")
file(GLOB CURR_TARGET_FORMS "src/*.ui")
file(GLOB CURR_TARGET_HEADERS "inc/*.h*")



#==============================================================================
# Add Executable
#==============================================================================
add_executable(${CURR_TARGET}
               ${PLATFORM}
               ${CURR_TARGET_SOURCES}
               ${CURR_TARGET_HEADERS}
               ${CURR_TARGET_FORMS}               
               )

#==============================================================================
# Add Dependencies
#==============================================================================

qt5_use_modules(${CURR_TARGET}
                 Widgets)

add_dependencies(${CURR_TARGET}
                 sgen_utils
                 common_utils)

#==============================================================================
# Target Link Libraries
#==============================================================================
target_link_libraries(${CURR_TARGET}
                      sgen_utils
                      common_utils
                      Qt5::Widgets)

#==============================================================================
# Install
#==============================================================================
INSTALL(TARGETS ${CURR_TARGET} RUNTIME DESTINATION bin)



