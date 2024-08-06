project(RaptorBase)

add_library(
    ${PROJECT_NAME}
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
    ZmqWrapper
    Logger
)

INSTALL(
    TARGETS
    ${PROJECT_NAME}
    LIBRARY DESTINATION lib
)
