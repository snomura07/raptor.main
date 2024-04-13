project(ProxyTest)

include_directories(
    ${INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/protobuf
)

add_executable(
    ${PROJECT_NAME}Pub
    pub.cpp
)

target_include_directories(
    ${PROJECT_NAME}Pub
    PRIVATE
)

target_link_libraries(
    ${PROJECT_NAME}Pub
    PRIVATE
    pthread
    zmq
    protobuf-example
)

##################

# ソースファイルを追加
add_executable(
    ${PROJECT_NAME}Sub
    sub.cpp
)

target_include_directories(
    ${PROJECT_NAME}Sub
    PRIVATE
)

# 必要に応じてライブラリやリンクするものを追加
target_link_libraries(
    ${PROJECT_NAME}Sub
    PRIVATE
    pthread
    zmq
    protobuf-example
)

INSTALL(
    TARGETS
    ${PROJECT_NAME}Sub
    ${PROJECT_NAME}Pub
    RUNTIME DESTINATION bin
)
