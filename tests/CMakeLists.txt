enable_testing(true)

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED Test Widgets)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS CoreAddons I18n WidgetsAddons)

set(ListOfUnitTests
        annotations/AnnotationAreaTest.cpp
        annotations/modifiers/ResizeHandlesTest
        annotations/modifiers/AnnotationItemResizerTest
        annotations/modifiers/AnnotationMultiItemResizerTest
        annotations/modifiers/AnnotationItemSelectorTest
        annotations/modifiers/AnnotationItemModifierTest
        annotations/modifiers/AnnotationItemArrangerTest
        annotations/modifiers/AnnotationItemMoverTest
        annotations/AnnotationItemFactoryTest
        annotations/AnnotationPropertiesFactoryTest
        annotations/undo/AddCommandTest
        annotations/undo/DeleteCommandTest
        annotations/undo/MoveCommandTest
        widgets/ToolPickerTest
        widgets/ColorPickerTest
        widgets/SizePickerTest
        widgets/FillPickerTest
        common/formatter/ConfigNameFormatterTest
        common/helper/KeyHelperTest
        common/helper/MathHelperTest)

foreach (UnitTest ${ListOfUnitTests})
    get_filename_component(UnitTestName ${UnitTest} NAME_WE)
    add_executable(${UnitTestName} ${UnitTest} ${kimageannotator_SRCS})
    target_link_libraries(${UnitTestName} Qt5::Test Qt5::Widgets KF5::CoreAddons KF5::I18n KF5::WidgetsAddons)
    add_test(${UnitTestName} ${UnitTestName})
endforeach (UnitTest)
