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
        ${CMAKE_SOURCE_DIR}/src/widgets/FillPicker.cpp
        )

set(kimageannotator_SRCS ${kimageannotator_SRCS} PARENT_SCOPE)

add_library(kImageAnnotator
        SHARED
        ${kimageannotator_SRCS}
        ${CMAKE_SOURCE_DIR}/include/kImageAnnotator/KImageAnnotator.h
        ${CMAKE_SOURCE_DIR}/icons/kImageAnnotator_resources.qrc
        )

add_library(kImageAnnotator::kImageAnnotator ALIAS kImageAnnotator)

target_include_directories(kImageAnnotator
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )

target_link_libraries(kImageAnnotator PUBLIC Qt5::Widgets kColorPicker)

target_compile_definitions(kImageAnnotator PRIVATE KIMAGEANNOTATOR_LIB)

set_target_properties(kImageAnnotator
        PROPERTIES
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
