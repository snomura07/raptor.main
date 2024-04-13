project(ProxyTest)

include_directories(
    ${INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/protobuf
    ${CMAKE_SOURCE_DIR}/common
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
    ZmqWrapper
    protobuf-example
)

##################

add_executable(
    ${PROJECT_NAME}Sub
    sub.cpp
)

target_include_directories(
    ${PROJECT_NAME}Sub
    PRIVATE
)

target_link_libraries(
    ${PROJECT_NAME}Sub
    PRIVATE
    pthread
    zmq
    ZmqWrapper
    protobuf-example
)

##################
add_executable(
    ${PROJECT_NAME}Sub2
    sub2.cpp
)

target_include_directories(
    ${PROJECT_NAME}Sub2
    PRIVATE
)

target_link_libraries(
    ${PROJECT_NAME}Sub2
    PRIVATE
    pthread
    zmq
    ZmqWrapper
    protobuf-example
)

INSTALL(
    TARGETS
    ${PROJECT_NAME}Sub
    ${PROJECT_NAME}Sub2
    ${PROJECT_NAME}Pub
    RUNTIME DESTINATION bin
)
