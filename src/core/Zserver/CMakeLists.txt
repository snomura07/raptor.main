project(Zserver)

add_executable(
    ${PROJECT_NAME}
    module/${PROJECT_NAME}.cpp
    module/Gateway.cpp
    module/Router.cpp
    module/Zdata.cpp
    controller/GpioController.cpp
    controller/CameraController.cpp
    controller/HelloController.cpp
    controller/ConfigController.cpp
    runner/${PROJECT_NAME}Runner.cpp
    config/AppConfig.cpp
)
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
)
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    pthread
    Gpio
    Camera
    ZmqWrapper
    MasterConfig
    InfoChat
    RaptorBase
    ${OpenCV_LIBS}
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
