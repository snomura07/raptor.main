project(CameraLibTest)

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
    Camera
    ${OpenCV_LIBS}
)

INSTALL(
    TARGETS
    ${PROJECT_NAME}
    RUNTIME DESTINATION bin/test
)
