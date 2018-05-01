enable_testing(true)

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED Test Widgets)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS CoreAddons I18n WidgetsAddons)

set(ListOfUnitTests AnnotationAreaTest
                    ToolPickerTest
                    ColorPickerTest
                    SizePickerTest
                    FillPickerTest
                    ResizeHandlesTest
                    AnnotationItemResizerTest
                    AnnotationMultiItemResizerTest
                    AnnotationItemSelectorTest
                    AnnotationItemModifierTest
                    AnnotationItemArrangerTest
                    AnnotationItemMoverTest
                    AnnotationItemFactoryTest
                    AnnotationPropertiesFactoryTest
                    AddCommandTest
                    DeleteCommandTest
                    ConfigNameFormatterTest
                    KeyHelperTest
                    MathHelperTest)

foreach(unitTest ${ListOfUnitTests})
    add_executable(${unitTest} ${unitTest}.cpp ${kimageannotator_SRCS})
    target_link_libraries(${unitTest} Qt5::Test Qt5::Widgets KF5::CoreAddons KF5::I18n KF5::WidgetsAddons)
    add_test(${unitTest} ${unitTest})
endforeach(unitTest)
