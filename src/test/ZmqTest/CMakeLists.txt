project(ZmqTest)

add_executable(
    server
    server.cpp
)

target_include_directories(
    server
    PRIVATE
)

target_link_libraries(
    server
    PRIVATE
    pthread
    zmq
    protobuf-example
)

##################

# ソースファイルを追加
add_executable(
    client
    client.cpp
)

target_include_directories(
    client
    PRIVATE
)

# 必要に応じてライブラリやリンクするものを追加
target_link_libraries(
    client
    PRIVATE
    pthread
    zmq
    protobuf-example
)

INSTALL(
    TARGETS
    server
    client
    RUNTIME DESTINATION bin
)
