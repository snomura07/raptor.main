project(HealthCheckTest)

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
