project(Zserver)

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
    ZmqWrapper
    protobuf-ZserverMsg
)

#######################################
add_executable(
    Zclient
    module/${PROJECT_NAME}.cpp
    module/Gateway.cpp
    module/Router.cpp
    controller/GpioController.cpp
    runner/ZclientRunner.cpp
)
target_include_directories(
    Zclient
    PRIVATE
)
target_link_libraries(
    Zclient
    PRIVATE
    pthread
    Gpio
    ZmqWrapper
    protobuf-ZserverMsg
)

INSTALL(
    TARGETS
    ${PROJECT_NAME}
    Zclient
    RUNTIME DESTINATION bin
)
