project(HealthCheckMultiTest)

include_directories(
    ${INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/protobuf
    ${CMAKE_SOURCE_DIR}/common
    ${CMAKE_SOURCE_DIR}/third_party/json/single_include
)

add_executable(
    ${PROJECT_NAME}
    client.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    pthread
    ZmqWrapper
)
