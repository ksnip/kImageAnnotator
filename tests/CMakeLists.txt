enable_testing(true)

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED Test Widgets)

set(kimageannotator_SRCS ${CMAKE_SOURCE_DIR}/src/KImageAnnotator.cpp
                         ${CMAKE_SOURCE_DIR}/src/AnnotationArea.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotationItems/AnnotationItemFactory.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotationItems/AnnotationItemProperties.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotationItems/AnnotationItemModifier.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotationItems/ControlPoints.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotationItems/AbstractAnnotationItem.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotationItems/AbstractAnnotationLine.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotationItems/AbstractAnnotationRect.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotationItems/AnnotationLine.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotationItems/AnnotationArrow.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotationItems/AnnotationRect.cpp
                         ${CMAKE_SOURCE_DIR}/src/annotationItems/AnnotationEllipse.cpp
                         ${CMAKE_SOURCE_DIR}/src/widgets/ToolPicker.cpp
                         ${CMAKE_SOURCE_DIR}/src/widgets/ColorPicker.cpp
                         ${CMAKE_SOURCE_DIR}/src/widgets/SizePicker.cpp)

set(ListOfUnitTests AnnotationAreaTest
                    ToolPickerTest
                    ColorPickerTest
                    ControlPointsTest)

foreach(unitTest ${ListOfUnitTests})
    add_executable(${unitTest} ${unitTest}.cpp ${kimageannotator_SRCS})
    target_link_libraries(${unitTest} Qt5::Test Qt5::Widgets)
    add_test(${unitTest} ${unitTest})
endforeach(unitTest)
