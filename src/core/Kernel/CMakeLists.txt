project(Kernel)

add_executable(
    ${PROJECT_NAME}
    config/AppConfig.cpp
    module/${PROJECT_NAME}.cpp
    module/ConfSummary.cpp
    module/ProcessInfo.cpp
    module/Launcher.cpp
    module/ProcessMonitor.cpp
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
    RaptorBase
    MasterConfig
    ZmqWrapper
    InfoChat
    Env
    protobuf-ProcessMonitorMsg
)

INSTALL(
    TARGETS
    ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

INSTALL(
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/config/${PROJECT_NAME}.json
    DESTINATION /opt/raptor/config
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
    protobuf-ProcessMonitorMsg
)

INSTALL(
    TARGETS
    ${PROJECT_NAME}Monitor
    RUNTIME DESTINATION bin/monitor
)
