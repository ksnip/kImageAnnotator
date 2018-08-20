find_package(Qt5 ${QT_MIN_VERSION} REQUIRED Widgets)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS CoreAddons I18n WidgetsAddons)

set(kimageannotator_SRCS
        ${CMAKE_SOURCE_DIR}/src/gui/KImageAnnotator.cpp
        ${CMAKE_SOURCE_DIR}/src/gui/VisibilitySwitcher.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/core/AnnotationArea.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/core/AnnotationItemFactory.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/core/AnnotationProperties.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/core/AnnotationPropertiesFactory.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/modifiers/AnnotationItemModifier.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/modifiers/AnnotationItemResizer.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/modifiers/AnnotationMultiItemResizer.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/modifiers/AnnotationItemSelector.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/modifiers/AnnotationItemMover.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/modifiers/AnnotationItemArranger.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/modifiers/resizeHandles/AbstractItemResizeHandles.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/modifiers/resizeHandles/AbstractRectResizeHandles.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/modifiers/resizeHandles/LineResizeHandles.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/modifiers/resizeHandles/RectResizeHandles.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/modifiers/resizeHandles/PathResizeHandles.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/modifiers/resizeHandles/ResizeHandle.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/modifiers/resizeHandles/ResizeHandlesFactory.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/items/AbstractAnnotationItem.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/items/AbstractAnnotationLine.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/items/AbstractAnnotationRect.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/items/AbstractAnnotationPath.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/items/AnnotationLine.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/items/AnnotationArrow.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/items/AnnotationRect.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/items/AnnotationEllipse.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/items/AnnotationNumber.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/items/AnnotationPen.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/undo/AddCommand.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/undo/DeleteCommand.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/undo/MoveCommand.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/undo/ResizeCommand.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/undo/ArrangeCommand.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/misc/ShadowEffect.cpp
        ${CMAKE_SOURCE_DIR}/src/backend/Config.cpp
        ${CMAKE_SOURCE_DIR}/src/common/helper/IconCreater.cpp
        ${CMAKE_SOURCE_DIR}/src/common/helper/CursorHelper.cpp
        ${CMAKE_SOURCE_DIR}/src/common/helper/KeyHelper.cpp
        ${CMAKE_SOURCE_DIR}/src/common/helper/MathHelper.cpp
        ${CMAKE_SOURCE_DIR}/src/common/helper/ItemHelper.cpp
        ${CMAKE_SOURCE_DIR}/src/common/helper/ShapeHelper.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/ToolPicker.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/ColorPicker.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/SizePicker.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/FillPicker.cpp)

#set(kimageannotator_SRCS ${kimageannotator_SRCS} PARENT_SCOPE)
#
#set(kimageannotator_ICON_QRC ${CMAKE_SOURCE_DIR}/icons/resources.qrc)
#
#add_executable(kimageannotator_app main.cpp ${kimageannotator_SRCS} ${kimageannotator_ICON_QRC} ${CMAKE_SOURCE_DIR}/include/kImageAnnotator/KImageAnnotator.h)
#
#target_include_directories(kimageannotator_app PRIVATE ${CMAKE_SOURCE_DIR}/include)
#
#target_link_libraries(kimageannotator_app Qt5::Widgets KF5::CoreAddons KF5::I18n KF5::WidgetsAddons)


add_library(kImageAnnotator ${kimageannotator_SRCS} ${CMAKE_SOURCE_DIR}/include/kImageAnnotator/KImageAnnotator.h)

add_library(kImageAnnotator::kImageAnnotator ALIAS kImageAnnotator)

option(BUILD_SHARED_LIBS "Build shared library" ON)
include(GenerateExportHeader)

generate_export_header(kImageAnnotator
        EXPORT_MACRO_NAME KIMAGEANNOTATOR_API
        EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/include/KImageAnnotator.h
        )

target_include_directories(kImageAnnotator
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

set_target_properties(kImageAnnotator PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        )

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED Widgets)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS CoreAddons I18n WidgetsAddons)

target_link_libraries(kImageAnnotator Qt5::Widgets KF5::CoreAddons KF5::I18n KF5::WidgetsAddons)

include(GNUInstallDirs)

install(TARGETS kImageAnnotator
        EXPORT kImageAnnotator-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${LIBLEGACY_INCLUDE_DIRS}
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/kImageAnnotator
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT kImageAnnotator-targets
        FILE kImageAnnotator-targets.cmake
        NAMESPACE kImageAnnotator::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/kImageAnnotator
)


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

export(EXPORT kImageAnnotator-targets
        FILE ${CMAKE_BINARY_DIR}/cmake/kImageAnnotator-targets.cmake
        NAMESPACE kImageAnnotator::
)