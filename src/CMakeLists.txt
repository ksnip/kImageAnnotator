set(kimageannotator_SRCS
        gui/KImageAnnotator.cpp
        gui/VisibilitySwitcher.cpp
        annotations/core/AnnotationArea.cpp
        annotations/core/AnnotationItemFactory.cpp
        annotations/core/AnnotationProperties.cpp
        annotations/core/AnnotationPropertiesFactory.cpp
        annotations/modifiers/AnnotationItemModifier.cpp
        annotations/modifiers/AnnotationItemResizer.cpp
        annotations/modifiers/AnnotationMultiItemResizer.cpp
        annotations/modifiers/AnnotationItemSelector.cpp
        annotations/modifiers/AnnotationItemMover.cpp
        annotations/modifiers/AnnotationItemArranger.cpp
        annotations/modifiers/resizeHandles/AbstractItemResizeHandles.cpp
        annotations/modifiers/resizeHandles/AbstractRectResizeHandles.cpp
        annotations/modifiers/resizeHandles/LineResizeHandles.cpp
        annotations/modifiers/resizeHandles/RectResizeHandles.cpp
        annotations/modifiers/resizeHandles/PathResizeHandles.cpp
        annotations/modifiers/resizeHandles/ResizeHandle.cpp
        annotations/modifiers/resizeHandles/ResizeHandlesFactory.cpp
        annotations/items/AbstractAnnotationItem.cpp
        annotations/items/AbstractAnnotationLine.cpp
        annotations/items/AbstractAnnotationRect.cpp
        annotations/items/AbstractAnnotationPath.cpp
        annotations/items/AnnotationLine.cpp
        annotations/items/AnnotationArrow.cpp
        annotations/items/AnnotationRect.cpp
        annotations/items/AnnotationEllipse.cpp
        annotations/items/AnnotationNumber.cpp
        annotations/items/AnnotationPen.cpp
        annotations/undo/AddCommand.cpp
        annotations/undo/DeleteCommand.cpp
        annotations/undo/MoveCommand.cpp
        annotations/undo/ResizeCommand.cpp
        annotations/undo/ArrangeCommand.cpp
        annotations/misc/ShadowEffect.cpp
        backend/Config.cpp
        common/helper/IconCreater.cpp
        common/helper/CursorHelper.cpp
        common/helper/KeyHelper.cpp
        common/helper/MathHelper.cpp
        common/helper/ItemHelper.cpp
        common/helper/ShapeHelper.cpp
        widgets/ToolPicker.cpp
        widgets/ColorPicker.cpp
        widgets/SizePicker.cpp
        widgets/FillPicker.cpp)

set(kimageannotator_ICON_QRC ${CMAKE_SOURCE_DIR}/icons/resources.qrc)

add_library(kImageAnnotator
        ${kimageannotator_SRCS}
        ${CMAKE_SOURCE_DIR}/include/kImageAnnotator/KImageAnnotator.h
        ${kimageannotator_ICON_QRC}
        )

add_library(kImageAnnotator::kImageAnnotator ALIAS kImageAnnotator)

target_include_directories(kImageAnnotator
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )

target_link_libraries(kImageAnnotator PUBLIC
        Qt5::Widgets KF5::CoreAddons KF5::I18n KF5::WidgetsAddons
        )
target_compile_definitions(kImageAnnotator PRIVATE KIMAGEANNOTATOR_LIB)

set_target_properties(kImageAnnotator PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        )

install(TARGETS kImageAnnotator
        EXPORT kImageAnnotator-targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        )

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/kImageAnnotator
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )
