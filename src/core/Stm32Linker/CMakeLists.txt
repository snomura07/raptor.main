project(Stm32Linker)

add_executable(
    ${PROJECT_NAME}
    config/AppConfig.cpp
    module/${PROJECT_NAME}.cpp
    module/ReadData.cpp
    module/SendData.cpp
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
    RaptorBase
    Gpio
    MasterConfig
    InfoChat
)


INSTALL(
    TARGETS
    ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

INSTALL(
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/config/${PROJECT_NAME}.json
    DESTINATION /usr/local/config
)

execute_process(
    COMMAND sh -c "echo /usr/local/config/${PROJECT_NAME}.json >> ${CONF_SUMMARY}"
)
