cmake_minimum_required(VERSION 3.5)
project(kImageAnnotator LANGUAGES CXX VERSION 0.7.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

option(BUILD_TESTS "Build Unit Tests" OFF)
option(BUILD_EXAMPLE "Build Example Application" ON)

include(GNUInstallDirs)

if (WIN32)
	set(KIMAGEANNOTATOR_LANG_INSTALL_DIR "translations")
elseif (APPLE)
	set(KIMAGEANNOTATOR_LANG_INSTALL_DIR "../Resources")
elseif (UNIX)
	set(KIMAGEANNOTATOR_LANG_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/kImageAnnotator/translations")
	string(REGEX REPLACE "//" "/" KIMAGEANNOTATOR_LANG_INSTALL_DIR "${KIMAGEANNOTATOR_LANG_INSTALL_DIR}")
endif ()

set(QT_MIN_VERSION 5.15)

option(BUILD_WITH_QT6 "Build against Qt6" OFF)

if (BUILD_WITH_QT6)
	set(QT_MAJOR_VERSION 6)
else()
	set(QT_MAJOR_VERSION 5)
endif()

find_package(Qt${QT_MAJOR_VERSION} ${QT_MIN_VERSION} REQUIRED Widgets Svg)

if (UNIX AND NOT APPLE)
	find_package(X11 REQUIRED)
endif ()

include(FeatureSummary)

set(KCOLORPICKER_MIN_VERSION 0.3.0)
find_package(kColorPicker-Qt${QT_MAJOR_VERSION} ${KCOLORPICKER_MIN_VERSION} REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src)
add_subdirectory(translations)

if (BUILD_EXAMPLE)
	add_subdirectory(example)
endif (BUILD_EXAMPLE)

if (BUILD_TESTS)
	add_subdirectory(tests)
endif (BUILD_TESTS)

include(CMakePackageConfigHelpers)

add_library(kImageAnnotator
			${KIMAGEANNOTATOR_SRCS}
			${CMAKE_CURRENT_SOURCE_DIR}/include/kImageAnnotator/KImageAnnotator.h
			${CMAKE_CURRENT_SOURCE_DIR}/resources/kImageAnnotator_resources.qrc
        src/common/helper/DesktopEnvironmentChecker.cpp src/common/helper/DesktopEnvironmentChecker.h src/common/enum/DesktopEnvironmentType.h)

add_library(kImageAnnotator::kImageAnnotator ALIAS kImageAnnotator)

target_include_directories(kImageAnnotator
						   PUBLIC
						   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
						   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
						   $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/kImageAnnotator-Qt${QT_MAJOR_VERSION}>
						   )

target_link_libraries(kImageAnnotator PUBLIC Qt${QT_MAJOR_VERSION}::Widgets Qt${QT_MAJOR_VERSION}::Svg PRIVATE kColorPicker::kColorPicker-Qt${QT_MAJOR_VERSION})

set_target_properties(kImageAnnotator PROPERTIES OUTPUT_NAME kImageAnnotator-Qt${QT_MAJOR_VERSION})

if (UNIX AND NOT APPLE)
	# X11::X11 imported target only available with sufficiently new CMake
	if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.14.0)
		target_link_libraries(kImageAnnotator PRIVATE X11::X11)
	else()
		target_link_libraries(kImageAnnotator PRIVATE X11)
	endif()
endif ()

target_compile_definitions(kImageAnnotator PRIVATE KIMAGEANNOTATOR_LIB)
target_compile_definitions(kImageAnnotator PRIVATE KIMAGEANNOTATOR_LANG_INSTALL_DIR="${KIMAGEANNOTATOR_LANG_INSTALL_DIR}")

set_target_properties(kImageAnnotator
					  PROPERTIES
					  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib
					  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib
					  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
					  VERSION ${PROJECT_VERSION}
					  SOVERSION 0
					  )

install(TARGETS kImageAnnotator
		EXPORT kImageAnnotator-targets
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/kImageAnnotator
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/kImageAnnotator-Qt${QT_MAJOR_VERSION}
		)

configure_package_config_file(
		${CMAKE_CURRENT_SOURCE_DIR}/cmake/kImageAnnotatorConfig.cmake.in
		${CMAKE_CURRENT_BINARY_DIR}/cmake/kImageAnnotator-Qt${QT_MAJOR_VERSION}Config.cmake
		INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kImageAnnotator-Qt${QT_MAJOR_VERSION}
)

write_basic_package_version_file(
		${CMAKE_CURRENT_BINARY_DIR}/cmake/kImageAnnotator-Qt${QT_MAJOR_VERSION}Config-version.cmake
		VERSION ${PROJECT_VERSION}
		COMPATIBILITY AnyNewerVersion
)

install(FILES
		${CMAKE_CURRENT_BINARY_DIR}/cmake/kImageAnnotator-Qt${QT_MAJOR_VERSION}Config.cmake
		${CMAKE_CURRENT_BINARY_DIR}/cmake/kImageAnnotator-Qt${QT_MAJOR_VERSION}Config-version.cmake
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kImageAnnotator-Qt${QT_MAJOR_VERSION}
		)

export(
		EXPORT kImageAnnotator-targets
		FILE ${CMAKE_CURRENT_BINARY_DIR}/cmake/kImageAnnotator-Qt${QT_MAJOR_VERSION}-targets.cmake
		NAMESPACE kImageAnnotator::
)

install(
		EXPORT kImageAnnotator-targets
		FILE kImageAnnotator-targets.cmake
		NAMESPACE kImageAnnotator::
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kImageAnnotator-Qt${QT_MAJOR_VERSION}
)

# uninstall target
if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
