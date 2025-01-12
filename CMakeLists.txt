cmake_minimum_required(VERSION 3.16)

SET(RELEASE_DATE 2024-12-20)
SET(PROJECT_NAME wbase27)

project(${PROJECT_NAME} VERSION 1.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2 Widgets)

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
    src/main.cpp 

    res/resources.qrc
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

qt_add_qml_module(${PROJECT_NAME}
    URI wbase27
    VERSION 1.0
    QML_FILES
            src/Main.qml

    RESOURCES res/resources.qrc
    QML_FILES src/WorkAreaRow.qml
    SOURCES src/standbymanager.h src/standbymanager.cpp
    SOURCES src/presetmanager.h src/presetmanager.cpp
)


if (UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Quick Qt6::QuickControls2 Qt6::Widgets)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Quick Qt6::QuickControls2 Qt6::Widgets)
endif(UNIX)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}_app")

