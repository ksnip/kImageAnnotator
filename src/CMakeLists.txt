find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED Widgets)

set(kimageannotator_SRCS main.cpp
                         KImageAnnotator.cpp
                         AnnotationArea.cpp
                         annotationItems/AnnotationItemFactory.cpp
                         annotationItems/AnnotationItemProperties.cpp
                         annotationItems/AnnotationItemModifier.cpp
                         annotationItems/AbstractAnnotationItem.cpp
                         annotationItems/AbstractAnnotationLine.cpp
                         annotationItems/AbstractAnnotationItem.cpp
                         annotationItems/AnnotationLineItem.cpp
                         widgets/ToolPicker.cpp)

add_executable(kimageannotator_app ${kimageannotator_SRCS} ${kimageannotator_ICON_RES_RCC})

target_link_libraries(kimageannotator_app Qt5::Widgets)
