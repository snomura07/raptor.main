project(JsonTest)

include_directories(
    ${INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/utils
    ${CMAKE_SOURCE_DIR}/third_party/json/single_include
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
)

INSTALL(
    TARGETS
    ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
