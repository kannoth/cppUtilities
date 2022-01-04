cmake_minimum_required(VERSION 3.0...3.12)

project(tcp_server_test)

enable_testing()

add_executable(${PROJECT_NAME})

target_sources( ${PROJECT_NAME}
    PRIVATE
    tcp_server_test.cc
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} cru::net cru::utils gtest tests::main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})