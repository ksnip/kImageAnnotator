enable_testing(true)

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED Test Widgets)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS CoreAddons I18n WidgetsAddons)

set(ListOfUnitTests
        annotations/core/AnnotationAreaTest.cpp
        annotations/core/AnnotationItemFactoryTest
        annotations/core/AnnotationPropertiesFactoryTest
        annotations/modifiers/AnnotationItemResizerTest
        annotations/modifiers/AnnotationMultiItemResizerTest
        annotations/modifiers/AnnotationItemSelectorTest
        annotations/modifiers/AnnotationItemModifierTest
        annotations/modifiers/AnnotationItemArrangerTest
        annotations/modifiers/AnnotationItemMoverTest
        annotations/modifiers/resizeHandles/LineResizeHandlesTest
        annotations/modifiers/resizeHandles/RectResizeHandlesTest
        annotations/undo/AddCommandTest
        annotations/undo/DeleteCommandTest
        annotations/undo/MoveCommandTest
        annotations/undo/ResizeCommandTest
        annotations/undo/ArrangeCommandTest.cpp
        widgets/ToolPickerTest
        widgets/ColorPickerTest
        widgets/SizePickerTest
        widgets/FillPickerTest
        common/helper/KeyHelperTest
        common/helper/MathHelperTest
        common/helper/ItemHelperTest
        common/helper/ShapeHelperTest)

add_library(kimageannotator_LIB STATIC ${kimageannotator_SRCS})
target_link_libraries(kimageannotator_LIB Qt5::Widgets KF5::CoreAddons KF5::I18n KF5::WidgetsAddons)

foreach (UnitTest ${ListOfUnitTests})
    get_filename_component(UnitTestName ${UnitTest} NAME_WE)
    add_executable(${UnitTestName} ${UnitTest})
    target_link_libraries(${UnitTestName} Qt5::Test kimageannotator_LIB)
    add_test(${UnitTestName} ${UnitTestName})
endforeach (UnitTest)
