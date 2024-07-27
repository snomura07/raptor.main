project(CpuTemperatureMonitor)

include_directories(
    ${INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/protobuf
    ${CMAKE_SOURCE_DIR}/common
    ${CMAKE_SOURCE_DIR}/utils
    ${CMAKE_SOURCE_DIR}/third_party/json/single_include
)

add_executable(
    ${PROJECT_NAME}
    config/AppConfig.cpp
    module/${PROJECT_NAME}.cpp
    runner/${PROJECT_NAME}Runner.cpp
)
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
)
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    pthread
    Env
    RaptorBase
    ZmqWrapper
    MasterConfig
    protobuf-CpuTemperatureMsg
)


INSTALL(
    TARGETS
    ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

INSTALL(
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/config/${PROJECT_NAME}.json
    DESTINATION /usr/local/config
)

execute_process(
    COMMAND sh -c "echo /usr/local/config/${PROJECT_NAME}.json >> ${CONF_SUMMARY}"
)

##################
## monitor
add_executable(
    ${PROJECT_NAME}Monitor
    config/AppConfig.cpp
    monitor/Monitor.cpp
)
target_include_directories(
    ${PROJECT_NAME}Monitor
    PRIVATE
)
target_link_libraries(
    ${PROJECT_NAME}Monitor
    PRIVATE
    pthread
    RaptorBase
    ZmqWrapper
    MasterConfig
    protobuf-CpuTemperatureMsg
)

INSTALL(
    TARGETS
    ${PROJECT_NAME}Monitor
    RUNTIME DESTINATION bin/monitor
)
