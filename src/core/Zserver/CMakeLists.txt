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
    ZmqWrapper
)

INSTALL(
    TARGETS
    ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
