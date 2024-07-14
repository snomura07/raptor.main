project(Zserver)
find_package(OpenCV REQUIRED)

include_directories(
    ${INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/protobuf
    ${CMAKE_SOURCE_DIR}/common
    ${CMAKE_SOURCE_DIR}/utils
)

add_executable(
    ${PROJECT_NAME}
    module/${PROJECT_NAME}.cpp
    module/Gateway.cpp
    module/Router.cpp
    controller/GpioController.cpp
    controller/CameraController.cpp
    runner/${PROJECT_NAME}Runner.cpp
)
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${OpenCV_INCLUDE_DIRS}
)
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    pthread
    Gpio
    Camera
    ZmqWrapper
    protobuf-ZserverMsg
    ${OpenCV_LIBS}
)

#######################################
add_executable(
    Zclient
    module/${PROJECT_NAME}.cpp
    module/Gateway.cpp
    module/Router.cpp
    controller/GpioController.cpp
    controller/CameraController.cpp
    runner/ZclientRunner.cpp
)
target_include_directories(
    Zclient
    PRIVATE
    ${OpenCV_INCLUDE_DIRS}
)
target_link_libraries(
    Zclient
    PRIVATE
    pthread
    Gpio
    Camera
    ZmqWrapper
    protobuf-ZserverMsg
    ${OpenCV_LIBS}
)

INSTALL(
    TARGETS
    ${PROJECT_NAME}
    Zclient
    RUNTIME DESTINATION bin
)
