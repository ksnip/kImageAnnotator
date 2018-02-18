cmake_minimum_required(VERSION 3.0)

project(kimageannotator)

set(QT_MIN_VERSION     "5.7.0")
set(KF5_MIN_VERSION    "5.29.0")
set(PLASMA_MIN_VERSION "5.4.0")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_AUTOMOC ON)

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules
                      ${CMAKE_MODULE_PATH}
                      ${ECM_MODULE_PATH}
                      ${ECM_KDE_MODULE_DIR}
)

include(KDEInstallDirs)

add_subdirectory(src)
# add_subdirectory(tests)
