add_executable(kImageAnnotator-example ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

target_link_libraries(kImageAnnotator-example PRIVATE kImageAnnotator::kImageAnnotator)