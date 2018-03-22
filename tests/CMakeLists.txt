enable_testing(true)

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED Test Widgets)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS CoreAddons I18n WidgetsAddons)

set(kimageannotator_SRCS ${CMAKE_SOURCE_DIR}/src/gui/KImageAnnotator.cpp
                         ${CMAKE_SOURCE_DIR}/src/gui/VisibilitySwitcher.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotations/AnnotationArea.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotations/AnnotationItemFactory.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotations/AnnotationItemModifier.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotations/AnnotationProperties.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotations/AnnotationPropertiesFactory.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotations/ControlPoints.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotations/items/AbstractAnnotationItem.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotations/items/AbstractAnnotationLine.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotations/items/AbstractAnnotationRect.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotations/items/AnnotationLine.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotations/items/AnnotationArrow.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotations/items/AnnotationRect.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotations/items/AnnotationEllipse.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotations/items/AnnotationNumber.cpp
                         ${CMAKE_SOURCE_DIR}/src/backend/Config.cpp
                         ${CMAKE_SOURCE_DIR}/src/common/formatter/ConfigNameFormatter.cpp
                         ${CMAKE_SOURCE_DIR}/src/common/helper/IconCreater.cpp
                         ${CMAKE_SOURCE_DIR}/src/widgets/ToolPicker.cpp
                         ${CMAKE_SOURCE_DIR}/src/widgets/ColorPicker.cpp
                         ${CMAKE_SOURCE_DIR}/src/widgets/SizePicker.cpp
                         ${CMAKE_SOURCE_DIR}/src/widgets/FillPicker.cpp)

set(ListOfUnitTests AnnotationAreaTest
                    ToolPickerTest
                    ColorPickerTest
                    SizePickerTest
                    FillPickerTest
                    ControlPointsTest
                    AnnotationItemModifierTest
                    ConfigNameFormatterTest
                    AnnotationItemFactoryTest
                    AnnotationPropertiesFactoryTest)

foreach(unitTest ${ListOfUnitTests})
    add_executable(${unitTest} ${unitTest}.cpp ${kimageannotator_SRCS})
    target_link_libraries(${unitTest} Qt5::Test Qt5::Widgets KF5::CoreAddons KF5::I18n KF5::WidgetsAddons)
    add_test(${unitTest} ${unitTest})
endforeach(unitTest)
