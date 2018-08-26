cmake_minimum_required(VERSION 3.5)

project(kImageAnnotator LANGUAGES CXX VERSION 0.0.1)

set(QT_MIN_VERSION "5.6.1")
set(KF5_MIN_VERSION "5.29.0")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules
        ${CMAKE_MODULE_PATH}
        ${ECM_MODULE_PATH}
        ${ECM_KDE_MODULE_DIR})

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED Widgets Test)
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS CoreAddons WidgetsAddons)

include(GNUInstallDirs)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(example)


include(CMakePackageConfigHelpers)

configure_package_config_file(
        ${CMAKE_SOURCE_DIR}/cmake/kImageAnnotator-config.cmake.in
        ${CMAKE_BINARY_DIR}/cmake/kImageAnnotator-config.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kImageAnnotator
)

write_basic_package_version_file(
        ${CMAKE_BINARY_DIR}/cmake/kImageAnnotator-config-version.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)

install(FILES
        ${CMAKE_BINARY_DIR}/cmake/kImageAnnotator-config.cmake
        ${CMAKE_BINARY_DIR}/cmake/kImageAnnotator-config-version.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kImageAnnotator
        )


export(
        EXPORT kImageAnnotator-targets
        FILE ${CMAKE_BINARY_DIR}/cmake/kImageAnnotator-targets.cmake
        NAMESPACE kImageAnnotator::
)

install(
        EXPORT kImageAnnotator-targets
        FILE kImageAnnotator-targets.cmake
        NAMESPACE kImageAnnotator::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kImageAnnotator
)
