project(ZmqWrapperTest)

add_executable(
    ${PROJECT_NAME}Server
    server.cpp
)

target_include_directories(
    ${PROJECT_NAME}Server
    PRIVATE
)

target_link_libraries(
    ${PROJECT_NAME}Server
    PRIVATE
    pthread
    ZmqWrapper
    protobuf-example
)

##################

# ソースファイルを追加
add_executable(
    ${PROJECT_NAME}Client
    client.cpp
)

target_include_directories(
    ${PROJECT_NAME}Client
    PRIVATE
    pthread
)

# 必要に応じてライブラリやリンクするものを追加
target_link_libraries(
    ${PROJECT_NAME}Client
    PRIVATE
    pthread
    ZmqWrapper
    protobuf-example
)

INSTALL(
    TARGETS
    ${PROJECT_NAME}Server
    ${PROJECT_NAME}Client
    RUNTIME DESTINATION bin
)
