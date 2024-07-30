cmake_minimum_required(VERSION 3.16)

project(Server VERSION 0.1 LANGUAGES CXX)

configure_file(config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h @ONLY)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(icon_resource "${CMAKE_CURRENT_SOURCE_DIR}/res.rc")

find_package(Qt6 6.4 REQUIRED COMPONENTS
    Gui
    Quick
    Sql
    Network
    Core)


qt_standard_project_setup(REQUIRES 6.6)

qt_add_executable(${PROJECT_NAME}
    main.cpp

    messagesdb.h
    messagesdb.cpp

    servermodel.h
    servermodel.cpp
    serverview.h
    serverview.cpp
    serverviewmodel.h
    serverviewmodel.cpp

    config.h.in
    README.md
    ${icon_resource}
)

qt_add_qml_module(${PROJECT_NAME}
    URI Server
    VERSION 1.0
    QML_FILES
        GUI/BottomItem.qml
	GUI/ButtonSendMessage.qml
	GUI/ButtonServerStart.qml
	GUI/ButtonTemplate.qml
	GUI/InputMessage.qml
	GUI/InputText.qml
	GUI/InputTextPortServer.qml
	GUI/LabelsText.qml
	GUI/LabelsTextForDelegate.qml
	GUI/LightConnected.qml
	GUI/TopItem.qml
	GUI/ListViewMessages.qml
	GUI/ListViewClients.qml
	GUI/ServerWindow.qml
#	GUI/ListViewTemplate.qml

	GUI/ServerFuncs.js

)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Sql
    PRIVATE Qt6::Network
    PRIVATE Qt6::Core
    PRIVATE Qt6::Gui
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
