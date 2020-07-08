add_library(Parser STATIC parser.c)

target_link_libraries(Parser PRIVATE Terminal)

target_include_directories(Parser
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE Terminal
)
