project(ChatServer)

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
    RaptorBase
    MasterConfig
    ZmqWrapper
    ApiClient
    Logger
    protobuf-ChatServerMsg
    ${OPENSSL_LIBS}
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

execute_process(
    COMMAND sh -c "echo /opt/raptor/config/${PROJECT_NAME}.json >> ${CONF_SUMMARY}"
)
