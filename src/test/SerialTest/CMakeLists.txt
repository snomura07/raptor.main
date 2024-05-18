project(SerialTest)

include_directories(
    ${INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/common
    ${CMAKE_SOURCE_DIR}/utils
)

add_executable(
    ${PROJECT_NAME}
    main.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    pigpio
)

############

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
    pigpio
)


INSTALL(
    TARGETS
    ${PROJECT_NAME}
    ${PROJECT_NAME}Write
    RUNTIME DESTINATION bin/test
)
