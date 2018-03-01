find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED Widgets)

set(kimageannotator_SRCS main.cpp
                         KImageAnnotator.cpp
                         AnnotationArea.cpp
                         annotationItems/AnnotationItemFactory.cpp
                         annotationItems/AnnotationItemProperties.cpp
                         annotationItems/AnnotationItemModifier.cpp
                         annotationItems/ControlPoints.cpp
                         annotationItems/AbstractAnnotationItem.cpp
                         annotationItems/AbstractAnnotationLine.cpp
                         annotationItems/AbstractAnnotationRect.cpp
                         annotationItems/AnnotationLine.cpp
                         annotationItems/AnnotationArrow.cpp
                         annotationItems/AnnotationRect.cpp
                         annotationItems/AnnotationEllipse.cpp
                         widgets/ToolPicker.cpp
                         widgets/ColorPicker.cpp)

add_executable(kimageannotator_app ${kimageannotator_SRCS} ${kimageannotator_ICON_RES_RCC})

target_link_libraries(kimageannotator_app Qt5::Widgets)
