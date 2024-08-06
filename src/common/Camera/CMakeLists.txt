project(Camera)
find_package(OpenCV REQUIRED)

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
    Env
    ${OpenCV_LIBS}
)

INSTALL(
    TARGETS
    ${PROJECT_NAME}
    LIBRARY DESTINATION lib
)
