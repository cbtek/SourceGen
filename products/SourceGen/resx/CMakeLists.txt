project(sourcegen2)
FILE(GLOB sourcegen2_SOURCES "*.cpp")
FILE(GLOB sourcegen2_HEADERS "*.h*")
FILE(GLOB sourcegen2_FORMS "*.ui")
FILE(GLOB sourcegen2_RESOURCES "*.qrc")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Widgets REQUIRED)
qt5_wrap_ui(sourcegen2_FORMS_MOC ${sourcegen2_FORMS})

QT5_ADD_RESOURCES(sourcegen2_RESOURCES_RCC ${sourcegen2_RESOURCES})
ADD_EXECUTABLE(sourcegen2 ${PLATFORM}
                ${sourcegen2_SOURCES}
                ${sourcegen2_HEADERS_MOC}
                ${sourcegen2_FORMS_MOC}
                ${sourcegen2_RESOURCES_RCC})
qt5_use_modules(sourcegen2 Widgets)
add_dependencies(sourcegen2 ezutils)
target_link_libraries(sourcegen2 ezutils)
