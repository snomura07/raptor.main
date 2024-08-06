project(ProtobufTest)

link_directories(
	${CMAKE_SOURCE_DIR}/../lib
)

add_executable(
    ${PROJECT_NAME}
    main.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    protobuf-example
)

# install
install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
