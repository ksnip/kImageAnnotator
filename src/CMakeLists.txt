find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED Widgets)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS CoreAddons I18n WidgetsAddons)

set(kimageannotator_SRCS main.cpp
                         gui/KImageAnnotator.cpp
                         gui/VisibilitySwitcher.cpp
                         annotations/AnnotationArea.cpp
                         annotations/AnnotationItemFactory.cpp
                         annotations/AnnotationItemResizer.cpp
                         annotations/AnnotationItemSelector.cpp
                         annotations/AnnotationProperties.cpp
                         annotations/AnnotationPropertiesFactory.cpp
                         annotations/ControlPoints.cpp
                         annotations/items/AbstractAnnotationItem.cpp
                         annotations/items/AbstractAnnotationLine.cpp
                         annotations/items/AbstractAnnotationRect.cpp
                         annotations/items/AnnotationLine.cpp
                         annotations/items/AnnotationArrow.cpp
                         annotations/items/AnnotationRect.cpp
                         annotations/items/AnnotationEllipse.cpp
                         annotations/items/AnnotationNumber.cpp
                         backend/Config.cpp
                         common/formatter/ConfigNameFormatter.cpp
                         common/helper/IconCreater.cpp
                         widgets/ToolPicker.cpp
                         widgets/ColorPicker.cpp
                         widgets/SizePicker.cpp
                         widgets/FillPicker.cpp)

add_executable(kimageannotator_app ${kimageannotator_SRCS} ${kimageannotator_ICON_RES_RCC})

target_link_libraries(kimageannotator_app Qt5::Widgets KF5::CoreAddons KF5::I18n KF5::WidgetsAddons)
