add_library(Api STATIC api.c)

target_link_libraries(Api PRIVATE Parser Terminal Store)

target_include_directories(Api
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)


