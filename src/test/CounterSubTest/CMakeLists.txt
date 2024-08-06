project(CounterSubTest)

add_executable(
    ${PROJECT_NAME}
    main.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    pthread
    zmq
    ZmqWrapper
    protobuf-CounterMsg
)

INSTALL(
    TARGETS
    ${PROJECT_NAME}
    RUNTIME DESTINATION bin/test
)
