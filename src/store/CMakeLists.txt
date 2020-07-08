add_library(Store STATIC store.c)

target_link_libraries(Store PRIVATE Terminal)

target_include_directories(Store
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE Terminal
)
