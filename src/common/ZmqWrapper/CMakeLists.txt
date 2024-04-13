project(ZmqWrapper)

include_directories(
    ${INCLUDE_DIRS}
)

add_library(
    ${PROJECT_NAME}
    # SHARED
    STATIC
    ${PROJECT_NAME}.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    pthread
    zmq
)

INSTALL(
    TARGETS
    ${PROJECT_NAME}
    LIBRARY DESTINATION lib
)
