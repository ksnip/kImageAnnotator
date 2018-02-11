cmake_minimum_required(VERSION 3.0)

project(kimageannotator)

set(QT_MIN_VERSION     "5.7.0")
set(KF5_MIN_VERSION    "5.29.0")
set(PLASMA_MIN_VERSION "5.4.0")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules
                      ${CMAKE_MODULE_PATH}
                      ${ECM_MODULE_PATH}
                      ${ECM_KDE_MODULE_DIR}
)

include(KDEInstallDirs)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED Widgets)

set(kimageannotator_SRCS src/main.cpp
                         src/KImageAnnotator.cpp
                         src/AnntationArea.cpp
    )


add_executable(kimageannotator_app ${kimageannotator_SRCS})

target_link_libraries(kimageannotator_app Qt5::Widgets)
