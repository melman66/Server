cmake_minimum_required(VERSION 3.16)

project(Server VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS
    Gui
    Quick
    Sql
    Network
    Core)


qt_standard_project_setup()

qt_add_executable(appServer
    main.cpp

    messagesdb.h
    messagesdb.cpp

    servermodel.h
    servermodel.cpp
    serverview.h
    serverview.cpp
    serverviewmodel.h
    serverviewmodel.cpp

)

qt_add_qml_module(appServer
    URI Server
    VERSION 1.0
    QML_FILES
        GUI/ServerWindow.qml
	GUI/InputText.qml
	GUI/LightConnected.qml
	GUI/LabelsText.qml
	GUI/ListViewTemplate.qml
	GUI/ButtonTemplate.qml
	GUI/ListViewDelegate.qml
	GUI/LabelsTextForDelegate.qml
	GUI/InputMessage.qml
	GUI/ButtonSendMessage.qml
	GUI/TopItem.qml
	GUI/BottomItem.qml
	GUI/InputTextPortServer.qml
	GUI/ButtonServerStart.qml
	GUI/ListViewMessages.qml
	GUI/ListViewClients.qml

	GUI/ServerFuncs.js

)

set_target_properties(appServer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appServer
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Sql
    PRIVATE Qt6::Network
    PRIVATE Qt6::Core
    PRIVATE Qt6::Gui
)

install(TARGETS appServer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
