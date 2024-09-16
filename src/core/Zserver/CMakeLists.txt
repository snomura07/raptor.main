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
    ${OpenCV_LIBS}
)

INSTALL(
    TARGETS
    ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
