add_library(Terminal STATIC terminal.c)

target_include_directories(Terminal
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
