project(StandbyWaitTest)

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
    ZmqWrapper
)

############

add_executable(
    ${PROJECT_NAME}Switch
    switch.cpp
)

target_include_directories(
    ${PROJECT_NAME}Switch
    PRIVATE
)

target_link_libraries(
    ${PROJECT_NAME}Switch
    PRIVATE
    pthread
    ZmqWrapper
)


INSTALL(
    TARGETS
    ${PROJECT_NAME}
    ${PROJECT_NAME}Switch
    RUNTIME DESTINATION bin/test
)
