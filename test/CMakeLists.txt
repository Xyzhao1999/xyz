

add_executable(test_log test_log.cpp)
target_link_libraries(test_log PRIVATE xyz::xyz)

add_executable(test_json test_json.cpp)
target_link_libraries(test_json PRIVATE xyz::xyz)
