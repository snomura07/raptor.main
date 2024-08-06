project(SerialGpioTest)

add_executable(
    ${PROJECT_NAME}Write
    write.cpp
)

target_include_directories(
    ${PROJECT_NAME}Write
    PRIVATE
)

target_link_libraries(
    ${PROJECT_NAME}Write
    PRIVATE
    Gpio
)

#############################
add_executable(
    ${PROJECT_NAME}Read
    read.cpp
)

target_include_directories(
    ${PROJECT_NAME}Read
    PRIVATE
)

target_link_libraries(
    ${PROJECT_NAME}Read
    PRIVATE
    Gpio
)

#############################
add_executable(
    ${PROJECT_NAME}ReadWrite
    readwrite.cpp
)

target_include_directories(
    ${PROJECT_NAME}ReadWrite
    PRIVATE
)

target_link_libraries(
    ${PROJECT_NAME}ReadWrite
    PRIVATE
    Gpio
)

INSTALL(
    TARGETS
    ${PROJECT_NAME}Write
    ${PROJECT_NAME}Read
    ${PROJECT_NAME}ReadWrite
    RUNTIME DESTINATION bin/test
)
