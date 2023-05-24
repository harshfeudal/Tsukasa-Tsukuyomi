cmake_minimum_required(VERSION 3.15)
project(Tsukasa-Tsukuyomi VERSION 1.0.0.0 DESCRIPTION "An anime Discord modration bot")

aux_source_directory(src mainsrc)
aux_source_directory(src/cmd_lists/cmd_common common)
aux_source_directory(src/cmd_lists/cmd_moderation moderation)
aux_source_directory(src/cmd_engine cmd_engine)

add_executable(${PROJECT_NAME} ${mainsrc} ${common} ${moderation} ${cmd_engine} "Tsukasa Tsukuyomi.rc" )

target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/dpp.lib)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/lib/opencv_world470d.lib)
target_include_directories(${PROJECT_NAME} PRIVATE "handler" "include" "lib")

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)