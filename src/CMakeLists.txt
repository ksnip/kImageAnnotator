find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED Widgets)

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
        ${CMAKE_SOURCE_DIR}/src/annotations/modifiers/AbstractItemResizeHandles.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/modifiers/LineResizeHandles.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/modifiers/RectResizeHandles.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/modifiers/ResizeHandlesFactory.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/items/AbstractAnnotationItem.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/items/AbstractAnnotationLine.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/items/AbstractAnnotationRect.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/items/AnnotationLine.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/items/AnnotationArrow.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/items/AnnotationRect.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/items/AnnotationEllipse.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/items/AnnotationNumber.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/undo/AddCommand.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/undo/DeleteCommand.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/undo/MoveCommand.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/undo/ResizeCommand.cpp
        ${CMAKE_SOURCE_DIR}/src/annotations/undo/ArrangeCommand.cpp
        ${CMAKE_SOURCE_DIR}/src/backend/Config.cpp
        ${CMAKE_SOURCE_DIR}/src/common/formatter/ConfigNameFormatter.cpp
        ${CMAKE_SOURCE_DIR}/src/common/helper/IconCreater.cpp
        ${CMAKE_SOURCE_DIR}/src/common/helper/CursorHelper.cpp
        ${CMAKE_SOURCE_DIR}/src/common/helper/KeyHelper.cpp
        ${CMAKE_SOURCE_DIR}/src/common/helper/MathHelper.cpp
        ${CMAKE_SOURCE_DIR}/src/common/helper/ItemHelper.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/ToolPicker.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/ColorPicker.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/SizePicker.cpp
        ${CMAKE_SOURCE_DIR}/src/widgets/FillPicker.cpp)

set(kimageannotator_SRCS ${kimageannotator_SRCS} PARENT_SCOPE)

add_executable(kimageannotator_app main.cpp ${kimageannotator_SRCS} ${kimageannotator_ICON_RES_RCC})

target_link_libraries(kimageannotator_app Qt5::Widgets KF5::CoreAddons KF5::I18n KF5::WidgetsAddons)
