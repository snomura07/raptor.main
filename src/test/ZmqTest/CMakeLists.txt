project(ZmqTest)

include_directories(
    ${LIB_DIRS}
)

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
)

INSTALL(
    TARGETS
    server
    client
    RUNTIME DESTINATION bin
)
