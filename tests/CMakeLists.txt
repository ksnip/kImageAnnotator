enable_testing(true)

set(ListOfUnitTests
        annotations/core/AnnotationAreaTest.cpp
        annotations/core/AnnotationItemFactoryTest.cpp
        annotations/core/AnnotationPropertiesFactoryTest.cpp
        annotations/modifiers/AnnotationItemResizerTest.cpp
        annotations/modifiers/AnnotationMultiItemResizerTest.cpp
        annotations/modifiers/AnnotationItemSelectorTest.cpp
        annotations/modifiers/AnnotationItemModifierTest.cpp
        annotations/modifiers/AnnotationItemArrangerTest.cpp
        annotations/modifiers/AnnotationItemMoverTest.cpp
        annotations/modifiers/resizeHandles/LineResizeHandlesTest.cpp
        annotations/modifiers/resizeHandles/RectResizeHandlesTest.cpp
        annotations/undo/AddCommandTest.cpp
        annotations/undo/DeleteCommandTest.cpp
        annotations/undo/MoveCommandTest.cpp
        annotations/undo/ResizeCommandTest.cpp
        annotations/undo/ArrangeCommandTest.cpp
        widgets/ToolPickerTest.cpp
        widgets/ColorPickerTest.cpp
        widgets/SizePickerTest.cpp
        widgets/FillPickerTest.cpp
        common/helper/KeyHelperTest.cpp
        common/helper/MathHelperTest.cpp
        common/helper/ItemHelperTest.cpp
        common/helper/ShapeHelperTest.cpp)

add_library(kImageAnnotatorStatic STATIC ${kimageannotator_SRCS})
target_link_libraries(kImageAnnotatorStatic Qt5::Widgets KF5::CoreAddons KF5::I18n KF5::WidgetsAddons)

foreach (UnitTest ${ListOfUnitTests})
    get_filename_component(UnitTestName ${UnitTest} NAME_WE)
    add_executable(${UnitTestName} ${UnitTest})
    target_link_libraries(${UnitTestName} kImageAnnotatorStatic Qt5::Test)
    add_test(${UnitTestName} ${UnitTestName})
endforeach (UnitTest)
