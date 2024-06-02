project(CameraTest)
find_package(OpenCV REQUIRED)

include_directories(
    ${INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/common
)

add_executable(
    ${PROJECT_NAME}
    main.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    ${OpenCV_LIBS}
)

INSTALL(
    TARGETS
    ${PROJECT_NAME}
    RUNTIME DESTINATION bin/test
)
