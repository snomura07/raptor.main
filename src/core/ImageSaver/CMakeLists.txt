project(ImageSaver)

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
    ZmqWrapper
    ${OpenCV_LIBS}
    Image
    protobuf-CamMsg
    Logger
    MasterConfig
    InfoChat
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
