find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED Widgets)

set(kimageannotator_SRCS main.cpp
                         KImageAnnotator.cpp
                         AnnotationArea.cpp)

add_executable(kimageannotator_app ${kimageannotator_SRCS})

target_link_libraries(kimageannotator_app Qt5::Widgets)
