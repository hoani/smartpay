add_library(Api STATIC api.c)

target_include_directories(Api
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)


