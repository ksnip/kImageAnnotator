enable_testing(true)

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED Test Widgets)

# Annotation Area Test
add_executable(AnnotationAreaTest AnnotationAreaTest.cpp ${CMAKE_SOURCE_DIR}/src/AnnotationArea.cpp)
target_link_libraries(AnnotationAreaTest Qt5::Test Qt5::Widgets)
add_test(CoreTest AnnotationAreaTest)
