cmake_minimum_required(VERSION 3.5)
project(kImageAnnotator LANGUAGES CXX VERSION 0.0.1)

set(QT_MIN_VERSION "5.6.1")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_MODULE_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules
        ${CMAKE_MODULE_PATH})

option(BUILD_TESTS "Build Unit Tests" OFF)

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED Widgets Test)
find_package(kColorPicker REQUIRED)

include(GNUInstallDirs)
include(FeatureSummary)

add_subdirectory(src)
add_subdirectory(example)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif (BUILD_TESTS)

include(CMakePackageConfigHelpers)

configure_package_config_file(
        ${CMAKE_SOURCE_DIR}/cmake/kImageAnnotatorConfig.cmake.in
        ${CMAKE_BINARY_DIR}/cmake/kImageAnnotatorConfig.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kImageAnnotator
)

write_basic_package_version_file(
        ${CMAKE_BINARY_DIR}/cmake/kImageAnnotatorConfig-version.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)

install(FILES
        ${CMAKE_BINARY_DIR}/cmake/kImageAnnotatorConfig.cmake
        ${CMAKE_BINARY_DIR}/cmake/kImageAnnotatorConfig-version.cmake
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
